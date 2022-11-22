package gui;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.ResourceBundle;

import controller.Controller;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import model.expressions.*;
import model.statements.threads.ForkStmt;
import model.statements.threads.barrier.AwaitBarrierStmt;
import model.statements.threads.barrier.BarrierStmt;
import repository.Repo;
import model.PrgState;

import model.adtContainers.IDictionary;
import model.adtContainers.MyDictionary;

import model.fileStatements.CloseRFileStmt;
import model.fileStatements.OpenRFileStmt;
import model.fileStatements.ReadFileStmt;

import model.heapExpressions.HeapReadingExp;
import model.heapStatements.HeapAllocationStmt;
import model.heapStatements.HeapWritingStmt;

import model.statements.*;
import model.types.*;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import javafx.util.Callback;


public class PrgListController implements Initializable {
    @FXML
    ListView<Controller> myPrgList;
    @FXML
    Button runButton;

    public void setUp(ObservableList<Controller> myData) {
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

        //Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
        IStmt stmt5 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new VarExp("a")))))));

        IStmt stmt6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new HeapReadingExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp('+', new ValueExp(new IntValue(5)),
                                                        new HeapReadingExp(new HeapReadingExp(new VarExp("a"))))))))));

        IStmt stmt7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new HeapReadingExp(new VarExp("v"))), new CompStmt(
                                new HeapWritingStmt("v", new ValueExp(new IntValue(30))),
                                new PrintStmt(new ArithExp('+', new ValueExp(new IntValue(5)),
                                        new HeapReadingExp(new VarExp("v"))))))));

        IStmt stmt8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new HeapAllocationStmt("a", new VarExp("v")),
                                        new CompStmt(new HeapAllocationStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new HeapReadingExp(new HeapReadingExp(new VarExp("a")))))))));

//        int v; v=4; (while (v>0) print(v);v=v-1);print(v)
        IStmt stmt9 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), ">"), new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));

        //int v; Ref int a; v=10; new(a,22);
        //fork(wH(a,30);v=32;print(v);print(rH(a)));
        //print(v);print(rH(a))
        IStmt stmt10 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new HeapAllocationStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new HeapWritingStmt("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new HeapReadingExp(new VarExp("a"))))))),
                                                                new CompStmt(new PrintStmt(new VarExp("v")), new PrintStmt(new HeapReadingExp(new VarExp("a")))))))));

        //int a; int b; int c;
        //a=1;b=2;c=5;
        //(switch(a*10)
        //(case (b*c) : print(a);print(b))
        //(case (10) : print(100);print(200))
        //(default : print(300)));
        //print(300)
        IStmt stmt11 = new CompStmt(new VarDeclStmt("a", new IntType()),
                new CompStmt(new VarDeclStmt("b", new IntType()),
                        new CompStmt(new VarDeclStmt("c", new IntType()),
                                new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(1))),
                                        new CompStmt(new AssignStmt("b", new ValueExp(new IntValue(2))),
                                                new CompStmt(new AssignStmt("c", new ValueExp(new IntValue(5))),
                                                        new CompStmt(new SwitchStmt(new ArithExp('*', new VarExp("a"),
                                                                new ValueExp(new IntValue(10))), new ArithExp('*', new VarExp("b"), new VarExp("b")), new CompStmt(new PrintStmt(new VarExp("a")), new PrintStmt(new VarExp("b"))),
                                                                new ValueExp(new IntValue(10)), new CompStmt(new PrintStmt(new ValueExp(new IntValue(100))), new PrintStmt(new ValueExp(new IntValue(200)))),
                                                                new PrintStmt(new ValueExp(new IntValue(100)))),
                                                                    new PrintStmt(new ValueExp(new IntValue(300))))))))));

        //        Ref int a; new(a,20);
        //        (for(v=0;v<3;v=v+1) fork(print(v); v=v*rh(a)));
        //        print(rh(a))
        IStmt stmt12 = new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                new CompStmt(new HeapAllocationStmt("a", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("v", new IntType()),
                                new CompStmt(new ForStmt("v",
                                        new ValueExp(new IntValue(0)),
                                        new ValueExp(new IntValue(3)),
                                        new ArithExp('+', new VarExp("v"), new ValueExp(new IntValue(1))),
                                        new ForkStmt(new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('*', new VarExp("v"), new HeapReadingExp(new VarExp("a"))))))),
                                            new PrintStmt(new HeapReadingExp(new VarExp("a")))))));

