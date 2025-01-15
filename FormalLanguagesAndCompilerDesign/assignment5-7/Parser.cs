namespace lab_part_2;

public class Parser
{
    private readonly Grammar _grammar;
    private Dictionary<string, HashSet<string>> _firstSet;
    private Dictionary<string, HashSet<string>> _followSet;
    private readonly Dictionary<(string, string), (string, int)> _parseTable;
    private readonly List<List<string>> _productionsRhs;

    public Parser(Grammar grammar) {
        _grammar = grammar;
        _firstSet = new Dictionary<string, HashSet<string>>();
        _followSet = new Dictionary<string, HashSet<string>>();
        _parseTable = new Dictionary<(string, string), (string, int)>();
        _productionsRhs = new List<List<string>>();
        
        GenerateFirst();
        GenerateFollow();
        GenerateParseTable();
    }

    public string FirstToString() => _firstSet.Aggregate("============= First =============\n",
        (current, keyValuePair) => current + $"{keyValuePair.Key}: [{string.Join(", ", keyValuePair.Value)}]\n");
    
    public string FollowToString() => _followSet.Aggregate("============= Follow =============\n",
        (current, keyValuePair) => current + $"{keyValuePair.Key}: [{string.Join(", ", keyValuePair.Value)}]\n");
    
    /// Don't use this for printing to the console, since parse table can be large. Output it to a file.
    public string ParseTableToString() => _parseTable.Aggregate("============= Parse Table =============\n",
        (current, keyValuePair) => current + $"{keyValuePair.Key}: [{string.Join(", ", keyValuePair.Value)}]\n");

    public Grammar Grammar() => _grammar;
    
    public List<int> ParseSequence(List<string> sequence)
    {
        var alpha = new Stack<string>();
        var beta = new Stack<string>();
        var result = new List<int>();
        
        // init
        alpha.Push("$");
        for (var i = sequence.Count - 1; i >= 0; i--)
        {
            alpha.Push(sequence[i]);
        }
        
        beta.Push("$");
        beta.Push(_grammar.StartingSymbol);
        
        while (!(alpha.Peek() == "$" && beta.Peek() == "$"))
        {
            var alphaPeek = alpha.Peek();
            var betaPeek = beta.Peek();
            var key = (betaPeek, alphaPeek);
            var value = _parseTable[key];

            if (value.Item1 != "err")
            {
                if (value.Item1 == "pop")
                {
                    alpha.Pop();
                    beta.Pop();
                }
                else
                {
                    beta.Pop();
                    if (value.Item1 != "epsilon")
                    {
                        var val = value.Item1.Split(" ");
                        for (var i = val.Length - 1; i >= 0; i--)
                        {
                            beta.Push(val[i]);
                        }
                    }
                    result.Add(value.Item2);
                }
            }
            else
            {
                Console.WriteLine($"Syntax error for key: {key}");
                Console.WriteLine($"Alpha: {string.Join(", ", alpha)}\nBeta: {string.Join(", ", beta)}");
                result = new List<int> { -1 };
                return result;
            }
        }

        return result;
    }

    public List<string> GetProductionByOrderNumber(int order)
    {
        if (order == 0)
        {
            return new List<string>();
        }

        var production = _productionsRhs[order - 1];
        
        return production.Contains("epsilon") ? new List<string> { "epsilon" } : production;
    }
    
    #region Private methods
    
    private void GenerateFirst() {
        // init: for each non-terminal, add left-most element in production if it's a terminal or epsilon
        foreach (var nonTerminal in _grammar.NonTerminals) {
            _firstSet.Add(nonTerminal, new HashSet<string>());
            
            _grammar.ProductionSet
                .GetByNonTerminal(new List<string> { nonTerminal })
                .Where(production => _grammar.Terminals.Contains(production[0]) || production[0].Equals("epsilon"))
                .ToList()
                .ForEach(production =>
                {
                    _firstSet[nonTerminal].Add(production[0]);
                });
        }

        var done = false;
        while (!done)
        {
            done = true;
            var newFirstSet = new Dictionary<string, HashSet<string>>();

            foreach (var nonTerminal in _grammar.NonTerminals)
            {
                var productionsOfNonTerminal = _grammar.ProductionSet.GetByNonTerminal(new List<string> { nonTerminal });
                var toAdd = new HashSet<string>();
                toAdd.UnionWith(_firstSet[nonTerminal]);
                foreach (var rhs in productionsOfNonTerminal)
                {
                    var rhsNonTerminals = new List<string>();
                    var rhsTerminal = string.Empty;
                    
                    // add all non-terminals in a list until you find the first terminal
                    foreach (var symbol in rhs)
                    {
                        if (_grammar.NonTerminals.Contains(symbol))
                        {
                            rhsNonTerminals.Add(symbol);
                        }
                        else 
                        {
                            rhsTerminal = symbol;
                            break;
                        }
                    }
                    
                    toAdd.UnionWith(GetConcatenationOfLengthOne(rhsNonTerminals, rhsTerminal));
                }
                
                if (!AreSetsEqual(toAdd, _firstSet[nonTerminal]))
                {
                    done = false;
                }

                newFirstSet.Add(nonTerminal, toAdd);
            }
            
            _firstSet = newFirstSet;
        }
    }
    
