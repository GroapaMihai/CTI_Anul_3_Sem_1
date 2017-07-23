
public class PrimeEvent extends Event {

    public PrimeEvent(EventType type, int number) {
        super(type, number);
    }
    
    public boolean isPrime(int value) {
        if(value % 3 == 0)
            return false;
        
        int i = 5;
        
        while((i * i) <= value) {
            if((value % i == 0) || (value % (i + 2) == 0))
                return false;
            i += 6;
        }

        return true;
    }
    
    @Override
    public int execute() {
        if(number == 2)
            return 2;
        
        if(number <= 4)
            return 3;
        
        if(number % 2 == 0)
            number--;

        // verific doar numere impare
        for(int i = number; i > 2; i = i - 2)
            if(isPrime(i))
                return i;
        
        return -1;
    }
}