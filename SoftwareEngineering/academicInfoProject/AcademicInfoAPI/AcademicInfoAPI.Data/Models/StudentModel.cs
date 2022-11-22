namespace AcademicInfoAPI.Data.Models;

public class StudentModel
{
    public int ID { get; set; }
    public string FirstName { get; set; }
    public string LastName { get; set; }
    public decimal GradeAverage { get; set; }
    public int Year { get; set; }
    public int Group { get; set; }
}