package app.model;

import app.socket.Client;

import java.util.ArrayList;
import java.util.List;

public class FileController {

    Client client;

    public FileInfo upload() {
        System.out.println("uploading");

        return new FileInfo("testUpload", "testUser", 123);
    }

    public void download(FileInfo file) {
        System.out.println("downloading " + file.getFilename());
    }

    public void remove(FileInfo file) {
        System.out.println("removing " + file.getFilename());
    }

    public List<FileInfo> listServerFiles() {
        List<FileInfo> personData = new ArrayList<>();
        personData.add(new FileInfo("test", "test", 2));
        personData.add(new FileInfo("test2", "test", 3));
        personData.add(new FileInfo("test3", "test", 4));

        return personData;
    }

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }
}
