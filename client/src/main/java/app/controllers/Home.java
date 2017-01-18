package app.controllers;

import app.Main;
import app.model.FileController;
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

    private FileController fileController;

    public Home() {
        fileController = new FileController();
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
        FileInfo fileInfo = fileController.upload();
        if (fileInfo != null)
            mainApp.addPersonData(fileInfo);
    }

    @FXML
    private void handleDownloadButton() {
        FileInfo fileInfo = fileTable.getSelectionModel().getSelectedItem();
        if (fileInfo == null)
            return;

        fileController.download(fileInfo);
    }

    @FXML
    private void handleDeleteButton() {
        FileInfo fileInfo = fileTable.getSelectionModel().getSelectedItem();
        if (fileInfo == null)
            return;

        fileController.remove(fileInfo);
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