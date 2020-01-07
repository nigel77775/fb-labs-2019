package com.company;

import java.math.BigInteger;
import java.util.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;

import static java.math.BigInteger.*;

public class Main {


    public static void main(String[] args) {
        pq();
    }

    public static void pq() {
        BigInteger p_1 = number(rand());
        BigInteger q_1 = number(rand());
        BigInteger p1_1 = number(rand());
        BigInteger q1_1 = number(rand());

        BigInteger p = prov(p_1, q_1, p1_1, q1_1).get(0);
        BigInteger q = prov(p_1, q_1, p1_1, q1_1).get(1);
        BigInteger p1 = prov(p_1, q_1, p1_1, q1_1).get(2);
        BigInteger q1 = prov(p_1, q_1, p1_1, q1_1).get(3);


        System.out.println("Generate prime numbers : p =  " + p + ", q = " + q);
        System.out.println("Generate prime numbers : p1 =  " + p1.toString(16) + ", q1 = " + q1.toString(16));
        System.out.println();

        BigInteger fN = getFN(p, q);
        BigInteger fN1 = getFN(p1, q1);

        BigInteger e = getE(fN);
        System.out.println("e = " + e.toString(16));
        BigInteger e1 = getE(fN1);
        System.out.println("e1 = " + e1.toString(16));

        BigInteger n = getN(p, q);
        System.out.println("n = " + n.toString(16));
        BigInteger n1 = getN(p1, q1);
        System.out.println("n1 = " + n1.toString(16));

        BigInteger d = getD(e, fN);
        System.out.println("d = " + d.toString(16));
        BigInteger d1 = getD(e1, fN1);
        System.out.println("d1 = " + d1.toString(16));

        getKeyPair(fN, n, e, p, q);
        getKeyPair(fN1, n1, e1, p1, q1);

        BigInteger m = getRandMes(n);//відкритe повідомлення m
        BigInteger m1 = getRandMes(n1);

        System.out.println();
        System.out.println("A's message for B  = " + m.toString(16));
        System.out.println("A's message for B  = " + m1.toString(16));
        System.out.println();


        BigInteger c = encrypt(m, e, n);//Зашифрування відкритого повідомлення
        BigInteger c1 = encrypt(m1, e1, n1);


        System.out.println("encrypted message = " + c.toString(16));
        System.out.println("encrypted message = " + c1.toString(16));
        System.out.println();

        BigInteger m_1 = decrypt(c, d, n);//Розшифрування криптограми
        BigInteger m1_1 = decrypt(c1, d1, n1);

        System.out.println("decrypted message = " + m_1.toString(16));
        System.out.println("decrypted message = " + m1_1.toString(16));
        System.out.println();

        BigInteger s = sign(m_1, d, n);//Цифровий підпис у системі RSA.
        BigInteger s1 = sign(m1_1, d1, n1);

        System.out.println("sing = " + s.toString(16));
        System.out.println("sing = " + s1.toString(16));
        System.out.println();

        messPair(s, m_1);
        messPair(s1, m1_1);

        BigInteger mes = varificateSign(s, e, n);
        BigInteger mes1 = varificateSign(s1, e1, n1);

        System.out.println();
        System.out.println("verificated sign message = " + mes.toString(16));
        System.out.println("verificated sign message = " + mes1.toString(16));
        System.out.println();
        verify(receive(send(m, s, n, n1, e1, d), d1, n1), e, n);

    }


    public static ArrayList<BigInteger> send(BigInteger k, BigInteger s, BigInteger n, BigInteger n1, BigInteger e1, BigInteger d) {
        s = sign(k, d, n);
        BigInteger s1 = sign(s, e1, n1);
        BigInteger k1 = sign(k, e1, n1);

        ArrayList send = new ArrayList();
        send.add(s);
        send.add(0, s1);
        send.add(1, k1);

        System.out.println("A send message to B (" + k1.toString(16) + "," + s1.toString(16) + ")");

        return send;

    }

