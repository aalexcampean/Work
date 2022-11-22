using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Config
{
    public class ContractOfStudy
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int ID { get; set; }
        public string UserID { get; set; }
        public int YearID { get; set; }
        public bool IsSigned { get; set; }
        public ApplicationUser User { get; set; }
        public AcademicYear Year { get; set; }
        public virtual ICollection<UserCourseGrade> UserCourses { get; set; }
    }
}
