from FA import FiniteAutomata


def print_menu():
    print("1.Print set of states")
    print("2.Print alphabet")
    print("3.Print transitions")
    print("4.Print initial state")
    print("5.Print final states")
    print("6.Check if string is accepted ")


if __name__ == '__main__':
    while True:
        fa = FiniteAutomata()
        fa.readFromFile()
        print_menu()
        option = input("Choose option: ")
        if option == "1":
            print(fa.statesToString())
        elif option == "2":
            print(fa.alphabetToString())
        elif option == "3":
            print(fa.transitionToString())
        elif option == "4":
            print(fa.initialStateToString())
        elif option == "5":
            print(fa.finalStatesToString())
        elif option == "6":
            given_string = input("Give a string: ")
            if fa.isAccepted(given_string):
                print("Accpeted")
            else:
                print("Not accpeted")
        else:
            print("Bye")
            break
