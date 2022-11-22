package catalog.Repository;

import org.junit.Assert;
import org.junit.Ignore;
import org.junit.Test;
import ro.ubb.catalog.Domain.Clinic;
import ro.ubb.catalog.Repository.TextFile.ClinicFileRepository;

public class ClinicFileRepositoryTest {
    private ClinicFileRepository repository;

    @Ignore
    @Test
    public void testAll() throws Exception {
        testSave();
        testDelete();
        testUpdate();
    }

    @Ignore
    @Test
    public void testSave() throws Exception {
        for (int i = 1; i < 5; i++) {
            Long id = Long.parseLong(String.valueOf(i));
            String name = "name" + String.valueOf(i);
            String location = "location" + String.valueOf(i);
            Integer yearFounded = 2010 + i;
            Clinic clinic = new Clinic(name, location, yearFounded);
            clinic.setId(id);
            this.repository.save(clinic);
        }
        Assert.assertEquals(this.repository.size(), 4);
    }

    @Ignore
    @Test
    public void testDelete() {
        this.repository.delete(2L);
        Assert.assertEquals(this.repository.size(), 3);

        this.repository.delete(3L);
        Assert.assertEquals(this.repository.size(), 2);
    }

    @Ignore
    @Test
    public void testUpdate() {
        Long id = 4L;
        String updatedName = "name20";
        String updatedLocation = "location20";
        Integer updatedYearFounded = 2010 + 20;
        Clinic clinic = new Clinic(updatedName, updatedLocation, updatedYearFounded);
        clinic.setId(id);
        this.repository.update(clinic);

        Assert.assertEquals(this.repository.size(), 2);
    }
}
