package ro.ubb.catalog;

import java.io.FileInputStream;
import java.io.IOException;

import org.xml.sax.SAXException;
import ro.ubb.catalog.Domain.*;
import ro.ubb.catalog.Domain.Validators.*;
import ro.ubb.catalog.Repository.*;
import ro.ubb.catalog.Repository.Database.ClinicDbRepo;
import ro.ubb.catalog.Repository.Database.EmployeePetDbRepository;
import ro.ubb.catalog.Repository.Database.SurgeryDbRepository;
import ro.ubb.catalog.Repository.Database.VetDbRepo;
import ro.ubb.catalog.Repository.Database.PetDbRepo;
import ro.ubb.catalog.Repository.TextFile.EmployeeContractFileRepository;
import ro.ubb.catalog.Repository.TextFile.OwnerFileRepository;
import ro.ubb.catalog.Repository.TextFile.VetContractFileRepository;
import ro.ubb.catalog.Repository.XMLFile.*;
import ro.ubb.catalog.Service.*;
import ro.ubb.catalog.UI.*;

import javax.xml.parsers.ParserConfigurationException;
import java.util.HashMap;
import java.util.Properties;
import java.util.stream.Stream;


/**
 * Created by radu.
 * <p>
 * Catalog App
 * </p>
 * <p>
 * I1:
 *
 * <ul>
 * <li>F1: add student</li>
 * <li>F2: print all students</li>
 * <li>in memory repo</li>
 * </ul>
 * <p>
 * I2:
 * <ul>
 * <li>in file repo</li>
 * <li>F3: print students whose name contain a given string</li>
 * </ul>
 */

public class Main {
    private static HashMap<String, String> readPropertiesSettings() {
        HashMap<String, String> propertiesMap = new HashMap<>();
        Properties properties = new Properties();

        String configFile = "data/settings.properties";
        FileInputStream fileInputStream;
        try {
            fileInputStream = new FileInputStream(configFile);
        } catch (IOException exception) {
            System.out.println(exception.getMessage());
            return propertiesMap;
        }
        Stream.ofNullable(fileInputStream).findAny().ifPresentOrElse((el) -> {
            try {
                properties.load(fileInputStream);
                propertiesMap.put("database", properties.getProperty("database"));
                propertiesMap.put("user", properties.getProperty("user"));
                propertiesMap.put("password", properties.getProperty("password"));
            } catch (IOException ioException) {
                System.out.println("IOException: " + ioException.getMessage());
            }
        }, () -> System.out.println("Invalid config file"));
        return propertiesMap;
    }


