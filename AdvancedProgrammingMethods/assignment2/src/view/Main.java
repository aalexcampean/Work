package view;

import controller.Controller;
import model.PrgState;
import model.adtContainers.IStack;
import model.adtContainers.MyStack;
import model.expressions.ArithExp;
import model.expressions.ValueExp;
import model.expressions.VarExp;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IValue;
import model.values.IntValue;
import repository.Repo;

import java.util.Scanner;

public class Main {
    static Repo myRepo = new Repo();
    static Controller myController = new Controller(myRepo);

    public static void main(String[] args) throws Exception{
        // ex 1:  int v; v = 2; Print(v)
        IStmt stmt1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));
        // ex 2: a=2+3*5;b=a+1;Print(b)
        IStmt stmt2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()),
                new CompStmt(new AssignStmt("a", new ArithExp('+', new ValueExp(new IntValue(2)), new ArithExp('*',
                        new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))), new CompStmt(
                        new AssignStmt("b", new ArithExp('+', new VarExp("a"), new ValueExp(new IntValue(1)))),
                        new PrintStmt(new VarExp("b"))))));

        // ex 3: bool a; int v; a=true;(If a Then v=2 Else v=3); Print(v)
        IStmt stmt3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v",
                new IntType()), new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))),
                        new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                        VarExp("v"))))));


        PrgState myPrgState1 = new PrgState(stmt1);
        PrgState myPrgState2 = new PrgState(stmt2);
        PrgState myPrgState3 = new PrgState(stmt3);

        myController.addProgram(myPrgState1);
        myController.addProgram(myPrgState2);
        myController.addProgram(myPrgState3);

        int command, stmtNr;

        while (true) {
            System.out.println("--- 0. exit");
            System.out.println("--- 1. int v; v = 2; Print(v)");
            System.out.println("--- 2. a = 2 + 3 * 5; b = a + 1; Print(b)");
            System.out.println("--- 3. bool a; int v; a = true; (if a then v = 2 else v = 3); Print(v)");
            System.out.println("------- choose a program: ");
            Scanner choice = new Scanner(System.in);
            try {
                command = choice.nextInt();
                if (command == 0) {
                    break;
                }
                stmtNr = command - 1;
                myController.allSteps(stmtNr);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }
}