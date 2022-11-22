package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.Vet;
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

public class VetFileRepo extends FileRepository<Long, Vet> {

    public VetFileRepo(Validator<Vet> validator, String fileName) {
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
                String fn = items.get(1);
                String ln = items.get((2));
                int sal = Integer.parseInt(items.get(3));
                int rate = Integer.parseInt(items.get(4));
                String date = items.get((5));

                Vet v = new Vet(fn, ln, sal, rate, date);
                v.setId(id);

                try {
                    super.save(v);
                } catch (ValidatorException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public Optional<Vet> save(Vet entity) throws ValidatorException {
        Optional<Vet> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    @Override
    public Optional<Vet> delete(Long id) {
        Optional<Vet> opt = super.delete(id);
        saveToFile();
        return opt;
    }

    @Override
    public Optional<Vet> update(Vet v) {
        Optional<Vet> opt = super.update(v);
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
    protected void saveToFile(Vet entity) {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getFirstName() + "," + entity.getLastName() + "," + entity.getSalary() + "," + entity.getRating() + "," + entity.getDate());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
