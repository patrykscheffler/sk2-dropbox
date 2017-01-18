package app.model;

public class FileController {

    public FileInfo upload(){
        System.out.println("uploading");

        return new FileInfo("testUpload", "testUser", 123);
    }

    public void download(FileInfo file){
        System.out.println("downloading " + file.getFilename());
    }

    public void remove(FileInfo file){
        System.out.println("removing " + file.getFilename());
    }
}
