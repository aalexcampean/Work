using Microsoft.EntityFrameworkCore;

namespace dotNetTemplate.Data;

public class SubscriptionsDbContext : DbContext
{
    public SubscriptionsDbContext(DbContextOptions<SubscriptionsDbContext> options) : base(options)
    {
    }

    public DbSet<Person> Persons { get; set; }
    public DbSet<Channel> Channels { get; set; }

    protected override void OnModelCreating(ModelBuilder builder)
    {
        builder.Entity<Person>().HasKey(person => person.ID);
        builder.Entity<Channel>().HasKey(channel => channel.ID);

        builder.Entity<Channel>().HasOne(channel => channel.Owner)
            .WithMany(person => person.Channels)
            .HasForeignKey(channel => channel.OwnerId);
        
        base.OnModelCreating(builder);
    }
}