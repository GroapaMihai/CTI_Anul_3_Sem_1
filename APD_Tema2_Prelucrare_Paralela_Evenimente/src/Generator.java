
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.ArrayBlockingQueue;

public class Generator extends Thread {
    private String line;
    private FileReader fr;
    private BufferedReader br;
    private String fileName;
    private ArrayBlockingQueue<Event> queue;
    private String[] tokens;
    private EventFactory factory;
    
    public Generator(String fileName, ArrayBlockingQueue<Event> queue) {
    	this.fileName = fileName;
        this.queue = queue;
        factory = new EventFactory();
    }
    
    @Override
    public void run() {
        Event event;
        int number;
        
        try {
            fr = new FileReader(fileName);
            br = new BufferedReader(fr);
            
            // citesc linie cu linie fisierul de intrare
            // "sparg" linia in 3 tokeni, delimitati de ',' 
            while (true) {      
                line = br.readLine();
                
                if(line == null)
                    break;

                tokens = line.split(",");
                                
                // extrag informatiile necesare crearii evenimentului
                number = Integer.valueOf(tokens[2]);
                event = factory.createEvent(tokens[1], number);
                
                // thread-ul generator asteapta perioada specificata
                try {
                    Thread.sleep(Integer.valueOf(tokens[0]));
                } catch (InterruptedException ex) {
                    System.out.println("Error: " + ex.getMessage());
                }
                
                try {
					queue.put(event);
				} catch (InterruptedException ex) {
					System.out.println("Error: " + ex.getMessage());
				}
            }        
        } catch (IOException ex) {
          System.out.println("Error: " + ex.getMessage());
        }
    }
}