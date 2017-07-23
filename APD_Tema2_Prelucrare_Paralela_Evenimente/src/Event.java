
public class Event {
    protected final EventType type;
    protected int number;
    
    public Event(EventType type, int number) {
        this.type = type;
        this.number = number;
    }
    
    public EventType getEventType() {
        return type;
    }
    
    public int getNumber() {
        return number;
    }
    
    public int execute() {
        return -1;
    }
    
    @Override
    public String toString() {
        return type + " " + number;
    }
}