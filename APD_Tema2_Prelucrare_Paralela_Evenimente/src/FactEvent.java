
public class FactEvent extends Event {

    public FactEvent(EventType type, int number) {
        super(type, number);
    }
    
    @Override
    public int execute() {
        int factorial = 1;
        int currentNumber = 1;
        
        while(factorial <= number) {
            factorial *= currentNumber++;
        }
        
        return currentNumber - 2;
    }
}