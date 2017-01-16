package app;

import app.socket.Client;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {

    private Stage primaryStage;

    @Override
    public void start(Stage primaryStage) throws Exception {
        this.primaryStage = primaryStage;

        initLoginLayout();
        initHomeLayout();
    }

    public void initLoginLayout() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("/fxml/login.fxml"));
        primaryStage.setScene(new Scene(root, 650, 400));
        primaryStage.setResizable(false);
        primaryStage.show();
    }

    public void initHomeLayout() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("/fxml/home.fxml"));
        primaryStage.setScene(new Scene(root, 1000, 550));
        primaryStage.setResizable(false);
        primaryStage.show();
    }

    public static void main(String[] args) {
//        Client client = new Client("localhost", 1234);
//        client.loop();
        launch(args);
    }

}