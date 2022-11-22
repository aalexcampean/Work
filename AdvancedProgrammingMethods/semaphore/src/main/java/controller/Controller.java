package controller;

import model.PrgState;
import model.adtContainers.IList;
import model.adtContainers.MyList;
import model.types.RefType;
import model.values.IValue;
import model.values.RefValue;
import repository.IRepo;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private IRepo repo;
    private ExecutorService executor;

    public Controller(IRepo r){
        this.repo = r;
    }

    public IRepo getRepo() {
        return repo;
    }

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList
                .stream()
                .filter(p -> p.isNotCompleted())
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrg(List<PrgState> prgList) throws Exception {
        List<Callable<PrgState>> callList = prgList
                .stream()
                .map((PrgState p) -> (Callable<PrgState>)(() -> {return p.oneStep();}))
                .collect(Collectors.toList());

        List<PrgState> newPrgList = executor.invokeAll(callList)
                .stream()
                .map(future -> {try {return future.get();} catch (Exception e) {return null;}})
                .filter(p -> p != null)
                .collect(Collectors.toList());

        prgList.addAll(newPrgList);
        for (PrgState prg : prgList) {
            this.repo.logPrgStateExec(prg);
        }
        //prgList.forEach(p -> {try {this.repo.logPrgStateExec(p);} catch (Exception e) {System.out.print(e.getMessage());}});

        IList<PrgState> copyPrgList = new MyList<PrgState>(prgList);
        this.repo.setPrgList(copyPrgList);
    }

    public void oneStepGui() throws Exception{
        executor = Executors.newFixedThreadPool(2);
        IList<PrgState> list = repo.getPrgList();
        List<PrgState> prgList = list.getAll();

        if (prgList.size() > 0) {
            for (PrgState prg : prgList) {
                prg.getHeap().setContent(garbageCollector(
                        getTblAddrs(prg.getSymTable().values()),
                        prg.getHeap().getContent()));
            }
            oneStepForAllPrg(prgList);

            executor.shutdownNow();
            IList<PrgState> copyList = new MyList<>(prgList);
            this.repo.setPrgList(copyList);
        }
        else {
            executor.shutdownNow();
            IList<PrgState> copyPrgList = new MyList<>(prgList);
            repo.setPrgList(copyPrgList);
            throw new Exception("Program finished successfully");
        }
    }

    public void allSteps() throws Exception {
        this.executor = Executors.newFixedThreadPool(2);

        List<PrgState> prgList = removeCompletedPrg(this.repo.getPrgList().getAll());

        while (prgList.size() > 0) {

//            prgList.forEach(p -> p.getHeap().setContent(garbageCollector(getSymTAddresses(p.getSymTable().values()), p.getHeap().getContent())));

            oneStepForAllPrg(prgList);
            prgList = removeCompletedPrg(this.repo.getPrgList().getAll());
        }

        this.executor.shutdownNow();

        IList<PrgState> copyPrgList = new MyList<PrgState>(prgList);
        this.repo.setPrgList(copyPrgList);
    }

    // Garbage Collector
    public List<Integer> getTblAddrs(Collection<IValue> tableAddrs) {
        return tableAddrs.stream()
                .filter(v -> v.getType() instanceof RefType)
                .map(v-> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    public Map<Integer, IValue> garbageCollector(List<Integer> symbTblAddrs, Map<Integer, IValue> heap) {
        List<Integer> heapAddrs = getTblAddrs(heap.values());
        return heap.entrySet()
                .stream()
                .filter(v -> symbTblAddrs.contains(v.getKey()) || heapAddrs.contains(v.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public String toString() {
        try {
            return this.repo.getPrgList().get(0).getExeStack().toString();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return "";
        }
    }
}
