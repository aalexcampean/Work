using System.ComponentModel.DataAnnotations.Schema;

namespace dotNetTemplate.Data;

public class Channel
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    public int OwnerId { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public string Subscribers { get; set; }
    public Person Owner { get; set; }
}