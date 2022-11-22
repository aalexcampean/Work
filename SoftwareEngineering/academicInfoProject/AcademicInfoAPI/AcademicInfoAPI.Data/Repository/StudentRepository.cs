using AcademicInfoAPI.Data.Config;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace AcademicInfoAPI.Data.Repository
{
    public class StudentRepository
    {
        private readonly ApplicationDbContext dbContext;
        public StudentRepository(ApplicationDbContext dbContext)
        {
            this.dbContext = dbContext;
        }

        public void Add(Student student)
        {
            dbContext.Student.Add(student);
            dbContext.SaveChanges();
        }

        public List<Student> GetStudentsByYear(int yearID)
        {
            var x = dbContext.Student.Include(item => item.User).Include(item => item.Group).ThenInclude(item => item.Year).Where(item => item.Group.YearID == yearID).ToList();
            return x;
        }
      
        public List<Student> GetStudentsByGroup(int groupID)
        {
            return dbContext.Student.Include(item => item.User).Include(item => item.Group).ThenInclude(item => item.Year).Where(item => item.Group.ID == groupID).ToList();
        }
        
        public List<Student> GetStudentsByCourse(int courseID)
        {
            List<ApplicationUser> users = dbContext.Users.Where(user => user.Contracts.Any(contract => contract.UserCourses
                    .Any(userCourse => userCourse.CourseID == courseID)))
                .ToList();
            
            return dbContext.Student.Include(item => item.User).Include(item => item.Group).ThenInclude(item => item.Year)
                .Where(student => users.Any(user => user.Id == student.UserID))
                .ToList();
        }

        public decimal GetStudentAverage(int studentID)
        {
            Student student = dbContext.Student.Where(item => item.ID == studentID).FirstOrDefault();

            var grades = dbContext.UserCourses
                .Where(item => item.Contract.UserID == student.UserID && item.Contract.YearID == student.Group.YearID)
                
                .Select(item => item.Grade).ToList();

            if (grades.Count > 0)
            {
                return (decimal) grades.Average(item => item);
            }

            return 0;
        }
    }
}