//        Ref int a; Ref int b; int v;
//        new(a,0); new(b,0);
//        wh(a,1); wh(b,2);
//        v=(rh(a)<rh(b))?100:200;
//        print(v);
//        v= ((rh(b)-2)>rh(a))?100:200;
//        print(v);
        IStmt stmt13 = new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                new CompStmt(new VarDeclStmt("b", new RefType(new IntType())),
                        new CompStmt(new VarDeclStmt("v", new IntType()),
                                new CompStmt(new HeapAllocationStmt("a", new ValueExp(new IntValue(0))),
                                        new CompStmt(new HeapAllocationStmt("b", new ValueExp(new IntValue(0))),
                                                new CompStmt(new HeapWritingStmt("a", new ValueExp(new IntValue(1))),
                                                        new CompStmt(new HeapWritingStmt("b", new ValueExp(new IntValue(2))),
                                                                new CompStmt(new CondAssignStmt("v",
                                                                        new RelationalExp(new HeapReadingExp(new VarExp("a")), new HeapReadingExp(new VarExp("b")),"<"),
                                                                        new ValueExp(new IntValue(100)),
                                                                        new ValueExp(new IntValue(200))),
                                                                            new CompStmt(new PrintStmt(new VarExp("v")),
                                                                                    new CompStmt(new CondAssignStmt("v",
                                                                                            new RelationalExp(new ArithExp('-', new HeapReadingExp(new VarExp("b")), new ValueExp(new IntValue(2))), new HeapReadingExp(new VarExp("a")),">"),
                                                                                            new ValueExp(new IntValue(100)),
                                                                                            new ValueExp(new IntValue(200))),
                                                                                                new PrintStmt(new VarExp("v"))))))))))));

//        v=10;
//        (fork(v=v-1;v=v-1;print(v)); sleep(10);print(v*10)
        IStmt stmt14 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                    new CompStmt(new ForkStmt(new CompStmt(new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))),
                            new CompStmt(new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("v"))))),
                            new CompStmt(new SleepStmt(10), new PrintStmt(new ArithExp('*', new VarExp("v"), new ValueExp(new IntValue(10))))))));


//        v=0;
//        (repeat (fork(print(v);v=v-1);v=v+1) until v==3);
//        x=1;y=2;z=3;w=4;
//        print(v*10)
        IStmt stmt15 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(0))),
                        new CompStmt(new RepeatStmt(
                                new CompStmt(
                                        new ForkStmt(new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp('-', new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                        new AssignStmt("v", new ArithExp('+', new VarExp("v"), new ValueExp(new IntValue(1))))),
                                new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(3)), "==")),
                                    new CompStmt(new VarDeclStmt("x", new IntType()),
                                            new CompStmt(new AssignStmt("x", new ValueExp(new IntValue(1))),
                                                    new CompStmt(new VarDeclStmt("y", new IntType()),
                                                            new CompStmt(new AssignStmt("y", new ValueExp(new IntValue(2))),
                                                                    new CompStmt(new VarDeclStmt("z", new IntType()),
                                                                            new CompStmt(new AssignStmt("z", new ValueExp(new IntValue(3))),
                                                                                    new CompStmt(new VarDeclStmt("w", new IntType()),
                                                                                            new CompStmt(new AssignStmt("w", new ValueExp(new IntValue(4))),
                                                                                                    new PrintStmt(new ArithExp('*', new VarExp("v"), new ValueExp(new IntValue(10)))))))))))))));

