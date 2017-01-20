package app.model;

import app.socket.Client;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class FileController {

    Client client;

    public FileInfo upload(File file) {
        System.out.println("uploading " + file.getName() + " " + file.length());
        client.uploadFile(file);
        return new FileInfo(file.getName(), client.getUserName(), file.length());
    }

    public void download(FileInfo fileInfo, File file) {
        System.out.println("downloading " + fileInfo.getFilename());
        client.downloadFile(fileInfo, file);
    }

    public void remove(FileInfo file) {
        System.out.println("removing " + file.getFilename());
        client.removeFile(file);
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
