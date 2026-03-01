public class Test {
    private static int a = 3;

    public static void main(String[] args) {
        System.out.println(Test.add(a));
    }

    public static int add(int a) {
        return a + 1;
    }
}