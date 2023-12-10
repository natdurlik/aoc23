import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.math.BigInteger;
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
        int[] times = {47, 70, 75, 66};
        int[] distances = {282, 1079, 1147, 1062};

        long ans = 1;
        for (int i = 0; i < times.length; i++) {
            long ways = 0;
            for (int speed = 0; speed <= times[i]; speed++) {
                if (speed * (times[i] - speed) > distances[i]) {
                    ways++;
                }
            }
            System.out.println(ways);
            ans *= ways;
        }
        System.out.println(ans);
    }


    public static void part2(BufferedReader br) throws Exception {
        long time = 47707566L;
        long distance = 282107911471062L;

        // speed(time-speed)>distance
        // -x^2+tx-d>0
        double sdel = Math.sqrt(time * time - 4 * distance);
        double x1 = (-time - sdel) / (-2);
        double x2 = (-time + sdel) / (-2);
        System.out.println((long) Math.ceil(x1) - (long) Math.ceil(x2));
    }


    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("jaoc23/src/input"));
//        part1(br);
        part2(br);

    }
}