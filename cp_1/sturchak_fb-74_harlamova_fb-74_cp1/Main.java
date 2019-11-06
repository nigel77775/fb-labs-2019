package com.company;

import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {


    public static void main(String[] args) throws IOException {

        String path = ("C:\\Users\\kateh\\Documents\\кпи\\крипта\\king1.txt");
        String str = ReadText(path);

        String Capital = CapitalLeters(str);

        String Remove = RemoveSpace(Capital);
        String Leave = LeaveSpace(Capital);

        int AmountR = AmountLetters(Remove);
        int AmountL = AmountLetters(Leave);

//        System.out.println("Monogramma");
//
//        System.out.println("Без пробелов");
//     //   Monogram(Remove, AmountR);
//        float count1 = (float) ((1 - (Monogram(Remove, AmountR)) / (Math.log(33) / Math.log(2))));
//        System.out.println("Redundancy = " + count1 + "\n");
//
//
//        System.out.println("С пробелами");
//  //     Monogram(Leave, AmountL);
//        float count2 = (float) ((1 - (Monogram(Leave, AmountL)) / (Math.log(33) / Math.log(2))));
//        System.out.println("Redundancy = " + count2 +"\n" );

        System.out.println("BigrammaPut");

        System.out.println("с пробелами");
        //BigramWr(Leave, AmountL);
        float a = (float) ((1 - (BigramWr(Leave, AmountL)) / (Math.log(33) / Math.log(2))));
        System.out.println("Redundancy = " + a + "\n" );


        System.out.println("без");
        //BigramWr(Remove, AmountR);
        float b = (float) ((1 - (BigramWr(Remove, AmountR)) / (Math.log(33) / Math.log(2))));
        System.out.println("Redundancy = " + b + "\n" );

        System.out.println("Bigramma");

        System.out.println("с пробелами");
        BigramWithOut(Leave, AmountL);
        float c = (float) ((1 - (BigramWr(Leave, AmountL)) / (Math.log(33) / Math.log(2))));
        System.out.println("Redundancy = " + c + "\n" );


        System.out.println("без");
        BigramWithOut(Remove, AmountR);
        float d = (float) ((1 - (BigramWr(Remove, AmountR)) / (Math.log(33) / Math.log(2))));
        System.out.println("Redundancy = " + d + "\n" );


    }


    public static String ReadText(String path) {
        String text = "";
        String buf = "";
        try {
            FileInputStream File = new FileInputStream(path);
            DataInputStream dis = new DataInputStream(File);
            BufferedReader br = new BufferedReader(new InputStreamReader(dis));

            while ((buf = br.readLine()) != null) {
                text += buf;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return text;
    }


    public static String CapitalLeters(String text) {
        String str = text.toLowerCase();
        return str;
    }

    public static String RemoveSpace(String text) {
        String str1 = text.replaceAll("[^а-я]", "");
        return str1;
    }

    public static String LeaveSpace(String text) {
        String str1 = text.replaceAll("[^а-я ]", "");
        return str1;
    }

    public static int AmountLetters(String text) {
        int Amount = text.length();
        return Amount;
    }

    public static float Monogram(String text, int amount) {
        char[] strchar = text.toCharArray();
        Map<Character, Float> MonoMap = new HashMap<Character, Float>();
        int calc = 0;
        char letter = strchar[calc];
        for (int i = 0; i < text.length(); i++) {
            letter = strchar[i];
            if (!MonoMap.containsKey(letter)) {
                MonoMap.put(letter, (float) 1);
            } else {
                MonoMap.put(letter, MonoMap.compute(letter, (k, v) -> (float) v + 1));
            }
        }
        float res = 0;
        for (Character key : MonoMap.keySet()) {
            float a = MonoMap.get(key) / amount;
            System.out.format(key + " " + "%.6f%n",a);
        }
        for (float values : MonoMap.values()) {
            res += (float) ((values / amount) * (Math.log(values / amount)) / Math.log(2));
        }
        System.out.println("Result = " +(-res) + "\n");
        // return 0;
        return (-res);
    }

    public static float BigramWr(String str, int amount) {
        char[] strtochar = str.toCharArray();
        Character ch1, ch2;
        Map<String, Float> BiMap = new HashMap<String, Float>();
        for (int i = 0; i < str.length() - 1; i++) {
            ch1 = strtochar[i];
            ch2 = strtochar[i + 1];
            String s1 = ch1.toString();
            String s2 = ch2.toString();
            String s3 = s1 + s2;
            if (!BiMap.containsKey(s3)) {
                BiMap.put(s3, (float) 1);
            } else {
                BiMap.put(s3, BiMap.compute(s3, (k, v) -> (float) v + 1));
            }
        }
        float res = 0;
        for (String key : BiMap.keySet()){
            System.out.format(key + " " + "%.6f%n", BiMap.get(key)/amount);
        }
        for (float values : BiMap.values()) {
            res += (float) ((values / amount) * (Math.log(values / amount)) / Math.log(2));
        }
        System.out.println("Result = " +(-res/2) + " \n");
        // return 0;
        return (-res / 2);
    }

    public static float BigramWithOut(String str, int amount) {
        Map<String,Float> BiMap = new HashMap<String, Float>();
        char [] chtostr = str.toCharArray();
        Character ch1,ch2;
        for (int i=0; i<str.length()-1;i++){
            ch1= chtostr[i];
            ch2 = chtostr[i+1];
            String s1 = ch1.toString();
            String s2 = ch2.toString();
            String s3 = s1 + s2;
            if(BiMap.containsKey(s3)){
                BiMap.put(s3, BiMap.compute(s3, (k,v)-> (float) v+1));
            }
            else {
                BiMap.put(s3,(float) 1);

                i++;
            }
        }
        for (String key : BiMap.keySet() ){
            System.out.format(key + "  " + "%.6f%n",BiMap.get(key)/amount);
        }
        float res = 0;
        for (float values : BiMap.values()){
            res += ((values/amount)*((Math.log(values/amount))/Math.log(2)));
        }
        System.out.println("Result = " + (-res/2));
        return (-res/2);
    }
}