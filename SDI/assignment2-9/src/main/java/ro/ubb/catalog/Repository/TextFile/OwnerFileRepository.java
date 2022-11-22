package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.Owner;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Repository.InMemory.InMemoryRepository;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class OwnerFileRepository extends InMemoryRepository<Long, Owner> {
    private String fileName;

    public OwnerFileRepository(Validator<Owner> validator, String fileName){
        super(validator);
        this.fileName=fileName;

        loadData();
    }

    public void loadData(){
        Path path= Paths.get(fileName);

        try{
            Files.lines(path).forEach(line->{
                List<String> items = Arrays.asList(line.split(","));

                Long id=Long.valueOf(items.get(0));
                String firstName=String.valueOf(items.get(1));
                String lastName=String.valueOf((items.get(2)));

                Owner owner=new Owner(firstName, lastName);
                owner.setId(id);

                try{
                    super.save(owner);
                }catch (ValidatorException e){
                    e.printStackTrace();
                }
            });

        }catch (IOException ex){
            ex.printStackTrace();
        }
    }

    @Override
    public Optional<Owner> save(Owner entity) throws ValidatorException{
        Optional <Owner> optional=super.save(entity);

        if (optional.isPresent()) {
            return optional;
        }
        saveToFile(entity);
        return Optional.empty();
    }

    public void saveToFile(Owner entity){
        Path path=Paths.get(fileName);

        try(BufferedWriter bufferedWriter=Files.newBufferedWriter(path, StandardOpenOption.APPEND)){
            bufferedWriter.write(
                    entity.getId() + "," + entity.getFirstName() + "," +entity.getLastName());
            bufferedWriter.newLine();
        }catch (IOException ex){
            ex.printStackTrace();
        }
    }

    @Override
    public Optional<Owner> delete (Long id){
        Optional<Owner> opt=super.delete(id);
        return opt;
    }

    @Override
    public Optional<Owner> update (Owner owner){
        Optional<Owner> opt=super.update(owner);
        return opt;
    }
}
