
public class EventFactory {
    private EventType type;
    
    private EventType getType(String name) {
        if(name.equals("PRIME"))
            return EventType.PRIME;
        if(name.equals("FACT"))
            return EventType.FACT;
        if(name.equals("SQUARE"))
            return EventType.SQUARE;
        return EventType.FIB;
    }
    
    public Event createEvent(String name, int number) {
        type = getType(name);
        
        switch(type) {
            case PRIME : return new PrimeEvent(type, number);
            case FACT : return new FactEvent(type, number);
            case SQUARE : return new SquareEvent(type, number);
            case FIB : return new FibEvent(type, number);
        }
        throw new IllegalArgumentException("The event type " + type + 
                " is not recognized.");
    }
}