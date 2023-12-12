import java.io.BufferedReader;
import java.io.FileReader;
import java.lang.reflect.Array;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.*;

public class Main {

    public static int stoi(String s, int beginIndex) throws ParseException {
        NumberFormat nf = NumberFormat.getInstance();
        return nf.parse((s.substring(beginIndex)).strip()).intValue();
    }

    public static long arrangements_dp(long[][][] dp, char[] spring, int[] groupSizes, int[] currSizes, int springIdx, int groupIdx) {
        int si = springIdx;
        int gi = groupIdx;
        int curr = currSizes[groupIdx];

        if (springIdx == spring.length) {
            if (groupIdx == groupSizes.length ||
                    (groupIdx + 1 == groupSizes.length && groupSizes[groupIdx] == currSizes[groupIdx])) {
                return dp[si][gi][curr] = 1;
            }
            return dp[si][gi][curr] = 0;
        }

        if (dp[si][gi][curr] != -1) {
            return dp[si][gi][curr];
        }

        if (groupIdx == groupSizes.length) {
            if (spring[springIdx] == '#') {
                return dp[si][gi][curr] = 0;
            }

            return dp[si][gi][curr] = arrangements_dp(dp, spring, groupSizes, currSizes, springIdx + 1, groupIdx);
        }

        if (spring[springIdx] == '.') {
            if (currSizes[groupIdx] != 0) {
                if (currSizes[groupIdx] != groupSizes[groupIdx]) {
                    return dp[si][gi][curr] = 0;
                }
                groupIdx++;
            }

            return dp[si][gi][curr] = arrangements_dp(dp, spring, groupSizes, currSizes, springIdx + 1, groupIdx);
        }

        if (spring[springIdx] == '#') {
            int[] newCurrSizes = currSizes.clone();
            newCurrSizes[groupIdx]++;
            if (groupSizes[groupIdx] < newCurrSizes[groupIdx]) {
                return dp[si][gi][curr] = 0;
            }

            return dp[si][gi][curr] = arrangements_dp(dp, spring, groupSizes, newCurrSizes, springIdx + 1, groupIdx);
        }

        if (spring[springIdx] == '?') {
            if (currSizes[groupIdx] != 0) {
                if (currSizes[groupIdx] < groupSizes[groupIdx]) {
                    int[] newCurrSizes = currSizes.clone();
                    newCurrSizes[groupIdx]++;
                    return dp[si][gi][curr] = arrangements_dp(dp, spring, groupSizes, newCurrSizes, springIdx + 1, groupIdx);
                }
                if (currSizes[groupIdx] == groupSizes[groupIdx]) {
                    groupIdx++;
                }
                return dp[si][gi][curr] = arrangements_dp(dp, spring, groupSizes, currSizes, springIdx + 1, groupIdx);
            }

            long part = arrangements_dp(dp, spring, groupSizes, currSizes, springIdx + 1, groupIdx);
            int[] newCurrSizes = currSizes.clone();
            newCurrSizes[groupIdx]++;
            return dp[si][gi][curr] = part + arrangements_dp(dp, spring, groupSizes, newCurrSizes, springIdx + 1, groupIdx);
        }

        return 0;
    }

    public static void part1(BufferedReader br) throws Exception {
        String line;
        ArrayList<char[]> springs = new ArrayList<>();
        ArrayList<int[]> groupSizes = new ArrayList<>();

        int repeat = 5;
        while ((line = br.readLine()) != null) {
            String[] tmp = line.split(" ");
            StringBuilder stringBuilder = new StringBuilder(tmp[0]);
            for (int i = 1; i < repeat; i++) {
                stringBuilder.append("?").append(tmp[0]);
            }
            springs.add(stringBuilder.toString().toCharArray());

            String[] nums = tmp[1].split(",");
            ArrayList<Integer> sizes = new ArrayList<>();
            for (String num : nums) {
                sizes.add(stoi(num, 0));
            }
            ArrayList<Integer> groupSize = new ArrayList<>();
            for (int i = 0; i < repeat; i++) {
                groupSize.addAll(sizes);
            }

            groupSizes.add(groupSize.stream().mapToInt(Integer::intValue).toArray());
        }

        long ans = 0;
        for (int i = 0; i < springs.size(); i++) {
            int[] currSizes = new int[groupSizes.get(i).length + 1];
            long[][][] dp = new long[springs.get(i).length + 1][groupSizes.get(i).length + 1][springs.get(i).length + 1];
            for (int j = 0; j < dp.length; j++) {
                for (int k = 0; k < dp[0].length; k++) {
                    Arrays.fill(dp[j][k], -1);
                }
            }

            long ways = arrangements_dp(dp, springs.get(i), groupSizes.get(i), currSizes, 0, 0);
            ans += ways;
        }
        System.out.println(ans);

    }


    public static void part2(BufferedReader br) throws Exception {

    }


    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("jaoc23/src/input"));
        part1(br);
//        part2(br);

    }
}