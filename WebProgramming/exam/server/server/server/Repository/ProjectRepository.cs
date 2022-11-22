using Microsoft.EntityFrameworkCore;
using server.Data;
using server.Model;

namespace server.Repository;

public class ProjectRepository
{
    private readonly ProjectsDbContext _context;

    public ProjectRepository(ProjectsDbContext context)
    {
        _context = context;
    }
    
    public List<ProjectModel> GetAllProjects()
    {
        return _context.Projects
            .Select(project => new ProjectModel
            {
                Id = project.ID,
                ProjectManagerId = project.ProjectManagerID,
                Name = project.Name,
                Description = project.Description,
                Members = project.Members
            })
            .ToList();
    }
    
    public List<ProjectModel> GetProjectsByMember(string memberName)
    {
        return _context.Projects.Where(project => project.Members.Contains(memberName))
            .Select(project => new ProjectModel
            {
                Id = project.ID,
                ProjectManagerId = project.ProjectManagerID,
                Name = project.Name,
                Description = project.Description,
                Members = project.Members
            })
            .ToList();
    }
    
    public int IsAMember(string memberName, Project project)
    {
        return project.Members.IndexOf($"{memberName},");
    }
    
    public void AddMemberToProject(string memberName, List<string> projects)
    {
        SoftwareDeveloper softwareDeveloper = _context.SoftwareDevelopers.AsNoTracking()
            .FirstOrDefault(developer => developer.Name == memberName);
        
        if (softwareDeveloper == null) return;
        
        projects.ForEach(receivedProjectName =>
        {
            Project project = _context.Projects.AsNoTracking().FirstOrDefault(project => project.Name == receivedProjectName);
            if (project != null)
            {
                int startIndex = IsAMember(memberName, project);
                if (startIndex != -1) return;
                
                project.Members = $"{project.Members}{memberName}, ";

                _context.Update(project);
                _context.SaveChanges();
            }
            else
            {
                Project newProject = new Project
                {
                    ProjectManagerID = softwareDeveloper.ID,
                    Name = receivedProjectName,
                    Description = "",
                    Members = $"{memberName}, "
                };
                _context.Projects.Add(newProject);
                _context.SaveChanges();
            }
        });

        
    }
}