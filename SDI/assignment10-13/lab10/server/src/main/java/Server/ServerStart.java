package Server;

import Server.Controller.AppointmentController;
import Server.Controller.OwnerController;
import Server.Controller.PetController;
import Server.Controller.VetController;
import Server.TCP.TCPConnection;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class ServerStart {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext("server.config");
        TCPConnection tcpConnection = context.getBean(TCPConnection.class);

        OwnerController ownerController = context.getBean(OwnerController.class);
        PetController petController = context.getBean(PetController.class);
        VetController vetController = context.getBean(VetController.class);
        AppointmentController appointmentController = context.getBean(AppointmentController.class);

        tcpConnection.startServer();
    }
}
