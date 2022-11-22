using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;

namespace AcademicInfoAPI.Data.Config;

public class Teacher
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    public string UserID { get; set; }
    public ApplicationUser User { get; set; }
    public virtual ICollection<Course> Courses { get; set; }
}