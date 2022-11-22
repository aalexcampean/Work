using AcademicInfoAPI.Data.Config;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Config
{
    public class Course
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int ID { get; set; }
        public int TeacherID { get; set; }
        public string Name { get; set; }
        public int NoOfCredits { get; set; }

        public bool IsOptional { get; set; }
        public int CurriculumID { get; set; }
        public Teacher Teacher { get; set; }
        public Curriculum Curriculum { get; set; }
        public virtual ICollection<UserCourseGrade> UserCourses { get; set; }
    }
}
