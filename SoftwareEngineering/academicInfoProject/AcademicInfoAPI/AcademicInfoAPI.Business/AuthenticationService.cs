using AcademicInfoAPI.Data.Config;
using AcademicInfoAPI.Data.Models;
using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Business
{
    public class AuthenticationService
    {
        private readonly UserManager<ApplicationUser> userManager;
        private readonly RoleManager<IdentityRole> roleManager;

        public AuthenticationService(UserManager<ApplicationUser> userManager, RoleManager<IdentityRole> roleManager)
        {
            this.userManager = userManager;
            this.roleManager = roleManager;
        }
        public async Task<bool> CheckUser(AuthenticationModel data)
        {
            ApplicationUser user = await userManager.FindByNameAsync(data.Username);
            if (await userManager.CheckPasswordAsync(user, data.Password))
            {
                return true;
            }
            return false;
        }

        public async Task<ApplicationUser> GetUser(string userName)
        {
            return await userManager.FindByNameAsync(userName); 
        }

        public async Task<IList<string>> GetRoles(string username)
        {
            ApplicationUser user = await userManager.FindByNameAsync(username);
            return await userManager.GetRolesAsync(user);
        }

        public async Task<bool> CreateUser(AuthenticationModel data)
        {
            var user = new ApplicationUser { UserName = data.Username };
            var result = await userManager.CreateAsync(user, data.Password);
            return result.Succeeded;
        }

        public async Task<bool> AddRole(string role)
        {
            var res = await roleManager.CreateAsync(new IdentityRole(role));
            return res.Succeeded;
        }
    }
}
