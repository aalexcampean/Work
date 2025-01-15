using lab_part_2;

void GrammarMenu(Grammar grammar)
{
    while (true)
    {
        Console.WriteLine();
        Console.WriteLine("1. Show non-terminals");
        Console.WriteLine("2. Show starting symbol");
        Console.WriteLine("3. Show terminals");
        Console.WriteLine("4. Show productions");
        Console.WriteLine("5. Show productions for a non-terminal");
        Console.WriteLine("6. CFG check");
        Console.Write(">>>>>>> ");
    
        var option = Console.ReadLine();
        switch (option)
        {
            case "0":
                return;
            case "1":
                Console.WriteLine(string.Join(", ", grammar.NonTerminals));
                break;
            case "2":
                Console.WriteLine(grammar.StartingSymbol);
                break;
            case "3":
                Console.WriteLine(string.Join(", ", grammar.Terminals));
                break;
            case "4":
                Console.WriteLine(grammar.ProductionSet.ToString());
                break;
            case "5":
                Console.Write("Non-terminal >>>>>>> ");
                var lhs = (Console.ReadLine() ?? string.Empty).Split(" ").ToList();
                Console.WriteLine(grammar.ProductionSet.GetByNonTerminalToString(lhs));
                break;
            case "6":
                Console.WriteLine(grammar.IsCfg() ? "CFG" : "Not CFG");
                break;
        }
    }
}

// var grammar = new Grammar("../../../resources/g1.in");
//
// GrammarMenu(grammar);
//
// var parser = new Parser(grammar);
// Console.WriteLine(parser.FirstToString());
// Console.WriteLine(parser.FollowToString());
//
// var sequence = SequenceHelper.GetSequenceFromListFile("../../../resources/seq.txt");
// Console.WriteLine(string.Join(", ", parser.ParseSequence(sequence)));
//
// var parserOutput = new ParserOutput(parser, sequence);
// parserOutput.WriteTreeToFile("../../../resources/out1.txt");

var grammar = new Grammar("../../../resources/g2.in");

GrammarMenu(grammar);

var parser = new Parser(grammar);
Console.WriteLine(parser.FirstToString());
Console.WriteLine(parser.FollowToString());

var sequence = SequenceHelper.GetSequenceFromPif("../../../resources/PIF.txt");
Console.WriteLine(string.Join(", ", parser.ParseSequence(sequence)));

var parserOutput = new ParserOutput(parser, sequence);
parserOutput.WriteTreeToFile("../../../resources/out2.txt");