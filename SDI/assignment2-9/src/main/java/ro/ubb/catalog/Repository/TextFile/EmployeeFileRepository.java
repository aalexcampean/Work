package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.Employee;
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

public class EmployeeFileRepository extends FileRepository<Long, Employee>{

    public EmployeeFileRepository(Validator<Employee> validator, String fn) {
        super(validator, fn);
        loadData();
    }

    @Override
    protected void loadData() {
        Path path = Paths.get(this.getFileName());

        try {
            Files.lines(path).forEach(line -> {
                List<String> items = Arrays.asList(line.split(","));

                Long id = Long.valueOf(items.get(0));
                String firstName = items.get(1);
                String lastName = items.get(1);
                int salary = Integer.parseInt(items.get(3));
                int rating = Integer.parseInt(items.get(4));
                String date = items.get(5);

                Employee employee = new Employee(firstName, lastName, salary, rating, date);
                employee.setId(id);

                try {
                    super.save(employee);
                } catch (ValidatorException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public Optional<Employee> save(Employee entity) throws ValidatorException {
        Optional<Employee> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    @Override
    public Optional<Employee> delete(Long id) {
        Optional<Employee> opt = super.delete(id);
        saveToFile();
        return opt;
    }

    @Override
    public Optional<Employee> update(Employee employee) {
        Optional<Employee> opt = super.update(employee);
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
                                    + "," + e.getValue().getFirstName()
                                    + "," + e.getValue().getLastName()
                                    + "," + e.getValue().getSalary()
                                    + "," + e.getValue().getRating()
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
    protected void saveToFile(Employee entity) {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getFirstName() + "," + entity.getLastName() + "," + entity.getSalary()
                        + "," + entity.getRating() + "," + entity.getDate());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
