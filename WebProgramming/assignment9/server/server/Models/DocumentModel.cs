namespace server.Models;

public class DocumentModel
{
    public int Id { get; set; }
    public string Title { get; set; }
    public string Author { get; set; }
    public int NumberOfPages { get; set; }
    public string Type { get; set; }
    public string Format { get; set; }
}