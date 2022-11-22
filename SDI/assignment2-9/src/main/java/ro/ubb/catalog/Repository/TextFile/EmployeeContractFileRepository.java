


package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.EmployeeContract;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;


public class EmployeeContractFileRepository extends FileRepository<Long,EmployeeContract>{

    public EmployeeContractFileRepository(Validator<EmployeeContract> validator, String fileName) {
        super(validator, fileName);
        loadData();
    }

    @Override
    protected void loadData() {
        Path path = Paths.get(this.getFileName());

        try {
            Files.lines(path).forEach(line -> {
                System.out.println("*");
                List<String> items = Arrays.asList(line.split(","));

                Long id = Long.valueOf(items.get(0));
                LocalDate date = LocalDate.parse(items.get(1));
                int eid = Integer.parseInt(items.get(2));
                int cid = Integer.parseInt(items.get(3));
                
                EmployeeContract ec = new EmployeeContract(date, eid, cid);
                ec.setId(id);

                try {
                    super.save(ec);
                } catch (ValidatorException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }


    @Override
    public Optional<EmployeeContract> delete(Long id) {
        Optional<EmployeeContract> opt = super.delete(id);
        saveToFile();
        return opt;
    }

    @Override
    public Optional<EmployeeContract> update(EmployeeContract v) {
        Optional<EmployeeContract> opt = super.update(v);
        saveToFile();
        return opt;
    }


    @Override
    protected void saveToFile() {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.TRUNCATE_EXISTING)) {
            this.getEntities().entrySet()
                    .forEach(e -> {
                        try {
                            bufferedWriter.write(e.getKey()
                                    + "," + e.getValue().getDate()
                                    + "," + e.getValue().getEmployeeID()
                                    + "," + e.getValue().getClinicID());
                            bufferedWriter.newLine();
                        } catch (IOException ex) {
                            ex.printStackTrace();
                        }
                    });
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<EmployeeContract> save(EmployeeContract entity) throws ValidatorException {
        Optional<EmployeeContract> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    @Override
    protected void saveToFile(EmployeeContract entity) {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getDate() + ","  + entity.getEmployeeID() + ","  + entity.getClinicID());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}