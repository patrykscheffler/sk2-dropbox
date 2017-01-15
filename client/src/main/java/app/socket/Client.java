package app.socket;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class Client {
    String hostName;
    int port;

    Socket socket;
    OutputStream toServer;
    InputStream fromServer;


    public Client(String hostName, int port) {
        this.hostName = hostName;
        this.port = port;
    }

    public void openConnection() {
        try {
            this.socket = new Socket(this.hostName, this.port);
            this.toServer = this.socket.getOutputStream();
            this.fromServer = this.socket.getInputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void closeConnection() {
        try {
            this.socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
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
}