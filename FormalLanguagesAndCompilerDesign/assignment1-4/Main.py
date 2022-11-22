from Model.SymbolTable import SymbolTable
from Scanner import Scanner

if __name__ == '__main__':
    fileName = input("Insert file name: ")

    scanner = Scanner(fileName, "Output.txt", "PIF.txt", "ST.txt")
    scanner.scan()