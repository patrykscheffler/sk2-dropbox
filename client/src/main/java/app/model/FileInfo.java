package app.model;

import javafx.beans.property.*;

public class FileInfo {
    private final StringProperty filename;
    private final StringProperty user;
    private final LongProperty size;

    public FileInfo(String filename, String user, long size) {
        this.filename = new SimpleStringProperty(filename);
        this.user = new SimpleStringProperty(user);
        this.size = new SimpleLongProperty(size);
    }

    public String getFilename() {
        return filename.get();
    }

    public StringProperty filenameProperty() {
        return filename;
    }

    public void setFilename(String filename) {
        this.filename.set(filename);
    }

    public String getUser() {
        return user.get();
    }

    public StringProperty userProperty() {
        return user;
    }

    public void setUser(String user) {
        this.user.set(user);
    }

    public long getSize() {
        return size.get();
    }

    public LongProperty sizeProperty() {
        return size;
    }

    public void setSize(int size) {
        this.size.set(size);
    }
}