    public static ArrayList<BigInteger> receive(ArrayList<BigInteger> send, BigInteger d1, BigInteger n1) {

        ArrayList<BigInteger> receive = new ArrayList<>();

        BigInteger k = send.get(1).modPow(d1, n1);
        BigInteger s = send.get(0).modPow(d1, n1);

        receive.add(0, k);
        receive.add(1, s);

        System.out.println("B receive message from A  (" + k.toString(16) + "," + s.toString(16) + ")");

        return receive;
    }

    public static Boolean verify(ArrayList<BigInteger> receive, BigInteger e, BigInteger n) {


        BigInteger s = receive.get(1);
        BigInteger k = receive.get(0);
        BigInteger prov = s.modPow(e, n);


        if (k.compareTo(prov) == 0) {
            System.out.println("identity verification is passed");
            return true;
        } else if (k.compareTo(prov) != 0) {
            System.out.println("identity verification isn't passed");
            return false;
        }
        return true;
    }


    public static BigInteger getN(BigInteger p, BigInteger q) {

        BigInteger n = p.multiply(q);
        return n;
    }

    public static BigInteger getFN(BigInteger p, BigInteger q) {

        BigInteger fN = (p.subtract(valueOf(1))).multiply(q.subtract(valueOf(1)));
        return fN;
    }

    public static ArrayList getKeyPair(BigInteger fN, BigInteger n, BigInteger e, BigInteger p, BigInteger q) {

        BigInteger d = getD(e, fN);

        ArrayList openKeyPair = new ArrayList();
        openKeyPair.add(n);
        openKeyPair.add(e);


        System.out.println("open key pair (" + n.toString(16) + "," + e.toString(16) + ")");

        ArrayList closeKeyPair = new ArrayList();
        closeKeyPair.add(p);
        closeKeyPair.add(q);
        closeKeyPair.add(d);

        System.out.println("close key pair (" + d.toString(16) + "," + p.toString(16) + " ," + q.toString(16) + ")");

        return openKeyPair;
    }

    public static ArrayList messPair(BigInteger s, BigInteger m) {

        ArrayList messPair = new ArrayList();
        messPair.add(s);
        messPair.add(m);
        System.out.println("electronic signature (" + s.toString(16) + "," + m.toString(16) + ")");
        return messPair;
    }

    public static BigInteger getD(BigInteger e, BigInteger fN) {
        BigInteger d = e.modInverse(fN);
        return d;
    }

    public static BigInteger getRandMes(BigInteger n) {

        System.out.println("n " + n);
        BigInteger maxLimit = (n.subtract(valueOf(1)));
        BigInteger minLimit = new BigInteger("2");

        BigInteger bigInteger = maxLimit.subtract(minLimit);
        Random randNum = new Random();
        int len = maxLimit.bitLength();
        BigInteger mes = new BigInteger(len, randNum);

        if (mes.compareTo(minLimit) < 0)
            mes = mes.add(minLimit);

        if (mes.compareTo(bigInteger) >= 0)
            mes = mes.mod(bigInteger).add(minLimit);

        return mes;
    }

    public static BigInteger encrypt(BigInteger m, BigInteger e, BigInteger n) {
        BigInteger c = m.modPow(e, n);
        System.out.println();
        return c;
    }

    public static BigInteger decrypt(BigInteger c, BigInteger d, BigInteger n) {
        BigInteger m = c.modPow(d, n);
        return m;
    }


    public static BigInteger sign(BigInteger M, BigInteger d, BigInteger n) {
        BigInteger s = M.modPow(d, n);//
        return s;
    }

    public static BigInteger varificateSign(BigInteger s, BigInteger e, BigInteger n) {
        BigInteger m = s.modPow(e, n);//
        return m;
    }

    public static BigInteger getRand(BigInteger fN) {
        BigInteger maxLimit = (fN.subtract(valueOf(1)));
        BigInteger minLimit = new BigInteger("0");

        BigInteger bigInteger = maxLimit.subtract(minLimit);
        Random randNum = new Random();
        int len = maxLimit.bitLength();
        BigInteger res = new BigInteger(len, randNum);

        if (res.compareTo(minLimit) < 0)
            res = res.add(minLimit);

        if (res.compareTo(bigInteger) >= 0)
            res = res.mod(bigInteger).add(minLimit);

        BigInteger e = verificateGcd(res, fN);

        return e;
    }

