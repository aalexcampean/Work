package view;

import controller.Controller;
import model.PrgState;
import model.expressions.ArithIExp;
import model.expressions.RelationalIExp;
import model.expressions.ValueIExp;
import model.expressions.VarIExp;
import model.fileStatements.CloseRFileStmt;
import model.fileStatements.OpenRFileStmt;
import model.fileStatements.ReadFileStmt;
import model.heapExpressions.HeapReadingExp;
import model.heapStatements.HeapAllocationStmt;
import model.heapStatements.HeapWritingStmt;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.types.RefType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import repository.Repo;
import view.Commands.ExitCommand;
import view.Commands.RunExample;

public class Interpreter {

    public static void main(String[] args) {

        // ex 1:  int v; v = 2; Print(v)
        IStmt stmt1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueIExp(new IntValue(2))),
                        new PrintStmt(new VarIExp("v"))));
        // ex 2: a=2+3*5;b=a+1;Print(b)
        IStmt stmt2 = new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(new VarDeclStmt("b", new IntType()),
                new CompStmt(new AssignStmt("a", new ArithIExp('+', new ValueIExp(new IntValue(2)), new ArithIExp('*',
                        new ValueIExp(new IntValue(3)), new ValueIExp(new IntValue(5))))), new CompStmt(
                        new AssignStmt("b", new ArithIExp('+', new VarIExp("a"), new ValueIExp(new IntValue(1)))),
                        new PrintStmt(new VarIExp("b"))))));

        // ex 3: bool a; int v; a=true;(If a Then v=2 Else v=3); Print(v)
        IStmt stmt3 = new CompStmt(new VarDeclStmt("a", new BoolType()), new CompStmt(new VarDeclStmt("v",
                new IntType()), new CompStmt(new AssignStmt("a", new ValueIExp(new BoolValue(true))),
                new CompStmt(new IfStmt(new VarIExp("a"), new AssignStmt("v", new ValueIExp(new IntValue(2))),
                        new AssignStmt("v", new ValueIExp(new IntValue(3)))), new PrintStmt(new
                        VarIExp("v"))))));

        IStmt stmt4 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                new CompStmt(new AssignStmt("varf", new ValueIExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFileStmt(new VarIExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                        new CompStmt(new AssignStmt("varc", new ValueIExp(new IntValue())),
                                                new CompStmt(new ReadFileStmt(new VarIExp("varf"), "varc"),
                                                        new CompStmt(new PrintStmt(new VarIExp("varc")),
                                                                new CompStmt(new ReadFileStmt(new VarIExp("varf"), "varc"),
                                                                        new CompStmt(new PrintStmt(new VarIExp("varc")), new CloseRFileStmt(new VarIExp("varf")))))))))));

        //Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        IStmt stmt5 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueIExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarIExp("v")),
                                        new CompStmt(new PrintStmt(new VarIExp("v")), new PrintStmt(new VarIExp("a")))))));

        IStmt stmt6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueIExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarIExp("v")),
                                        new CompStmt(new PrintStmt(new HeapReadingExp(new VarIExp("v"))),
                                                new PrintStmt(new ArithIExp('+', new ValueIExp(new IntValue(5)),
                                                        new HeapReadingExp(new HeapReadingExp(new VarIExp("a"))))))))));

        IStmt stmt7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueIExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new HeapReadingExp(new VarIExp("v"))), new CompStmt(
                                new HeapWritingStmt("v", new ValueIExp(new IntValue(30))),
                                new PrintStmt(new ArithIExp('+', new ValueIExp(new IntValue(5)),
                                        new HeapReadingExp(new VarIExp("v"))))))));

        IStmt stmt8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueIExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarIExp("v")),
                                        new CompStmt(new HeapAllocationStmt("v", new ValueIExp(new IntValue(30))),
                                                new PrintStmt(new HeapReadingExp(new HeapReadingExp(new VarIExp("a")))))))));

//        int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        IStmt stmt9 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueIExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalIExp(new VarIExp("v"), new ValueIExp(new IntValue(0)), ">"), new CompStmt(new PrintStmt(new VarIExp("v")), new AssignStmt("v", new ArithIExp('-', new VarIExp("v"), new ValueIExp(new IntValue(1)))))),
                                new PrintStmt(new VarIExp("v")))));


        PrgState myPrgState1 = new PrgState(stmt1);
        PrgState myPrgState2 = new PrgState(stmt2);
        PrgState myPrgState3 = new PrgState(stmt3);
        PrgState myPrgState4 = new PrgState(stmt4);
        PrgState myPrgState5 = new PrgState(stmt5);
        PrgState myPrgState6 = new PrgState(stmt6);
        PrgState myPrgState7 = new PrgState(stmt7);
        PrgState myPrgState8 = new PrgState(stmt8);
        PrgState myPrgState9 = new PrgState(stmt9);


        Repo myRepo1 = new Repo(myPrgState1, "logFile1.out");
        Controller myController1 = new Controller(myRepo1);
        Repo myRepo2 = new Repo(myPrgState2, "logFile2.out");
        Controller myController2 = new Controller(myRepo2);
        Repo myRepo3 = new Repo(myPrgState3, "logFile3.out");
        Controller myController3 = new Controller(myRepo3);
        Repo myRepo4 = new Repo(myPrgState4, "logFile4.out");
        Controller myController4 = new Controller(myRepo4);
        Repo myRepo5 = new Repo(myPrgState5, "logFile5.out");
        Controller myController5 = new Controller(myRepo5);
        Repo myRepo6 = new Repo(myPrgState6, "logFile6.out");
        Controller myController6 = new Controller(myRepo6);
        Repo myRepo7 = new Repo(myPrgState7, "logFile7.out");
        Controller myController7 = new Controller(myRepo7);
        Repo myRepo8 = new Repo(myPrgState8, "logFile8.out");
        Controller myController8 = new Controller(myRepo8);
        Repo myRepo9 = new Repo(myPrgState9, "logFile10.out");
        Controller myController9 = new Controller(myRepo9);


        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", stmt1.toString(), myController1));
        menu.addCommand(new RunExample("2", stmt2.toString(), myController2));
        menu.addCommand(new RunExample("3", stmt3.toString(), myController3));
        menu.addCommand(new RunExample("4", stmt4.toString(), myController4));
        menu.addCommand(new RunExample("5", stmt5.toString(), myController5));
        menu.addCommand(new RunExample("6", stmt6.toString(), myController6));
        menu.addCommand(new RunExample("7", stmt7.toString(), myController7));
        menu.addCommand(new RunExample("8", stmt8.toString(), myController8));
        menu.addCommand(new RunExample("9", stmt9.toString(), myController9));


        menu.show();
    }
}