using Microsoft.EntityFrameworkCore;

namespace server.Data;

public class ProjectsDbContext : DbContext
{
    public ProjectsDbContext(DbContextOptions<ProjectsDbContext> options) : base(options)
    {
    }

    public DbSet<SoftwareDeveloper> SoftwareDevelopers { get; set; }
    public DbSet<Project> Projects { get; set; }

    protected override void OnModelCreating(ModelBuilder builder)
    {
        builder.Entity<SoftwareDeveloper>().HasKey(developer => developer.ID);
        builder.Entity<Project>().HasKey(channel => channel.ID);

        builder.Entity<Project>().HasOne(project => project.ProjectManager)
            .WithMany(developer => developer.Projects)
            .HasForeignKey(project => project.ProjectManagerID);
        
        base.OnModelCreating(builder);
    }
}