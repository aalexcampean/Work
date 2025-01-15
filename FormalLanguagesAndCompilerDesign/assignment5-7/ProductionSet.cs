namespace lab_part_2;

public class ProductionSet
{
    private readonly Dictionary<List<string>, List<List<string>>> _productions;

    public ProductionSet(IEnumerable<string> lines)
    {
        _productions = new Dictionary<List<string>, List<List<string>>>();
        
        foreach (var line in lines)
        {
            var sides = line.Split("->");
            
            var lhs = sides[0].Trim().Split(" ").ToList();
            
            sides[1].Trim().Split(" | ").ToList().ForEach(token =>
            {
                var rhs = token.Trim().Split(" ").Where(x => x != "epsilon").ToList();
                rhs = rhs.Any() ? rhs : new List<string> { "epsilon" };
                Add(lhs, rhs);
            });
        }
    }

    public Dictionary<List<string>, List<List<string>>> Productions() => _productions;

    public List<List<string>> GetByNonTerminal(List<string> lhs)
    {
        var key = GetKey(lhs);

        return key is null ? new List<List<string>>() : _productions[key];
    }
    
    public Dictionary<string, List<List<string>>> ProductionsByNonTerminalInRhs(string nonTerminal)
    {
        var result = new Dictionary<string, List<List<string>>>();

        foreach (var (k, v) in _productions)
        {
            // We assume it's CFG
            var key = k.First();

            var productionsContainingNonTerminal = v.
                Where(production => production.Contains(nonTerminal));
            
            foreach (var production in productionsContainingNonTerminal)
            {
                if (!result.ContainsKey(key))
                {
                    result.Add(key, new List<List<string>>());
                }

                result[key].Add(production);
            }
        }

        return result;
    }
    
    public string GetByNonTerminalToString(List<string> lhs)
    {
        var key = GetKey(lhs);

        var lhsString = string.Join(" ", lhs);

        return key is null ? 
            string.Empty : 
            _productions[key].Aggregate(string.Empty, (current, rhs) => current + $"{lhsString} -> {string.Join(" ", rhs)}\n");
    }

    public override string ToString()
    {
        var result = string.Empty;
        foreach (var (lhs, values) in _productions)
        {
            var lhsString = string.Join(" ", lhs);
            result = values.Aggregate(result, (current, rhs) => current + $"{lhsString} -> {string.Join(" ", rhs)}\n");
        }

        return result;
    }
    
    public List<string> GetKey(ICollection<string> lhs) =>
        _productions.Keys.FirstOrDefault(x => AreListsEqual(x, lhs));
    
    private void Add(List<string> lhs, List<string> rhs)
    {
        var key = GetKey(lhs);

        if (key is null)
        {
            _productions[lhs] = new List<List<string>> { rhs };
        }
        else
        {
            _productions[key].Add(rhs);
        }
    }
    
    private static bool AreListsEqual(IReadOnlyCollection<string> a, ICollection<string> b) =>
        a.All(b.Contains) && a.Count == b.Count;
}