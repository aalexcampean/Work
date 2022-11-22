package gui;

import java.io.BufferedReader;
import java.net.URL;
import java.util.HashMap;
import java.util.List;
import java.util.ResourceBundle;

import controller.Controller;
import model.PrgState;
import model.adtContainers.IList;
import model.adtContainers.MyList;
import model.statements.IStmt;


import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import model.values.IValue;
import model.values.StringValue;

public class PrgRunController implements Initializable {
    Controller myController;

    @FXML
    Label nrPrgStates;

    // programStateList
    @FXML
    ListView<String> prgStateList;

    // executionStack
    @FXML
    ListView<String> exeStackList;

    // symbolTable
    @FXML
    TableView<HashMap.Entry<String, IValue>> symTable;
    @FXML
    TableColumn<HashMap.Entry<String, IValue>, String> symTableVariable;
    @FXML
    TableColumn<HashMap.Entry<String, IValue>, String> symTableValue;

    // heapTable
    @FXML
    TableView<HashMap.Entry<Integer, IValue>> heapTable;
    @FXML
    TableColumn<HashMap.Entry<Integer,IValue>, String> heapTableAddress;
    @FXML
    TableColumn<HashMap.Entry<Integer,IValue>, String> heapTableValue;

    // fileTable
    @FXML
    TableView<HashMap.Entry<StringValue, BufferedReader>> fileTable;
    @FXML
    TableColumn<HashMap.Entry<StringValue, BufferedReader>, String> fileTableIdentifier;
    @FXML
    TableColumn<HashMap.Entry<StringValue, BufferedReader>, String> fileTableFileName;

    // outList
    @FXML
    ListView<String> outList;

    // latchTable
    @FXML
    TableView<HashMap.Entry<Integer, Integer>> latchTable;
    @FXML
    TableColumn<HashMap.Entry<Integer, Integer>, String> latchTableAddress;
    @FXML
    TableColumn<HashMap.Entry<Integer, Integer>, String> latchTableValue;

    // runOneStep Button
    @FXML
    Button runButton;


    public PrgRunController(Controller myController) {
        this.myController = myController;
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        initialRun();
        prgStateList.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                setSymTableAndExeStack();
            }
        });
        runButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle (ActionEvent e) {
                try {
                    myController.oneStepGui();
                    updateUIComponents();
                } catch (Exception e1) {
                    Alert alert = new Alert(AlertType.INFORMATION);
                    alert.setTitle("Toy Language - Current program finished");
                    alert.setHeaderText(null);
                    alert.setContentText("Program successfully finished!");
                    Button confirm = (Button) alert.getDialogPane().lookupButton( ButtonType.OK );
                    confirm.setDefaultButton(false);
                    confirm.setStyle("-fx-focus-color: transparent; -fx-faint-focus-color: transparent;");
                    alert.showAndWait();
                    Stage stage = (Stage) heapTable.getScene().getWindow();
                    stage.close();
                }
//                try {
//                    updateUIComponents();
//                }
//                catch (Exception ex) {
//                    ex.printStackTrace();
//                }
            }
        });
    }

    public void initialRun() {
        setNumberLabel();
        setPrgStateList();
        prgStateList.getSelectionModel().selectFirst();
        setSymTableAndExeStack();
        setHeapTable();
        setFileTable();
        setOutList();
        setLatchTable();
    }

    public void updateUIComponents() {
        setNumberLabel();
        setPrgStateList();
        if(prgStateList.getSelectionModel().getSelectedItem() == null) {
            prgStateList.getSelectionModel().selectFirst();
        }
        setSymTableAndExeStack();
        setHeapTable();
        setFileTable();
        setOutList();
        setLatchTable();

        List<PrgState> updatedList = myController.removeCompletedPrg(myController.getRepo().getPrgList().getAll());
        IList<PrgState> copyList = new MyList<>(updatedList);
        myController.getRepo().setPrgList(copyList);
    }

    public void setNumberLabel() {
        nrPrgStates.setText("The number of PrgStates: " + myController.getRepo().getPrgList().size());
    }

    public void setPrgStateList() {
        ObservableList<String> prgStateIdList = FXCollections.observableArrayList();
        for(PrgState e : myController.getRepo().getPrgList().getAll()) {
            prgStateIdList.add(Integer.toString(e.getId()));
        }
        prgStateList.setItems(prgStateIdList);
    }

    public void setSymTableAndExeStack() {
        ObservableList<HashMap.Entry<String, IValue>> symTableList = FXCollections.observableArrayList();
        ObservableList<String> exeStackItemsList = FXCollections.observableArrayList();
        symTableVariable.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getKey()));
        symTableValue.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getValue().toString()));
        List<PrgState> allPrgs = myController.getRepo().getPrgList().getAll();

        PrgState prgResult = null;

        for(PrgState e : allPrgs) {
            if(e.getId() == Integer.parseInt(prgStateList.getSelectionModel().getSelectedItem())) {
                prgResult = e;
                break;
            }
        }

        if(prgResult != null) {
            symTableList.addAll(prgResult.getSymTable().getContent().entrySet());
            for(IStmt e : prgResult.getExeStack().getStmts()) {
                exeStackItemsList.add(e.toString());
            }
            symTable.setItems(symTableList);
            exeStackList.setItems(exeStackItemsList);
            symTable.refresh();
        }else {
            exeStackList.setItems(exeStackItemsList);
        }
    }

    public void setHeapTable() {
        if (myController.getRepo().getPrgList().size() > 0) {
            ObservableList<HashMap.Entry<Integer, IValue>> heapTableList = FXCollections.observableArrayList();
            heapTableAddress.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(Integer.toString(cellData.getValue().getKey())));
            heapTableValue.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getValue().toString()));
            heapTableList.addAll(myController.getRepo().getPrgList().get(0).getHeap().getContent().entrySet());

            heapTable.setItems(heapTableList);
            heapTable.refresh();
        }

    }

    public void setFileTable() {
        if (myController.getRepo().getPrgList().size() > 0) {
            ObservableList<HashMap.Entry<StringValue, BufferedReader>> fileTableList = FXCollections.observableArrayList();
            fileTableIdentifier.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getKey().toString()));
            fileTableFileName.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getValue().toString()));
            fileTableList.addAll(myController.getRepo().getPrgList().get(0).getFileTable().getContent().entrySet());

            fileTable.setItems(fileTableList);
        }
    }

    public void setOutList() {
        if (myController.getRepo().getPrgList().size() > 0) {
            ObservableList<String> outObservableList = FXCollections.observableArrayList();
            for (IValue e : myController.getRepo().getPrgList().get(0).getOut().getAll()) {
                outObservableList.add(e.toString());
            }

            outList.setItems(outObservableList);
            outList.refresh();
        }
    }

    public void setLatchTable() {
        if (myController.getRepo().getPrgList().size() > 0) {
            ObservableList<HashMap.Entry<Integer, Integer>> latchTableList = FXCollections.observableArrayList();
            latchTableAddress.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(Integer.toString(cellData.getValue().getKey())));
            latchTableValue.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(Integer.toString(cellData.getValue().getValue())));
            latchTableList.addAll(myController.getRepo().getPrgList().get(0).getLatchTbl().getContent().getContent().entrySet());

            latchTable.setItems(latchTableList);
            latchTable.refresh();
        }
    }



}
