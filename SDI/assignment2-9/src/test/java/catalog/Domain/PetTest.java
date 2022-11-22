package catalog.Domain;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import ro.ubb.catalog.Domain.Pet;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

/**
 * @author olivia.
 */
public class PetTest {
    private static final Long ID = 1L;
    private static final Long NEW_ID = 2L;
    private static final String SPECIES = "dog";
    private static final String NEW_SPECIES = "cat";
    private static final String BREED = "Golden Retriever";
    private static final String NEW_BREED = "new breed";
    private static final String NAME = "petName";
    private static final String NEW_NAME = "newName";
    private static final int PERSON_ID = 1;

    private Pet pet;

    @Before
    public void setUp() throws Exception {
        pet = new Pet(SPECIES,BREED,NAME,PERSON_ID);
        pet.setId(ID);
    }

    @After
    public void tearDown() throws Exception {
        pet=null;
    }

    @Test
    public void testGetPetName() throws Exception {
        assertEquals("Name should be ", NAME, pet.getPetName());
    }

    @Test
    public void testSetPetName() throws Exception {
        pet.setPetName(NEW_NAME);
        assertEquals("Names should be equal", NEW_NAME, pet.getPetName());
    }

    @Test
    public void testGetId() throws Exception {
        assertEquals("Ids should be equal", ID, pet.getId());
    }

    @Test
    public void testSetId() throws Exception {
        pet.setId(NEW_ID);
        assertEquals("Ids should be equal", NEW_ID, pet.getId());
    }

    @Test
    public void testGetSpecies() throws Exception {
        assertEquals("Species should be equal", SPECIES, pet.getSpecies());
    }

    @Test
    public void testSetSpecies() throws Exception {
        pet.setSpecies(NEW_SPECIES);
        assertEquals("Species should be equal", NEW_SPECIES, pet.getSpecies());
    }

    @Test
    public void testGetBreed() throws Exception {
        assertEquals("Breeds should be equal", BREED, pet.getBreed());
    }

    @Test
    public void testSetBreed() throws Exception {
        pet.setBreed(NEW_BREED);
        assertEquals("Breeds should be equal", NEW_BREED, pet.getBreed());
    }
}