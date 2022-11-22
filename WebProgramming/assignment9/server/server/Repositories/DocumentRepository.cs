using Microsoft.EntityFrameworkCore;
using server.Data;
using server.Models;

namespace server.Repositories;

public class DocumentRepository
{
    private readonly DocumentManagerDbContext _context;

    public DocumentRepository(DocumentManagerDbContext context)
    {
        _context = context;
    }

    public Document GetDocumentById(int documentId)
    {
        return _context.Documents.AsNoTracking().FirstOrDefault(doc => doc.ID == documentId);
    }

    public List<DocumentModel> GetAllDocuments()
    {
        return _context.Documents.Select(doc => new DocumentModel
        {
            Id = doc.ID,
            Title = doc.title,
            Author = doc.author,
            NumberOfPages = doc.numberOfPages,
            Format = doc.format,
            Type = doc.type
        }).ToList();
    }

    public List<DocumentModel> GetDocumentsByFormat(string format)
    {
        return _context.Documents.Where(doc => doc.format == format).Select(doc => new DocumentModel
            {
                Id = doc.ID,
                Title = doc.title,
                Author = doc.author,
                NumberOfPages = doc.numberOfPages,
                Format = doc.format,
                Type = doc.type
            }).ToList();
        }

    public List<DocumentModel> GetDocumentsByType(string type)
    {
        return _context.Documents.Where(doc => doc.type == type).Select(doc => new DocumentModel
        {
            Id = doc.ID,
            Title = doc.title,
            Author = doc.author,
            NumberOfPages = doc.numberOfPages,
            Format = doc.format,
            Type = doc.type
        }).ToList();
    }

    public DocumentModel AddDocument(DocumentModel document)
    {
        Document newDocument = new Document
        {
            title = document.Title,
            author = document.Author,
            numberOfPages = document.NumberOfPages,
            format = document.Format,
            type = document.Type
        };
        _context.Documents.Add(newDocument);
        _context.SaveChanges();
        return document;
    }

    public DocumentModel DeleteDocument(int documentId)
    {
        Document deletedDocument = GetDocumentById(documentId);
        _context.Documents.Remove(deletedDocument);
        _context.SaveChanges();

        return new DocumentModel
        {
            Id = deletedDocument.ID,
            Title = deletedDocument.title,
            Author = deletedDocument.author,
            NumberOfPages = deletedDocument.numberOfPages,
            Format = deletedDocument.format,
            Type = deletedDocument.type
        };
    }

    public DocumentModel UpdateDocument(DocumentModel document)
    {
        Document oldDocument = GetDocumentById(document.Id);
        Document updateDocument = new Document
        {
            ID = document.Id,
            title = document.Title,
            author = document.Author,
            numberOfPages = document.NumberOfPages,
            format = document.Format,
            type = document.Type
        };
        _context.Documents.Update(updateDocument);
        _context.SaveChanges();

        return new DocumentModel
        {
            Id = oldDocument.ID,
            Title = oldDocument.title,
            Author = oldDocument.author,
            NumberOfPages = oldDocument.numberOfPages,
            Format = oldDocument.format,
            Type = oldDocument.type
        };
    }
}