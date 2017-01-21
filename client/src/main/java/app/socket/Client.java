package app.socket;

import app.model.FileInfo;

import java.io.*;
import java.net.Socket;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.List;

public class Client {
    public final static short CLIENT_CONN = 0x01;
    public final static short FILE_READ = 0xF1;
    public final static short FILE_WRITE = 0xF2;
    public final static short LIST_FILES = 0xF3;
    public final static short ACCEPT = 0x00;
    public final static short FAILURE = 0xFF;
    private String hostName;
    private String userName;
    private int port;
    private Socket socket;
    private DataOutputStream toServer;
    private DataInputStream fromServer;

    public Client(String hostName, String userName, int port) throws IOException {
        this.hostName = hostName;
        this.userName = userName;
        this.port = port;
        openConnection();
        closeConnection();
    }

    public void openConnection() throws IOException {
        this.socket = new Socket(this.hostName, this.port);
        this.toServer = new DataOutputStream(this.socket.getOutputStream());
        this.fromServer = new DataInputStream(this.socket.getInputStream());
        this.toServer.writeShort(CLIENT_CONN);
    }

    public void closeConnection() {
        try {
            this.socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void uploadFile(File file) {
        try {
            openConnection();
            SocketMessage socketMessage = new SocketMessage(this.userName, file.getName(), Math.toIntExact(file.length()));

            this.toServer.writeShort(FILE_WRITE);
            socketMessage.writeToBuffer(this.toServer);
            writeFileToBuffer(file);

            closeConnection();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void downloadFile(FileInfo fileInfo, File file) {
        try {
            openConnection();
            SocketMessage socketMessage = new SocketMessage(this.userName, fileInfo.getFilename(), Math.toIntExact(fileInfo.getSize()));

            this.toServer.writeShort(FILE_READ);
            socketMessage.writeToBuffer(this.toServer);

            short resp = this.fromServer.readShort();
            if (resp == ACCEPT) {
                writeBufferToFile(file, Math.toIntExact(fileInfo.getSize()));
            }

            closeConnection();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public List<FileInfo> listFiles() {
        List<FileInfo> fileInfos = new ArrayList<>();
        try {
            openConnection();
            this.toServer.writeShort(LIST_FILES);
            SocketMessage socketMessage;

            socketMessage = new SocketMessage(this.userName, "", 0);
            socketMessage.writeToBuffer(this.toServer);

            while ((socketMessage = SocketMessage.readFromBuffer(this.fromServer)).getName().charAt(0) != '\0')
                fileInfos.add(new FileInfo(socketMessage.getName(), this.userName, socketMessage.getSize()));

            closeConnection();

        } catch (IOException e) {
            e.printStackTrace();
        }
//        List<FileInfo> fileData = new ArrayList<>();
//        fileData.add(new FileInfo("test", "test", 2));
//        fileData.add(new FileInfo("test2", "test", 3));
//        fileData.add(new FileInfo("test3", "test", 4));

        return fileInfos;
    }

    public void removeFile(FileInfo fileInfo) {
//        TODO
    }

    private void writeBufferToFile(File file, int size) throws IOException {
        FileOutputStream fo = new FileOutputStream(file, false);
        fo.getChannel().truncate(0);

        byte[] buffer = new byte[1024];
        int i, leftToWrite;

        leftToWrite = size;
        while (leftToWrite > 0) {
            i = this.fromServer.read(buffer);
            fo.write(buffer, 0, i);
            leftToWrite -= i;
        }
    }

    private void writeFileToBuffer(File file) throws IOException {
        FileInputStream fi = new FileInputStream(file);
        byte[] buffer = new byte[1024];
        int i, leftToWrite;

        leftToWrite = Math.toIntExact(file.length());
        while (leftToWrite > 0) {
            i = fi.read(buffer);
            this.toServer.write(buffer, 0, i);
            leftToWrite -= i;
        }
    }

    public String getUserName() {
        return userName;
    }
}