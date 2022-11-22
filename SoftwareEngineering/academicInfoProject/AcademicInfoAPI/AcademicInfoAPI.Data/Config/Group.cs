using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;

namespace AcademicInfoAPI.Data.Config;

public class Group
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    public int YearID { get; set; }
    public AcademicYear Year { get; set; }
    public virtual ICollection<Student> Students { get; set; }
}