    public static BigInteger verificateGcd(BigInteger randE, BigInteger fN) {
        BigInteger tempGcd = randE.gcd(fN);
        if (tempGcd.compareTo(valueOf(1)) == 0) {
            return randE;
        } else if (tempGcd.compareTo(valueOf(1)) != 0) {
            randE = getRand(fN);
        }
        return randE;
    }


    public static BigInteger getE(BigInteger fN) {
        BigInteger e = getRand(fN);
        return e;
    }

    public static BigInteger rand() {
        BigInteger maxLimit = new BigInteger("10000000000000000000000000000000000000000000000000000000000000000000000000000");
        BigInteger minLimit = new BigInteger("500000000000000000000000000000000");

        BigInteger bigInteger = maxLimit.subtract(minLimit);
        Random randNum = new Random();
        int len = maxLimit.bitLength();
        BigInteger mes = new BigInteger(len, randNum);

        if (mes.compareTo(minLimit) < 0)
            mes = mes.add(minLimit);

        if (mes.compareTo(bigInteger) >= 0)
            mes = mes.mod(bigInteger).add(minLimit);


        return mes;
    }

    public static BigInteger number(BigInteger mes) {
        if (millerRabin(mes) == true) {
            return mes;
        } else if (millerRabin(mes) == false) {
            do mes = rand();
            while (millerRabin(mes) == false);
        }
        return mes;

    }


    public static BigInteger randN(BigInteger n) {
        BigInteger maxLimit = n.subtract(valueOf(2));
        BigInteger minLimit = new BigInteger("2");

        BigInteger bigInteger = maxLimit.subtract(minLimit);
        Random randNum = new Random();
        int len = maxLimit.bitLength();
        BigInteger mes = new BigInteger(len, randNum);

        if (mes.compareTo(minLimit) < 0)
            mes = mes.add(minLimit);

        if (mes.compareTo(bigInteger) >= 0)
            mes = mes.mod(bigInteger).add(minLimit);


        return mes;
    }

    private static Boolean millerRabin(BigInteger n) {
        if (n.compareTo(valueOf(1)) == -1) {
            return false;
        }
        if (n.compareTo(valueOf(3)) == -1) {
            return false;
        }
        if (n.mod(valueOf(2)).equals(valueOf(0))) {
            return false;
        } else {
            int k = 15;
            for (int j = 0; j < k; j++) {
                BigInteger a = randN(n);
                if (a.compareTo(n) == -1) {
                    int s = 0;
                    BigInteger d = n.subtract(valueOf(1));
                    while (d.mod(valueOf(2)).equals(valueOf(0))) {
                        s++;
                        d = d.divide(valueOf(2));

                    }
                    BigInteger x = a.modPow(d, n);

                    if (x.equals(valueOf(1)) || x.equals(n.subtract(valueOf(1))))
                        continue;

                    for (int i = 1; i < s; i++) {

                        x = (x.multiply(x)).mod(n);

                        if (x.equals(valueOf(1))) {
                            return false;
                        }

                        if (x.equals(n.subtract(valueOf(1))))
                            break;

                    }

                    if (x.compareTo(n.subtract(valueOf(1))) != 0) {
                        return false;
                    }
                }
            }
            return true;
        }
    }


    public static ArrayList<BigInteger> prov(BigInteger p, BigInteger q, BigInteger p1, BigInteger q1) {
        BigInteger pq = p.multiply(q);
        BigInteger p1q1 = p1.multiply(q1);


        ArrayList val = new ArrayList();
        ArrayList val1 = new ArrayList();

        if (p1q1.compareTo(pq) == 1) {
            val.add(0, p);
            val.add(1, q);
            val.add(2, p1);
            val.add(3, q1);
        } else {
            do {
                p = number(rand());
                q = number(rand());
                p1 = number(rand());
                q1 = number(rand());

                val1.add(0, p);
                val1.add(1, q);
                val1.add(2, p1);
                val1.add(3, q1);

                return val1;

            } while (p1q1.compareTo(pq) != 1);

        }
        return val;
    }

}









