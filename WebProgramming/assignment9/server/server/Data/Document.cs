using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace server.Data;

public class Document
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    
    [Required(ErrorMessage = "Title is required")]
    [StringLength(maximumLength:50, MinimumLength = 2)]
    public string title { get; set; }
    
    [Required(ErrorMessage = "Author is required")]
    [StringLength(maximumLength:50, MinimumLength = 2)]
    public string author { get; set; }
    
    [Required(ErrorMessage = "NumberOfPages is required")]
    public int numberOfPages { get; set; }
    
    [Required(ErrorMessage = "Type is required")]
    [StringLength(maximumLength:50, MinimumLength = 2)]
    public string type { get; set; }
    
    [Required(ErrorMessage = "Format is required")]
    [StringLength(maximumLength:50, MinimumLength = 2)]
    public string format { get; set; }
}