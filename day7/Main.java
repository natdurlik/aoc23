import java.io.BufferedReader;
import java.io.FileReader;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.*;

class HandBid {
    public String hand;
    public int bid;

    public HandBid(String hand, int bid) {
        this.hand = hand;
        this.bid = bid;
    }
}

class HandBidComparatorPart1 implements Comparator<HandBid> {
    @Override
    public int compare(HandBid lhs, HandBid rhs) {
        int ltype = get_type(lhs.hand);
        int rtype = get_type(rhs.hand);
        if (ltype != rtype) {
            return Integer.compare(ltype, rtype);
        }

        ArrayList<Character> order = new ArrayList<>(List.of('A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'));
        Collections.reverse(order);

        for (int i = 0; i < lhs.hand.length(); i++) {
            int lpos = order.indexOf(lhs.hand.charAt(i));
            int rpos = order.indexOf(rhs.hand.charAt(i));
            if (lpos != rpos) {
                return Integer.compare(lpos, rpos);
            }
        }

        return 0;
    }

    public int get_type(String hand) {
        int[] counter = new int[255];
        for (char c : hand.toCharArray()) {
            counter[c]++;
        }

        int[] types = new int[6];
        for (int count : counter) {
            if (count != 0) {
                types[count]++;
            }
        }

        if (types[5] == 1) return 6;
        if (types[4] == 1) return 5;
        if (types[3] == 1 && types[2] == 1) return 4;
        if (types[3] == 1) return 3;
        if (types[2] == 2) return 2;
        if (types[2] == 1) return 1;
        return 0;
    }

}

class HandBidComparatorPart2 implements Comparator<HandBid> {
    @Override
    public int compare(HandBid lhs, HandBid rhs) {
        int ltype = get_type(lhs.hand);
        int rtype = get_type(rhs.hand);
        if (ltype != rtype) {
            return Integer.compare(ltype, rtype);
        }

        ArrayList<Character> order = new ArrayList<>(List.of('A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'));
        Collections.reverse(order);

        for (int i = 0; i < lhs.hand.length(); i++) {
            int lpos = order.indexOf(lhs.hand.charAt(i));
            int rpos = order.indexOf(rhs.hand.charAt(i));
            if (lpos != rpos) {
                return Integer.compare(lpos, rpos);
            }
        }

        return 0;
    }

    public int get_type(String hand) {
        int[] counter = new int[255];
        int jokers = 0;
        for (char c : hand.toCharArray()) {
            if (c != 'J') {
                counter[c]++;
            } else {
                jokers++;
            }
        }
        if (jokers == 5 || jokers == 4) return 6;

        int[] types = new int[6];
        for (int count : counter) {
            if (count != 0) {
                types[count]++;
            }
        }

        if (jokers != 0) {
            for (int i = 5; i >= 0; i--) {
                if (types[i] > 0) {
                    types[i]--;
                    types[i + jokers]++;
                    break;
                }
            }
        }

        if (types[5] == 1) return 6;
        if (types[4] == 1) return 5;
        if (types[3] == 1 && types[2] == 1) return 4;
        if (types[3] == 1) return 3;
        if (types[2] == 2) return 2;
        if (types[2] == 1) return 1;
        return 0;
    }

}

public class Main {

    public static int stoi(String s, int beginIndex) throws ParseException {
        NumberFormat nf = NumberFormat.getInstance();
        return nf.parse((s.substring(beginIndex)).strip()).intValue();
    }

    public static void part1(BufferedReader br) throws Exception {
        String line;

        ArrayList<HandBid> hands = new ArrayList<>();
        while ((line = br.readLine()) != null) {
            String hand = line.split(" ")[0];
            int bid = stoi(line.split(" ")[1], 0);
            System.out.println(hand);
            System.out.println(bid);
            hands.add(new HandBid(hand, bid));
        }

        hands.sort(new HandBidComparatorPart1());

        long ans = 0;
        for (int i = 0; i < hands.size(); i++) {
            ans += ((long) hands.get(i).bid * (i + 1));
        }

        System.out.println(ans);
    }


    public static void part2(BufferedReader br) throws Exception {
        String line;

        ArrayList<HandBid> hands = new ArrayList<>();
        while ((line = br.readLine()) != null) {
            String hand = line.split(" ")[0];
            int bid = stoi(line.split(" ")[1], 0);
            System.out.println(hand);
            System.out.println(bid);
            hands.add(new HandBid(hand, bid));
        }

        hands.sort(new HandBidComparatorPart2());

        long ans = 0;
        for (int i = 0; i < hands.size(); i++) {
            ans += ((long) hands.get(i).bid * (i + 1));
        }

        System.out.println(ans);
    }


    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("jaoc23/src/input"));
//        part1(br);
        part2(br);

    }
}