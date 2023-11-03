public class RabinKarpAlgorithm {

    public static void search(String text, String pattern, int q) {
        int n = text.length();
        int m = pattern.length();
        int h = 1;
        int d = 256; // Number of characters in the input alphabet

        for (int i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }

        int p = 0; // Hash value for pattern
        int t = 0; // Hash value for text

        // Calculate the hash value of the pattern and the first window of text
        for (int i = 0; i < m; i++) {
            p = (d * p + pattern.charAt(i)) % q;
            t = (d * t + text.charAt(i)) % q;
        }

        for (int i = 0; i <= n - m; i++) {
            if (p == t) {
                // Check character by character
                boolean match = true;
                for (int j = 0; j < m; j++) {
                    if (text.charAt(i + j) != pattern.charAt(j)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    System.out.println("Pattern found at position " + i);
                }
            }

            if (i < n - m) {
                // Update hash value for the next window of text
                t = (d * (t - text.charAt(i) * h) + text.charAt(i + m)) % q;
                if (t < 0) {
                    t = (t + q);
                }
            }
        }
    }

    public static void main(String[] args) {
        // Test Case 1
        String text1 = "2359023141526739921";
        String pattern1 = "31415";
        int q1 = 13;
        System.out.println("Test Case 1:");
        search(text1, pattern1, q1);

        // Test Case 2
        String text2 = "ABAAABCDBBABCDDEBCABC";
        String pattern2 = "ABC";
        int q2 = 101;
        System.out.println("\nTest Case 2:");
        search(text2, pattern2, q2);
    }
}
