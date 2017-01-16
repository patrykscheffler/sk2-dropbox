package app.controllers;

import app.Main;
import app.model.FileInfo;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;

public class Home {
    @FXML
    private TableView<FileInfo> fileTable;
    @FXML
    private TableColumn<FileInfo, String> filenameColumn;

    @FXML
    private Label nameLabel;
    @FXML
    private Label sizeLabel;

    @FXML
    private Button uploadButton;
    @FXML
    private Button downloadButton;
    @FXML
    private Button deleteButton;

    private Main mainApp;

    public Home() {
    }

    @FXML
    private void initialize() {
        filenameColumn.setCellValueFactory(cellData -> cellData.getValue().filenameProperty());
    }

    public void setMainApp(Main mainApp) {
        this.mainApp = mainApp;

        fileTable.setItems(mainApp.getPersonData());
    }

}