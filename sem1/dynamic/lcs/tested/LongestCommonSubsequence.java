package tested;

import java.util.stream.IntStream;

/*
 * Класс-утилита (им можно пользоваться без создания набором статических методов, как например классом Math) LongestCommonSubsequence
 * Использовать саму функцию можно посредством вызова LongestCommonSubsequence.apply(a, b)
 */
public class LongestCommonSubsequence {

    //Делаем конструктор приватным, чтобы им можно было пользоваться только как классом утилитой (иметь доступ только к его методам как статическим функциям)
    private LongestCommonSubsequence() {}

    private static int recursiveImpl(
            final CharSequence a,
            final CharSequence b,
            final int m,
            final int n,
            final int[][] dp) {
        if ((m == 0) || (n == 0)) {
            return 0;
        }
        if (dp[m][n] != -1) {
            return dp[m][n];
        }
        if (a.charAt(m - 1) == b.charAt(n - 1)) {
            dp[m][n] = 1 + recursiveImpl(a, b, m - 1, n - 1, dp);
            return dp[m][n];
        }
        dp[m][n] = Math.max(recursiveImpl(a, b, m, n - 1, dp), recursiveImpl(a, b, m - 1, n, dp));
        return dp[m][n];
    }

    /*
     * @param a: CharSequence - первая строка
     * @param b: CharSequence - вторая строка
     * @result int - наибольшая общая подпоследовательность строк a и b
     */
    public static int apply(final CharSequence a, final CharSequence b) {
        final int m = a.length();
        final int n = b.length();
        final int[][] dp = IntStream.rangeClosed(0, m)
                .mapToObj($0 -> IntStream.rangeClosed(0, n)
                        .map($1 -> -1)
                        .toArray())
                .toArray(int[][]::new);
        return recursiveImpl(a, b, m, n, dp);
    }

    //Прогоняем тесты (по дефолту, при выгрузке репозитория при чистом запуске)
    public static void main(String[] args) {
        LongestCommonSubsequenceTest.test();
    }

}

class LongestCommonSubsequenceTest {

    public static void test() {
        TestChecker testChecker = new TestChecker(LongestCommonSubsequence.class);
        Object[][] testCases = {
                { "AGGTAB", "GXTXAYB", 4, "lcs(\"AGGTAB\", \"GXTXAYB\") == 4" },
                { "aab", "aa", 2, "lcs(\"aab\", \"aa\") == 2" },
                { "afewfabcaac", "aawevaa", 4, "lcs(\"afewfabcaac\", \"aawevaa\") == 4" },
        };
        int passed = 0;
        int error = 0;
        for (Object[] testCase : testCases) {
            try {
                int expected = (Integer) testCase[2];
                int actual = LongestCommonSubsequence.apply(
                        (CharSequence) testCase[0],
                        (CharSequence) testCase[1]);
                String testName = (String) testCase[3];
                testChecker.check((expected == actual), testName);
                System.out.printf("%s passed\n", testCase[3]);
                passed++;
            } catch (TestNotPassedException e) {
                System.out.println(e.getMessage());
                error++;
            }
        }
        System.out.printf("Tests: passed: %d, error: %d\n", passed, error);
    }

}

class TestNotPassedException extends RuntimeException {

    public TestNotPassedException(String name, Class<?> clazz) {
        super(String.format("Test in class \"%s\" named \"%s\" not passed", clazz.getName(), name));
    }

}

class TestChecker {

    private final Class<?> clazz;

    public TestChecker(Class<?> clazz) {
        this.clazz = clazz;
    }

    public void check(boolean condition, String testName) {
        if (!condition) {
            throw new TestNotPassedException(testName, clazz);
        }
    }

}
