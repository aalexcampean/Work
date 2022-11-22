using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using AcademicInfoAPI.Business;
using AcademicInfoAPI.Data.Config;
using AcademicInfoAPI.Data.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace AcademicInfoAPI.Web.Controllers
{
    [Authorize]
    [Route("api/course")]
    public class CourseController : Controller
    {
        private readonly CourseService courseService;

        public CourseController(CourseService courseService)
        {
            this.courseService = courseService;
        }
        [HttpGet]
        public IActionResult Index()
        {
            return Json(courseService.GetAllCourses());
        }

         [HttpGet]
         [Route("{username}")]
         public IActionResult GetCoursesByUsername(string username)
         {
             return Json(courseService.GetCoursesByUsername(username));
         }

        [HttpGet]
        [Route("grades/{username}/{year}")]
        public IActionResult GetCoursesGradesByUsernameAndYear(string username, int year)
        {
            return Json(courseService.GetCoursesByUsernameAndYear(username,year));
        }

        [HttpGet]
        [Route("curriculum/{year}")]
        public IActionResult GetCoursesByYearOfStudy(int year)
        {
            return Json(courseService.GetCoursesByYear(year));
        }
        
        [HttpPost]
        [Route("optional")]
        public IActionResult AddOptionalCourse([FromBody] CourseModel data)
        {
            if (ModelState.IsValid)
            {
                var loggedUsername = User.Claims.AsEnumerable().Where(item => item.Type == "username").Select(item => item.Value).FirstOrDefault();
                CourseModel course = courseService.AddOptionalCourse(loggedUsername, data);
                return Ok(course);
            }
            return BadRequest(ModelState.Values.Aggregate(
                new List<string>(),
                (a, c) =>
                {
                    a.AddRange(c.Errors.Select(r => r.ErrorMessage));
                    return a;
                },
                a => a
            ));
        }

        [HttpPost]
        [Route("grade")]
        public IActionResult GradeStudent([FromBody] GradeUserModel data)
        {
            if (ModelState.IsValid)
            {
                
                 return Ok(courseService.GradeStudent(data));
            }
            return BadRequest(ModelState.Values.Aggregate(
                new List<string>(),
                (a, c) =>
                {
                    a.AddRange(c.Errors.Select(r => r.ErrorMessage));
                    return a;
                },
                a => a
            ));
        }
    }
}
