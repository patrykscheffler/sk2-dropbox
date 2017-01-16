package app.controllers;

import app.Main;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;

public class Login {
    @FXML
    private TextField hostIp;
    @FXML
    private TextField port;
    @FXML
    private TextField username;

    @FXML
    private Button submitButton;

    private Main mainApp;

    public Login() {
    }

    @FXML
    private void initialize() {
    }

    public void setMainApp(Main mainApp){
        this.mainApp = mainApp;
    }
}
