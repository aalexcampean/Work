using dotNetTemplate.Data;
using dotNetTemplate.Repository;
using dotNetTemplate.Service;
using Microsoft.EntityFrameworkCore;
using Microsoft.OpenApi.Models;

public class Program
{
    public static void Main(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);
        var connectionString = builder.Configuration.GetConnectionString("DefaultConnection");
        ConfigurationManager configuration = builder.Configuration;

        builder.Services.AddCors(options =>
        {
            options.AddDefaultPolicy(policy =>
            {
                policy.AllowAnyHeader().AllowAnyMethod().AllowAnyOrigin().Build();
            });
        });

        builder.Services.AddDbContext<SubscriptionsDbContext>(options =>
        {
            options.UseMySql(connectionString, ServerVersion.AutoDetect(connectionString));
        });
        
        builder.Services.AddTransient<ChannelService, ChannelService>();
        builder.Services.AddTransient<ChannelRepository, ChannelRepository>();

        builder.Services.AddSwaggerGen(c =>
        {
            c.SwaggerDoc("v1", new OpenApiInfo {Title = "DocumentManagerAPI", Version = "v1"});
        });

        builder.Services.AddControllers();

        var app = builder.Build();

        if (app.Environment.IsDevelopment())
        {
            app.UseDeveloperExceptionPage();
            app.UseSwagger();
            app.UseSwaggerUI(c => c.SwaggerEndpoint("/swagger/v1/swagger.json", "DocumentManager v1"));
        }

        app.UseCors();
        app.UseRouting();
        app.UseDefaultFiles();
        app.UseStaticFiles();
        app.UseAuthentication();
        app.UseAuthorization();
        app.UseHttpsRedirection();
        app.MapControllers();

        app.UseEndpoints(endpoints =>
        {
            endpoints.MapControllerRoute(
                name: "default",
                pattern: "{controller=Home}/{action=Index}");

            endpoints.MapFallbackToController("Index", "Fallback");
        });

        app.Run();
    }
}