package ro.ubb.catalog.Repository.XMLFile;

import org.w3c.dom.Element;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.EmployeePet;

import java.util.Optional;

public class EmployeePetXMLRepository extends XMLRepo<Long, EmployeePet>{
    public EmployeePetXMLRepository(Validator<EmployeePet> validator, String fn) {
        super(validator, fn);
    }

    @Override
    protected void saveToFile(EmployeePet entity) {
        Element newSurgery = this.document.createElement(this.getXMLEntityTag());
        newSurgery.setAttribute("id", String.valueOf(entity.getId()));

        Element employeeId = this.document.createElement("employeeId");
        employeeId.appendChild(this.document.createTextNode(String.valueOf(entity.getEmployeeId())));
        newSurgery.appendChild(employeeId);

        Element petId = this.document.createElement("petId");
        petId.appendChild(this.document.createTextNode(String.valueOf(entity.getPetId())));
        newSurgery.appendChild(petId);

        Element typeOfAction = this.document.createElement("typeOfAction");
        typeOfAction.appendChild(this.document.createTextNode(String.valueOf(entity.getTypeOfAction())));
        newSurgery.appendChild(typeOfAction);

        Element date = this.document.createElement("date");
        date.appendChild(this.document.createTextNode(String.valueOf(entity.getDate())));
        newSurgery.appendChild(date);

        document.getDocumentElement().appendChild(newSurgery);
    }

    @Override
    protected EmployeePet parseXMLEntity(Element element) {
        Long id = Long.valueOf(element.getAttribute("id"));
        String employeeId = element.getElementsByTagName("employeeId").item(0).getTextContent();
        String petId = element.getElementsByTagName("petId").item(0).getTextContent();
        String typeOfAction = element.getElementsByTagName("typeOfAction").item(0).getTextContent();
        String date = element.getElementsByTagName("date").item(0).getTextContent();
        EmployeePet ep = new EmployeePet(Integer.parseInt(employeeId), Integer.parseInt(petId), typeOfAction, date);
        ep.setId(id);
        return ep;
    }

    @Override
    protected String getXMLEntityTag() {
        return "employeePet";
    }

    @Override
    public Optional<EmployeePet> save(EmployeePet entity) throws ValidatorException {
        Optional<EmployeePet> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile();
        return Optional.empty();
    }

    @Override
    public Optional<EmployeePet> delete (Long id)  {
        Optional<EmployeePet> opt=super.delete(id);
        saveToFile();
        return opt;
    }
    @Override
    public Optional<EmployeePet> update (EmployeePet employeePet){
        Optional<EmployeePet> opt=super.update(employeePet);
        saveToFile();
        return opt;
    }
}