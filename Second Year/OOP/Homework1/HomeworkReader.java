//package tema1;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author alexm
 */
public class HomeworkReader {
    
    private BufferedReader bf;
    
    public HomeworkReader(String filename) {
        try {
            bf = new BufferedReader(new FileReader(new File(filename)));
        } catch (FileNotFoundException ex) {
            Logger.getLogger(HomeworkReader.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public ProblemData readData(){
        ProblemData result = null;
        
        try {  
            //Cache
            String cacheType = bf.readLine().trim();
            int cacheCapacity = Integer.parseInt(bf.readLine().trim());
            
            //Scheduler
            String schedulerType = bf.readLine().trim();
            
            //Processes
            int numberOfEvents = Integer.parseInt(bf.readLine().trim());
            ProcessStructure[] processes = new ProcessStructure[numberOfEvents];
            for (int i = 0; i < numberOfEvents; ++i) {
                StringTokenizer st = new StringTokenizer(bf.readLine().trim());
                String procType = st.nextToken();
                int procWeight = Integer.parseInt(st.nextToken());
                processes[i] = new ProcessStructure(procType, procWeight);
            }
            
            //Numbers
            int numberOfNumbers = Integer.parseInt(bf.readLine().trim());
            int[] numbersToBeProcessed = new int[numberOfNumbers];
            for (int i = 0 ; i < numberOfNumbers; ++i) {
                numbersToBeProcessed[i] = Integer.parseInt(bf.readLine().trim());
            }
            
            result = new ProblemData(cacheType, cacheCapacity, schedulerType, processes, numbersToBeProcessed);
            
        } catch (IOException ex) {
            Logger.getLogger(HomeworkReader.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return result;
    }
    
    public void close() {
        try {
            bf.close();
        } catch (IOException ex) {
            Logger.getLogger(HomeworkReader.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
