import FA.FA
from LanguageSpecification import LanguageSpecification
from Model.ProgramInternalForm import ProgramInternalForm
from Model.SymbolTable import SymbolTable


class Scanner:
    def __init__(self, input_file, output_file, pif_file, st_file):
        self.language_spec = LanguageSpecification()
        self.PIF = ProgramInternalForm()
        self.ST = SymbolTable()

        self.input_file = input_file
        self.output_file = output_file
        self.pif_file = pif_file
        self.st_file = st_file

    def getQuotesIndexes(self, line):
        return [index for index, character in enumerate(line) if "\"" in character]

    def joinStringConstants(self, quote_indexes, tokens):
        # TODO: Treat error when there are too many quotes
        while len(quote_indexes) >= 2:
            first_pos = quote_indexes[0]
            second_pos = quote_indexes[1]

            tokens = tokens[:first_pos] + [''.join(tokens[first_pos: second_pos + 1])] + tokens[second_pos + 1:]

            quote_indexes.pop(0)
            quote_indexes.pop(0)
            for i in range(len(quote_indexes)):
                quote_indexes[i] -= len(tokens[first_pos: second_pos]) - 1

        return tokens

    def splitBySeparator(self, line):
        index = 0
        tokens = []
        token = ''

        for char in line:
            if not self.language_spec.isSeparator(char):
                token += line[index]
            else:
                if token:
                    tokens.append(token)
                tokens.append(line[index])
                token = ''

            index += 1

        if token:
            tokens.append(token)

        return self.joinStringConstants(self.getQuotesIndexes(tokens), tokens)

    def splitByOperator(self, line):
        index = 0
        tokens = []
        token = ''

        while index in range(len(line)):
            # It is worth checking if we have a logical operator only in the beginning of the token as otherwise
            # it is certain this cannot be the case
            if index == 0 and self.language_spec.isPartOfLogicalOperator(line[index], line):
                return [line]

            if not self.language_spec.isPartOfOperator(line[index]):
                token += line[index]
            else:
                operator = ''

                if index + 1 < len(line):
                    if self.language_spec.isOperator(line[index] + line[index + 1]):
                        operator = line[index: index + 2]
                        index += 1
                    else:
                        operator = line[index]
                else:
                    operator = line[index]

                if token:
                    tokens.append(token)
                tokens.append(operator)
                token = ''

            index += 1

        if token:
            tokens.append(token)

        return tokens

    def splitLine(self, line):
        split_line = self.splitBySeparator(line)
        line_index = 0
        while line_index < len(split_line):
            result = self.splitByOperator(split_line[line_index])
            split_line = split_line[:line_index] + result + split_line[line_index + 1:]
            line_index += len(result)

        return split_line

    def scan(self):
        fa_constant = FA.FA.FiniteAutomata()
        fa_constant.readFromFile('FAConstant.in')
        fa_identifier = FA.FA.FiniteAutomata()
        fa_identifier.readFromFile('FAIdentifier.in')
        with open(self.input_file, 'r') as file:
            line_index = 0
            for line in file:
                line_index += 1
                split_line = self.splitLine(line)

                for token in split_line:
                    if self.language_spec.isOperator(token) or self.language_spec.isSeparator(token) \
                            or self.language_spec.isReservedWord(token):
                        if token == ' ':
                            self.PIF.insert("" "", (-1, -1))
                        elif token == '\n':
                            self.PIF.insert("\ n", (-1, -1))
                        elif token == '\t':
                            self.PIF.insert("\ t", (-1, -1))
                        else:
                            self.PIF.insert(token, (-1, -1))
                    else:
                        if self.language_spec.isConstant(token):
                            if token not in self.ST:
                                self.ST.insert(token)
                            self.PIF.insert("const", self.ST.getPosition(token))
                        elif self.language_spec.isIdentifier(token):
                            if token not in self.ST:
                                self.ST.insert(token)
                            self.PIF.insert("id", self.ST.getPosition(token))
                        else:
                            print(f"Lexical error at line {line_index}")

                self.printOutput()

    def printOutput(self):
        with open(self.pif_file, 'w') as file:
            file.write("{:<10} {:<10} \n".format("Code", "Position"))
            for token in self.PIF.content:
                file.write("{:<10} {:<10} \n".format(token[0], str(token[1])))

        with open(self.st_file, 'w') as file:
            file.write("{:<10} {:<10} \n".format("Index", "Values"))

            for index in range(self.ST.capacity):
                node = self.ST[index]
                values = [] if node is not None else None
                while node is not None:
                    values.append(node.key)
                    node = node.next

                file.write("{:<10} {:<10} \n".format(index, str(values)))


if __name__ == "__main__":
    scanner = Scanner("In.txt", "Out.txt", "ProgramInternalFile.txt", "SymbolTableFile.txt")
    scanner.splitByOperator("and")
    scanner.splitLine("if a==2 and b != 3:\n\ta += 1")
    scanner.splitBySeparator("if a==2 and b==here:")
    scanner.splitLine("write(\"I want juice\")\nwrite(\"I want water\")")
