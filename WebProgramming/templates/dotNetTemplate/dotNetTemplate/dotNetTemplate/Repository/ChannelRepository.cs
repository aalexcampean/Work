using System.Linq;
using System.Reflection.Metadata;
using dotNetTemplate.Data;
using dotNetTemplate.Model;
using Microsoft.EntityFrameworkCore;

namespace dotNetTemplate.Repository;

public class ChannelRepository
{
    private readonly SubscriptionsDbContext _context;

    public ChannelRepository(SubscriptionsDbContext context)
    {
        _context = context;
    }
    
    public List<ChannelModel> GetAllChannels()
    {
        return _context.Channels
            .Select(channel => new ChannelModel
            {
                Id = channel.ID,
                OwnerId = channel.OwnerId,
                Name = channel.Name,
                Description = channel.Description,
                Subscribers = channel.Subscribers
            })
            .ToList();
    }
    
    public List<ChannelModel> GetChannelsByOwner(string ownerName)
    {
        return _context.Channels.Where(channel => channel.Owner.Name == ownerName)
            .Select(channel => new ChannelModel
            {
                Id = channel.ID,
                OwnerId = channel.OwnerId,
                Name = channel.Name,
                Description = channel.Description,
                Subscribers = channel.Subscribers
            })
            .ToList();
    }

    public List<ChannelModel> GetChannelsByUser(string userName)
    {
        return _context.Channels.Where(channel => channel.Subscribers.Contains(userName))
            .Select(channel => new ChannelModel
            {
                Id = channel.ID,
                OwnerId = channel.OwnerId,
                Name = channel.Name,
                Description = channel.Description,
                Subscribers = channel.Subscribers
            })
            .ToList();
    }

    public int IsSubscribed(string userName, Channel channel)
    {
        return channel.Subscribers.IndexOf($"{userName} ");
    }
    
    public void SubscribeUser(string userName, string channelName)
    {
        Channel channel = _context.Channels.AsNoTracking().FirstOrDefault(channel => channel.Name == channelName);
        if (channel != null)
        {
            int startIndex = IsSubscribed(userName, channel);
            DateTime now = DateTime.Now;
            if (startIndex != -1)
            {
                int endIndex = channel.Subscribers.IndexOf(",", startIndex);
                channel.Subscribers = channel.Subscribers.Remove(startIndex, endIndex - startIndex + 2);
            }
            
            channel.Subscribers = $"{channel.Subscribers}{userName} subscribed on: {now.ToString("MMMM dd yyyy")}, ";

            _context.Update(channel);
            _context.SaveChanges();
        }
        else
        {
            throw new Exception("Channel does not exist!");
        }
    }
}