//        Ref int v1; Ref int v2; Ref int v3;
//        new(v1, 2); new(v2, 3); new(v3, 4);
//        newBarrier(cnt, rH(v2));
//        fork(await(cnt); wh(v1, rh(v1) * 10); print(rh(v1)));
//        fork(await(cnt); wh(v2, rh(v2) * 10); wh(v2, rh(v2) * 10)); print(rh(v2)));
//        await(cnt);
//        print(rh(v3));
        IStmt stmt16 = new CompStmt(new VarDeclStmt("v1", new RefType(new IntType())),
                new CompStmt(new VarDeclStmt("v2", new RefType(new IntType())),
                        new CompStmt(new VarDeclStmt("v3", new RefType(new IntType())),
                                new CompStmt(new VarDeclStmt("cnt", new IntType()),
                                        new CompStmt(new HeapAllocationStmt("v1", new ValueExp(new IntValue(2))),
                                                new CompStmt(new HeapAllocationStmt("v2", new ValueExp(new IntValue(3))),
                                                        new CompStmt(new HeapAllocationStmt("v3", new ValueExp(new IntValue(4))),
                                                                new CompStmt(new BarrierStmt("cnt", new HeapReadingExp(new VarExp("v2"))),
                                                                        new CompStmt(new ForkStmt(new CompStmt(new AwaitBarrierStmt("cnt"),
                                                                                new CompStmt(new HeapWritingStmt("v1", new ArithExp('*', new HeapReadingExp(new VarExp("v1")), new ValueExp(new IntValue(10)))),
                                                                                        new PrintStmt(new HeapReadingExp(new VarExp("v1")))))),
                                                                                new CompStmt(new ForkStmt(new CompStmt(new AwaitBarrierStmt("cnt"),
                                                                                        new CompStmt(new HeapWritingStmt("v2", new ArithExp('*', new HeapReadingExp(new VarExp("v2")), new ValueExp(new IntValue(10)))),
                                                                                                new CompStmt(new HeapWritingStmt("v2", new ArithExp('*', new HeapReadingExp(new VarExp("v2")), new ValueExp(new IntValue(10)))),
                                                                                                        new PrintStmt(new HeapReadingExp(new VarExp("v2"))))))),
                                                                                        new CompStmt(new AwaitBarrierStmt("cnt"),
                                                                                                new PrintStmt(new HeapReadingExp(new VarExp("v3"))))))))))))));

        // creating a list with all the statements so that we can perform the type checks
        ArrayList<IStmt> stmts = new ArrayList<IStmt>(Arrays.asList(stmt1, stmt2, stmt3, stmt3, stmt4, stmt5, stmt6, stmt7, stmt8, stmt9, stmt10, stmt11, stmt12, stmt13, stmt14, stmt15, stmt16));
        // type checking all the statements
        for (IStmt s : stmts) {
            try {
                IDictionary<String, IType> typeEnv = new MyDictionary<>();
                s.typeCheck(typeEnv);
            } catch (Exception e) {
                Alert alertType = new Alert(Alert.AlertType.INFORMATION);
                alertType.setTitle("Toy Language - TypeCheck Outcome");
                alertType.setHeaderText(null);
                alertType.setContentText("TypeCheck Failed!");
                Button confirm = (Button) alertType.getDialogPane().lookupButton( ButtonType.OK );
                confirm.setDefaultButton(false);
                confirm.setStyle("-fx-focus-color: transparent; -fx-faint-focus-color: transparent;");
                alertType.showAndWait();
                System.exit(1);
//                System.out.println(e.getMessage());
            }
        }
        System.out.println("All types checks have passed!");

        for (int i = 1; i < 17; i++) {
            String filName = "logFile" + i + ".out";

            PrgState myPrgState = new PrgState(stmts.get(i));
            Repo myRepo = new Repo(myPrgState, filName);
            Controller myController = new Controller(myRepo);
            myData.add(myController);
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        ObservableList<Controller> myData = FXCollections.observableArrayList();
        setUp(myData);
        myPrgList.setItems(myData);
        System.out.println(myData.toString());

        myPrgList.getSelectionModel().selectFirst();
        runButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle (ActionEvent e) {
                Stage programStage = new Stage();
                Parent programRoot;
                Callback<Class<?>, Object> controllerFactory = type -> {
                    if (type == PrgRunController.class) {
                        return new PrgRunController(myPrgList.getSelectionModel().getSelectedItem());
                    } else {
                        try {
                            return type.newInstance();
                        } catch (Exception exc) {
                            System.err.println("Could not create controller for " + type.getName());
                            throw new RuntimeException(exc);
                        }
                    }
                };
                try {
                    FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ProgramLayout.fxml"));
                    fxmlLoader.setControllerFactory(controllerFactory);
                    programRoot = fxmlLoader.load();
                    Scene programScene = new Scene(programRoot);
                    programStage.setTitle("Toy Language - Program running");
                    programStage.setScene(programScene);
                    programStage.show();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        });
    }
}
