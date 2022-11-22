package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.EmployeePet;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class EmployeePetFileRepository extends FileRepository<Long, EmployeePet> {
    public EmployeePetFileRepository(Validator<EmployeePet> validator, String fileName) {
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
                int employeeId = Integer.parseInt(items.get(1));
                int petId = Integer.parseInt(items.get(2));
                String typeOfAction = items.get(3);
                String date = items.get((4));

                EmployeePet employeePet = new EmployeePet(employeeId, petId, typeOfAction, date);
                employeePet.setId(id);

                try {
                    super.save(employeePet);
                } catch (ValidatorException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public Optional<EmployeePet> save(EmployeePet entity) throws ValidatorException {
        Optional<EmployeePet> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    @Override
    public Optional<EmployeePet> delete(Long id) {
        Optional<EmployeePet> opt = super.delete(id);
        saveToFile();
        return opt;
    }

    @Override
    public Optional<EmployeePet> update(EmployeePet employeePet) {
        Optional<EmployeePet> opt = super.update(employeePet);
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
                                    + "," + e.getValue().getEmployeeId()
                                    + "," + e.getValue().getPetId()
                                    + "," + e.getValue().getTypeOfAction()
                                    + "," + e.getValue().getDate());
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
    protected void saveToFile(EmployeePet entity) {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getEmployeeId() + "," + entity.getPetId() + "," + entity.getTypeOfAction() + "," + entity.getDate());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
