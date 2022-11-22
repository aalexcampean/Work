using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Config
{
    public class CurriculumContract
    {
        public int CurriculumID { get; set; }
        public int ContractID { get; set; }
        public Curriculum Curriculum { get; set; }
        public ContractOfStudy Contract { get; set; }
    }
}
