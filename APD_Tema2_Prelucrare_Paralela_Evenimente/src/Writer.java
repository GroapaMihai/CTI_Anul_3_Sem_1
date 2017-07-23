import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

public class Writer extends Thread {
	private FileWriter fw;
	private BufferedWriter bw;
	private List<Integer> output;
	
	public Writer(String fileName, List<Integer> output) {
        File file = new File(fileName);
        this.output = output;
        
        try {
        	fw = new FileWriter(file);
			bw = new BufferedWriter(fw);
		} catch (IOException ex) {
			System.out.println("Error: " + ex.getMessage());
		}
	}
	
	@Override
	public void run() {
		for(int i = 0; i < output.size(); i++)
			try {
				bw.write(String.valueOf(output.get(i)));
				bw.newLine();
			} catch (IOException ex) {
				System.out.println("C Error: " + ex.getMessage());
			} 
		
			   try {
			      if(bw != null)
			    	  bw.close();
			      if(fw != null)
			    	  fw.close();
			   } catch(Exception ex) {
				   System.out.println("Error: " + ex.getMessage());
			    }
	}
}