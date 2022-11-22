using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AcademicInfoAPI.Data.Config;

namespace AcademicInfoAPI.Data.Models
{
    public class CourseModel
    {
        
        public int Id { get; set; }
        public string Name { get; set; }
        public int NoOfCredits { get; set; }

        public bool isOptional { get; set; }
        public int CurriculumID { get; set; }
        public int TeacherID { get; set; }
    }
}
