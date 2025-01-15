namespace lab_part_2;

public class Node
{
    public int Parent { get; set; }
    public string Value { get; set; }
    public int Index { get; set; }
    public int Sibling { get; set; }
    public bool HasRight { get; set; }
}