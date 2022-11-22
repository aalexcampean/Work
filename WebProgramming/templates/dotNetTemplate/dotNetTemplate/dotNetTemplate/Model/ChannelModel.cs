namespace dotNetTemplate.Model;

public class ChannelModel
{
    public int Id { get; set; }
    public int OwnerId { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public string Subscribers { get; set; }
}