    private void GenerateFollow() {
        foreach (var nonTerminal in _grammar.NonTerminals) {
            _followSet.Add(nonTerminal, new HashSet<string>());
        }
        _followSet[_grammar.StartingSymbol].Add("epsilon");

        var done = false;
        while (!done)
        {
            done = true;
            var newColumn = new Dictionary<string, HashSet<string>>();

            foreach (var nonTerminal in _grammar.NonTerminals)
            {
                newColumn.Add(nonTerminal, new HashSet<string>());
                
                // retrieve all productions containing the non-terminal in the rhs
                var productionsWithNonTerminalInRhs = _grammar.ProductionSet.ProductionsByNonTerminalInRhs(nonTerminal);
                
                var toAdd = new HashSet<string>();
                toAdd.UnionWith(_followSet[nonTerminal]);

                foreach (var (k, v) in productionsWithNonTerminalInRhs)
                {
                    foreach (var productionList in v)
                    {
                        for (var indexOfNonTerminal = 0; indexOfNonTerminal < productionList.Count; ++indexOfNonTerminal)
                        {
                            if (productionList[indexOfNonTerminal].Equals(nonTerminal))
                            {
                                // when there is a non-terminal X on the last position, follow set of X will be
                                // equivalent to follow set of LHS non-terminal
                                if (indexOfNonTerminal + 1 == productionList.Count)
                                {
                                    toAdd.UnionWith(_followSet[k]);
                                }
                                else
                                {
                                    var followSymbol = productionList[indexOfNonTerminal + 1];
                                    
                                    // non-terminal is not on the last position and is followed by a terminal
                                    if (_grammar.Terminals.Contains(followSymbol))
                                    {
                                        toAdd.Add(followSymbol);
                                    }
                                    // non-terminal is not on the last position and is followed by a non-terminal
                                    // case 1: epsilon belongs to first(non-terminal)
                                    // case 2: otherwise
                                    else
                                    {
                                        foreach (var symbol in _firstSet[followSymbol])
                                        {
                                            // firstSet(followSymbol) - epsilon U followSet(k)
                                            var followSetCopy = new HashSet<string>();
                                            followSetCopy.UnionWith(_followSet[k]);
                                            followSetCopy.UnionWith(_firstSet[followSymbol]);
                                            followSetCopy.Remove("epsilon");
                                            
                                            toAdd.UnionWith(symbol.Equals("epsilon")
                                                ? followSetCopy
                                                : _firstSet[followSymbol]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
                if (!AreSetsEqual(toAdd, _followSet[nonTerminal]))
                {
                    done = false;
                }
                newColumn[nonTerminal] = toAdd;
            }
            _followSet = newColumn;
        }
    }
    
    private void GenerateParseTable() {
        var rows = new List<string>();
        rows.AddRange(_grammar.NonTerminals);
        rows.AddRange(_grammar.Terminals);
        rows.Add("$");

        var columns = new List<string>();
        columns.AddRange(_grammar.Terminals);
        columns.Add("$");

        // initialize everything with err
        foreach (var row in rows)
            foreach (var col in columns)
                _parseTable[(row, col)] = ("err", -1);

        // add pop diagonal
        foreach (var col in columns)
            _parseTable[(col, col)] = ("pop", -1);

        // add acc
        _parseTable[("$", "$")] = ("acc", -1);
        
        foreach (var (k, v) in _grammar.ProductionSet.Productions())
        {
            // get lhs nonTerminal
            var nonTerminal = k.First();
            
            // constructing the _productionRHS List 
            // if we find an epsilon, we add to the list epsilon along with it's nonTerminal
            _productionsRhs.AddRange(v.Select(production => 
                production[0] != "epsilon" ? production : new List<string> { "epsilon", nonTerminal }));
        }
        
        foreach (var (k, v) in _grammar.ProductionSet.Productions())
        {
            var key = k.First();
            
            foreach (var production in v)
            {
                var firstSymbol = production[0];

                // if it is a Terminal
                if (_grammar.Terminals.Contains(firstSymbol))
                {
                    if (_parseTable[(key, firstSymbol)].Item1.Equals("err"))
                    {
                        // add in the parseTable a string composed if the production rhs and its index from the _productionsRhs
                        _parseTable[(key, firstSymbol)] = (string.Join(" ", production), _productionsRhs.IndexOf(production) + 1);
                    }
                    else // we have a conflict
                    {
                        Console.WriteLine("Found a conflict for pair: " + key + ", " + firstSymbol);
                    }
                }
                // if it is a nonTerminal
                else if (_grammar.NonTerminals.Contains(firstSymbol))
                {
                    // if the production rhs has only 1 element
                    if (production.Count == 1)
                    {
                        foreach (var symbol in _firstSet[firstSymbol]) // parsing through the values of First(firstSymbol)
                        {
                            if (_parseTable[(key, symbol)].Item1.Equals("err")) // if in the paring table (key, First(firstSymbol)) we have err
                            {
                                _parseTable[(key, symbol)] = (string.Join(" ", production),_productionsRhs.IndexOf(production)+1);
                            }
                            else
                            {
                                Console.WriteLine("Found a conflict for pair: " + key + ", " + symbol);
                            }
                        }
                    }
                    else  // if the production rhs has multiple elements
                    {
                        var i = 1;
                        var nextSymbol = production[1];
                        var firstSetForProduction = _firstSet[firstSymbol];

                        // go through the production until we reach a terminal or we get at the end
                        while (i < production.Count && _grammar.NonTerminals.Contains(nextSymbol)) {
                            // get thr set of First(nextSymbol)
                            var firstForNext = _firstSet[nextSymbol];
                            
                            // if the FirstSet of the first terminal contains epsilon, 
                            // we remove it and add the FirstSet of the current terminal
                            if (firstSetForProduction.Contains("epsilon")) {
                                firstSetForProduction.Remove("epsilon");
                                firstSetForProduction.UnionWith(firstForNext);
                            }

                            i++;
                            if (i < production.Count)
                                nextSymbol = production[i];
                        }
                        
                        // replace epsilon with $ for all epsilon in the FirstSet of the first terminal
                        // in the current production
                        firstSetForProduction = firstSetForProduction
                            .Select(symbol => symbol == "epsilon" ? "$" : symbol)
                            .ToHashSet();
                        
                        foreach (var symbolToAdd in firstSetForProduction)
                        {
                            // for every entry in the parsing table of the NonTerminal lhs and 
                            // every terminal in the FirstSet of the first NonTerminal in the rhs
                            // check if we can make and entry in the table or not
                            if (_parseTable[(key, symbolToAdd)].Item1.Equals("err")) 
                            {
                                _parseTable[(key, symbolToAdd)] = (string.Join(" ", production), _productionsRhs.IndexOf(production) + 1);
                            }
                            else
                            {
                                Console.WriteLine("Found a conflict for pair: " + key + ", " + symbolToAdd);
                            }
                        }
                    }
                } 
                else  // if it is epsilon
                {
                    // get the followSet of the NonTerminal
                    var follow = _followSet[key];
                    foreach (var symbol in follow)
                    {
                        if (symbol == "epsilon") // if the element from the follow set is also epsilon ($)
                        {
                            // add in the parsing table for NonTerminal lhs and $ epsilon and the index
                            if (_parseTable[(key, "$")].Item1.Equals("err"))
                            {
                                var prod = new List<string> { "epsilon", key };
                                _parseTable[(key, "$")] = ("epsilon", _productionsRhs.IndexOf(prod) + 1);
                            }
                            else
                            {
                                Console.WriteLine("Found a conflict for pair: " + key + ", " + symbol);
                            }
                        }
                        else if (_parseTable[(key, symbol)].Item1.Equals("err")) // else or each terminal in Follow(NonTerminal), make entry A –>  ε in the table.
                        {
                            var prod = new List<string> { "epsilon", key };
                            _parseTable[(key, symbol)] = ("epsilon", _productionsRhs.IndexOf(prod) + 1);
                        }
                        else
                        {
                            Console.WriteLine("Found a conflict for pair: " + key + ", " + symbol);
                        }
                    }
                }
            }
        }
    }
    
    private IEnumerable<string> GetConcatenationOfLengthOne(List<string> nonTerminals, string terminal) {
        switch (nonTerminals.Count)
        {
            case 0:
                return new HashSet<string>();
            case 1:
                return _firstSet[nonTerminals[0]];
        }

        var allEpsilon = true;
        nonTerminals.ForEach(x =>
        {
            if (!_firstSet[x].Contains("epsilon"))
            {
                allEpsilon = false;
            }
        });
        
        var result = new HashSet<string>();
        
        if (allEpsilon)
        {
            result.Add(string.IsNullOrEmpty(terminal) ? "epsilon" : terminal);
        }

        var i = 0;
        var epsilonFound = true;
        while (i < nonTerminals.Count && epsilonFound)
        {
            epsilonFound = false;
            foreach (var s in _firstSet[nonTerminals[i]])
            {
                if (s == "epsilon")
                {
                    epsilonFound = true;
                }
                else
                {
                    result.Add(s);
                }
            }
            i++;
        }

        return result;
    }

    private static bool AreSetsEqual<T>(IReadOnlyCollection<T> a, IReadOnlySet<T> b)
        => a.Count == b.Count && a.All(b.Contains);

    #endregion
}