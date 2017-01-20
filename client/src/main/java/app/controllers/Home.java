package app.controllers;

import app.Main;
import app.model.FileController;
import app.model.FileInfo;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;

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
    private Stage stage;

    private FileController fileController = new FileController();

    private FileChooser fileChooser = new FileChooser();

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
        File file = fileChooser.showOpenDialog(stage);
        if (file == null)
            return;

        FileInfo fileInfo = fileController.upload(file);
        if (fileInfo != null)
            mainApp.addFileData(fileInfo);
    }

    @FXML
    private void handleDownloadButton() {
        FileInfo fileInfo = fileTable.getSelectionModel().getSelectedItem();
        if (fileInfo == null)
            return;

        File file = fileChooser.showSaveDialog(stage);
        if (file == null)
            return;

        fileController.download(fileInfo, file);
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
        fileTable.setItems(mainApp.getFileData());
        fileController.setClient(mainApp.getClient());
    }

    public void getServerFileList() {
        fileController.listServerFiles().stream().forEach(e -> mainApp.addFileData(e));
    }

    private void showFileDetails(FileInfo file) {
        if (file != null) {
            nameLabel.setText(file.getFilename());
            sizeLabel.setText(Long.toString(file.getSize()));
        } else {
            nameLabel.setText("");
            sizeLabel.setText("");
        }
    }

    public void setStage(Stage stage) {
        this.stage = stage;
    }
}