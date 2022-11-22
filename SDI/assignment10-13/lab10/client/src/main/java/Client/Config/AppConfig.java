package Client.Config;

import Client.Controller.AppointmentController;
import Client.Controller.OwnerController;
import Client.Controller.PetController;
import Client.Controller.VetController;
import Client.TCP.TCPConnection;
import Client.View.UI;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Configuration
public class AppConfig {
    @Bean
    ExecutorService executorService() {
        return Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
    }

    @Bean
    TCPConnection tcpConnection() {
        return new TCPConnection(executorService());
    }

    @Bean
    OwnerController ownerController() {
        return new OwnerController(tcpConnection(), executorService());
    }

    @Bean
    PetController petController() {
        return new PetController(tcpConnection(), executorService());
    }

    @Bean
    VetController vetController() {
        return new VetController(tcpConnection(), executorService());
    }

    @Bean
    AppointmentController appointmentController() {
        return new AppointmentController(tcpConnection(), executorService());
    }

    @Bean
    UI ui() {
        return new UI(ownerController(), petController(), vetController(), appointmentController());
    }
}
