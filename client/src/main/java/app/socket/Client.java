package app.socket;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class Client {

    String hostName;
    int port;

    Socket socket;

    public Client(String hostName, int port) {
        this.hostName = hostName;
        this.port = port;
    }

    public void loop(){
        try{
            this.socket = new Socket(this.hostName, this.port);

            DataOutputStream toServer = new DataOutputStream(this.socket.getOutputStream());
            BufferedReader fromServer = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));

            toServer.writeBytes("hello\n");
            System.out.println(fromServer.readLine());

            this.socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
