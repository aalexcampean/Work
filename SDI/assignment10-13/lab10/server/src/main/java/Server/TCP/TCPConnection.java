package Server.TCP;

import Common.Request.Request;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.function.UnaryOperator;

public class TCPConnection {
    private int port;
    private Map<String, UnaryOperator<Request>> requestHandler;
    private ExecutorService executorService;

    public TCPConnection(ExecutorService executorService, int port) {
        this.port = port;
        this.requestHandler = new HashMap<>();
        this.executorService = executorService;
    }

    public void addHandler(String request, UnaryOperator<Request> handler) {
        requestHandler.put(request, handler);
    }

    public void startServer() {
        try (var serverSocket = new ServerSocket(this.port)) {
            System.out.println("Server has started");
            System.out.println("Waiting for clients...");

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client has connected");
                executorService.submit(new ClientHandler(clientSocket));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private class ClientHandler implements Runnable {
        Socket socket;

        public ClientHandler(Socket clientSocket) {
            this.socket = clientSocket;
        }

        @Override
        public void run() {
            try (var is = socket.getInputStream();
                 var os = socket.getOutputStream()) {

                Request request = new Request();
                request.read(is);

                System.out.println("Request has been received: " + request);
                Request response = requestHandler.get(request.getHeader()).apply(request);
                System.out.println("Response has been computed: " + response);

                response.write(os);
                System.out.println("Response has been sent to client");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
