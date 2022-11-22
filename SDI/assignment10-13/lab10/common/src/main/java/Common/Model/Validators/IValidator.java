package Common.Model.Validators;

public interface IValidator<T> {
    void validate(T entity) throws ValidatorException;
}
