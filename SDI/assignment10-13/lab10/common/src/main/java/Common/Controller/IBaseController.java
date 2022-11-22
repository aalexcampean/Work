package Common.Controller;

public interface IBaseController {
    int PORT = 1234;
    String HOST = "localhost";

    void addRequestHandlers();
}
