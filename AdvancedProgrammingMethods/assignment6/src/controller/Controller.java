package controller;

import model.PrgState;
import model.adtContainers.IList;
import model.adtContainers.MyList;
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

    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList
                .stream()
                .filter(p -> p.isNotCompleted())
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrg(List<PrgState> prgList) throws Exception {
        prgList.forEach(p -> { try {this.repo.logPrgStateExec(p);} catch (Exception e) {e.printStackTrace();}});

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
        prgList.forEach(p -> {try {this.repo.logPrgStateExec(p);} catch (Exception e) {System.out.print(e.getMessage());}});

        IList<PrgState> copyPrgList = new MyList<PrgState>(prgList);
        this.repo.setPrgList(copyPrgList);
    }

    public void allSteps() throws Exception{
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

    public Set<Integer> getSymTAddresses(Collection<IValue> getAddressesFromTable) {
        return getAddressesFromTable.stream()
                .filter(v -> v.getType() instanceof RefValue)
                .map(v-> ((RefValue) v).getAddress())
                .collect(Collectors.toSet());
    }

    public Map<Integer, IValue> garbageCollector(Set<Integer> symbolTableAddresses, Map<Integer, IValue> heap) {
        Set<Integer> heapAddresses = getSymTAddresses(heap.values());
        return heap.entrySet()
                .stream()
                .filter(v -> symbolTableAddresses.contains(v.getKey()) || heapAddresses.contains(v.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }
}
