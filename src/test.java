public class test {
    public static int f(int n)
    {   
        if(n==1)
            return 1;
        else return n*f(n-1);

    }
    static public void main(String[] args) {
        say s = new say("hello");
        s.sayString();
        System.out.println("hello world");
        System.out.println(f(5));
    }
    
}
