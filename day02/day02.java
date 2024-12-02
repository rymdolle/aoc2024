import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

public class day02 {
    public static void main(String[] args) {
        try (FileInputStream input = new FileInputStream("day02/input.txt")) {
            Scanner scanner = new Scanner(input);

            var part1 = new HashSet<String>();
            var part2 = new HashSet<String>();
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                Scanner lineScanner = new Scanner(line);

                var report = new ArrayList<Integer>();

                while (lineScanner.hasNextInt()) {
                    report.add(lineScanner.nextInt());
                }

                if (checkReport(report)) {
                    part1.add(line);
                    part2.add(line);
                } else {
                    for (int i = 0; i < report.size(); i++) {
                        var dampen = new ArrayList<>(report);
                        dampen.remove(i);
                        if (checkReport(dampen)) {
                            part2.add(line);
                            break;
                        }
                    }
                }
            }
            System.out.println(part1.size());
            System.out.println(part2.size());
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static boolean checkReport(ArrayList<Integer> report) {
        int dir = report.get(1) - report.get(0);
        for (int i = 0; i < report.size() - 1; i++) {
            int diff = report.get(i + 1) - report.get(i);

            // check if the direction is changing
            if (diff < 0 && dir > 0 || diff > 0 && dir < 0) {
                return false;
            }

            // check if the difference is too large
            if (Math.abs(diff) <= 0 || Math.abs(diff) > 3) {
                return false;
            }
            dir += diff;
        }

        return true;
    }
}
