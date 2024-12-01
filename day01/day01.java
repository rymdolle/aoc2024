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
            int part1 = 0;
            int part2 = 0;
            for (int i = 0; i < first.size(); i++) {
                int count = Collections.frequency(second, first.get(i));
                part2 += first.get(i) * count;
                int diff = Math.abs(first.get(i) - second.get(i));
                part1 += diff;
            }
            System.out.println(part1);
            System.out.println(part2);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
