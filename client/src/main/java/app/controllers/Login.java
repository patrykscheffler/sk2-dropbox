package app.controllers;

import app.Main;
import app.socket.Client;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.Socket;

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

    @FXML
    private void initialize() {
    }

    @FXML
    private void handleSubmitButton() throws IOException {
        if (!validateFields())
            return;
        try {
            Client client = new Client(hostIp.getText(), username.getText(), Integer.parseInt(port.getText()));
            mainApp.setClient(client);
        }catch (NumberFormatException e){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.initOwner(stage);
            alert.setHeaderText("Port is not a number");
            alert.showAndWait();

            return;
        }catch (Exception e){
            System.out.println(e);

            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.initOwner(stage);
            alert.setHeaderText("Unable to create connection");
            alert.showAndWait();

            return;
        }
        stage.close();
        mainApp.initHomeLayout();
    }

    private boolean validateFields(){
        StringBuilder stringBuilder = new StringBuilder();
        if (!validateField(hostIp))
            stringBuilder.append("HostIp needed \n");

        if (!validateField(port))
            stringBuilder.append("Port needed \n");

        if (!validateField(username))
            stringBuilder.append("Username needed \n");

        if(stringBuilder.length() == 0){
            return true;
        } else {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.initOwner(stage);
            alert.setHeaderText("Check fields");
            alert.setContentText(stringBuilder.toString());
            alert.showAndWait();

            return false;
        }
    }

    private boolean validateField(TextField field){
        return !(field.getText() == null || field.getText().length() == 0);
    }

    public void setMainApp(Main mainApp) {
        this.mainApp = mainApp;
    }

    public void setStage(Stage stage) {
        this.stage = stage;
    }
}
