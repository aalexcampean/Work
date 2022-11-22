package ro.ubb.catalog.UI;

import ro.ubb.catalog.Domain.Employee;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Service.EmployeeService;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;

public class EmployeeConsole {

    private EmployeeService employeeService;

    public EmployeeConsole(EmployeeService employeeService){
        this.employeeService = employeeService;
    }

    public void printMenu() {
        System.out.println("1. Add an employee");
        System.out.println("2. Print all employees");
        System.out.println("3. Filter employees by their last name");
        System.out.println("4. Delete an employee");
        System.out.println("5. Update an employee");
        System.out.println("0. Exit");
    }

    public void runConsole(){

        printMenu();

        try{
            System.out.println("Input option: ");
            BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
            String option = bufferRead.readLine();
            while (!Objects.equals(option, "0")) {
                if (Objects.equals(option, "1"))
                    addEmployees();
                else if (Objects.equals(option, "2"))
                    printAllEmployees();
                else if (Objects.equals(option, "3"))
                    filterEmployees();
                else if (Objects.equals(option, "4"))
                    deleteEmployee();
                else if (Objects.equals(option, "5"))
                    updateEmployee();
                else System.out.println("Invalid option!");

                printMenu();
                System.out.println("Input option: ");
                option = bufferRead.readLine();
            }
        }
        catch(IOException ex) {
            ex.printStackTrace();
        }
    }

    private void printAllEmployees(){
        Set<Employee> employees = employeeService.getAllEmployees();
        employees.stream().forEach(System.out::println);
    }

    private void addEmployees() {

        Employee employee= readEmployee();

        try {
            employeeService.addEmployee(employee);
        } catch (ValidatorException e) {
            e.printStackTrace();
        }
    }

    private Employee readEmployee() {
        System.out.println("Read employee");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());
            String firstName = bufferRead.readLine();
            String lastName = bufferRead.readLine();
            int salary = Integer.parseInt(bufferRead.readLine());
            int rating = Integer.parseInt(bufferRead.readLine());
            String date = bufferRead.readLine();

            Employee employee = new Employee(firstName, lastName, salary, rating, date);
            employee.setId(id);

            System.out.println("Finish read employee");
            return employee;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    private void filterEmployees() {
        System.out.println("Input the string to be filtered by: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            String str = bufferRead.readLine();
            System.out.println("Filtered employees with last name containing: " + str);
            Set<Employee> employees = employeeService.filterEmployeesByLastName(str);
            employees.stream().forEach(System.out::println);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void deleteEmployee(){

        System.out.println("Enter the ID of the employee to be deleted: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            //Long id = Long.valueOf(bufferRead.readLine());
            String str = String.valueOf(bufferRead.readLine());
            boolean allDigits = true;
            for (int i = 0; i < str.length(); i++) {

                if (!Character.isDigit(str.charAt(i))) {
                    allDigits = false;
                    break;
                }
            }
            if(!allDigits)
                System.out.println("IDs can only be positive integers!");
            else {
                long id = Long.parseLong(str);
                employeeService.deleteEmployee(id);
                System.out.println("Employee with id " + str + " was deleted (if it existed)");

            }
        } catch (IOException ex) {
            //ex.printStackTrace();
            System.out.println("IDs can only be positive integers!");
            //System.exit(1);
        }
    }

    private void updateEmployee() throws IOException {

        System.out.println("Enter the ID of the employee to be updated: ");
        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));

        //Long id = Long.valueOf(bufferRead.readLine());
        String str = String.valueOf(bufferRead.readLine());
        boolean allDigits = true;
        for (int i = 0; i < str.length(); i++) {

            if (!Character.isDigit(str.charAt(i))) {
                allDigits = false;
                break;
            }
        }
        if(!allDigits)
            System.out.println("IDs can only be positive integers!");
        else
        {

            try {
                System.out.println("Enter the new employee details:");
                long id = Long.parseLong(str);
                System.out.println("Enter the new first name:");
                String firstName = bufferRead.readLine();
                System.out.println("Enter the new last name:");
                String lastName = bufferRead.readLine();
                System.out.println("Enter the new salary:");
                int salary = Integer.parseInt(bufferRead.readLine());
                System.out.println("Enter the new rating:");
                int rating = Integer.parseInt(bufferRead.readLine());
                System.out.println("Enter the new date:");
                String date = bufferRead.readLine();

                Employee employee = new Employee(firstName, lastName, salary, rating, date);
                employee.setId(id);
                employeeService.updateEmployee(employee);
                System.out.println("Employee with id " + str + " was updated (if it exists)");

            } catch (IOException|ValidatorException ex) {
                //ex.printStackTrace();
                System.out.println(ex.getMessage());
                //System.exit(1);
            }

        }

    }
}
