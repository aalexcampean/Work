using System.Configuration;
using Microsoft.EntityFrameworkCore;

namespace server.Data;

public class DocumentManagerDbContext : DbContext
{
    public DocumentManagerDbContext(DbContextOptions<DocumentManagerDbContext> options) : base(options)
    {
        
    }
    
    public DbSet<Document> Documents { get; set; }
    
    protected override void OnModelCreating(ModelBuilder builder)
    {
        builder.Entity<Document>().HasKey(document => document.ID);    
        base.OnModelCreating(builder);
    }
}