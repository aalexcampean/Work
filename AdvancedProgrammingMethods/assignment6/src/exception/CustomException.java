package exception;

public class CustomException extends RuntimeException {
    public CustomException(String messageError){
        super(messageError);
    }
}
