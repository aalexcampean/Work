using dotNetTemplate.Model;
using dotNetTemplate.Service;
using Microsoft.AspNetCore.Mvc;

namespace dotNetTemplate.Migrations;

[ApiController]
[Route("api")]
public class HomeController : Controller
{
    private readonly ChannelService _channelService;

    public HomeController(ChannelService channelService)
    {
        _channelService = channelService;
    }

    [HttpGet]
    public IActionResult Index()
    {
        return Json(_channelService.GetAllChannels());
    }

    [HttpGet]
    [Route("owner/{ownerName}")]
    public IActionResult GetChannelsByOwner(string ownerName)
    {
        return Json(_channelService.GetChannelsByOwner(ownerName));
    }

    [HttpGet]
    [Route("user/{userName}")]
    public IActionResult GetChannelsByUser(string userName)
    {
        return Json(_channelService.GetChannelsByUser(userName));
    }
    
    [HttpPut("user/{userName}")]
    public IActionResult SubscribeUser(string userName,[FromBody] ChannelModel data)
    {
        try
        {
            _channelService.SubscribeUser(userName, data.Name);
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }
        return Ok();
    }
}