import java.util.Random;
/**
 * NickGen class, generates a random nick
 * @author Nathan
 *
 */
public class NickGen
{
	/**
	 * Constructor
	 */
    public NickGen()
    {
    }
    /**
     * Returns a random String
     * @return
     */
    public static String getUniqueID()
    {
        String str=new  String("QAa0bcLdUK2eHfJgTP8XhiFj61DOklNm9nBoI5pGqYVrs3CtSuMZvwWx4yE7zR");
     	StringBuffer sb=new StringBuffer();
     	Random r = new Random();
     	int te=0;
     	for(int i=1;i<=4;i++){
     		te=r.nextInt(62);
     		sb.append(str.charAt(te));
     	}
     	return sb.toString();
    }
}