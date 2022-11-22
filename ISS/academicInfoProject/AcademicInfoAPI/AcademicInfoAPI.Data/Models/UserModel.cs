using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Models
{
    public class UserProfileModel
    {
        [Required]
        [MinLength(3)]
        public string FirstName { get; set; }
        [Required]
        [MinLength(3)]
        public string LastName { get; set; }
        [Required]
        [MinLength(3)]
        public string Email { get; set; }
        [Required]
        [MinLength(3)]
        public string PhoneNumber { get; set; }

    }
}
