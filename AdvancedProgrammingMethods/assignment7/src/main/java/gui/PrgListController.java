package gui;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.ResourceBundle;

import controller.Controller;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import repository.Repo;
import model.PrgState;

import model.adtContainers.IDictionary;
import model.adtContainers.MyDictionary;

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

        //int v; Ref int a; v=10;new(a,22);
        //fork(wH(a,30);v=32;print(v);print(rH(a)));
        //print(v);print(rH(a))
        IStmt stmt10 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueIExp(new IntValue(10))),
                                new CompStmt(new HeapAllocationStmt("a", new ValueIExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new HeapWritingStmt("a", new ValueIExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueIExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarIExp("v")), new PrintStmt(new HeapReadingExp(new VarIExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarIExp("v")), new PrintStmt(new HeapReadingExp(new VarIExp("a")))))))));


        // creating a list with all the statements so that we can perform the type checks
        ArrayList<IStmt> stmts = new ArrayList<IStmt>(Arrays.asList(stmt1, stmt2, stmt3, stmt3, stmt4, stmt5, stmt6, stmt7, stmt8, stmt9, stmt10));
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

        for (int i = 0; i < 10; i++) {
            String filName = "logFile" + (i + 1) + ".out";

            PrgState myPrgState = new PrgState(stmts.get(i + 1));
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
