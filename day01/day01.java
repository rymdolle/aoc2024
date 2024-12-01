import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class day01 {
    public static void main(String[] args) {
        try (FileInputStream input = new FileInputStream("day01/input.txt")) {
            Scanner scanner = new Scanner(input);

            var first = new ArrayList<Integer>();
            var second = new ArrayList<Integer>();
            while (scanner.hasNextLine()) {
                first.add(scanner.nextInt());
                second.add(scanner.nextInt());
                scanner.nextLine();
            }

            Collections.sort(first);
            Collections.sort(second);
            System.out.println(first.size());
            int sum = 0;
            for (int i = 0; i < first.size(); i++) {
                int diff = Math.abs(first.get(i) - second.get(i));
                sum += diff;
            }
            System.out.println(sum);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
