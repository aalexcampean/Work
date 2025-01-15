package ssvv.example;


import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.mockito.junit.MockitoJUnitRunner;
import ssvv.example.domain.Nota;
import ssvv.example.domain.Student;
import ssvv.example.domain.Tema;
import ssvv.example.repository.NotaXMLRepo;
import ssvv.example.repository.StudentXMLRepo;
import ssvv.example.repository.TemaXMLRepo;
import ssvv.example.service.Service;
import ssvv.example.validation.NotaValidator;
import ssvv.example.validation.StudentValidator;
import ssvv.example.validation.TemaValidator;
import ssvv.example.validation.ValidationException;

import java.time.LocalDate;

import static junit.framework.TestCase.assertEquals;
import static org.mockito.Mockito.*;

@RunWith(MockitoJUnitRunner.class)
public class MockitoTest {

    private StudentValidator studentValidator = new StudentValidator();
    private TemaValidator temaValidator = new TemaValidator();

    @Mock
    private StudentXMLRepo studentXMLRepoMock = new StudentXMLRepo( "fisiere/Studenti.xml");
    @Mock
    private TemaXMLRepo temaXMLRepoMock = new TemaXMLRepo( "fisiere/Teme.xml");

    private NotaValidator notaValidator = new NotaValidator(studentXMLRepoMock, temaXMLRepoMock);

    @Mock
    private NotaXMLRepo notaXMLRepo = new NotaXMLRepo( "fisiere/Note.xml");

    private Service service;

    @Before
    public void setUp() {
        MockitoAnnotations.openMocks(this);
        service = new Service(studentXMLRepoMock, studentValidator, temaXMLRepoMock, temaValidator, notaXMLRepo, notaValidator);
    }

    @Test
    public void test_add_student() {
        Student expected = new Student("15", "alex", 900,"alex@yahoo.com");
        Student student = service.addStudent(expected);
        assertEquals(student, null);
    }

    @Test
    public void test_add_student_assignment() {
        Student expected = new Student("15", "alex", 900,"alex@yahoo.com");
        Student student = service.addStudent(expected);
        assertEquals(student, null);

        Tema tema = new Tema("13", "ssvv", 8, 7);
        Tema temaAdded = service.addTema(tema);
        assertEquals(temaAdded, null);
    }

    @Test
    public void test_add_all() {
        Student expected = new Student("15", "alex", 900,"alex@yahoo.com");
        Student student = service.addStudent(expected);
        assertEquals(student, null);

        Tema tema = new Tema("13", "ssvv", 8, 7);
        Tema temaAdded = service.addTema(tema);
        assertEquals(temaAdded, null);

        try{
            Nota nota = new Nota("100", null, null, 10, LocalDate.of(2018, 10, 26));
            double notaAdded = service.addNota(nota, "Good job");
            assertEquals(notaAdded, 10);
        }
        catch (ValidationException e){
            assertEquals(e.getMessage(), "Studentul nu exista!");
        }
    }
}
