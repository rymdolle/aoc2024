import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

public class day02 {
    public static void main(String[] args) {
        try (FileInputStream input = new FileInputStream("day02/input.txt")) {
            Scanner scanner = new Scanner(input);

            int linum = 0;
            var reports = new HashSet<Integer>();
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                Scanner lineScanner = new Scanner(line);

                var report = new ArrayList<Integer>();

                while (lineScanner.hasNextInt()) {
                    report.add(lineScanner.nextInt());
                }

                int dir = report.get(1) - report.get(0);
                for (int i = 1; i < report.size(); i++) {
                    int diff = report.get(i) - report.get(i - 1);
                    if (diff < 0 && dir > 0 || diff > 0 && dir < 0) {
                        dir = 0;
                        break;
                    }
                    if (Math.abs(diff) <= 0 || Math.abs(diff) > 3) {
                        dir = 0;
                        break;
                    }
                    dir += diff;
                }

                if (dir != 0) {
                    reports.add(linum);
                }

                linum++;
            }
            System.out.println(reports.size());
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
