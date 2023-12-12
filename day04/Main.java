import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
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

        long sum = 0;
        while ((line = br.readLine()) != null) {
            line = line.split(":")[1];
            List<String> winNums = new ArrayList<>(List.of((line.split("\\|")[0]).split(" ")));
            List<String> myNums = new ArrayList<>(List.of((line.split("\\|")[1]).split(" ")));
            winNums.removeIf(""::equals);
            myNums.removeIf(""::equals);
            myNums.retainAll(winNums);

            long counter = myNums.isEmpty() ? 0 : (1L << (myNums.size() - 1));
            sum += counter;
        }

        System.out.println(sum);
    }


    public static void part2(BufferedReader br) throws Exception {
        String input;
        List<String> lines = new ArrayList<>();
        while ((input = br.readLine()) != null) {
            lines.add(input);
        }

        long sum = 0;
        List<Long> copies = new ArrayList<>(Collections.nCopies(lines.size()+1, 1L));
        for (String line : lines) {
            int id = stoi(line, 5);
            line = line.split(":")[1];
            List<String> winNums = new ArrayList<>(List.of((line.split("\\|")[0]).split(" ")));
            List<String> myNums = new ArrayList<>(List.of((line.split("\\|")[1]).split(" ")));
            winNums.removeIf(""::equals);
            myNums.removeIf(""::equals);
            myNums.retainAll(winNums);

            long counter = myNums.size();
            for (int i = id + 1; i < Math.min(copies.size(), counter + id + 1); i++) {
                copies.set(i, copies.get(i) + copies.get(id));
            }

            sum += copies.get(id);
        }

        System.out.println(sum);
    }


    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("jaoc23/src/input"));
//        part1(br);
        part2(br);

    }
}