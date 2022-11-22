using AcademicInfoAPI.Business;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace AcademicInfoAPI.Web.Controllers
{
    [Authorize]
    [Route("api/years")]
    public class YearsController : Controller
    {
        private readonly CourseService courseController;
        public YearsController(CourseService courseController)
        {
            this.courseController = courseController;
        }

        [HttpGet]
        [Route("")]
        public IActionResult Index()
        {
            return Json(this.courseController.GetAllYears());
        }

        [HttpGet]
        [Route("{yearID}")]
        public IActionResult GetGroupsFromYear(int yearID)
        {
            return Json(this.courseController.GetAllGroupsByYear(yearID));
        }

        [HttpGet]
        [Route("groups")]
        public IActionResult GetGroups()
        {
            return Json(this.courseController.GetAllGroups());
        }

        [HttpGet]
        [Route("user/{username}")]
        public IActionResult GetUserYears(string username)
        {
            return Json(this.courseController.GetUserYears(username));
        }
    }
}
