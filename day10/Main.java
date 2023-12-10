import java.io.BufferedReader;
import java.io.FileReader;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.*;

class Position {
    public Position(int row, int col) {
        this.row = row;
        this.col = col;
    }

    int row;
    int col;
}

public class Main {

    public static int stoi(String s, int beginIndex) throws ParseException {
        NumberFormat nf = NumberFormat.getInstance();
        return nf.parse((s.substring(beginIndex)).strip()).intValue();
    }

    public static void part1(BufferedReader br) throws Exception {
        List<char[]> gridTmp = new ArrayList<>();
        String line;
        while ((line = br.readLine()) != null) {
            gridTmp.add(line.toCharArray());
        }
        char[][] grid = gridTmp.toArray(char[][]::new);

        Map<Character, int[][]> symbolToMoves = new HashMap<>();
        symbolToMoves.put('|', new int[][]{{-1, 0}, {1, 0}});
        symbolToMoves.put('-', new int[][]{{0, -1}, {0, 1}});
        symbolToMoves.put('L', new int[][]{{-1, 0}, {0, 1}});
        symbolToMoves.put('J', new int[][]{{-1, 0}, {0, -1}});
        symbolToMoves.put('7', new int[][]{{0, -1}, {1, 0}});
        symbolToMoves.put('F', new int[][]{{1, 0}, {0, 1}});

        // get start position
        Position start = new Position(-1, -1);
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid.length; j++) {
                if (grid[i][j] == 'S') {
                    start.row = i;
                    start.col = j;
                    break;
                }
            }
        }

        grid[start.row][start.col] = 'F'; // fixme!

        int loopSize = 0;
        boolean[][] pipes = new boolean[grid.length][grid[0].length];
        Position curr = start;
        Position prev = new Position(-1, -1);

        while (!pipes[curr.row][curr.col]) {
            loopSize++;
            pipes[curr.row][curr.col] = true;

            int[][] moves = symbolToMoves.get(grid[curr.row][curr.col]);
            for (int[] move : moves) {
                int row = curr.row + move[0];
                int col = curr.col + move[1];

                if (row != prev.row || col != prev.col) {
                    prev = curr;
                    curr = new Position(row, col);
                    break;
                }

            }
        }

        System.out.println("loop size: " + loopSize);
        System.out.println("farthest from start: " + loopSize / 2);
    }


    public static void part2(BufferedReader br) throws Exception {
        List<char[]> gridTmp = new ArrayList<>();
        String line;
        while ((line = br.readLine()) != null) {
            gridTmp.add(line.toCharArray());
        }
        char[][] grid = gridTmp.toArray(char[][]::new);

        Map<Character, int[][]> symbolToMoves = new HashMap<>();
        symbolToMoves.put('|', new int[][]{{-1, 0}, {1, 0}});
        symbolToMoves.put('-', new int[][]{{0, -1}, {0, 1}});
        symbolToMoves.put('L', new int[][]{{-1, 0}, {0, 1}});
        symbolToMoves.put('J', new int[][]{{-1, 0}, {0, -1}});
        symbolToMoves.put('7', new int[][]{{0, -1}, {1, 0}});
        symbolToMoves.put('F', new int[][]{{1, 0}, {0, 1}});

        // get start position
        Position start = new Position(-1, -1);
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == 'S') {
                    start.row = i;
                    start.col = j;
                    break;
                }
            }
        }

        grid[start.row][start.col] = 'F'; // fixme: starting symbol

        int loopSize = 0;
        boolean[][] inLoop = new boolean[grid.length][grid[0].length];
        Position curr = start;
        Position prev = new Position(-1, -1);

        while (!inLoop[curr.row][curr.col]) {
            loopSize++;
            inLoop[curr.row][curr.col] = true;

            int[][] moves = symbolToMoves.get(grid[curr.row][curr.col]);
            for (int[] move : moves) {
                int row = curr.row + move[0];
                int col = curr.col + move[1];

                if (row != prev.row || col != prev.col) {
                    prev = curr;
                    curr = new Position(row, col);
                    break;
                }

            }
        }

        // part one answer
        System.out.println("loop size: " + loopSize);
        System.out.println("farthest from start: " + loopSize / 2);

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (!inLoop[i][j]) {
                    grid[i][j] = '.';
                }
                if (grid[i][j] == '7' || grid[i][j] == 'F') {
                    grid[i][j] = '|';
                }
            }
        }

        int enclosed = 0;
        for (char[] row : grid) {
            int pipes = 0;
            for (char symbol : row) {
                if (symbol == '|') {
                    pipes++;
                }
                if (pipes % 2 == 1 && symbol == '.') {
                    enclosed++;
                }
            }
        }

        System.out.println("enclosed: " + enclosed);
    }


    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("jaoc23/src/input"));
//        part1(br);
        part2(br);

    }
}