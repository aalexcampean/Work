using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcademicInfoAPI.Data.Config
{
    public class ApplicationDbContext : IdentityDbContext<ApplicationUser, IdentityRole, string>
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
    : base(options)
        {
            
        }
        public DbSet<Course> Courses { get; set; }
        public DbSet<AcademicYear> AcademicYear { get; set; }
        public DbSet<Group> Group { get; set; }
        public DbSet<Student> Student { get; set; }
        public DbSet<Teacher> Teacher { get; set; }
        public DbSet<UserCourseGrade> UserCourses { get; set; }
        public DbSet<Curriculum> Curriculums { get; set; }
        public DbSet<ContractOfStudy> ContractsOfStudies { get; set; }


        protected override void OnModelCreating(ModelBuilder builder)
        {
            builder.Entity<AcademicYear>().HasKey(item => item.ID);
            builder.Entity<ContractOfStudy>().HasKey(item => item.ID);
            builder.Entity<Course>().HasKey(item => item.ID);
            builder.Entity<Curriculum>().HasKey(item => item.ID);
            builder.Entity<Group>().HasKey(item => item.ID);
            builder.Entity<Student>().HasKey(item => item.ID);
            builder.Entity<Teacher>().HasKey(item => item.ID);
            builder.Entity<UserCourseGrade>().HasKey(item => new { item.CourseID, item.ContractID });
            
            builder.Entity<Course>().HasOne(p => p.Curriculum).WithMany(b => b.Courses).HasForeignKey(p => p.CurriculumID);
            builder.Entity<Course>().HasOne(p => p.Teacher).WithMany(b => b.Courses).HasForeignKey(p => p.TeacherID);
            builder.Entity<UserCourseGrade>().HasOne(p => p.Course).WithMany(b => b.UserCourses).HasForeignKey(p => p.CourseID);
            builder.Entity<UserCourseGrade>().HasOne(p => p.Contract).WithMany(b => b.UserCourses).HasForeignKey(p => p.ContractID);
            builder.Entity<ContractOfStudy>().HasOne(p => p.User).WithMany(b => b.Contracts).HasForeignKey(p =>p.UserID);
            builder.Entity<ContractOfStudy>().HasOne(p => p.Year).WithMany(b => b.Contracts).HasForeignKey(p =>p.YearID);
            builder.Entity<Group>().HasOne(p => p.Year).WithMany(b => b.Groups).HasForeignKey(p =>p.YearID);
            builder.Entity<Student>().HasOne(p => p.Group).WithMany(b => b.Students).HasForeignKey(p =>p.GroupID);
            builder.Entity<Student>().HasOne(p => p.User).WithMany(b => b.StudentRoles).HasForeignKey(p =>p.UserID);
            builder.Entity<Teacher>().HasOne(p => p.User).WithMany(b => b.TeacherRoles).HasForeignKey(p => p.UserID);
            
            base.OnModelCreating(builder);
        }

    }
}
