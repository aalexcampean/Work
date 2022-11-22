using AcademicInfoAPI.Data.Config;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Repository
{
    public class AcademicYearRepository
    {
        private readonly ApplicationDbContext _context;
        public AcademicYearRepository(ApplicationDbContext context)
        {
            _context = context;
        }

         public AcademicYear Get(int year)
         {
             return _context.AcademicYear.FirstOrDefault(item => item.Year == year);
         }

        public List<AcademicYear> GetAll()
        {
            return _context.AcademicYear.ToList();
        }
    }
}
