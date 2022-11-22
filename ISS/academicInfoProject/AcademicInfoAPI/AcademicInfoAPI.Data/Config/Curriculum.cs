using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Config
{
    public class Curriculum
    {
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int ID { get; set; }
        public int Year { get; set; }
        public ICollection<Course> Courses { get; set; }
    }
}
