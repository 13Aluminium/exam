import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Item {
    char name;
    double profit;
    double weight;

    public Item(char name, double profit, double weight) {
        this.name = name;
        this.profit = profit;
        this.weight = weight;
    }
}

public class FractionalKnapsack {
    public static double fractionalKnapsack(List<Item> items, double capacity) {
        Collections.sort(items, (item1, item2) -> Double.compare(item2.profit / item2.weight, item1.profit / item1.weight));

        double totalProfit = 0;
        double currentWeight = 0;

        for (Item item : items) {
            if (currentWeight + item.weight <= capacity) {
                currentWeight += item.weight;
                totalProfit += item.profit;
            } else {
                double remainingCapacity = capacity - currentWeight;
                totalProfit += (item.profit / item.weight) * remainingCapacity;
                break;
            }
        }

        return totalProfit;
    }

    public static void main(String[] args) {
        // Test Case 1
        List<Item> items1 = new ArrayList<>();
        items1.add(new Item('A', 1, 2));
        items1.add(new Item('B', 2, 3));
        items1.add(new Item('C', 5, 4));
        double capacity1 = 5;

        // Test Case 2
        List<Item> items2 = new ArrayList<>();
        items2.add(new Item('A', 10, 2));
        items2.add(new Item('B', 5, 3));
        items2.add(new Item('C', 15, 5));
        items2.add(new Item('D', 7, 7));
        items2.add(new Item('E', 6, 1));
        items2.add(new Item('F', 18, 4));
        items2.add(new Item('G', 3, 1));
        double capacity2 = 15;

        // Test Case 3
        List<Item> items3 = new ArrayList<>();
        items3.add(new Item('A', 12, 4));
        items3.add(new Item('B', 10, 6));
        items3.add(new Item('C', 8, 5));
        items3.add(new Item('D', 11, 7));
        items3.add(new Item('E', 14, 3));
        items3.add(new Item('F', 7, 1));
        items3.add(new Item('G', 9, 6));
        double capacity3 = 18;

        double result1 = fractionalKnapsack(items1, capacity1);
        double result2 = fractionalKnapsack(items2, capacity2);
        double result3 = fractionalKnapsack(items3, capacity3);

        System.out.println("Test Case 1: Maximum Profit = " + result1);
        System.out.println("Test Case 2: Maximum Profit = " + result2);
        System.out.println("Test Case 3: Maximum Profit = " + result3);
    }
}
