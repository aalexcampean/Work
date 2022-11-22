namespace server.Model;

public class ProjectModel
{
    public int Id { get; set; }
    public int ProjectManagerId { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public string Members { get; set; }
}