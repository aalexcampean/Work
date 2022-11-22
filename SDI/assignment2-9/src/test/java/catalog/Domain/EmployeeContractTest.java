package catalog.Domain;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import ro.ubb.catalog.Domain.EmployeeContract;

import static org.junit.Assert.assertEquals;

import java.time.LocalDate;

public class EmployeeContractTest {
    private static final Long ID = 1L;
    private static final Long NEW_ID = 2L;
    private static final int employeeID = 1;
    private static final int clinicID = 1;
    private static final int newEmployeeID = 2;
    private static final int newClinicID = 2;
    private static final LocalDate date = LocalDate.parse("05-01-2015");
    private static final LocalDate newDate = LocalDate.parse("01-02-2014");
    private EmployeeContract employeeContract;

    @Before
    public void setUp() throws Exception {
        employeeContract = new EmployeeContract(date, employeeID, clinicID);
        employeeContract.setId(ID);
    }

    @After
    public void tearDown() throws Exception {
        employeeContract = null;
    }

    @Test
    public void testGetID() throws Exception {
        assertEquals("IDs should be equal", ID, employeeContract.getId());
    }

    @Test
    public void testSetID() throws Exception {
        employeeContract.setId(NEW_ID);
        assertEquals("IDs should be equal", NEW_ID, employeeContract.getId());
    }

    @Test
    public void testGetECEmployeeID() throws Exception {
        assertEquals("EmployeeID should be ", employeeID, employeeContract.getEmployeeID());
    }

    @Test
    public void testSetECEmployeeID() throws Exception {
        employeeContract.setEmployeeID(newEmployeeID);
        assertEquals("EmployeeIDs should be equal", newEmployeeID, employeeContract.getEmployeeID());
    }

    @Test
    public void testGetECClinicID() throws Exception {
        assertEquals("ClinicIDs should be equal", clinicID, employeeContract.getClinicID());
    }

    @Test
    public void testSetECClinicID() throws Exception {
        employeeContract.setClinicID(newClinicID);
        assertEquals("ClinicIDs should be equal", newClinicID, employeeContract.getClinicID());
    }


    @Test
    public void testGetECDate() throws Exception {
        assertEquals("Dates should be equal", date, employeeContract.getDate());
    }

    @Test
    public void testSetECDate() throws Exception {
        employeeContract.setDate(newDate);
        assertEquals("Dates should be equal", newDate, employeeContract.getDate());
    }
}