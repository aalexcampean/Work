using server.Model;
using server.Repository;

namespace server.Service;

public class ProjectService
{
    private readonly ProjectRepository _projectRepository;

    public ProjectService(ProjectRepository projectRepository)
    {
        _projectRepository = projectRepository;
    }
    
    public List<ProjectModel> GetAllProjects()
    {
        return _projectRepository.GetAllProjects();
    }
    
    public List<ProjectModel> GetProjectsByMember(string memberName)
    {
        return _projectRepository.GetProjectsByMember(memberName);
    }

    public void AddMemberToProject(string memberName, List<string> projects)
    {
        _projectRepository.AddMemberToProject(memberName, projects);
    }
}