
public class SquareEvent extends Event {
    private int x;
    private int y;

    public SquareEvent(EventType type, int number) {
        super(type, number);
    }
    
    @Override
    public int execute() {
        x = number;
        
        while(true) {
          y = (x + number / x) / 2;
          if( y >= x ) 
              return x;
          x = y;
        }
    }    
}