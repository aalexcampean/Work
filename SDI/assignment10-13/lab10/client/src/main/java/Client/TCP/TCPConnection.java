package Client.TCP;

import Common.Controller.IBaseController;
import Common.Request.Request;
import Common.Request.RequestException;

import java.io.IOException;
import java.net.ConnectException;
import java.net.Socket;
import java.util.concurrent.ExecutorService;

public class TCPConnection {
    private ExecutorService executorService;

    public TCPConnection(ExecutorService executorService) {
        this.executorService = executorService;
    }

    public Request sendAndReceive(Request request) {
        try (var socket = new Socket(IBaseController.HOST, IBaseController.PORT);
             var is = socket.getInputStream();
             var os = socket.getOutputStream()) {
            System.out.println("Sending request: " + request);
            request.write(os);
            System.out.println("Request has been sent");

            Request response = new Request();
            response.read(is);
            System.out.println("Response has been received: " + response);

            return response;
        } catch (ConnectException ce) {
            throw new RequestException("Could not establish a connection with the server");
        } catch (IOException e) {
            e.printStackTrace();
            throw new RequestException("Exception arose in send and receive", e);
        }
    }
}
