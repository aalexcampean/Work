namespace lab_part_2;

public static class SequenceHelper
{
    public static List<string> GetSequenceFromPif(string fileName) =>
        File.ReadAllLines(fileName).Select(line => line.Split(" ")[1].TrimEnd(',')).ToList();
    
    public static List<string> GetSequenceFromListFile(string fileName) => 
        File.ReadAllLines(fileName)[0].Split(" ").ToList();
}