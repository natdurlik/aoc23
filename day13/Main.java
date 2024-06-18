import java.io.BufferedReader;
import java.io.FileReader;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.*;
import java.util.stream.Collectors;

public class Main {

    public static int stoi(String s, int beginIndex) throws ParseException {
        NumberFormat nf = NumberFormat.getInstance();
        return nf.parse((s.substring(beginIndex)).strip()).intValue();
    }

    public static void part1(BufferedReader br) throws Exception {
        String line;

        ArrayList<ArrayList<String>> patterns = new ArrayList<>();
        ArrayList<String> currentPattern = new ArrayList<>();
        while ((line = br.readLine()) != null) {
            if (line.isEmpty()) {
                patterns.add(currentPattern);
                currentPattern = new ArrayList<>();
            } else {
                currentPattern.add(line);
            }
        }
        patterns.add(currentPattern);

        int ans = 0;
        for (var pattern : patterns) {
            ans += reflectionInfo(pattern, 0);
        }

        System.out.println(ans);

    }

    private static ArrayList<String> transpose(ArrayList<String> pattern) {
        char[][] grid = new char[pattern.get(0).length()][pattern.size()];
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                grid[i][j] = pattern.get(j).charAt(i);
            }
        }

        return Arrays.stream(grid)
                .map(String::new)
                .collect(Collectors.toCollection(ArrayList::new));
    }


    private static int countDifferences(String a, String b) {
        int counter = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a.charAt(i) != b.charAt(i)) {
                counter++;
            }
        }
        return counter;
    }

    private static int reflectionLine(ArrayList<String> pattern, int smudges) {
        for (int j = 1; j < pattern.get(0).length(); j++) {
            int halfLength = Math.min(pattern.get(0).length() - j, j);
            int diff = 0;
            for (var line : pattern) {
                String left = new StringBuilder(line.substring(j - halfLength, j)).reverse().toString();
                String right = line.substring(j, j + halfLength);
                diff += countDifferences(left, right); // !left.equals(right) for the first part
            }

            if (diff == smudges) {
                return j;
            }
        }
        return 0;
    }

    public static void part2(BufferedReader br) throws Exception {
    }

    private static int reflectionInfo(ArrayList<String> pattern, int smudges) {
        int vertical = reflectionLine(pattern, smudges);
        if (vertical > 0) return vertical;
        var transposed = transpose(pattern);
        return reflectionLine(transposed, smudges) * 100;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("jaoc23/src/input"));
        part1(br);
//        part2(br);

    }
}