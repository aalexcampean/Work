package core.entity;

public class ClinicException extends RuntimeException {
    public ClinicException(String message) {
        super(message);
    }

    public ClinicException(String message, Throwable cause) {
        super(message, cause);
    }

    public ClinicException(Throwable cause) {
        super(cause);
    }
}
