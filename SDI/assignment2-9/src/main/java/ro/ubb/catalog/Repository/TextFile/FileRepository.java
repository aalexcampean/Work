package ro.ubb.catalog.Repository.TextFile;

import ro.ubb.catalog.Domain.BaseEntity;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Repository.InMemory.InMemoryRepository;

abstract public class FileRepository<ID, T extends BaseEntity<ID>> extends InMemoryRepository<ID, T> {

    private String fileName;

    public FileRepository(Validator<T> validator, String fileName) {
        super(validator);
        this.fileName = fileName;
    }

    protected String getFileName() {
        return this.fileName;
    }

    abstract protected void loadData();
    abstract protected void saveToFile();
    abstract protected void saveToFile(T entity);
}