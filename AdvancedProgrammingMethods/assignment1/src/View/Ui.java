package View;

import Model.IVehicle;
import Model.Car;
import Model.Truck;
import Model.Motorcycle;

import Repository.Repo;
import Controller.Controller;

import java.util.Arrays;
import java.util.Objects;
import java.util.Scanner;

import static java.lang.Integer.parseInt;

public class Ui {
    public static void main(String[] args){
        Repo repo = new Repo();
        Controller controller = new Controller(repo);
        start(controller);
    }

    public static void printMenu(){
        System.out.println("--0.Exit");
        System.out.println("--1.Add");
        System.out.println("--2.Delete");
        System.out.println("--3.Filter");
        System.out.println("--4.Print all");
        System.out.print("Command: ");
    }

    public static void start(Controller givenController){
        boolean done = true;
        while (done){
            printMenu();
            Scanner scanner = new Scanner(System.in);
            try{
                int cmd = scanner.nextInt();
                switch (cmd){
                    case 0:
                        done = false;
                        System.out.print("Exiting...");
                        break;
                    case 1:
                        System.out.println("Format: type(car, truck, motorcycle), repair cost");
                        String[] input = scanner.next().split(",");
                        if (input.length != 2){
                            System.out.println("2 arguments must be provided!");
                        }
                        else {
                            if(input[1].contains("-") || input[1].indexOf("0") == 0){
                                System.out.println("The repair cost cannot be <= 0!");
                            }
                            else{
                                givenController.add(input[0], parseInt(input[1]));
                            }
                        }
                        break;
                    case 2:
                        System.out.println("Format: type(car, truck, motorcycle), repair cost");
                        String[] input2 = scanner.next().split(",");
                        if (input2.length != 2){
                            System.out.println("2 arguments must be provided!");
                        }
                        else {
                            givenController.delete(input2[0], parseInt(input2[1]));
                        }
                        break;
                    case 3:
                        IVehicle[] filteredVehicles = givenController.filter(1000);
                        for (IVehicle veh : filteredVehicles){
                            if(veh == null) {
                                break;
                            }
                            System.out.println(veh.toString());
                        }
                        break;
                    case 4:
                        IVehicle[] allVehicles = givenController.getEntities();
                        for (IVehicle veh : allVehicles){
                            if(veh == null){
                                break;
                            }
                            System.out.println(veh.toString());
                        }
                        break;
                }
            }
            catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }
}
