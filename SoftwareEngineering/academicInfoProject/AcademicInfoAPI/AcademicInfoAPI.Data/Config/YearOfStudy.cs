using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Config
{
    public class YearOfStudy
    {
        public int Year { get; set; }
        public int CurriculumID { get; set; }
        public Curriculum Curriculum { get; set; }
    }
}
