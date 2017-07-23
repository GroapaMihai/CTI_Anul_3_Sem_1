import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class EventExecutor extends Thread {
	private AtomicInteger executedEvents;
	private AtomicInteger totalEvents;
	private AtomicInteger availableWorkers;
    private ArrayBlockingQueue<Event> queue;
    private ExecutorService tpe;
    
    public EventExecutor(ExecutorService tpe, ArrayBlockingQueue<Event> queue) {
        this.tpe = tpe;
        this.queue = queue;        
    }
    
    public void setExecutedEvents(AtomicInteger executedEvents) {
    	this.executedEvents = executedEvents;
    }
    
    public void setTotalEvents(AtomicInteger totalEvents) {
    	this.totalEvents = totalEvents;
    }
    
    public void setAvailableWorkers(AtomicInteger availableWorkers) {
    	this.availableWorkers = availableWorkers;
    }
    
    public void run() {
        while(!queue.isEmpty() || executedEvents.get() < totalEvents.get()) {
            if(availableWorkers.get() > 0 && !queue.isEmpty())
                try {
                    tpe.submit(new Worker(queue.take(), availableWorkers));  
                    availableWorkers.decrementAndGet();
                    executedEvents.incrementAndGet();
                } catch (InterruptedException ex) {
                    System.out.println(ex);
                } 
        } 
    }   
}