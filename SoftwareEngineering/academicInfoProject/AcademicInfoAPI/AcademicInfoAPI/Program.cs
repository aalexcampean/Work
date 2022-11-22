using AcademicInfoAPI.Business;
using AcademicInfoAPI.Data.Config;
using AcademicInfoAPI.Data.Repository;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.IdentityModel.Tokens;
using Microsoft.OpenApi.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var builder = WebApplication.CreateBuilder(args);
            ConfigurationManager configuration = builder.Configuration;

            builder.Services.AddCors(options =>
            {

                options.AddDefaultPolicy(policy =>
                {
                    policy.AllowAnyHeader().AllowAnyMethod().AllowAnyOrigin().Build();
                });
            });
            builder.Services.AddDbContext<ApplicationDbContext>(options =>
                  options.UseSqlServer(
                    configuration.GetConnectionString("DefaultConnection")));

            builder.Services.AddTransient<AuthenticationService, AuthenticationService>();
            builder.Services.AddTransient<CourseRepository, CourseRepository>();
            builder.Services.AddTransient<ContractRepository, ContractRepository>();
            builder.Services.AddTransient<AcademicYearRepository, AcademicYearRepository>();
            builder.Services.AddTransient<GroupRepository, GroupRepository>();
            builder.Services.AddTransient<StudentRepository, StudentRepository>();

            builder.Services.AddTransient<CourseService, CourseService>();
            builder.Services.AddTransient<UserRepository, UserRepository>();
            builder.Services.AddTransient<UserService, UserService>();

            builder.Services.AddSwaggerGen(c =>
            {
                c.SwaggerDoc("v1", new OpenApiInfo { Title = "AcademicInfoAPI", Version = "v1" });
            });
            builder.Services.AddIdentity<ApplicationUser, IdentityRole>(
                options => {
                    options.SignIn.RequireConfirmedAccount = false;
                    options.Password.RequireDigit = false;
                    options.Password.RequiredLength = 1;
                    options.Password.RequireLowercase = false;
                    options.Password.RequireNonAlphanumeric = false;
                    options.Password.RequireUppercase = false;
                    options.Password.RequiredUniqueChars = 0;
                }
                )
            .AddEntityFrameworkStores<ApplicationDbContext>();
            builder.Services.AddAuthentication(auth =>
            {
                auth.DefaultAuthenticateScheme = JwtBearerDefaults.AuthenticationScheme;
                auth.DefaultChallengeScheme = JwtBearerDefaults.AuthenticationScheme;
            })
            .AddJwtBearer(options =>
            {
                options.SaveToken = true;
                options.TokenValidationParameters = new TokenValidationParameters
                {
                    ValidateIssuer = true,
                    ValidIssuer = configuration["Jwt:Issuer"],
                    ValidateAudience = true,
                    ValidAudience = configuration["Jwt:Audience"],
                    ValidateIssuerSigningKey = true,
                    IssuerSigningKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(configuration["Jwt:Key"]))
                };
            });
            builder.Services.AddControllers();
            
            var app = builder.Build();

            if (app.Environment.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
                app.UseSwagger();
                app.UseSwaggerUI(c => c.SwaggerEndpoint("/swagger/v1/swagger.json", "AcademicInfoAPI v1"));
            }

            app.UseCors();
            app.UseRouting();
            app.UseDefaultFiles();
            app.UseStaticFiles();
            app.UseAuthentication();
            app.UseAuthorization();

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllerRoute(
                    name: "default",
                    pattern: "{controller=Home}/{action=Index}");

                endpoints.MapFallbackToController("Index", "Fallback");
            });

            app.Run();
        }

       
    }
}
