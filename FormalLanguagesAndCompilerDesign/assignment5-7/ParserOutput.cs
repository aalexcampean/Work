namespace lab_part_2;

public class ParserOutput
{
    private readonly Parser _parser;
    private readonly List<int> _productions;
    private int _nodeNumber = 1;
    private readonly bool _hasErrors;
    private List<Node> _nodeList = new();
    private Node _root;

    public ParserOutput(Parser parser, List<string> sequence)
    {
        _parser = parser;
        _productions = _parser.ParseSequence(sequence);
        _hasErrors = _productions.Contains(-1);

        GenerateTree();
    }

    public void WriteTreeToFile(string filePath)
    {
        _nodeList = _nodeList.OrderBy(x => x.Index).ToList();

        var lines = new List<string> { "INDEX" + " | " + "VALUE".PadRight(35) + " | " + "PARENT" + " | " + "SIBLING" };
        lines.AddRange(_nodeList.Select(x => $"{x.Index.ToString().PadRight(5)} | {x.Value.PadRight(35)} | {x.Parent.ToString().PadRight(6)} | {x.Sibling}"));
        
        File.WriteAllLines(filePath, lines);
    }

    #region Private methods

    private void GenerateTree()
    {
        if (_hasErrors) return;

        var nodeStack = new Stack<Node>();
        var productionsIndex = 0;
        
        // initialize the root
        _root = new Node
        {
            Parent = 0,
            Sibling = 0,
            HasRight = false,
            Index = _nodeNumber,
            Value = _parser.Grammar().StartingSymbol
        };
        
        _nodeNumber++;
        nodeStack.Push(_root);
        _nodeList.Add(_root);
        
        while (productionsIndex < _productions.Count && nodeStack.Any())
        {
            var fatherNode = nodeStack.Peek();
            if (_parser.Grammar().Terminals.Contains(fatherNode.Value) || fatherNode.Value.Contains("epsilon"))
            {
                while (nodeStack.Count > 0 && !nodeStack.Peek().HasRight)
                {
                    nodeStack.Pop();
                }
                
                if (nodeStack.Count > 0)
                    nodeStack.Pop();
                else
                    break;
                
                continue;
            }

            // children
            var production = _parser.GetProductionByOrderNumber(_productions[productionsIndex]);
            _nodeNumber += production.Count - 1;
            for (var i = production.Count - 1; i >= 0; i--)
            {
                var child = new Node
                {
                    Parent = fatherNode.Index,
                    Value = production[i],
                    Index = _nodeNumber,
                    Sibling = i == 0 ? 0 : _nodeNumber - 1,
                    HasRight = i != production.Count - 1
                };
                
                _nodeNumber--;
                nodeStack.Push(child);
                _nodeList.Add(child);
            }
            _nodeNumber += production.Count + 1;
            productionsIndex++;
        }
    }

    #endregion
}