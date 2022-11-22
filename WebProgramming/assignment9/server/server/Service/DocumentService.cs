using server.Models;
using server.Repositories;

namespace server.Service;

public class DocumentService
{
    private readonly DocumentRepository _documentRepository;

    public DocumentService(DocumentRepository documentRepository)
    {
        _documentRepository = documentRepository;
    }

    public List<DocumentModel> GetAllDocuments()
    {
        return _documentRepository.GetAllDocuments();
    }
    
    public List<DocumentModel> GetDocumentsByFormat(string format)
    {
        return _documentRepository.GetDocumentsByFormat(format);
    }
    
    public List<DocumentModel> GetDocumentsByType(string type)
    {
        return _documentRepository.GetDocumentsByType(type);
    }

    public DocumentModel AddDocument(DocumentModel document)
    {
        return _documentRepository.AddDocument(document);
    }
    
    public DocumentModel DeleteDocument(int documentId)
    {
        return _documentRepository.DeleteDocument(documentId);
    }
    
    public DocumentModel UpdateDocument(DocumentModel document)
    {
        return _documentRepository.UpdateDocument(document);
    }
}