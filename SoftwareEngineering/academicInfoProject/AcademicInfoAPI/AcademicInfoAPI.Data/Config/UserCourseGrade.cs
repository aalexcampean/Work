using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Config
{
    public class UserCourseGrade
    {
        public int CourseID { get; set; }
        public int ContractID { get; set; }
        public int Grade { get; set; }

        public Course Course { get; set; }
        public ContractOfStudy Contract { get; set; }
    }
}
