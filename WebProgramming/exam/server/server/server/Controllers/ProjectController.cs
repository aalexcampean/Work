using Microsoft.AspNetCore.Mvc;
using server.Model;
using server.Service;

namespace dotNetTemplate.Migrations;

[ApiController]
[Route("api")]
public class HomeController : Controller
{
    private readonly ProjectService _projectService;

    public HomeController(ProjectService projectService)
    {
        _projectService = projectService;
    }

    [HttpGet]
    public IActionResult Index()
    {
        return Json(_projectService.GetAllProjects());
    }

    [HttpGet]
    [Route("member/{memberName}")]
    public IActionResult GetProjectsByMember(string memberName)
    {
        return Json(_projectService.GetProjectsByMember(memberName));
    }

    [HttpPut("member/{memberName}")]
    public IActionResult SubscribeUser(string memberName, [FromBody] List<string> projects)
    {
        try
        {
            _projectService.AddMemberToProject(memberName, projects);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }

        return Ok();
    }
}