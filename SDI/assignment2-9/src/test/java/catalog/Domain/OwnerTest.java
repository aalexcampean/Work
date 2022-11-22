package catalog.Domain;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import ro.ubb.catalog.Domain.Owner;

import static org.junit.Assert.assertEquals;

public class OwnerTest {
    private static final Long ID = 1L;
    private static final Long NEW_ID = 2L;
    private static final String firstName = "fn1";
    private static final String lastName = "ln1";
    private static final String newfn ="Fn1";
    private static final String newln ="Fn1";
    private Owner o;

    @Before
    public void setUp() throws Exception {
        o = new Owner(firstName,lastName);
        o.setId(ID);
    }

    @After
    public void tearDown() throws Exception {
        o=null;
    }

    @Test
    public void testGetOwnerFName() throws Exception {
        assertEquals("Name should be ", firstName, o.getFirstName());
    }
    @Test
    public void testGetOwnerLName() throws Exception {
        assertEquals("Name should be ", lastName, o.getLastName());
    }

    @Test
    public void testSetOwnerName() throws Exception {
        o.setFirstName(newfn);
        assertEquals("First Names should be equal", newfn, o.getFirstName());
    }
    @Test
    public void testSetOwnerLName() throws Exception {
        o.setLastName(newln);
        assertEquals("Last Names should be equal", newln, o.getLastName());
    }

    @Test
    public void testGetId() throws Exception {
        assertEquals("Ids should be equal", ID, o.getId());
    }

    @Test
    public void testSetId() throws Exception {
        o.setId(NEW_ID);
        assertEquals("Ids should be equal", NEW_ID, o.getId());
    }
}
