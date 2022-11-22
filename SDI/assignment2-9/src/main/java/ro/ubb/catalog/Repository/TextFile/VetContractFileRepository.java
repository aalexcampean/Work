package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.VetContract;
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

public class VetContractFileRepository extends FileRepository<Long,VetContract>{
    public VetContractFileRepository(Validator<VetContract> validator, String fileName) {
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
                int vetID = Integer.parseInt(items.get(1));
                int clinicID = Integer.parseInt(items.get(2));
                LocalDate contractDate = LocalDate.parse(items.get(3));
                
                VetContract vc = new VetContract(vetID, clinicID, contractDate);
                vc.setId(id);

                try {
                    super.save(vc);
                } catch (ValidatorException e) {
                    e.printStackTrace();
                }
            });
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<VetContract> save(VetContract entity) throws ValidatorException {
        Optional<VetContract> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    @Override
    public Optional<VetContract> delete(Long id) {
        Optional<VetContract> opt = super.delete(id);
        saveToFile();
        return opt;
    }

    @Override
    public Optional<VetContract> update(VetContract entity) throws ValidatorException {
        Optional<VetContract> opt = super.update(entity);
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
                                    + "," + e.getValue().getVetID()
                                    + "," + e.getValue().getClinicID()
                                    + "," + e.getValue().getContractDate());
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
    protected void saveToFile(VetContract entity) {
        Path path = Paths.get(this.getFileName());

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(
                    entity.getId()+ ","  + entity.getVetID() + ","  + entity.getClinicID() + "," + entity.getContractDate());
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}