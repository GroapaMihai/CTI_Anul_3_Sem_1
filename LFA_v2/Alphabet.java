
import java.util.ArrayList;

public class Alphabet 
{
    private ArrayList<Character> characters;

    public Alphabet() 
    {
        characters = new ArrayList<Character> ();
    }

    public void addCharacter(char s) 
    {
        characters.add(s);
    }

    public ArrayList<Character> getAlphabetCharacters()
    {
    	return characters;
    }

    public boolean contains(char s) 
    {
        for(int i = 0; i < characters.size(); i++)
            if(characters.get(i) == s)
                return true;

        return false;
    }

    public boolean isEmpty() 
    {
        return (characters.size() == 0);
    }
}