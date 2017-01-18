package app.controllers;

import app.Main;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;

public class Login {
    @FXML
    private TextField hostIp;
    @FXML
    private TextField port;
    @FXML
    private TextField username;

    @FXML
    private Button submitButton;

    @FXML
    private Stage stage;

    private Main mainApp;

    public Login() {
    }

    @FXML
    private void initialize() {
    }

    @FXML
    private void handleSubmitButton() throws IOException {
        System.out.println("submit");
        stage.close();

        mainApp.initHomeLayout();
    }

    public void setMainApp(Main mainApp) {
        this.mainApp = mainApp;
    }

    public void setStage(Stage stage) {
        this.stage = stage;
    }
}