    public static void main(String args[]) throws ParserConfigurationException, IOException, SAXException {
        // Read Configurations
        HashMap<String, String> configurations = readPropertiesSettings();
        var dataBaseName = configurations.get("database");
        var userName = configurations.get("user");
        var password = configurations.get("password");

        // MARK: - Clinic
        Validator<Clinic> clinicValidator = new ClinicValidator();
//        Repository<Long, Clinic> clinicFileRepository = new ClinicFileRepository(clinicValidator, "./data/clinics");
//        Repository<Long, Clinic> clinicXMLRepository = new ClinicXMLRepository(clinicValidator, "./data/clinicsXML.xml");
        Repository<Long, Clinic> clinicDbRepository = new ClinicDbRepo(dataBaseName, userName, password);
        ClinicService clinicService = new ClinicService(clinicDbRepository, clinicValidator);
        ClinicConsole clinicConsole = new ClinicConsole(clinicService);

        Validator<Pet> petValidator = new PetValidator();
        //Repository<Long, Pet> petRepository = new PetXMLRepo(petValidator, "./data/petsXML.xml");
        Repository<Long, Pet> petRepository = new PetDbRepo(configurations.get("database"), configurations.get("user"), configurations.get("password"));
        PetService petService = new PetService(petRepository);
        //PetValidator petValidator1 = new PetValidator();
        PetConsole consoleP = new PetConsole(petService);


        Validator<EmployeeContract> ecValidator = new EmployeeContractValidator();
        Repository<Long, EmployeeContract> ecRepository = new EmployeeContractFileRepository(ecValidator, "./data/employeecontracts");
        EmployeeContractValidator ecValidator1 = new EmployeeContractValidator();
        EmployeeContractService ecService = new EmployeeContractService(ecRepository);
        EmployeeContractConsole consoleEC = new EmployeeContractConsole(ecService, ecValidator1);


        Validator<Employee> employeeValidator = new EmployeeValidator();
//        Repository<Long, Employee> employeeRepository = new EmployeeFileRepository(employeeValidator, "./data/employees");
        Repository<Long, Employee> employeeRepository = new EmployeeXMLRepository(employeeValidator, "./data/employeesXML.xml");
        EmployeeService employeeService = new EmployeeService(employeeRepository);
        EmployeeConsole consoleE = new EmployeeConsole(employeeService);


        // MARK: - Pet
//        Validator<Pet> petValidator = new PetValidator();
//        Repository<Long, Pet> petRepository = new PetFileRepository(petValidator, "./data/pets");
//        PetService petService = new PetService(petRepository);
//        PetValidator petValidator1 = new PetValidator();
//        PetConsole consoleP = new PetConsole(petService, petValidator1);

        // MARK: - EmployeePet
        Validator<EmployeePet> employeePetValidator = new EmployeePetValidator();
        // Repository<Long, EmployeePet> employeePetRepository = new EmployeePetFileRepository(employeePetValidator, "./data/employeePets");
        // Repository<Long, EmployeePet> employeePetRepository = new EmployeePetXMLRepository(employeePetValidator, "./data/employeePetsXML.xml");
        Repository<Long, EmployeePet> employeePetRepository = new EmployeePetDbRepository(configurations.get("database"), configurations.get("user"), configurations.get("password"));
        EmployeePetValidator employeePetValidator1 = new EmployeePetValidator();
        EmployeePetService employeePetService = new EmployeePetService(employeePetRepository, employeePetValidator1);
        EmployeePetConsole consoleEmployeePet = new EmployeePetConsole(employeePetService);

        // MARK: - Owner
        Validator<Owner> ownerValidator = new OwnerValidator();
        Repository<Long, Owner> ownerRepository = new OwnerFileRepository(ownerValidator, "./data/owners");
        OwnerService ownerService = new OwnerService(ownerRepository);
        OwnerConsole consoleO = new OwnerConsole(ownerService);


        // MARK: - Surgery
        Validator<Surgery> surgeryValidator = new SurgeryValidator();
        // Repository<Long, Surgery> surgeryRepository = new SurgeryFileRepository(surgeryValidator, "./data/surgeries");
        // Repository<Long, Surgery> surgeryRepository = new SurgeryXMLRepository(surgeryValidator, "./data/surgeriesXML.xml");
        Repository<Long, Surgery> surgeryRepository = new SurgeryDbRepository(configurations.get("database"), configurations.get("user"), configurations.get("password"));
        SurgeryValidator surgeryValidator1 = new SurgeryValidator();
        SurgeryService surgeryService = new SurgeryService(surgeryRepository, surgeryValidator1);
        SurgeryConsole consoleSurgery = new SurgeryConsole(surgeryService);

        // MARK: - Vet
        Validator<Vet> vetValidator = new VetValidator();
//        Repository<Long, Vet> vetRepository = new VetFileRepo(vetValidator, "./data/vets");
        //Repository<Long, Vet> vetRepository = new VetXMLRepo(vetValidator, "./data/vetsXML.xml");
        Repository<Long, Vet> vetRepository = new VetDbRepo(configurations.get("database"), configurations.get("user"), configurations.get("password"));
        VetService vetService = new VetService(vetRepository, vetValidator);
        VetConsole consoleV = new VetConsole(vetService);

        // MARK: - VetContract
        Validator<VetContract> vetContractValidator = new VetContractValidator();
        Repository<Long, VetContract> vetContractRepository = new VetContractFileRepository(vetContractValidator, "./data/vetContracts");
        VetContractService vetContractService = new VetContractService(vetContractRepository, vetContractValidator);
        VetContractConsole consoleVC = new VetContractConsole(vetContractService);


        //consoleP.runConsole();
        // System.out.println("---------------");
        //consoleEmployeePet.runConsole();
        // System.out.println("---------------");
//        consoleSurgery.runConsole();
        // System.out.println("---------------");
        // consoleO.runConsole();
        // System.out.println("---------------");
        //consoleE.runConsole();
        // System.out.println("---------------");
        //consoleEC.runConsole();
        // consoleEC.runConsole();
        // System.out.println("---------------");
        //consoleV.runConsole();
//         consoleV.runConsole();
//         consoleVC.runConsole();
        // System.out.println("---------------");
        clinicConsole.runConsole();

        System.out.println("BYEBYE");
    }
}
