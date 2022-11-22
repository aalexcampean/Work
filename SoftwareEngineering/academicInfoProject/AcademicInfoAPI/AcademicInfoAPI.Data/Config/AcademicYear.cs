using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;

namespace AcademicInfoAPI.Data.Config;

public class AcademicYear
{
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public int ID { get; set; }
    public int Year { get; set; }
    public virtual ICollection<ContractOfStudy> Contracts { get; set; }
    public virtual ICollection<Group> Groups { get; set; }
}