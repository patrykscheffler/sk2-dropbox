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

    public static SocketMessage readFromBuffer(DataInputStream dataInputStream) throws IOException {
        byte[] user = new byte[nameBits];
        dataInputStream.read(user, 0, nameBits);
        byte[] name = new byte[nameBits];
        dataInputStream.read(name, 0, nameBits);
        int size = dataInputStream.readInt();

        return new SocketMessage(new String(user), new String(name), size);
    }

    public void writeToBuffer(DataOutputStream dataOutputStream) throws IOException {
//        this.user = String.format("%0$-" + nameBits + "s", this.user).substring(0,nameBits-1) + '\0';
//        this.name = String.format("%0$-" + nameBits + "s", this.name).substring(0,nameBits-1) + '\0';

        this.user = formatStringToLength(this.user, this.nameBits);
        this.name = formatStringToLength(this.name, this.nameBits);

        dataOutputStream.write(this.user.getBytes());
        dataOutputStream.write(this.name.getBytes());
        dataOutputStream.writeInt(this.size);
    }

    private String formatStringToLength(String toFormat, int length){
        String ret;
        if(toFormat.length() < length){
            StringBuilder stringBuilder = new StringBuilder(String.format("%0$-" + length + "s", toFormat));
            stringBuilder.setCharAt(toFormat.length(), '\0');
            ret = stringBuilder.toString();
        }else{
            ret = String.format("%0$-" + length + "s", toFormat).substring(0,length-1) + '\0';
        }
        return ret;
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
