using Microsoft.AspNetCore.Mvc;
using server.Models;
using server.Service;

namespace server.Controllers;

[ApiController]
[Route("api")]
public class HomeController : Controller
{
    private readonly DocumentService _documentService;

    public HomeController(DocumentService documentService)
    {
        _documentService = documentService;
    }

    [HttpGet]
    public IActionResult Index()
    {
        return Json(_documentService.GetAllDocuments());
    }

    [HttpGet]
    [Route("format/{format}")]
    public IActionResult GetDocumentsByFormat(string format)
    {
        return Json(_documentService.GetDocumentsByFormat(format));
    }

    [HttpGet]
    [Route("type/{type}")]
    public IActionResult GetDocumentsByType(string type)
    {
        return Json(_documentService.GetDocumentsByType(type));
    }
    
    [HttpPost]
    [Route("document")]
    public IActionResult AddDocument([FromBody] DocumentModel data)
    {
        DocumentModel documentModel;
        try
        {
             documentModel = _documentService.AddDocument(data);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }
        return Json(documentModel);
    }
    
    [HttpDelete("document/{id}")]
    public IActionResult DeleteDocument(int id)
    {
        DocumentModel documentModel;
        try
        {
            documentModel = _documentService.DeleteDocument(id);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }
        return Json(documentModel);
    }
    
    [HttpPut("document/{id}")]
    public IActionResult UpdateDocument(int id, [FromBody] DocumentModel data)
    {
        DocumentModel documentModel;
        try
        {
            documentModel = _documentService.UpdateDocument(data);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }
        return Json(documentModel);
    }
}