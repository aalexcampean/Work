package ro.ubb.catalog.Repository.XMLFile;

import org.w3c.dom.Element;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.Surgery;

import java.util.Optional;

public class SurgeryXMLRepository extends XMLRepo<Long, Surgery>{
    public SurgeryXMLRepository(Validator<Surgery> validator, String fn) {
        super(validator, fn);
    }

    @Override
    protected void saveToFile(Surgery entity) {
        Element newSurgery = this.document.createElement(this.getXMLEntityTag());
        newSurgery.setAttribute("id", String.valueOf(entity.getId()));

        Element petId = this.document.createElement("petId");
        petId.appendChild(this.document.createTextNode(String.valueOf(entity.getPetId())));
        newSurgery.appendChild(petId);

        Element vetId = this.document.createElement("vetId");
        vetId.appendChild(this.document.createTextNode(String.valueOf(entity.getVetId())));
        newSurgery.appendChild(vetId);

        Element surgeryDate = this.document.createElement("surgeryDate");
        surgeryDate.appendChild(this.document.createTextNode(String.valueOf(entity.getSurgeryDate())));
        newSurgery.appendChild(surgeryDate);

        Element surgeryType = this.document.createElement("surgeryType");
        surgeryType.appendChild(this.document.createTextNode(String.valueOf(entity.getSurgeryType())));
        newSurgery.appendChild(surgeryType);

        document.getDocumentElement().appendChild(newSurgery);
    }

    @Override
    protected Surgery parseXMLEntity(Element element) {
        Long id = Long.valueOf(element.getAttribute("id"));
        String petId = element.getElementsByTagName("petId").item(0).getTextContent();
        String vetId = element.getElementsByTagName("vetId").item(0).getTextContent();
        String surgeryDate = element.getElementsByTagName("surgeryDate").item(0).getTextContent();
        String surgeryType = element.getElementsByTagName("surgeryType").item(0).getTextContent();
        Surgery s = new Surgery(Integer.parseInt(petId), Integer.parseInt(vetId), surgeryDate, surgeryType);
        s.setId(id);
        return s;
    }

    @Override
    protected String getXMLEntityTag() {
        return "surgery";
    }

    @Override
    public Optional<Surgery> save(Surgery entity) throws ValidatorException {
        Optional<Surgery> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile();
        return Optional.empty();
    }

    @Override
    public Optional<Surgery> delete (Long id)  {
        Optional<Surgery> opt=super.delete(id);
        saveToFile();
        return opt;
    }
    @Override
    public Optional<Surgery> update (Surgery v){
        Optional<Surgery> opt=super.update(v);
        saveToFile();
        return opt;
    }
}