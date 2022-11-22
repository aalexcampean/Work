using AcademicInfoAPI.Business;
using AcademicInfoAPI.Data.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AcademicInfoAPI.Web.Controllers
{
    [Authorize]
    [Route("api/profile")]
    public class ProfileController : Controller
    {
        public UserService userService { get; set; }
        public ProfileController(UserService userService)
        {
            this.userService = userService;
        }
        [HttpGet]
        public IActionResult Index()
        {
            var loggedUsername = User.Claims.AsEnumerable().Where(item => item.Type == "username").Select(item => item.Value).FirstOrDefault();
            UserProfileModel user = userService.GetAuthenticatedUser(loggedUsername);
            return Json(user);
        }

        [HttpPost]
        public IActionResult UpdateProfile([FromBody] UserProfileModel userModel)
        {
            if (ModelState.IsValid)
            {
                var loggedUsername = User.Claims.AsEnumerable().Where(item => item.Type == "username").Select(item => item.Value).FirstOrDefault();
                UserProfileModel user = userService.UpdateUser(loggedUsername, userModel);
                return Ok(user);
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
        [Route("enroll/{year}")]
        public IActionResult EnrollStudent(int year)
        {

            var loggedUsername = User.Claims.AsEnumerable().Where(item => item.Type == "username").Select(item => item.Value).FirstOrDefault();
            if (!User.Claims.AsEnumerable().Where(item => item.Type == "http://schemas.microsoft.com/ws/2008/06/identity/claims/role" && item.Value == "student").Any())
            {
                return BadRequest("User must be a student!");
            }

            try
            {
                userService.EnrollStudent(year, loggedUsername);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            return Ok();
        }

        [HttpPost]
        [Route("check-enroll/{year}")]
        public IActionResult CheckEnrollStudent(int year)
        {

            var loggedUsername = User.Claims.AsEnumerable().Where(item => item.Type == "username").Select(item => item.Value).FirstOrDefault();
            if (!User.Claims.AsEnumerable().Where(item => item.Type == "http://schemas.microsoft.com/ws/2008/06/identity/claims/role" && item.Value == "student").Any())
            {
                return BadRequest("User must be a student!");
            }

            try
            {
                userService.CheckEnrollStudent(year, loggedUsername);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            return Ok();
        }

        [HttpPost]
        [Route("sign-contract/{yearId}")]
        public IActionResult SignContract(int yearId, [FromBody] List<CourseModel> courses)
        {
            if (courses is null)
            {
                return BadRequest("Select your courses!");
            }

            var loggedUsername = User.Claims.AsEnumerable().Where(item => item.Type == "username").Select(item => item.Value).FirstOrDefault();

            if (!User.Claims.AsEnumerable().Where(item => item.Type == "http://schemas.microsoft.com/ws/2008/06/identity/claims/role" && item.Value == "student").Any())
            {
                return BadRequest("User must be a student!");
            }
            try
            {
                userService.SignContract(loggedUsername, yearId, courses);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }

            return Ok();
        }
    }
}
