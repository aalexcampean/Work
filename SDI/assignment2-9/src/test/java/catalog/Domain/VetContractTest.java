package catalog.Domain;

import junit.framework.TestCase;
import ro.ubb.catalog.Domain.VetContract;

import java.time.LocalDate;

public class VetContractTest extends TestCase {

    private static final int vetID = 1;
    private static final int clinicID = 1;
    private static final int vetIDNew = 2;
    private static final int clinicIDNew = 2;
    private static final LocalDate contractDate = LocalDate.parse("2022-04-04");
    private static final LocalDate contractDateNew = LocalDate.parse("2022-04-05");
    private VetContract vetContract;

    public void setUp() throws Exception {
        vetContract = new VetContract(vetID, clinicID, contractDate);
        vetContract.setId(1L);
    }

    public void tearDown() throws Exception {
        vetContract = null;
    }

    public void testGetVetID() {
        assertEquals(vetContract.getVetID(), vetID);
    }

    public void testSetVetID() {
        vetContract.setVetID(vetIDNew);
        assertEquals(vetContract.getVetID(), vetIDNew);
    }

    public void testGetClinicID() {
        assertEquals(vetContract.getClinicID(), clinicID);
    }

    public void testSetClinicID() {
        vetContract.setClinicID(clinicIDNew);
        assertEquals(vetContract.getClinicID(), clinicIDNew);
    }

    public void testGetContractDate() {
        assertEquals(vetContract.getContractDate(), contractDate);
    }

    public void testSetContractDate() {
        vetContract.setContractDate(contractDateNew);
        assertEquals(vetContract.getContractDate(), contractDate);
    }
}