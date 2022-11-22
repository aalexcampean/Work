package ro.ubb.catalog.Repository.XMLFile;

import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import ro.ubb.catalog.Domain.Clinic;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Domain.Validators.ValidatorException;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.Optional;
import java.util.stream.IntStream;

public class ClinicXMLRepository extends XMLRepo<Long, Clinic> {

    public ClinicXMLRepository(Validator<Clinic> validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    protected void saveToFile(Clinic clinic) {
        Element newVet = this.document.createElement(this.getXMLEntityTag());
        newVet.setAttribute("id", String.valueOf(clinic.getId()));

        Element name = this.document.createElement("name");
        name.appendChild(this.document.createTextNode(String.valueOf(clinic.getName())));
        newVet.appendChild(name);

        Element location = this.document.createElement("location");
        location.appendChild(this.document.createTextNode(String.valueOf(clinic.getLocation())));
        newVet.appendChild(location);

        Element yearFounded = this.document.createElement("yearFounded");
        yearFounded.appendChild(this.document.createTextNode(String.valueOf(clinic.getYearFounded())));
        newVet.appendChild(yearFounded);

        document.getDocumentElement().appendChild(newVet);
    }

    @Override
    protected Clinic parseXMLEntity(Element element) {
        Long id = Long.valueOf(element.getAttribute("id"));

        String name = element.getElementsByTagName("name").item(0).getTextContent();
        String location = element.getElementsByTagName("location").item(0).getTextContent();
        String yearFounded = element.getElementsByTagName("yearFounded").item(0).getTextContent();

        Clinic clinic = new Clinic(name, location, Integer.parseInt(yearFounded));
        clinic.setId(id);

        return clinic;
    }

    @Override
    protected String getXMLEntityTag() {
        return "clinic";
    }

    @Override
    public Optional<Clinic> save(Clinic clinic) throws ValidatorException {
        Optional<Clinic> optional = super.save(clinic);
        if (optional.isPresent()) {
            return optional;
        }
        saveToFile();
        return Optional.empty();
    }

    @Override
    public Optional<Clinic> delete(Long id) {
        Optional<Clinic> clinic = findOne(id);
        NodeList clinics = this.document.getElementsByTagName("clinic");
        try {
            IntStream.range(0, clinics.getLength())
                    .mapToObj(clinics::item)
                    .filter(xmlClinic -> !String.valueOf(id).equals(xmlClinic.getAttributes().getNamedItem("id").getTextContent()));

            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(this.document);
            StreamResult result = new StreamResult(new File(this.getFileName()));
            transformer.transform(source, result);

        } catch (Exception e) {
            e.printStackTrace();
        }
        return clinic;
    }

    @Override
    public Optional<Clinic> update(Clinic clinic) {
        NodeList clinics = this.document.getElementsByTagName("clinic");
        try {
            IntStream.range(0, clinics.getLength())
                    .mapToObj(clinics::item)
                    .filter(xmlClinic -> String.valueOf(clinic.getId()).equals(xmlClinic.getAttributes().getNamedItem("id").getTextContent()))
                    .forEach(xmlClinic -> {
                        xmlClinic.getChildNodes().item(0).setTextContent(clinic.getName());
                        xmlClinic.getChildNodes().item(1).setTextContent(clinic.getLocation());
                        xmlClinic.getChildNodes().item(2).setTextContent(String.valueOf(clinic.getYearFounded()));
                    });

            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(this.document);
            StreamResult result = new StreamResult(new File(this.getFileName()));
            transformer.transform(source, result);

        } catch (Exception e) {
            e.printStackTrace();
        }
        return Optional.ofNullable(clinic);
    }
}
