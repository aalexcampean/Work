package ro.ubb.catalog.Repository.XMLFile;

import org.w3c.dom.Element;
import ro.ubb.catalog.Domain.Owner;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;

import java.util.Optional;

public class OwnerXMLRepo extends XMLRepo<Long, Owner> {
    public OwnerXMLRepo(Validator<Owner> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    protected void saveToFile(Owner entity) {
        Element newOwner = this.document.createElement(this.getXMLEntityTag());
        newOwner.setAttribute("id", String.valueOf(entity.getId()));

        Element fn = this.document.createElement("firstName");
        fn.appendChild(this.document.createTextNode(String.valueOf(entity.getFirstName())));
        newOwner.appendChild(fn);

        Element ln = this.document.createElement("lastName");
        ln.appendChild(this.document.createTextNode(String.valueOf(entity.getLastName())));
        newOwner.appendChild(ln);

        document.getDocumentElement().appendChild(newOwner);
    }

    @Override
    protected Owner parseXMLEntity(Element element) {
        Long id = Long.valueOf(element.getAttribute("id"));

        String fn = element.getElementsByTagName("firstName").item(0).getTextContent();
        String ln = element.getElementsByTagName("lastName").item(0).getTextContent();

        Owner o = new Owner(fn, ln);
        o.setId(id);

        return o;
    }

    @Override
    protected String getXMLEntityTag() {
        return "owner";
    }

    @Override
    public Optional<Owner> save(Owner entity) throws ValidatorException {
        Optional<Owner> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile();
        return Optional.empty();
    }

    @Override
    public Optional<Owner> delete(Long id) {
        Optional<Owner> opt = super.delete(id);
        saveToFile();
        return opt;

    }

    @Override
    public Optional<Owner> update(Owner o) {
        Optional<Owner> opt = super.update(o);
        saveToFile();
        return opt;
    }
}
