//package tema1;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author alexm
 */
public class HomeworkWriter {
    
    private PrintWriter pw;
    
    public HomeworkWriter(String filename) {
        try {
            pw = new PrintWriter(new File(filename));
        } catch (FileNotFoundException ex) {
            Logger.getLogger(HomeworkWriter.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void println(String text) {
        pw.println(text);
    }
    
    public void close() {
        pw.close();
    }
}
