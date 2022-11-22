using System.ComponentModel.DataAnnotations.Schema;
using System.Threading.Channels;

namespace server.Data;

public class SoftwareDeveloper
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    public string Name { get; set; }
    public int Age { get; set; }
    public string Skills { get; set; }
    public ICollection<Project> Projects { get; set; }
}