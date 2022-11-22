package catalog.Domain;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import ro.ubb.catalog.Domain.Surgery;

import static org.junit.Assert.assertEquals;

public class SurgeryTest {
    private static final Long ID = 1L;
    private static final Long NEW_ID = 2L;
    private static final int petId = 1;
    private static final int vetId = 1;
    private static final int newPetId = 2;
    private static final int newVetId = 2;
    private static final String surgeryDate = "04-06-2021";
    private static final String newSurgeryDate = "12-10-2021";
    private static final String surgeryType = "dental";
    private static final String newSurgeryType = "tumor";
    private Surgery surgery;

    @Before
    public void setUp() throws Exception {
        surgery = new Surgery(petId, vetId, surgeryDate, surgeryType);
        surgery.setId(ID);
    }

    @After
    public void tearDown() throws Exception {
        surgery = null;
    }

    @Test
    public void testGetId() throws Exception {
        assertEquals("Ids should be equal", ID, surgery.getId());
    }

    @Test
    public void testSetId() throws Exception {
        surgery.setId(NEW_ID);
        assertEquals("Ids should be equal", NEW_ID, surgery.getId());
    }

    @Test
    public void testGetSurgeryPetId() throws Exception {
        assertEquals("PetId should be ", petId, surgery.getPetId());
    }
    @Test
    public void testGetVetLName() throws Exception {
        assertEquals("VetId should be ", vetId, surgery.getVetId());
    }

    @Test
    public void testSetSurgeryPetId() throws Exception {
        surgery.setPetId(newPetId);
        assertEquals("PetIds should be equal", newPetId, surgery.getPetId());
    }

    @Test
    public void testGetSurgeryVetId() throws Exception {
        assertEquals("VetIds should be equal", vetId, surgery.getVetId());
    }

    @Test
    public void testSetSurgeryVetId() throws Exception {
        surgery.setVetId(newVetId);
        assertEquals("VetIds should be equal", newVetId, surgery.getVetId());
    }

    @Test
    public void testGetSurgeryDate() throws Exception {
        assertEquals("Surgery dates should be equal", surgeryDate, surgery.getSurgeryDate());
    }

    @Test
    public void testSetSurgeryDate() throws Exception {
        surgery.setSurgeryDate(newSurgeryDate);
        assertEquals("Surgery dates should be equal", newSurgeryDate, surgery.getSurgeryDate());
    }

    @Test
    public void testGetSurgeryType() throws Exception {
        assertEquals("Surgery types should be equal", surgeryType, surgery.getSurgeryType());
    }

    @Test
    public void testSetSurgeryType() throws Exception {
        surgery.setSurgeryType(newSurgeryType);
        assertEquals("Surgery types should be equal", newSurgeryType, surgery.getSurgeryType());
    }
}