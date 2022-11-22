import re


class LanguageSpecification:
    def __init__(self):
        self.__operators = ["==", "!=", "<=", ">=", "<", ">", "=", "+", "-", "/", "*", "+=", "-=", "/=", "*="]
        self.__logical_operators = ["or", "and", "not"]
        self.__separators = ["(", ")", "[", "]", "{", "}", ":", ",", " ", "\n", "\t"]
        self.__reserved_words = ["read", "write", "fread", "fwrite", "if", "else", "while", "for", "int", "char",
                               "string", "var", "const"]

    def isOperator(self, token):
        return token in self.__operators

    def isPartOfOperator(self, char):
        for operator in self.__operators:
            if char in operator:
                return True
        return False

    def isPartOfLogicalOperator(self, char, token):
        if char == "a" and token == "and":
            return True
        elif char == "n" and token == "not":
            return True
        elif char == "o" and token == "or":
            return True
        else:
            return False

    def isSeparator(self, token):
        return token in self.__separators

    def isReservedWord(self, token):
        return token in self.__reserved_words

    def isIdentifier(self, token):
        return re.match(r'^[a-zA-Z]([a-zA-Z]|[0-9])*$', token) is not None

    def isConstant(self, token):
        return re.match('(^(0|[\+\-]?[1-9][0-9]*))$|(^"[a-z|A-Z| |!|?|.|\']"*)$|^\'.\'$|^\".*\"$', token) is not None

