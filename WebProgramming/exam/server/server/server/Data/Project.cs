using System.ComponentModel;
using System.ComponentModel.DataAnnotations.Schema;

namespace server.Data;

public class Project
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    [DefaultValue(null)]
    public int ProjectManagerID { get; set; }
    public string Name { get; set; }
    [DefaultValue(null)]
    public string Description { get; set; }
    [DefaultValue(null)]
    public string Members { get; set; }
    public SoftwareDeveloper ProjectManager { get; set; }
}