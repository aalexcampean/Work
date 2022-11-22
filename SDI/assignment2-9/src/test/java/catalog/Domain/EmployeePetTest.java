package catalog.Domain;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import ro.ubb.catalog.Domain.EmployeePet;

import static org.junit.Assert.assertEquals;

public class EmployeePetTest {
    private static final Long ID = 1L;
    private static final Long NEW_ID = 2L;
    private static final int employeeId = 1;
    private static final int petId = 1;
    private static final int newEmployeeId = 2;
    private static final int newPetId = 2;
    private static final String typeOfAction = "clean";
    private static final String newTypeOfAction = "feed";
    private static final String date = "04-06-2021";
    private static final String newDate = "12-10-2021";
    private EmployeePet employeePet;

    @Before
    public void setUp() throws Exception {
        employeePet = new EmployeePet(employeeId, petId, typeOfAction, date);
        employeePet.setId(ID);
    }

    @After
    public void tearDown() throws Exception {
        employeePet = null;
    }

    @Test
    public void testGetId() throws Exception {
        assertEquals("Ids should be equal", ID, employeePet.getId());
    }

    @Test
    public void testSetId() throws Exception {
        employeePet.setId(NEW_ID);
        assertEquals("Ids should be equal", NEW_ID, employeePet.getId());
    }

    @Test
    public void testGetEPEmployeeId() throws Exception {
        assertEquals("EmployeeId should be ", employeeId, employeePet.getEmployeeId());
    }

    @Test
    public void testSetEPEmployeeId() throws Exception {
        employeePet.setEmployeeId(newEmployeeId);
        assertEquals("EmployeeIds should be equal", newEmployeeId, employeePet.getEmployeeId());
    }

    @Test
    public void testGetEPPetId() throws Exception {
        assertEquals("PetIds should be equal", petId, employeePet.getPetId());
    }

    @Test
    public void testSetEPPetId() throws Exception {
        employeePet.setPetId(newPetId);
        assertEquals("PetIds should be equal", newPetId, employeePet.getPetId());
    }

    @Test
    public void testGetEPTypeOfAction() throws Exception {
        assertEquals("Types of action should be equal", typeOfAction, employeePet.getTypeOfAction());
    }

    @Test
    public void testSetEPTypeOfAction() throws Exception {
        employeePet.setTypeOfAction(newTypeOfAction);
        assertEquals("Types of action should be equal", newTypeOfAction, employeePet.getTypeOfAction());
    }

    @Test
    public void testGetEPDate() throws Exception {
        assertEquals("Dates should be equal", date, employeePet.getDate());
    }

    @Test
    public void testSetEPDate() throws Exception {
        employeePet.setDate(newDate);
        assertEquals("Dates should be equal", newDate, employeePet.getDate());
    }
}