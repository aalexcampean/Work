package ro.ubb.catalog.Repository.XMLFile;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import ro.ubb.catalog.Domain.BaseEntity;
import ro.ubb.catalog.Domain.Validators.Validator;
import ro.ubb.catalog.Repository.TextFile.FileRepository;

import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.*;

public abstract class XMLRepo <ID extends Serializable, T extends BaseEntity<ID>> extends FileRepository<ID, T> {
    protected DocumentBuilder documentBuilder;
    protected Document document;

    public XMLRepo(Validator<T> validator,String fileName) {
        super(validator, fileName);
        this.init_xml();
        this.loadData();
    }

    @Override
    protected void loadData() {
        NodeList list = this.document.getElementsByTagName(this.getXMLEntityTag());

        for (int listIndex = 0; listIndex < list.getLength(); listIndex++) {
            Node node = list.item(listIndex);

            T entity = this.parseXMLEntity((Element) node);

            this.save(entity);
        }
    }

    private void init_xml() {
        try {
            DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
            documentBuilderFactory.setFeature(XMLConstants.FEATURE_SECURE_PROCESSING, true);

            this.documentBuilder = documentBuilderFactory.newDocumentBuilder();
            this.document = this.documentBuilder.parse(new File(this.getFileName()));

            this.document.getDocumentElement().normalize();
        } catch (ParserConfigurationException | IOException | SAXException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void saveToFile() {
        this.document = this.documentBuilder.newDocument();
        Element rootElement = document.createElement("repository");
        this.document.appendChild(rootElement);

        this.getEntities().values().forEach(this::saveToFile);

        try {
            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.setOutputProperty(OutputKeys.METHOD, "xml");
            transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
            transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");

            transformer.transform(
                    new DOMSource(this.document),
                    new StreamResult(new FileOutputStream(this.getFileName()))
            );
        } catch (TransformerException | FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    protected abstract void saveToFile(T entity);
//    public abstract Optional<T> update(T entity);
//    public abstract Optional<T> delete(ID entityID);


    protected abstract T parseXMLEntity(Element element);
    protected abstract String getXMLEntityTag();
}