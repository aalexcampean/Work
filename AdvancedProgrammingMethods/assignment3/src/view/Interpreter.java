package view;

import controller.Controller;
import model.PrgState;
import model.adtContainers.IDictionary;
import model.expressions.ArithExp;
import model.expressions.ValueExp;
import model.expressions.VarExp;
import model.fileStatements.OpenRFileStmt;
import model.fileStatements.ReadFileStmt;
import model.fileStatements.CloseRFileStmt;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import repository.Repo;
import view.Commands.ExitCommand;
import view.Commands.RunExample;

import java.util.Scanner;

public class Interpreter {

    public static void main(String[] args) {

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

        IStmt stmt4 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFileStmt(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new AssignStmt("varc", new ValueExp(new IntValue())),
                                                new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                        new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                                        new CompStmt(new PrintStmt(new VarExp("varc")), new CloseRFileStmt(new VarExp("varf")))))))))));

        PrgState myPrgState1 = new PrgState(stmt1);
        PrgState myPrgState2 = new PrgState(stmt2);
        PrgState myPrgState3 = new PrgState(stmt3);
        PrgState myPrgState4 = new PrgState(stmt4);

        Repo myRepo1 = new Repo(myPrgState1, "logFile1.out");
        Controller myController1 = new Controller(myRepo1);
        Repo myRepo2 = new Repo(myPrgState2, "logFile2.out");
        Controller myController2 = new Controller(myRepo2);
        Repo myRepo3 = new Repo(myPrgState3, "logFile3.out");
        Controller myController3 = new Controller(myRepo3);
        Repo myRepo4 = new Repo(myPrgState4, "logFile4.out");
        Controller myController4 = new Controller(myRepo4);

//        myController.addProgram(myPrgState1);
//        myController.addProgram(myPrgState2);
//        myController.addProgram(myPrgState3);
//        myController.addProgram(myPrgState4);

        System.out.println("--- 0. exit");
        System.out.println("--- 1. int v; v = 2; Print(v)");
        System.out.println("--- 2. a = 2 + 3 * 5; b = a + 1; Print(b)");
        System.out.println("--- 3. bool a; int v; a = true; (if a then v = 2 else v = 3); Print(v)");
        System.out.println("------- choose a program: ");

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", stmt1.toString(), myController1));
        menu.addCommand(new RunExample("2", stmt2.toString(), myController2));
        menu.addCommand(new RunExample("3", stmt3.toString(), myController3));
        menu.addCommand(new RunExample("4", stmt4.toString(), myController4));

        menu.show();
    }
}