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


    private static boolean isAdjacent(int i, int j, ArrayList<String> grid) {
        int[][] directions = {
                {0, 1},
                {1, 0},
                {0, -1},
                {-1, 0},
                {1, 1},
                {-1, -1},
                {1, -1},
                {-1, 1}
        };

        for (int[] move : directions) {
            int row = i + move[0];
            int col = j + move[1];

            if (inGrid(row, col, grid) && isSymbol(row, col, grid)) {
                return true;
            }
        }

        return false;
    }

    private static boolean isSymbol(int row, int col, ArrayList<String> grid) {
        return grid.get(row).charAt(col) != '.' && !Character.isDigit(grid.get(row).charAt(col));
    }


    private static boolean inGrid(int i, int j, ArrayList<String> grid) {
        return i >= 0 && j >= 0 && i < grid.size() && j < grid.get(i).length();
    }

    public static void part1(BufferedReader br) throws Exception {
        String line;

        ArrayList<String> grid = new ArrayList<>();
        while ((line = br.readLine()) != null) {
            grid.add(line);
        }


        int sum = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.get(i).length(); j++) {
                if (Character.isDigit(grid.get(i).charAt(j))) {
                    int x = stoi(grid.get(i), j);
                    boolean adjacent = false;
                    while (j < grid.get(i).length() && Character.isDigit(grid.get(i).charAt(j))) {
                        if (!adjacent && isAdjacent(i, j, grid)) {
                            adjacent = true;
                        }
                        j++;
                    }
                    if (adjacent) {
                        sum += x;
                    }
                }
            }
        }

        System.out.println(sum);
    }


    public static void part2(BufferedReader br) throws Exception {
        String line;
        ArrayList<String> grid = new ArrayList<>();
        while ((line = br.readLine()) != null) {
            grid.add(line);
        }

        long sum = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.get(i).length(); j++) {
                if (grid.get(i).charAt(j) == '*') {
                    sum += gearRatio(i, j, grid);
                }
            }
        }

        System.out.println(sum);
    }

    private static long gearRatio(int i, int j, ArrayList<String> grid) throws ParseException {
        int[][] directions = {
                {0, 1},
                {1, 0},
                {0, -1},
                {-1, 0},
                {1, 1},
                {-1, -1},
                {1, -1},
                {-1, 1}
        };


        boolean[][] visited = new boolean[grid.size()][grid.get(0).length()];
        long mult=1;
        int counter=0;
        for (int[] move : directions) {
            int row = i + move[0];
            int col = j + move[1];

            if (inGrid(row, col, grid) && Character.isDigit(grid.get(row).charAt(col)) && !visited[row][col]) {
                counter++;
                if(counter<3) {
                    int num = getValue(row, col, grid, visited);
                    mult*=num;
                }
            }
        }
        if(counter!=2) {
            return 0;
        }

        return mult;
    }

    private static int getValue(int row, int col, ArrayList<String> grid, boolean[][] visited) throws ParseException {
        int j = col;
        while (j >= 0 && Character.isDigit(grid.get(row).charAt(j))) {
            visited[row][j] = true;
            j--;
        }
        j++;
        int x = stoi(grid.get(row), j);

        while (j < grid.get(row).length() && Character.isDigit(grid.get(row).charAt(j))) {
            visited[row][j] = true;
            j++;
        }
        return x;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("jaoc23/src/input"));
//        part1(br);
        part2(br);

    }
}