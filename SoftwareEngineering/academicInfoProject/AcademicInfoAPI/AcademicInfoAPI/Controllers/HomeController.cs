using AcademicInfoAPI.Business;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Web.Controllers
{
    [Authorize]
    [Route("api")]
    public class HomeController : Controller
    {
        private readonly AuthenticationService authenticationService;

        public HomeController(AuthenticationService authenticationService)
        {
            this.authenticationService = authenticationService;
        }

        [HttpGet]
        public async Task<IActionResult> Index()
        {
            var userId = User.FindFirstValue(ClaimTypes.NameIdentifier);
            var user = await authenticationService.GetUser(userId);
            var roles = await authenticationService.GetRoles(user.UserName);

            return Ok(roles);
        }
        [HttpGet]
        [Route("admin")]
        [Authorize(Roles ="admin")]
        public IActionResult Admin()
        {
            return Ok("admin");
        }
    }
}
