package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.Clinic;
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

public class ClinicFileRepository extends FileRepository<Long, Clinic>{

    public ClinicFileRepository(Validator<Clinic> validator, String inputFileName) {
        super(validator, inputFileName);
        this.loadData();
    }

    @Override
    public Optional<Clinic> save(Clinic entity) throws ValidatorException {
        Optional<Clinic> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    @Override
    public Optional<Clinic> delete(Long id) {
        Optional<Clinic> opt = super.delete(id);
        saveToFile();
        return opt;
    }

    @Override
    public Optional<Clinic> update(Clinic clinic) {
        Optional<Clinic> opt = super.update(clinic);
        saveToFile();
        return opt;
    }

    @Override
    protected void loadData() {
        Path path = Paths.get(this.getFileName());
        try {
            Files.lines(path).forEach(line -> {
                List<String> items = Arrays.asList(line.split(","));

                Long id = Long.valueOf(items.get(0));
                String name = items.get(1);
                String location = items.get(1);
                int yearFounded = Integer.parseInt(items.get(3));

                Clinic newClinic = new Clinic(name, location, yearFounded);
                newClinic.setId(id);

                try {
                    super.save(newClinic);
                } catch (ValidatorException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    @Override
    protected void saveToFile() {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.TRUNCATE_EXISTING)) {
            this.getEntities().entrySet()
                    .forEach(e -> {
                        try {
                            bufferedWriter.write(e.getKey() + "," + e.getValue().getName() + "," + e.getValue().getLocation() + "," + e.getValue().getYearFounded());
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
    protected void saveToFile(Clinic clinic) {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(clinic.getId() + "," + clinic.getName() + "," + clinic.getLocation() + "," + clinic.getYearFounded());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
