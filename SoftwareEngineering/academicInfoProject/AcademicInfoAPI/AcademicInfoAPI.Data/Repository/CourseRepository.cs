using AcademicInfoAPI.Data.Config;
using AcademicInfoAPI.Data.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Repository
{
    public class CourseRepository
    {
        private readonly ApplicationDbContext _context;
        public CourseRepository(ApplicationDbContext context)
        {
            _context = context;
        }

        public int GetStudentGrade(int studentID, int courseID)
        {
            Student student = _context.Student.Where(item => item.ID == studentID).FirstOrDefault();

            return _context.UserCourses
                .Where(userCourse => userCourse.Contract.UserID == student.UserID && userCourse.CourseID == courseID)
                .Sum(item => item.Grade);
        }

        public CourseModel GetCourseModel(string name)
        {
            Course course = _context.Courses.Where(item => item.Name == name).FirstOrDefault();
            return new CourseModel
            {
                Id = course.ID,
                Name = course.Name,
                NoOfCredits = course.NoOfCredits,
                isOptional = course.IsOptional,
                CurriculumID = course.CurriculumID,
                TeacherID = course.TeacherID,
            };
        }
        
        public List<CourseModel> GetAllCourses()
        {
            return _context.Courses.Select(c => new CourseModel
            {
                Id = c.ID,
                Name = c.Name,
                NoOfCredits = c.NoOfCredits,
                isOptional = c.IsOptional
            }).ToList();
        }

        public List<CourseGradeModel> GetCoursesByUsernameAndYear(string username, int year)
        {
            ApplicationUser user = _context.Users.Where(item => item.UserName == username).FirstOrDefault();

            return _context.Courses.Where(item => item.Curriculum.Year == year && item.UserCourses.Where(item => item.Contract.UserID == user.Id).Any()).Select(c => new CourseGradeModel
            {
                Id = c.ID,
                Name = c.Name,
                NoOfCredits = c.NoOfCredits,
                isOptional = c.IsOptional,
                CurriculumID = c.CurriculumID,
                TeacherID = c.TeacherID,
                Grade = c.UserCourses.Where(item => item.Contract.User.UserName == username).Select(c => c.Grade).FirstOrDefault()
            }).ToList();
        }

        public List<CourseModel> GetCoursesByYear(int year)
        {
            return _context.Courses.Where(item => item.Curriculum.Year == year).Select(c => new CourseModel
            {
                Id = c.ID,
                Name = c.Name,
                NoOfCredits = c.NoOfCredits,
                isOptional = c.IsOptional
            }).ToList();
        }

        public List<CourseGradeModel> GetCoursesByUsername(string username)
        {
            ApplicationUser user = _context.Users.Where(item => item.UserName == username).FirstOrDefault();

            return _context.Courses.Where(item => item.UserCourses.Where(item => item.Contract.UserID == user.Id).Any()).Select(c => new CourseGradeModel
            {
                Id = c.ID,
                Name = c.Name,
                NoOfCredits = c.NoOfCredits,
                isOptional = c.IsOptional,
                Grade = c.UserCourses.Where(item => item.Contract.User.UserName == username).Select(c => c.Grade).FirstOrDefault()
            }).ToList();
        }
        public CourseModel AddCourse(string loggedUsername, CourseModel course)
        {
            ApplicationUser appUser = _context.Users.FirstOrDefault(item => item.UserName == loggedUsername);
            Course newCourse = new Course
            {
                TeacherID = course.TeacherID,
                Name = course.Name,
                NoOfCredits = course.NoOfCredits,
                IsOptional = course.isOptional,
                CurriculumID = course.CurriculumID
            };
            _context.Courses.Add(newCourse);
            _context.SaveChanges();
            return GetCourseModel(newCourse.Name);
        }

        public UserCourseGrade AddGrade(UserCourseGrade userCourseGrade)
        {
            _context.UserCourses.Add(userCourseGrade);
            _context.SaveChanges();
            return userCourseGrade;
        }
    }
}
