using AcademicInfoAPI.Business;
using AcademicInfoAPI.Data.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.IdentityModel.Tokens;
using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Web.Controllers
{
    [AllowAnonymous]
    [Route("api/authentication")]
    public class AuthenticationController : Controller
    {
        private readonly AuthenticationService authenticationService;
        private readonly IConfiguration configuration;

        public AuthenticationController(AuthenticationService authenticationService, IConfiguration configuration)
        {
            this.authenticationService = authenticationService;
            this.configuration = configuration;
        }
        [HttpPost]
        [Route("login")]
        public async Task<IActionResult> Login([FromBody] AuthenticationModel data)
        {
            if (await authenticationService.CheckUser(data))
            {
                var roles = await authenticationService.GetRoles(data.Username);
                var claims = new List<Claim>();

                claims.Add(new Claim("username", data.Username));
                claims.Add(new Claim(JwtRegisteredClaimNames.Sub, data.Username));
                claims.Add(new Claim(JwtRegisteredClaimNames.Jti, Guid.NewGuid().ToString()));
                foreach (var role in roles)
                {
                    claims.Add(new Claim(ClaimTypes.Role, role));
                }
                
                var key = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(configuration.GetValue<string>("Jwt:Key")));
                var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);

                return Ok(new JwtSecurityTokenHandler().WriteToken(new JwtSecurityToken(
                    issuer: configuration.GetValue<string>("Jwt:Issuer"),
                    audience: configuration.GetValue<string>("Jwt:Audience"),
                    expires: DateTime.UtcNow.AddHours(6),
                    claims: claims,
                    signingCredentials: creds
                )));
            }
            return Unauthorized();
        }
        [HttpPost]
        [Route("register")]
        public async Task<IActionResult> Register([FromBody] AuthenticationModel data)
        {
            if (await authenticationService.CreateUser(data))
            {
                return await Login(data);
            }
            return BadRequest();
        }
        [HttpPost]
        [Route("role/{role}")]
        public async Task<IActionResult> AddRole(string role)
        {
            if (await authenticationService.AddRole(role))
            {
                return Ok();
            }
            return BadRequest();
        }
    }
}
