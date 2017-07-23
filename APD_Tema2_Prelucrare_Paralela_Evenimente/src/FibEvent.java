
public class FibEvent extends Event {
    private int f0 = 0;
    private int f1 = 1;
    private int fibo = 0;
    private int index = 0;

    public FibEvent(EventType type, int number) {
        super(type, number);
    }
    
    @Override
    public int execute() {
        while(fibo <= number) {
            fibo = f0 + f1;
            f0 = f1;
            f1 = fibo;
            index++;
        }
        
        return index;
    }
}