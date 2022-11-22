package catalog.Domain;

import junit.framework.TestCase;
import ro.ubb.catalog.Domain.Clinic;

public class ClinicTest extends TestCase {
    private static final Long ID = 1L;
    private static final String clinicName = "HappyClinic";
    private static final String clinicLocation = "Aurel Vlaicu 20";
    private static final int clinicYearFounded = 2015;
    private Clinic clinic;

    public void setUp() throws Exception {
        this.clinic = new Clinic(clinicName, clinicLocation, clinicYearFounded);
        this.clinic.setId(ID);
    }

    public void tearDown() throws Exception {
        clinic = null;
    }

    public void testTestGetName() {
        assertEquals(this.clinic.getName(), clinicName);
    }

    public void testGetLocation() {
        assertEquals(this.clinic.getLocation(), clinicLocation);
    }

    public void testGetYearFounded() {
        assertEquals(this.clinic.getYearFounded(), clinicYearFounded);
    }

    public void testTestSetName() {
        this.clinic.setName("New Clinic Name");
        assertEquals(this.clinic.getName(), "New Clinic Name");
    }

    public void testSetLocation() {
        this.clinic.setLocation("New Clinic Location");
        assertEquals(this.clinic.getLocation(), "New Clinic Location");
    }

    public void testSetYearFounded() {
        this.clinic.setYearFounded(2016);
        assertEquals(this.clinic.getYearFounded(), 2016);
    }
}