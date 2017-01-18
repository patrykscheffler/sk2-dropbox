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

        showFileDetails(null);
        fileTable.getSelectionModel().selectedItemProperty().addListener(
                (observable, oldValue, newValue) -> showFileDetails(newValue)
        );
    }

    @FXML
    private void handleUploadButton() {
        System.out.println("upload");
    }

    @FXML
    private void handleDownloadButton() {
        System.out.println("download");
    }

    @FXML
    private void handleDeleteButton() {
        System.out.println("delete");
    }

    public void setMainApp(Main mainApp) {
        this.mainApp = mainApp;

        fileTable.setItems(mainApp.getPersonData());
    }

    private void showFileDetails(FileInfo file) {
        if (file != null) {
            nameLabel.setText(file.getFilename());
            sizeLabel.setText(Integer.toString(file.getSize()));
        } else {
            nameLabel.setText("");
            sizeLabel.setText("");
        }
    }
}