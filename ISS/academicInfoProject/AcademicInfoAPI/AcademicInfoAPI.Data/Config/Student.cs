using System.ComponentModel.DataAnnotations.Schema;

namespace AcademicInfoAPI.Data.Config;

public class Student
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    public string UserID { get; set; }
    public int GroupID { get; set; }
    public ApplicationUser User { get; set; }
    public Group Group { get; set; }
}