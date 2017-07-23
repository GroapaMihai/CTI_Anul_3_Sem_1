import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    public static List<Integer> primeResults;
    public static List<Integer> factResults;
    public static List<Integer> squareResults;
    public static List<Integer> fibResults;
	
    public static void main(String[] args) {
    	int i;
    	int queueCapacity = Integer.parseInt(args[0]);
    	int eventsPerFile = Integer.parseInt(args[1]);
    	AtomicInteger executedEvents = new AtomicInteger(0);
    	AtomicInteger totalEvents = new AtomicInteger(eventsPerFile * (args.length - 2));
        int processors = Runtime.getRuntime().availableProcessors();
        AtomicInteger availableWorkers = new AtomicInteger(processors);
        
        ExecutorService tpe = Executors.newFixedThreadPool(processors);
        ArrayList<Generator> generators = new ArrayList<Generator> ();
        ArrayBlockingQueue<Event> queue = new ArrayBlockingQueue<>(queueCapacity, true);
        
        primeResults = Collections.synchronizedList(new ArrayList<>());
        factResults = Collections.synchronizedList(new ArrayList<>());
        squareResults = Collections.synchronizedList(new ArrayList<>());
        fibResults = Collections.synchronizedList(new ArrayList<>());
        
        for(i = 2; i < args.length; i++)
        	generators.add(new Generator(args[i], queue));
        
        EventExecutor executor = new EventExecutor(tpe, queue);
        executor.setExecutedEvents(executedEvents);
        executor.setTotalEvents(totalEvents);
        executor.setAvailableWorkers(availableWorkers);
        executor.start();
        
        for(i = 0; i < generators.size(); i++)
            generators.get(i).start();
        
        try {
        	executor.join();
        } catch (InterruptedException ex) {
        	System.out.println("Error: " + ex.getMessage());
        }
        
        tpe.shutdown();
        
        try {
            tpe.awaitTermination(Long.MAX_VALUE, TimeUnit.SECONDS);
        } catch (InterruptedException ex) {
        	System.out.println("Error: " + ex.getMessage());
        }
        
        for(i = 0; i < generators.size(); i++)
			try {
				generators.get(i).join();
			} catch (InterruptedException ex) {
				System.out.println("Error: " + ex.getMessage());
			}
        
        // sortez rezultatele
        Collections.sort(primeResults);
        Collections.sort(factResults);
        Collections.sort(squareResults);
        Collections.sort(fibResults);

        Writer primeWriter = new Writer("PRIME.out", primeResults);
        Writer factWriter = new Writer("FACT.out", factResults);
        Writer squareWriter = new Writer("SQUARE.out", squareResults);
        Writer fibWriter = new Writer("FIB.out", fibResults);
        
        primeWriter.start();
        factWriter.start();
        squareWriter.start();
        fibWriter.start();
        
        try {
			primeWriter.join();
	        factWriter.join();
	        squareWriter.join();
	        fibWriter.join();
		} catch (InterruptedException ex) {
			System.out.println("Error: " + ex.getMessage());
		}
    }
}