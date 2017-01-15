package app.socket;

import java.io.*;

public class SocketMessage {
    public static int nameBits = 64;
    private String user;
    private String name;
    private int size;

    public SocketMessage(String user, String name, int size) {
        this.user = user;
        this.name = name;
        this.size = size;
    }

    public static SocketMessage readFromBuffer(InputStream inputStream) throws IOException {
        DataInputStream dataInputStream = new DataInputStream(inputStream);

        byte[] user = new byte[nameBits];
        dataInputStream.read(user, 0, nameBits);
        byte[] name = new byte[nameBits];
        dataInputStream.read(name, 0, nameBits);
        int size = dataInputStream.readInt();

        return new SocketMessage(new String(user), new String(name), size);
    }

    public void writeToBuffer(OutputStream outputStream) throws IOException {
        DataOutputStream dataOutputStream = new DataOutputStream(outputStream);
        dataOutputStream.write(this.user.getBytes());
        dataOutputStream.write(this.name.getBytes());
        dataOutputStream.writeInt(this.size);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }
}
