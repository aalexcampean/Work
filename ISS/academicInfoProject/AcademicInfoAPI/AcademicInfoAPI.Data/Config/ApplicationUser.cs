using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Config
{
    public class ApplicationUser : IdentityUser
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public virtual ICollection<ContractOfStudy> Contracts { get; set; }
        public virtual ICollection<Student> StudentRoles { get; set; }
        public virtual ICollection<Teacher> TeacherRoles { get; set; }
    }
}
