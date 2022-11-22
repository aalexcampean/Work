package catalog.Domain;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import ro.ubb.catalog.Domain.Vet;

import static org.junit.Assert.assertEquals;

public class VetTest {
    private static final Long ID = 1L;
    private static final Long NEW_ID = 2L;
    private static final String firstName = "fn1";
    private static final String lastName = "ln1";
    private static final String date = "20-12-2000";
    private static final int salary = 100;
    private static final int rating = 10;
    private static final String newfn ="Fn1";
    private static final int newsalary = 120;
    private static final int newrating = 9;
    private Vet vet;

    @Before
    public void setUp() throws Exception {
        vet = new Vet(firstName,lastName,salary,rating,date);
        vet.setId(ID);
    }

    @After
    public void tearDown() throws Exception {
        vet=null;
    }

    @Test
    public void testGetVetFName() throws Exception {
        assertEquals("Name should be ", firstName, vet.getFirstName());
    }
    @Test
    public void testGetVetLName() throws Exception {
        assertEquals("Name should be ", lastName, vet.getLastName());
    }

    @Test
    public void testSetVetName() throws Exception {
        vet.setFirstName(newfn);
        assertEquals("Names should be equal", newfn, vet.getFirstName());
    }

    @Test
    public void testGetId() throws Exception {
        assertEquals("Ids should be equal", ID, vet.getId());
    }

    @Test
    public void testSetId() throws Exception {
        vet.setId(NEW_ID);
        assertEquals("Ids should be equal", NEW_ID, vet.getId());
    }

    @Test
    public void testGetSalary() throws Exception {
        assertEquals("Salaries should be equal", salary,vet.getSalary());
    }

    @Test
    public void testSetSalary() throws Exception {
        vet.setSalary(newsalary);
        assertEquals("Salaries should be equal", newsalary, vet.getSalary());
    }

    @Test
    public void testGetRating() throws Exception {
        assertEquals("Rating should be equal", rating, vet.getRating());
    }

    @Test
    public void testsetRating() throws Exception {
        vet.setRating(newrating);
        assertEquals("Breeds should be equal", newrating, vet.getRating());
    }
    @Test
    public void testGetDate() throws Exception {
        assertEquals("Dates should be equal", date, vet.getDate());
    }

}
