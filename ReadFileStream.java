import java.io.*;
 
/**
 * Copy one file to another using low level byte streams, one byte at a time.
 * @author www.codejava.net
 */
// modified by Sam Fryer, December, 2019

public class ReadFileStream {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide input and output files");
            System.exit(0);
        }
 
        String inputFile = args[0];
        String outputFile = args[1];
 
 
        try (
            InputStream inputStream = new FileInputStream(inputFile);
            OutputStream outputStream = new FileOutputStream(outputFile);
        ) {
 
            byte[] bytes = new byte[1024];
            int numRead = 0;
            while ((numRead = inputStream.read(bytes)) != -1) {
                outputStream.write(bytes);
            }
 
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
