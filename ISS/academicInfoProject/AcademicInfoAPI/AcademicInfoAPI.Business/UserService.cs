using AcademicInfoAPI.Data.Config;
using AcademicInfoAPI.Data.Models;
using AcademicInfoAPI.Data.Repository;
using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Business
{
    public class UserService
    {
        private readonly UserRepository userRepository;
        private readonly CourseRepository courseRepository;
        private readonly AcademicYearRepository academicYearRepository;
        private readonly ContractRepository contractRepository;
        private readonly StudentRepository studentRepository;
        private readonly GroupRepository groupRepository;

        public UserService(UserRepository userRepository, AcademicYearRepository yearRepository, CourseRepository courseRepository, ContractRepository contractRepository, StudentRepository studentRepository, GroupRepository groupRepository)
        {
            this.userRepository = userRepository;
            this.courseRepository = courseRepository;
            this.academicYearRepository = yearRepository;
            this.contractRepository = contractRepository;
            this.studentRepository = studentRepository;
            this.groupRepository = groupRepository;
        }
        
        public StudentModel MapToStudentModel(Student student)
        {
            UserProfileModel userProfile = userRepository.GetUserModelByID(student.UserID);
            return new StudentModel
            {
                FirstName = userProfile.FirstName,
                LastName = userProfile.LastName,
                GradeAverage = GetStudentAverage(student.ID),
                Group = student.GroupID,
                Year = student.Group.Year.Year
            };
        }
        
        public StudentCourseModel MapToStudentCourseModel(Student student, int courseID)
        {
            UserProfileModel userProfile = userRepository.GetUserModelByID(student.UserID);
            return new StudentCourseModel
            {
                ID = student.ID,
                FirstName = userProfile.FirstName,
                LastName = userProfile.LastName,
                GradeAverage = GetStudentAverage(student.ID),
                Group = student.GroupID,
                Year = student.Group.Year.Year,
                CourseID = courseID,
                Grade = courseRepository.GetStudentGrade(student.ID, courseID)
            };
        }
        public List<StudentModel> GetStudentsByYear(int yearID)
        {
            var students = studentRepository.GetStudentsByYear(yearID)
                .Select(student => MapToStudentModel(student)).ToList();
            students.Sort(Comparer<StudentModel>.Create((i1, i2) => i1.GradeAverage.CompareTo(i2.GradeAverage)));
            students.Reverse();
            return students;
        }
        public List<StudentModel> GetStudentsByGroup(int yearID)
        {
            var students = studentRepository.GetStudentsByGroup(yearID).AsEnumerable()
                .Select(student => MapToStudentModel(student)).ToList();
            students.Sort();
            students.Reverse();
            return students;
        }
        public List<StudentCourseModel> GetStudentsByCourse(int courseID)
        {
            return studentRepository.GetStudentsByCourse(courseID)
                .Select(student => MapToStudentCourseModel(student, courseID)).ToList();
        }
        
        public decimal GetStudentAverage(int studentID)
        {
            return studentRepository.GetStudentAverage(studentID);
        }

        public UserProfileModel GetAuthenticatedUser(string username)
        {
            return userRepository.GetUserModelByUsername(username);
        }

        public UserProfileModel UpdateUser(string loggedUsername, UserProfileModel user)
        {
            return userRepository.UpdateUser(loggedUsername, user);
        }

        public void EnrollStudent(int year, string username)
        {
            ApplicationUser user = userRepository.GetUser(username);
            if (user.Contracts != null)
            {
                if (user.Contracts.Count >= 2)
                {
                    throw new Exception("Student can be enrolled to maximum 2 years!");
                }
                if (user.Contracts.Where(item => item.Year.Year == year).Any())
                {
                    throw new Exception("Student is already enrolled!");
                }
            }
            AcademicYear academicYear = academicYearRepository.Get(year);
            ContractOfStudy contractOfStudy = new ContractOfStudy { UserID = user.Id, YearID = academicYear.ID };

            contractRepository.Add(contractOfStudy);
            Group group = groupRepository.GetFirstAvailableGroup(academicYear.ID);
            Student student = new Student { UserID = user.Id };
            student.GroupID = group.ID;
            studentRepository.Add(student);

        }

        public void CheckEnrollStudent(int year, string username)
        {
            ApplicationUser user = userRepository.GetUser(username);
            if (user.Contracts != null)
            {
                if (user.Contracts.Where(item => item.Year.Year == year).Any())
                {
                    throw new Exception("Student is already enrolled!");
                }
                if (user.Contracts.Count >= 2)
                {
                    throw new Exception("Student can be enrolled to maximum 2 years!");
                }
            }

        }

        public void SignContract(string loggedUsername, int yearId, List<CourseModel> courses)
        {
            contractRepository.Sign(loggedUsername, yearId, courses);
        }
    }
}
