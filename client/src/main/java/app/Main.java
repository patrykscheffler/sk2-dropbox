package app;

import app.controllers.Home;
import app.controllers.Login;
import app.model.FileInfo;
import app.socket.Client;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {

    private Stage primaryStage;
    private ObservableList<FileInfo> personData = FXCollections.observableArrayList();
    private Client client;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        this.primaryStage = primaryStage;
        initLoginLayout();
    }

    public void initLoginLayout() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(Main.class.getResource("/fxml/login.fxml"));
        Parent root = loader.load();

        Login loginController = loader.getController();
        loginController.setMainApp(this);
        loginController.setStage(primaryStage);

        primaryStage.setScene(new Scene(root, 650, 400));
        primaryStage.setResizable(false);
        primaryStage.show();
    }

    public void initHomeLayout() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(Main.class.getResource("/fxml/home.fxml"));
        Parent root = loader.load();

        Home homeController = loader.getController();
        homeController.setMainApp(this);
        homeController.getServerFileList();

        primaryStage.setScene(new Scene(root, 1000, 550));
        primaryStage.setResizable(false);
        primaryStage.show();

    }

    public ObservableList<FileInfo> getPersonData() {
        return personData;
    }

    public void addPersonData(FileInfo file){
        this.personData.add(file);
    }

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }
}