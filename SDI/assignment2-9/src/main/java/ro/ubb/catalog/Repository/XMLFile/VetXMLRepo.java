package ro.ubb.catalog.Repository.XMLFile;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.Vet;

import org.w3c.dom.Element;
import java.util.Optional;

public class VetXMLRepo extends XMLRepo<Long, Vet> {
    public VetXMLRepo(Validator<Vet> validator, String fn) {
        super(validator, fn);
    }

    @Override
    protected void saveToFile(Vet entity) {
        Element newVet = this.document.createElement(this.getXMLEntityTag());
        newVet.setAttribute("id", String.valueOf(entity.getId()));

        Element fn = this.document.createElement("firstName");
        fn.appendChild(this.document.createTextNode(String.valueOf(entity.getFirstName())));
        newVet.appendChild(fn);

        Element ln = this.document.createElement("lastName");
        ln.appendChild(this.document.createTextNode(String.valueOf(entity.getLastName())));
        newVet.appendChild(ln);

        Element salary = this.document.createElement("salary");
        salary.appendChild(this.document.createTextNode(String.valueOf(entity.getSalary())));
        newVet.appendChild(salary);

        Element rating = this.document.createElement("rating");
        rating.appendChild(this.document.createTextNode(String.valueOf(entity.getRating())));
        newVet.appendChild(rating);

        Element date = this.document.createElement("date");
        date.appendChild(this.document.createTextNode(String.valueOf(entity.getDate())));
        newVet.appendChild(date);

        document.getDocumentElement().appendChild(newVet);
    }

    @Override
    protected Vet parseXMLEntity(Element element) {
        Long id = Long.valueOf(element.getAttribute("id"));

        String fn = element.getElementsByTagName("firstName").item(0).getTextContent();
        String ln = element.getElementsByTagName("lastName").item(0).getTextContent();
        String sal = element.getElementsByTagName("salary").item(0).getTextContent();
        String rat = element.getElementsByTagName("rating").item(0).getTextContent();
        String date = element.getElementsByTagName("date").item(0).getTextContent();

        Vet v = new Vet(fn, ln, Integer.parseInt(sal), Integer.parseInt(rat), date);
        v.setId(id);

        return v;
    }

    @Override
    protected String getXMLEntityTag() {
        return "vet";
    }

    @Override
    public Optional<Vet> save(Vet entity) throws ValidatorException {
        Optional<Vet> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile();
        return Optional.empty();
    }

    @Override
    public Optional<Vet> delete(Long id) {
        Optional<Vet> opt = super.delete(id);
        saveToFile();
        return opt;

    }

    @Override
    public Optional<Vet> update(Vet v) {
        Optional<Vet> opt = super.update(v);
        saveToFile();
        return opt;

    }
}