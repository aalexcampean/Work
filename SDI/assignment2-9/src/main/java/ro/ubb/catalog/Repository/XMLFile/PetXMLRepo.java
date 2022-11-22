package ro.ubb.catalog.Repository.XMLFile;

import org.w3c.dom.Element;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.Pet;


import java.util.Optional;

public class PetXMLRepo extends XMLRepo<Long, Pet> {
    public PetXMLRepo(Validator<Pet> validator, String fn) {
        super(validator, fn);
    }

    @Override
    protected void saveToFile(Pet entity) {
        Element newPet = this.document.createElement(this.getXMLEntityTag());
        newPet.setAttribute("id", String.valueOf(entity.getId()));

        Element fn = this.document.createElement("species");
        fn.appendChild(this.document.createTextNode(String.valueOf(entity.getSpecies())));
        newPet.appendChild(fn);

        Element ln = this.document.createElement("breed");
        ln.appendChild(this.document.createTextNode(String.valueOf(entity.getBreed())));
        newPet.appendChild(ln);

        Element salary = this.document.createElement("petName");
        salary.appendChild(this.document.createTextNode(String.valueOf(entity.getPetName())));
        newPet.appendChild(salary);

        Element rating = this.document.createElement("personId");
        rating.appendChild(this.document.createTextNode(String.valueOf(entity.getPersonId())));
        newPet.appendChild(rating);


        document.getDocumentElement().appendChild(newPet);
    }

    @Override
    protected Pet parseXMLEntity(Element element) {
        Long id = Long.valueOf(element.getAttribute("id"));

        String species = element.getElementsByTagName("species").item(0).getTextContent();
        String breed = element.getElementsByTagName("breed").item(0).getTextContent();
        String petName = element.getElementsByTagName("petName").item(0).getTextContent();
        String personId = element.getElementsByTagName("personId").item(0).getTextContent();

        Pet v = new Pet(species, breed, petName, Integer.parseInt(personId));
        v.setId(id);

        return v;

    }

    @Override
    protected String getXMLEntityTag() {
        return "pet";
    }

    @Override
    public Optional<Pet> save(Pet entity) throws ValidatorException {
        Optional<Pet> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile();
        return Optional.empty();
    }

    @Override
    public Optional<Pet> delete(Long id) {
        Optional<Pet> opt = super.delete(id);
        saveToFile();
        return opt;

    }

    @Override
    public Optional<Pet> update(Pet v) {
        Optional<Pet> opt = super.update(v);
        saveToFile();
        return opt;

    }
}