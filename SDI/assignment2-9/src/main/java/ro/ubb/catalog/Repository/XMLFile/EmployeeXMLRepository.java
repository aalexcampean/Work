package ro.ubb.catalog.Repository.XMLFile;

import org.w3c.dom.Element;
import ro.ubb.catalog.Domain.Employee;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;

import java.util.Optional;

public class EmployeeXMLRepository extends XMLRepo<Long, Employee> {

    public EmployeeXMLRepository(Validator<Employee> validator, String fn) {
        super(validator, fn);
    }

    @Override
    protected void saveToFile(Employee entity) {
        Element newEmployee = this.document.createElement(this.getXMLEntityTag());
        newEmployee.setAttribute("id", String.valueOf(entity.getId()));

        Element fn = this.document.createElement("firstName");
        fn.appendChild(this.document.createTextNode(String.valueOf(entity.getFirstName())));
        newEmployee.appendChild(fn);

        Element ln = this.document.createElement("lastName");
        ln.appendChild(this.document.createTextNode(String.valueOf(entity.getLastName())));
        newEmployee.appendChild(ln);

        Element salary = this.document.createElement("salary");
        salary.appendChild(this.document.createTextNode(String.valueOf(entity.getSalary())));
        newEmployee.appendChild(salary);

        Element rating = this.document.createElement("rating");
        rating.appendChild(this.document.createTextNode(String.valueOf(entity.getRating())));
        newEmployee.appendChild(rating);

        Element date = this.document.createElement("date");
        date.appendChild(this.document.createTextNode(String.valueOf(entity.getDate())));
        newEmployee.appendChild(date);

        document.getDocumentElement().appendChild(newEmployee);
    }

    @Override
    protected Employee parseXMLEntity(Element element) {
        Long id = Long.valueOf(element.getAttribute("id"));

        String fn = element.getElementsByTagName("firstName").item(0).getTextContent();
        String ln = element.getElementsByTagName("lastName").item(0).getTextContent();
        String sal = element.getElementsByTagName("salary").item(0).getTextContent();
        String rat = element.getElementsByTagName("rating").item(0).getTextContent();
        String date = element.getElementsByTagName("date").item(0).getTextContent();

        Employee employee = new Employee(fn, ln, Integer.parseInt(sal), Integer.parseInt(rat), date);
        employee.setId(id);

        return employee;
    }

    @Override
    protected String getXMLEntityTag() {
        return "employee";
    }

    @Override
    public Optional<Employee> save(Employee entity) throws ValidatorException {
        Optional<Employee> optional = super.save(entity);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile();
        return Optional.empty();
    }

    @Override
    public Optional<Employee> delete(Long id) {
        Optional<Employee> opt = super.delete(id);
        saveToFile();
        return opt;

    }

    @Override
    public Optional<Employee> update(Employee employee) {
        Optional<Employee> opt = super.update(employee);
        saveToFile();
        return opt;

    }
}
