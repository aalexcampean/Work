using AcademicInfoAPI.Business;
using AcademicInfoAPI.Data.Config;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace AcademicInfoAPI.Web.Controllers
{
    [Authorize]
    [Route("api/students")]
    public class StudentsController : Controller
    {
        private readonly UserService userService;
        public StudentsController(UserService userService)
        {
            this.userService = userService;
        }
        [HttpGet]
        [Route("year/{yearID}")]
        public IActionResult GetStudentsByYear(int yearID)
        {
            return Json(userService.GetStudentsByYear(yearID));
        }

        [HttpGet]
        [Route("group/{groupID}")]
        public IActionResult GetStudentsByGroup(int groupID)
        {
            return Json(userService.GetStudentsByGroup(groupID));
        }
        
        [HttpGet]
        [Route("course/{courseID}")]
        public IActionResult GetStudentsByCourse(int courseID)
        {
            return Json(userService.GetStudentsByCourse(courseID));
        }
        
        [HttpGet]
        [Route("avg/{studentID}")]
        public IActionResult GetStudentAverage(int studentID)
        {
            return Json(userService.GetStudentAverage(studentID));
        }
    }
}
