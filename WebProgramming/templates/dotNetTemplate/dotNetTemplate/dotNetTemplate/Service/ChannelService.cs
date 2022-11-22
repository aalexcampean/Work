using dotNetTemplate.Model;
using dotNetTemplate.Repository;

namespace dotNetTemplate.Service;

public class ChannelService
{
    private readonly ChannelRepository _channelRepository;

    public ChannelService(ChannelRepository channelRepository)
    {
        _channelRepository = channelRepository;
    }
    
    public List<ChannelModel> GetAllChannels()
    {
        return _channelRepository.GetAllChannels();
    }
    
    public List<ChannelModel> GetChannelsByOwner(string ownerName)
    {
        return _channelRepository.GetChannelsByOwner(ownerName);
    }
    
    public List<ChannelModel> GetChannelsByUser(string userName)
    {
        return _channelRepository.GetChannelsByUser(userName);
    }

    public void SubscribeUser(string userName, string channelName)
    {
        _channelRepository.SubscribeUser(userName, channelName);
    }
}