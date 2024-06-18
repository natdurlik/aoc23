import java.io.BufferedReader;
import java.io.FileReader;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.*;
import java.util.stream.Collectors;

public class Main {

    private static void tiltNorth(char[][] grid) {
        for (int j = 0; j < grid[0].length; j++) {
            int counter = 0;
            int i = grid.length - 1;
            for (; i >= 0; i--) {
                if (grid[i][j] == 'O') {
                    grid[i][j] = '.';
                    counter++;
                } else if (grid[i][j] == '#') {
                    for (int k = i + 1; k < i + 1 + counter; k++) {
                        grid[k][j] = 'O';
                    }
                    counter = 0;
                }
            }
            for (int k = i + 1; k < i + 1 + counter; k++) {
                grid[k][j] = 'O';
            }
        }
    }

    private static int getTotalNorthLoad(char[][] tiltedNorth) {
        int totalLoad = 0;
        for (int j = 0; j < tiltedNorth[0].length; j++) {
            for (int i = 0; i < tiltedNorth.length; i++) {
                if (tiltedNorth[i][j] == 'O') {
                    totalLoad += tiltedNorth.length - i;
                }
            }
        }
        return totalLoad;
    }

    public static void part1(BufferedReader br) throws Exception {
        String inputLine;
        ArrayList<String> inputGrid = new ArrayList<>();
        while ((inputLine = br.readLine()) != null) {
            inputGrid.add(inputLine);
        }

        char[][] grid = inputGrid.stream().map(String::toCharArray).toArray(char[][]::new);
        tiltNorth(grid);
        int totalLoad = getTotalNorthLoad(grid);

        System.out.println(totalLoad);
    }

    public static void transpose(char[][] grid) {
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (i == j) break;
                char tmp = grid[i][j];
                grid[i][j] = grid[j][i];
                grid[j][i] = tmp;
            }
        }
    }

    public static void rotateRight(char[][] grid) {
        transpose(grid);
        for (int i = 0; i < grid.length; i++) {
            grid[i] = new StringBuilder(new String(grid[i])).reverse().toString().toCharArray();
        }
    }

    public static void cycle(char[][] grid) {
        for(int i=0;i<4;i++) {
            tiltNorth(grid);
            rotateRight(grid);
        }
    }

    public static void part2(BufferedReader br) throws Exception {
        String inputLine;
        ArrayList<String> inputGrid = new ArrayList<>();
        while ((inputLine = br.readLine()) != null) {
            inputGrid.add(inputLine);
        }

        char[][] grid = inputGrid.stream().map(String::toCharArray).toArray(char[][]::new);
        char[][] startGrid = Arrays.stream(grid).map(char[]::clone).toArray(char[][]::new);

        HashMap<String, Integer> reflectorToCycleIdx = new HashMap<>();

        int cycleSize;
        int cycleIdx = 0;
        int cycleBegin;
        int oneBillion = 1000000000;
        while (true) {
            String gridString = Arrays.stream(grid)
                    .map(String::new)
                    .collect(Collectors.joining());
            if (reflectorToCycleIdx.containsKey(gridString)) {
                cycleBegin = reflectorToCycleIdx.get(gridString);
                cycleSize = cycleIdx - cycleBegin;
                break;
            }
            reflectorToCycleIdx.put(gridString, cycleIdx);
            cycleIdx++;
            cycle(grid);
        }

        int sameCycleIdx = cycleBegin + (oneBillion - cycleBegin) % cycleSize;
        for (int i = 0; i < sameCycleIdx; i++) {
            cycle(startGrid);
        }

        System.out.println(getTotalNorthLoad(startGrid));
    }


    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("jaoc23/src/input"));
//        part1(br);
        part2(br);
    }
}