package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.Surgery;
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

public class SurgeryFileRepository extends FileRepository<Long, Surgery> {
    public SurgeryFileRepository(Validator<Surgery> validator, String fileName) {
        super(validator, fileName);
        loadData();
    }

    @Override
    protected void loadData() {
        Path path = Paths.get(this.getFileName());

        try {
            Files.lines(path).forEach(line -> {
                List<String> items = Arrays.asList(line.split(","));

                Long id = Long.valueOf(items.get(0));
                int petId = Integer.parseInt(items.get(1));
                int vetId = Integer.parseInt(items.get(2));
                String surgeryDate = items.get(3);
                String surgeryType = items.get(4);

                Surgery surgery = new Surgery(petId, vetId, surgeryDate, surgeryType);
                surgery.setId(id);

                try {
                    super.save(surgery);
                } catch (ValidatorException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public Optional<Surgery> save(Surgery entity) throws ValidatorException {
        Optional<Surgery> optional = super.save(entity);
        if(optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    @Override
    public Optional<Surgery> delete(Long id) {
        Optional<Surgery> opt = super.delete(id);
        saveToFile();
        return opt;
    }

    @Override
    public Optional<Surgery> update(Surgery s) {
        Optional<Surgery> opt = super.update(s);
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
                                    + "," + e.getValue().getPetId()
                                    + "," + e.getValue().getVetId()
                                    + "," + e.getValue().getSurgeryDate()
                                    + "," + e.getValue().getSurgeryType());
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
    protected void saveToFile(Surgery entity) {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId() + "," + entity.getPetId() + "," + entity.getVetId() + "," + entity.getSurgeryDate() + "," + entity.getSurgeryType());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
