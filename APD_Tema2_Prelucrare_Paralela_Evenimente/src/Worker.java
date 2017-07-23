import java.util.concurrent.atomic.AtomicInteger;

public class Worker extends Thread {
    private Event event;
    private AtomicInteger availableWorkers;
    
    public Worker(Event event, AtomicInteger availableWorkers) {
        this.event = event;
        this.availableWorkers = availableWorkers;
    }
    
    @Override
    public void run() {
        EventType type = event.getEventType();

        switch(type) {
            case PRIME : Main.primeResults.add(event.execute()); break;
            case FACT : Main.factResults.add(event.execute()); break;
            case SQUARE : Main.squareResults.add(event.execute()); break;
            case FIB : Main.fibResults.add(event.execute()); break;
        }
        
        availableWorkers.incrementAndGet();
    }
}