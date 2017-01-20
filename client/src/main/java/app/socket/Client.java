package app.socket;

import app.model.FileInfo;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class Client {
    String hostName;
    String userName;
    int port;

    Socket socket;
    OutputStream toServer;
    InputStream fromServer;


    public Client(String hostName, String userName, int port) throws IOException {
        this.hostName = hostName;
        this.userName = userName;
        this.port = port;
        openConnection();
        closeConnection();
    }

    public void openConnection() throws IOException {
            this.socket = new Socket(this.hostName, this.port);
            this.toServer = this.socket.getOutputStream();
            this.fromServer = this.socket.getInputStream();
    }

    public void closeConnection() {
        try {
            this.socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void uploadFile(File file){
//        TODO
    }

    public void downloadFile(FileInfo fileInfo, File file){
//        TODO
    }

    public void removeFile(FileInfo fileInfo){
//        TODO
    }

    public void loop() {
        try {
            this.openConnection();

            BufferedWriter toServer = new BufferedWriter(new OutputStreamWriter(this.toServer));
            toServer.write("hello\n");
            toServer.flush();

            SocketMessage socketMessage = SocketMessage.readFromBuffer(this.fromServer);
            System.out.println(socketMessage.getName());
            System.out.println(socketMessage.getSize());

            this.closeConnection();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public String getUserName() {
        return userName;
    }
}