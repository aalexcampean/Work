namespace lab_part_2;

public class Parser
{
    private readonly Grammar _grammar;
    private Dictionary<string, HashSet<string>> _firstSet;
    private Dictionary<string, HashSet<string>> _followSet;
    
    public Parser(Grammar grammar) {
        _grammar = grammar;
        _firstSet = new Dictionary<string, HashSet<string>>();
        _followSet = new Dictionary<string, HashSet<string>>();
        
        GenerateFirst();
        GenerateFollow();
    }

    public string FirstToString() => _firstSet.Aggregate("============= First =============\n",
        (current, keyValuePair) => current + $"{keyValuePair.Key}: [{string.Join(", ", keyValuePair.Value)}]\n");
    
    public string FollowToString() => _followSet.Aggregate("============= Follow =============\n",
        (current, keyValuePair) => current + $"{keyValuePair.Key}: [{string.Join(", ", keyValuePair.Value)}]\n");
    
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