using AcademicInfoAPI.Data.Config;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Repository
{
    public class GroupRepository
    {
        private readonly ApplicationDbContext dbContext;
        public GroupRepository(ApplicationDbContext dbContext)
        {
            this.dbContext = dbContext;
        }

        public Group GetFirstAvailableGroup(int yearID)
        {
            Group group = dbContext.Group.Where(item => item.Students.Count < 30 && item.Year.ID == yearID).FirstOrDefault();
            if (group == null)
            {
                group = new Group { YearID = yearID };
                dbContext.Group.Add(group);
                dbContext.SaveChanges();
                return dbContext.Group.Where(item => item.Students.Count < 30 && item.Year.ID == yearID).FirstOrDefault();
            }
            return group;


        }

        public List<Group> GetAllByYear(int yearID)
        {
            return this.dbContext.Group.Where(item => item.YearID == yearID).ToList();
        }

        public object GetAll()
        {
            return this.dbContext.Group.ToList();
        }
    }
}
