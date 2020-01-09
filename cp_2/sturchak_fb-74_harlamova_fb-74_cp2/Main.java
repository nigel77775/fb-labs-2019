package com.company;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

import static java.lang.String.valueOf;

public class Main {


    public static void main(String[] args) throws IOException {
        String out1 = readText("C:\\Users\\kateh\\Documents\\кпи\\крипта\\hello.txt");
        String out = readText("C:\\Users\\kateh\\IdeaProjects\\лаба2\\makas.txt");
        String str = out.replaceAll("[^а-я]", "");
        String str1 = out1.toLowerCase().replaceAll("[^а-я]", "");
        int amount = str.length();
//        System.out.println(amount / 16);
//        letter(str);
        block(str);
//        popularList('п');
//        index('б');
//        indexNew(16);
//        vigDenc(str);
//        System.out.println(str1);
//        vigEncr(str1);
        //keyLength(str,16);
        //calcIndex(str1);
//iS(str);
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

    public static char letter(String str) {
        Map<String, Integer> map = new HashMap<String, Integer>();
        String[] words = str.split("(?!^)");
//        char [] word = words.ToCharArray();
        for (String symb : words) {
            if (!symb.isEmpty()) {
                if (map.containsKey(symb)) {
                    map.put(symb, map.get(symb) + 1);
                } else {
                    map.put(symb, 1);

                }
            }
        }
        //  System.out.println(map);
        String s = "";
        char a = 0;
        float maxV = (Collections.max(map.values()));
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            if (entry.getValue() == maxV) {
                s = entry.getKey();
                a = s.charAt(0);
                //    System.out.println("Наиболее часто встречающаяся буква: " + s);
                break;
            }
        }
        return a;
    }

    public static void popularList(char c) {
        List<Character> popular = new ArrayList();
        popular.add(c);
        int[] indexes = new int[17];
        for (int i = 0; i < popular.size(); i++) {
            //     System.out.println(popular.get(i));
            indexes[i] = index(popular.get(i));
//           System.out.println(indexes[i]);
            indexes[i] = ((indexes[i] - 14) % 32);
            if ((indexes[i]) < 0) {
                indexes[i] += 32;
            }
//            System.out.println(indexes[i]);
            indexNew(indexes[i]);
        }


    }

    public static float calcIndex(String str) {
        float amount = str.length();
        Map<String, Integer> map = new HashMap<String, Integer>();
        String[] words = str.split("(?!^)");
        for (String symb : words) {
            if (!symb.isEmpty()) {
                if (map.containsKey(symb)) {
                    map.put(symb, map.get(symb) + 1);
                } else {
                    map.put(symb, 1);

                }
            }
        }
        //  System.out.println(map);
        String s = "";
        float index = 0;
        float coef;
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            coef = (entry.getValue() * (entry.getValue() - 1));
            index += ((coef) * (1 / ((amount) * (amount - 1))));
        }

        return index;
    }


    public static int index(char c) {
        String string = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
//        System.out.println(string.length());
        char[] ch = string.toCharArray();
        for (int i = 0; i < string.length(); i++) {
            if (ch[i] == c) {
                //  System.out.println(i);
                return i;
            }

        }
        return -1;
    }

    public static char indexNew(int number) {
        String string = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
        char[] ch = string.toCharArray();
        for (int i = 0; i < ch.length; i++) {
            if (i == number) {
                System.out.println(ch[i]);
                return ch[i];
            }
        }
        return 0;
    }

    public static void block(String text) {
        char[] charText = text.toCharArray();
        String firstTxt = "";
        for (int j = 0; j < 16; j++) {
            for (int i = j; i < charText.length; i += 16) {
                firstTxt += charText[i];
            }
            //System.out.println(firstTxt);
        }
        String[] str = new String[17];
        String str1 = "";
        int keyLen = 16;
        char[] sortChar = firstTxt.toCharArray();
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < sortChar.length; j++) {
                str1 += valueOf(sortChar[j]);
                str[i] = str1;
                if (j % 739 == 0) {
                    i++;
                    str1 = str1.replaceAll("[а-я]", "");
                }
            }
        }
        String count = "";
        for (int i = 0; i < 17; i++) {
            System.out.println(str[i]);
            popularList(letter(str[i]));
        }
        //  System.out.println(count);

    }

    public static void vigDenc(String str) {
        String key = "братьякарамазовы";
        String strDenc = "";
        char[] newStr = str.toCharArray();
        char[] newKey = key.toCharArray();
        int newLetterNum;
        for (int i = 0; i < str.length(); i++) {
            newLetterNum = ((newStr[i] - newKey[i % 16]) % 32);
            if (newLetterNum < 0) newLetterNum = newLetterNum + 32;
            strDenc += indexNew(newLetterNum);
        }
        System.out.println(strDenc);
    }

    public static void vigEncr(String str) {
        String key = "университет";
        String strEnc = "";
        char[] newStr = str.toCharArray();
        char[] newKey = key.toCharArray();
        int newLetterNum;
        for (int i = 0; i < str.length(); i++) {
            newLetterNum = ((newStr[i] + newKey[i % newKey.length]) % 32);
            if (newLetterNum < 0) newLetterNum = newLetterNum + 32;
            strEnc += indexNew(newLetterNum);
        }
        System.out.println(strEnc);
    }

    public static double iS(String string) {
        char[] allString = string.toCharArray();
        List<Character> subString = new ArrayList<>();
        for (int i = 2; i < 30; i++) {
            for (int j = 0; j < allString.length; j += i) {
                subString.add(allString[j]);
            }
            String res = Arrays.toString(subString.toArray()).replaceAll("[^а-я]", "");
            System.out.print("ИС = " + i + calcIndex(res));
            System.out.println();
            subString.clear();
        }
        return 0;
    }
}
