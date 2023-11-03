import java.util.Arrays;

public class MinimumCoinsChange {

    public static int minimumCoins(int[] denominations, int amount) {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;

        for (int coin : denominations) {
            for (int i = coin; i <= amount; i++) {
                if (dp[i - coin] != Integer.MAX_VALUE) {
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        return dp[amount] == Integer.MAX_VALUE ? -1 : dp[amount];
    }

    public static void main(String[] args) {
        // Test Case 1
        int[] denominations1 = {1, 2, 3};
        int amount1 = 5;

        // Test Case 2
        int[] denominations2 = {1, 5, 17, 18};
        int amount2 = 22;

        // Test Case 3
        int[] denominations3 = {1, 5, 10, 25, 100};
        int amount3 = 289;

        int result1 = minimumCoins(denominations1, amount1);
        int result2 = minimumCoins(denominations2, amount2);
        int result3 = minimumCoins(denominations3, amount3);

        System.out.println("Test Case 1: Minimum Coins = " + result1);
        System.out.println("Test Case 2: Minimum Coins = " + result2);
        System.out.println("Test Case 3: Minimum Coins = " + result3);
    }
}
