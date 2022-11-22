package Server.Config;

import Common.Controller.IBaseController;
import Common.Model.Domain.Appointment;
import Common.Model.Domain.Owner;
import Common.Model.Domain.Pet;
import Common.Model.Domain.Vet;
import Common.Model.Validators.AppointmentValidator;
import Common.Model.Validators.OwnerValidator;
import Common.Model.Validators.PetValidator;
import Common.Model.Validators.VetValidator;
import Server.Controller.AppointmentController;
import Server.Controller.OwnerController;
import Server.Controller.PetController;
import Server.Controller.VetController;
import Server.Repository.*;
import Server.Service.AppointmentService;
import Server.Service.OwnerService;
import Server.Service.PetService;
import Server.Service.VetService;
import Server.TCP.TCPConnection;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Configuration
public class AppConfig {
    @Bean
    IRepository<Long, Owner> ownerRepository() {
        return new OwnerRepository(new OwnerValidator());
    }

    @Bean
    IRepository<Long, Pet> petRepository() {
        return new PetRepository(new PetValidator());
    }

    @Bean
    IRepository<Long, Vet> vetRepository() {
        return new VetRepository(new VetValidator());
    }

    @Bean
    IRepository<Long, Appointment> appointmentRepository() {
        return new AppointmentRepository(new AppointmentValidator());
    }

    @Bean
    OwnerService ownerService() {
        return new OwnerService(ownerRepository(), petRepository());
    }

    @Bean
    PetService petService() {
        return new PetService(petRepository(), ownerRepository(), appointmentRepository());
    }

    @Bean
    VetService vetService() {
        return new VetService(vetRepository(), petRepository(), appointmentRepository());
    }

    @Bean
    AppointmentService appointmentService() {
        return new AppointmentService(appointmentRepository());
    }

    @Bean
    ExecutorService executorService() {
        return Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
    }

    @Bean
    TCPConnection tcpConnection() {
        return new TCPConnection(executorService(), IBaseController.PORT);
    }

    @Bean
    OwnerController ownerController() {
        return new OwnerController(tcpConnection(), executorService(), ownerService());
    }

    @Bean
    PetController petController() {
        return new PetController(tcpConnection(), executorService(), petService());
    }

    @Bean
    VetController vetController() {
        return new VetController(tcpConnection(), executorService(), vetService());
    }

    @Bean
    AppointmentController appointmentController() {
        return new AppointmentController(tcpConnection(), executorService(), appointmentService());
    }
}
