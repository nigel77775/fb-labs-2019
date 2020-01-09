package com.company;


import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {



        String out = readText("C:\\Users\\kateh\\Documents\\кпи\\крипта\\king1.txt");
        String Clear = out.toLowerCase();
        String s = Clear.replaceAll("[^а-я ]", "");
        int a = s.length();
        //  System.out.println( a);
          System.out.println(s);
           String str = Map(s, 1);
      //  Big(s, a);

    }

    static String readText(String path) throws IOException {
        StringBuffer sb = new StringBuffer();
        String res = "";
        try {
            BufferedReader in = new BufferedReader(new FileReader(path));
            String str;
            while ((str = in.readLine()) != null) {
                sb.append(str + " ");
            }
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        res = sb.toString();
        return res;

    }

    static String Map(String Text, int gramm) {
        int amount = Text.length();
        System.out.println(amount);
        HashMap<String, Float> Map = new HashMap<>();
        if (gramm == 1) {
             fillMap(Map, Text, amount, 1);
        }
        if (gramm == 2) {
             fillMap(Map, Text, amount / 2, 2);
        }
        return Text;
    }

    static String smaller(int i) {
        StringBuilder s = new StringBuilder();
        s.append("(?<=\\G");
        for (int j = 0; j < i; j++)
            s.append(".");
        s.append(")");
        return s.toString();
    }

    static void fillMap(HashMap<String, Float> map, String Clear, float amount, int gramm) {
      //  String Clear = Text.toLowerCase().replaceAll("[^а-я]", "");
        //  System.out.println(Clear);
        String[] arr = Clear.split(smaller(gramm));
        float sum = 0;
        for (String symb : arr) {
            if (!symb.isEmpty())
                if (map.containsKey(symb)) {
                    map.put(symb, map.compute(symb, (k, v) -> v + 1));
                } else {
                    map.put(symb, (float) 1);

                }
        }
        System.out.println(map);

        for (String k : map.keySet()) {
//            if (map.containsKey(k)){
//                map.put(k, map.get(k) / amount);}
//            System.out.format(k + " " + "%.6f%n", map.get(k) / amount);
        }

        for (float value : map.values()) {
            sum += (-((value / amount) * (Math.log(value / amount)) / Math.log(2)));
        }
        float red = (float) ((1 - (sum / gramm) / (Math.log(33) / Math.log(2))));
        System.out.println("Res = " + (sum / gramm));
        System.out.println("Red = " + red);
        String  s = "";
      //  return (s);
    }


    static void Big(String Clear, int Amount) {
        float sum = 0;
        HashMap<String, Float> map = new HashMap<>();
        String[] words = Clear.split("(?!^)");
        for (int i = 0; i < Clear.length() - 1; i++) {
            String s = words[i];
            String s1 = words[i + 1];
            String s2 = s + s1;
            if (!s2.isEmpty())
                if (map.containsKey(s2)) {
                    map.put(s2, map.compute(s2, (k, v) -> v + 1));
                } else {
                    map.put(s2, (float) 1);
                    i++;
                }
        }
        System.out.println(map);
        for (String k : map.keySet()) {
//            if (map.containsKey(k))
//                map.put(k, map.get(k) / Amount);
//            System.out.format(k + " " + "%.6f%n", map.get(k) / Amount);
        }
        for (float value : map.values()) {
            sum += (-((value / Amount) * (Math.log(value / Amount)) / Math.log(2)));
        }
        float red = (float) ((1 - (sum / 2) / (Math.log(33) / Math.log(2))));
        System.out.println("Res = " + (sum / 2));
        System.out.println("Red = " + red);
    }

}

