import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    public static int stoi(String s, int beginIndex) throws ParseException {
        NumberFormat nf = NumberFormat.getInstance();
        return nf.parse(s.substring(beginIndex)).intValue();
    }

    public static void part1(BufferedReader br) throws Exception {
        String line;

        int sum = 0;
        int[] maxes = new int[]{12, 13, 14};

        while ((line = br.readLine()) != null) {
            int id = stoi(line, 5);
            line = line.split(":")[1];

            boolean possible = true;
            String[] subgames = line.split(";");
            for (String subgame : subgames) {
                subgame = subgame.strip();

                String[] pulls = subgame.split(",");
                for (String pull : pulls) {
                    pull = pull.strip();
                    int x = stoi(pull, 0);
                    if (pull.contains("d") && x > maxes[0]) {
                        possible = false;
                        break;
                    }
                    if (pull.contains("g") && x > maxes[1]) {
                        possible = false;
                        break;
                    }
                    if (pull.contains("b") && x > maxes[2]) {
                        possible = false;
                        break;
                    }
                }
            }

            if (possible) {
                sum += id;
            }
        }

        System.out.println(sum);
    }


    public static void part2(BufferedReader br) throws Exception {
        String line;

        int sum = 0;

        while ((line = br.readLine()) != null) {
            int id = stoi(line, 5);
            line = line.split(":")[1];

            int[] maxes = new int[]{0, 0, 0};
            String[] subgames = line.split(";");
            for (String subgame : subgames) {
                subgame = subgame.strip();

                String[] pulls = subgame.split(",");
                for (String pull : pulls) {
                    int x = stoi(pull.strip(), 0);
                    if (pull.contains("d")) {
                        maxes[0] = Math.max(maxes[0], x);
                    }
                    if (pull.contains("g")) {
                        maxes[1] = Math.max(maxes[1], x);
                    }
                    if (pull.contains("b")) {
                        maxes[2] = Math.max(maxes[2], x);
                    }
                }
            }
            sum += maxes[0] * maxes[1] * maxes[2];
        }
        System.out.println(sum);
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("/home/leartsura/Documents/projects/java_aoc23/jaoc23/src/input"));
//        part1(br);
        part2(br);

    }
}