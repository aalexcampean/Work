package ro.ubb.catalog.Repository.XMLFile;

import org.w3c.dom.Element;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;
import ro.ubb.catalog.Domain.*;

import java.time.LocalDate;
import java.util.Optional;

public class EmployeeContractXMLRepository extends XMLRepo<Long, EmployeeContract>{
    public EmployeeContractXMLRepository(Validator<EmployeeContract> validator, String fn) {
        super(validator, fn);
    }

    @Override
    protected void saveToFile(EmployeeContract entity) {
        Element newEC = this.document.createElement(this.getXMLEntityTag());
        newEC.setAttribute("id", String.valueOf(entity.getId()));

        
        Element date = this.document.createElement("date");
        date.appendChild(this.document.createTextNode(String.valueOf(entity.getDate())));
        newEC.appendChild(date);

        Element eId = this.document.createElement("employeeID");
        eId.appendChild(this.document.createTextNode(String.valueOf(entity.getEmployeeID())));
        newEC.appendChild(eId);

        Element cId = this.document.createElement("clinicID");
        cId.appendChild(this.document.createTextNode(String.valueOf(entity.getClinicID())));
        newEC.appendChild(cId);


        document.getDocumentElement().appendChild(newEC);
    }

    @Override
    protected EmployeeContract parseXMLEntity(Element element) {
        Long id = Long.valueOf(element.getAttribute("id"));
        String employeeId = element.getElementsByTagName("employeeID").item(0).getTextContent();
        String clinicId = element.getElementsByTagName("clinicID").item(0).getTextContent();
        String date = element.getElementsByTagName("date").item(0).getTextContent();
        EmployeeContract ec = new EmployeeContract(LocalDate.parse(date),Integer.parseInt(employeeId), Integer.parseInt(clinicId));
        ec.setId(id);
        return ec;
    }

    @Override
    protected String getXMLEntityTag() {
        return "employeeContract";
    }

    @Override
    public Optional<EmployeeContract> save(EmployeeContract entity) throws ValidatorException {
        Optional<EmployeeContract> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile();
        return Optional.empty();
    }

    @Override
    public Optional<EmployeeContract> delete (Long id)  {
        Optional<EmployeeContract> opt=super.delete(id);
        saveToFile();
        return opt;
    }
    @Override
    public Optional<EmployeeContract> update (EmployeeContract v){
        Optional<EmployeeContract> opt=super.update(v);
        saveToFile();
        return opt;
    }
}
