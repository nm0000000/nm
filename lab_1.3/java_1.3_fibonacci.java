// СОЗДАНИЕ КУЧИ ФИБОНАЧЧИ НА JAVA

class Fibonacci {
    public static long fibonacci(long n) {
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        } else {
            return fibonacci(n - 1) + fibonacci(n - 2);
        }
    }

    public static void main(String[] args) {
        System.out.println("Value of 17th number in fibonacci series — " + fibonacci(17));
    }
}
