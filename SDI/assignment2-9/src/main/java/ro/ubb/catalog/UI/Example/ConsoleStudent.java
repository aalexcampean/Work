package ro.ubb.catalog.UI.Example;

import ro.ubb.catalog.Domain.Example.Student;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Service.Example.StudentService;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Set;

/**
 * @author radu.
 */
public class ConsoleStudent {
    private StudentService studentService;

    public ConsoleStudent(StudentService studentService) {
        this.studentService = studentService;
    }

    public void runConsole() {
//        addStudents();
        printAllStudents();
        filterStudents();
    }

    private void filterStudents() {
        System.out.println("filtered students (name containing 's2'):");
        Set<Student> students = studentService.filterStudentsByName("s2");
        students.stream().forEach(System.out::println);
    }

    private void printAllStudents() {
        Set<Student> students = studentService.getAllStudents();
        students.stream().forEach(System.out::println);
    }

    private void addStudents() {
        while (true) {
            Student student = readStudent();
            if (student == null || student.getId() < 0) {
                break;
            }
            try {
                studentService.addStudent(student);
            } catch (ValidatorException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ParserConfigurationException e) {
                e.printStackTrace();
            } catch (TransformerException e) {
                e.printStackTrace();
            }
        }
    }

    private Student readStudent() {
        System.out.println("Read student {id,serialNumber, name, group}");

        BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
        try {
            Long id = Long.valueOf(bufferRead.readLine());// ...
            String serialNumber = bufferRead.readLine();
            String name = bufferRead.readLine();
            int group = Integer.parseInt(bufferRead.readLine());// ...

            Student student = new Student(serialNumber, name, group);
            student.setId(id);

            return student;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return null;
    }
}
