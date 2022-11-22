using AcademicInfoAPI.Data.Config;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AcademicInfoAPI.Data.Models;
using Microsoft.EntityFrameworkCore;

namespace AcademicInfoAPI.Data.Repository
{
    public class ContractRepository
    {

        private readonly ApplicationDbContext _context;
        public ContractRepository(ApplicationDbContext context)
        {
            _context = context;
        }

        public ContractOfStudy Get(string username)
        {
            return _context.ContractsOfStudies.FirstOrDefault(item => item.User.UserName == username);
        }
        public ContractOfStudy GetByYear(string username, int yearId)
        {
            return _context.ContractsOfStudies.Include(item => item.UserCourses).FirstOrDefault(item => item.User.UserName == username && item.YearID == yearId);
        }

        public ContractOfStudy Add(ContractOfStudy contract)
        {
            _context.ContractsOfStudies.Add(contract);
            _context.SaveChanges();
            return contract;
        }
        
        public ContractOfStudy Sign(string username, int yearId, List<CourseModel> courses)
        {
            ContractOfStudy userContract = GetByYear(username, yearId);
            
            courses.Select(item => new UserCourseGrade 
            {
                CourseID = item.Id,
                ContractID = GetByYear(username, yearId).ID,
                Grade = 0
            }).ToList().ForEach(item => { userContract.UserCourses.Add(item); });

            userContract.IsSigned = true;
            _context.SaveChanges();

            return userContract;
        }
    }
}
