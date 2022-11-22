using AcademicInfoAPI.Data.Config;
using AcademicInfoAPI.Data.Models;
using AcademicInfoAPI.Data.Repository;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Business
{
    public class CourseService
    {
        private readonly CourseRepository courseRepository;
        private readonly AcademicYearRepository yearRepository;
        private readonly GroupRepository groupRepository;
        private readonly ContractRepository contractRepository;
        private readonly UserRepository userRepository;
        public CourseService(CourseRepository courseRepository, AcademicYearRepository yearRepository,
             GroupRepository groupRepository, ContractRepository contractRepository, UserRepository userRepository)
        {
            this.courseRepository = courseRepository;
            this.yearRepository = yearRepository;
            this.groupRepository = groupRepository;
            this.contractRepository = contractRepository;
            this.userRepository = userRepository;
        }

        public object GetAllGroups()
        {
            return this.groupRepository.GetAll();
        }

        public List<AcademicYearModel> GetUserYears(string username)
        {
            return this.userRepository.GetUser(username).StudentRoles.Select(item => new AcademicYearModel
            {
                ID = item.Group.Year.ID,
                Year = item.Group.Year.Year
            }).ToList();
        }

        public List<Group> GetAllGroupsByYear(int yearID)
        {
            return this.groupRepository.GetAllByYear(yearID);
        }

        public List<CourseGradeModel> GetCoursesByUsernameAndYear(string username, int year)
        {
            return courseRepository.GetCoursesByUsernameAndYear(username, year);
        }

        public List<AcademicYear> GetAllYears()
        {
            return yearRepository.GetAll();
        }

        public List<CourseModel> GetAllCourses()
        {
            return courseRepository.GetAllCourses();
        }

        public List<CourseGradeModel> GetCoursesByUsername(string username)
        {
            return courseRepository.GetCoursesByUsername(username);
        }

        public List<CourseModel> GetCoursesByYear(int year)
        {
            return courseRepository.GetCoursesByYear(year);
        }

        public CourseModel AddOptionalCourse(string loggedUsername, CourseModel data)
        {
            if (courseRepository.GetAllCourses().Any(course => course.Name == data.Name))
            {
                throw new Exception("A course with this name already exists!"); 
            }
            return courseRepository.AddCourse(loggedUsername, data);
        }

        public GradeUserModel GradeStudent(GradeUserModel data)
        {
            ApplicationUser user = this.userRepository.GetUserByStudentID(data.StudentID);
            ContractOfStudy contract = this.contractRepository.Get(user.UserName);
            UserCourseGrade userCourseGrade = new UserCourseGrade
            {
                ContractID = contract.ID,
                CourseID = data.CourseID,
                Grade = data.Grade
            };
            userCourseGrade = this.courseRepository.AddGrade(userCourseGrade);
            return new GradeUserModel
            {
                StudentID = data.StudentID,
                CourseID = userCourseGrade.CourseID,
                Grade = userCourseGrade.Grade
            };
        }
    }
}
