using System.ComponentModel.DataAnnotations.Schema;

namespace dotNetTemplate.Data;

public class Person
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    public string Name { get; set; }
    public int Age { get; set; }
    public string Gender { get; set; }
    public ICollection<Channel> Channels { get; set; }
}