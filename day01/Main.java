import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void part1(BufferedReader br) throws IOException {
        String line = null;

        int sum = 0;
        while ((line = br.readLine()) != null) {
            int x = 0;
            for (int i = 0; i < line.length(); i++) {
                if (Character.isDigit(line.charAt(i))) {
                    x += line.charAt(i) - '0';
                    System.out.println(x);
                    break;
                }
            }
            x *= 10;
            for (int i = line.length() - 1; i >= 0; i--) {
                if (Character.isDigit(line.charAt(i))) {
                    x += line.charAt(i) - '0';
                    System.out.println(x);
                    break;
                }
            }
            sum += x;
        }
        System.out.println(sum);
    }

    public static int isDigit(String s, int start) {
        if (Character.isDigit(s.charAt(start))) {
            return s.charAt(start) - '0';
        }

        String[] digits = new String[]{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        for (int i = 0; i < digits.length; i++) {
            if (s.substring(start).startsWith(digits[i])) {
                return i + 1;
            }
        }

        return -1;
    }

    public static void part2(BufferedReader br) throws IOException {
        String line = null;

        int sum = 0;
        while ((line = br.readLine()) != null) {
            int x = 0;
            for (int i = 0; i < line.length(); i++) {
                int d = isDigit(line, i);
                if (d!=-1) {
                    x += d;
                    System.out.println(x);
                    break;
                }
            }
            x *= 10;
            for (int i = line.length() - 1; i >= 0; i--) {
                int d = isDigit(line, i);
                if (d!=-1) {
                    x += d;
                    System.out.println(x);
                    break;
                }
            }
            sum += x;
        }
        System.out.println(sum);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("/home/leartsura/Documents/projects/java_aoc23/jaoc23/src/input"));
//        part1(br);
        part2(br);

    }
}