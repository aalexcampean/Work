using AcademicInfoAPI.Data.Config;
using AcademicInfoAPI.Data.Models;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Repository
{
    public class UserRepository
    {
        private readonly ApplicationDbContext _context;
        public UserRepository(ApplicationDbContext context)
        {
            _context = context;
        }
        
        public UserProfileModel GetUserModelByID(string id)
        {
            ApplicationUser user = _context.Users.Where(item => item.Id == id).FirstOrDefault();
            return new UserProfileModel {FirstName = user.FirstName, LastName = user.LastName , Email = user.Email, PhoneNumber = user.PhoneNumber};
        }

        public UserProfileModel GetUserModelByUsername(string username)
        {
            ApplicationUser user = _context.Users.Where(item => item.UserName == username).FirstOrDefault();
            return new UserProfileModel {FirstName = user.FirstName, LastName = user.LastName , Email = user.Email, PhoneNumber = user.PhoneNumber};
        }

        public UserProfileModel UpdateUser(string loggedUsername, UserProfileModel user)
        {
            ApplicationUser appUser = _context.Users.FirstOrDefault(item => item.UserName == loggedUsername);
            appUser.FirstName = user.FirstName;
            appUser.LastName = user.LastName;
            appUser.Email = user.Email;
            appUser.PhoneNumber = user.PhoneNumber;
            _context.Entry(appUser).State = Microsoft.EntityFrameworkCore.EntityState.Modified;
            _context.SaveChanges();
            return GetUserModelByUsername(loggedUsername);
        }

        public ApplicationUser GetUser(string username)
        {
            return _context.Users.Include(item => item.StudentRoles).ThenInclude(item => item.Group).ThenInclude(item => item.Year).Include(item => item.Contracts).ThenInclude(item => item.Year).FirstOrDefault(item => item.UserName == username);
        }

        // public void AddCourses(string username, int curriculumID)
        // {
        //     ApplicationUser appUser = _context.Users.FirstOrDefault(item => item.UserName == username);
        //     List<UserCourseGrade> courses = _context.Courses
        //         .Where(course => course.CurriculumID == curriculumID)
        //         .Select(item => new UserCourseGrade { CourseID=item.ID, UserID = appUser.Id, Grade = -1})
        //         .ToList();
        //     _context.UserCourses.AddRange(courses);
        //     _context.SaveChanges();
        // }
        public ApplicationUser GetUserByStudentID(int studentId)
        {
            return _context.Users.Where(user => user.StudentRoles.Any(student => student.ID == studentId))
                .FirstOrDefault();
        }
    }
}
