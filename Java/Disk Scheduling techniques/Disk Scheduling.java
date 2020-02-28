/*
	A simulation of different CPU disk scheduling techniques in java
*/
package com.company;

import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;

public class Main {
    public static Vector<Integer> outSequence = new Vector<>();
    public static Vector<Integer> opt = new Vector<>();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int headstart, numRequests, choice, headDirection;
        System.out.println("Enter head start: ");
        headstart = scanner.nextInt();
        System.out.println("Enter number of requests: ");
        numRequests = scanner.nextInt();
        Vector<Integer> v = new Vector<>();
        System.out.println("Fill the list of requests:");
        for (int i = 0; i < numRequests; i++) {
            int a = scanner.nextInt();
            v.add(a);
        }

        System.out.println("Enter the algorithm number you want to apply:");
        System.out.println("1:First Come First Served");
        System.out.println("2:Shortest Seek Time First");
        System.out.println("3:SCAN");
        System.out.println("4:C-SCAN");
        System.out.println("5:C-LOOK");
        System.out.println("6:Optimized");
        choice = scanner.nextInt();

        switch (choice) {
            case 1:
                int fcfs = FCFS(v, headstart);
                System.out.println("total head movement : "+fcfs);
                System.out.println("the sequence of head movement:");
                for (int i = 0; i < outSequence.size(); i++)
                    System.out.print(outSequence.get(i) + " ");
                int opti = optimized(v, 0);
                int diff = fcfs - opti;
                System.out.println("\nThe difference between FCFS and Optimized is " + fcfs + " - " + opti + " is:  " + diff);
                break;
            case 2:
                int sst = SST(v, headstart);
                System.out.println("total head movement : "+sst);
                System.out.println("the sequence of head movement:");
                for (int i = 0; i < outSequence.size(); i++)
                    System.out.print(outSequence.get(i) + " ");
                opti = optimized(v, 0);
                diff = sst - opti;
                System.out.println("\nThe difference between FCFS and Optimized is " + sst + " - " + opti + " is:  " + diff);
                break;
            case 3:
                System.out.println("Please,Enter head Direction:");
                headDirection = scanner.nextInt();
                int scan = SCAN(v, headstart, headDirection);
                System.out.println("total head movement : "+scan);
                System.out.println("the sequence of head movement:");
                for (int i = 0; i < outSequence.size(); i++)
                    System.out.print(outSequence.get(i) + " ");
                opti = optimized(v, 0);
                diff = scan - opti;
                System.out.println("\nThe difference between FCFS and Optimized is " + scan + " - " + opti + " is:  " + diff);
                break;
            case 4:
                System.out.println("Please,Enter head Direction:");
                headDirection = scanner.nextInt();
                int c_scan = C_SCAN(v, headstart, headDirection);
                System.out.println("total head movement : "+c_scan);
                System.out.println("the sequence of head movement:");
                for (int i = 0; i < outSequence.size(); i++)
                    System.out.print(outSequence.get(i) + " ");
                opti = optimized(v, 0);
                diff = c_scan - opti;
                System.out.println("\nThe difference between FCFS and Optimized is " + c_scan + " - " + opti + " is:  " + diff);
                break;
            case 5:
                System.out.println("Please,Enter head Direction:");
                headDirection = scanner.nextInt();
                int c_look = C_LOOK(v, headstart, headDirection);
                System.out.println("total head movement : "+c_look);
                System.out.println("the sequence of head movement:");
                for (int i = 0; i < outSequence.size(); i++)
                    System.out.print(outSequence.get(i) + " ");
                opti = optimized(v, 0);
                diff = c_look - opti;
                System.out.println("\nThe difference between FCFS and Optimized is " + c_look + " - " + opti + " is:  " + diff);
                break;
            case 6:
                System.out.println("total head movement : "+optimized(v, 0));
                System.out.println("the sequence of head movement:");
                for (int i = 0; i < opt.size(); i++)
                    System.out.print(opt.get(i) + " ");
                break;
        }

    }

    public static int FCFS(Vector<Integer> v, int st) {
        outSequence.clear();
        outSequence.add(st);
        int res = 0;
        for (int i = 0; i < v.size(); i++) {
            res += Math.abs(v.get(i) - st);
            st = v.get(i);
            outSequence.add(v.get(i));
        }
        return res;
    }

    public static int SST(Vector<Integer> v, int st) {
        outSequence.clear();
        outSequence.add(st);
        int res = 0;
        Vector<Boolean> vis = new Vector<Boolean>();
        for (int i = 0; i < v.size(); i++) {
            vis.add(false);
        }
        for (int i = 0; i < v.size(); i++) {
            int mn = 1000000, idx = -1;
            for (int j = 0; j < v.size(); j++) {
                if (!vis.get(j)) {
                    if (Math.abs(v.get(j) - st) < mn) {
                        mn = Math.abs(v.get(j) - st);
                        idx = j;
                    }
                }
            }
            res += Math.abs(v.get(idx) - st);
            st = v.get(idx);
            vis.set(idx, true);
            outSequence.add(v.get(idx));
        }
        return res;
    }

    public static int SCAN(Vector<Integer> v, int st, int h) {
        outSequence.clear();
        v.add(st);
        v.add(h);
        Collections.sort(v);
        int i = v.indexOf(st), move = 1, res = 0;
        if (h < st) {
            move = -1;
        }
        for (int k = 0; k < v.size() - 1; k++) {
            outSequence.add(v.get(i));
            i += move;
            if (i == v.indexOf(h)) {
                outSequence.add(v.get(i));
                if (move == -1)
                    move = 1;
                else
                    move = -1;
                i = v.indexOf(st) + move;
            }
        }
        for (int j = 0; j < outSequence.size() - 1; j++)
            res += Math.abs(outSequence.get(j) - outSequence.get(j + 1));
        return res;
    }

    public static int C_SCAN(Vector<Integer> v, int st, int h) {
        outSequence.clear();
        v.add(st);
        v.add(h);
        v.add(Math.abs(h - 199));//and the another end of the disk
        Collections.sort(v);
        int i = v.indexOf(st), move = 1, res = 0;
        if (h < st) {
            move = -1;
        }
        for (int k = 0; k < v.size() - 1; k++) {
            outSequence.add(v.get(i));
            i += move;
            if (i == v.indexOf(h)) {
                outSequence.add(v.get(i));
                i = v.indexOf(Math.abs(h - 199));
            }
        }
        for (int j = 0; j < outSequence.size() - 1; j++)
            res += Math.abs(outSequence.get(j) - outSequence.get(j + 1));
        return res;
    }

    public static int C_LOOK(Vector<Integer> v, int st, int h) {
        outSequence.clear();
        v.add(st);
        Collections.sort(v);
        int i = v.indexOf(st), move = 1, res = 0;
        if (h < st) {
            move = -1;
        }
        for (int k = 0; k < v.size() - 1; k++) {
            outSequence.add(v.get(i));
            i += move;
            if (i == 0) {
                outSequence.add(v.get(i));
                i = v.size() - 1;
            } else if (i == v.size() - 1) {
                outSequence.add(v.get(i));
                i = 0;
            }
        }
        for (int j = 0; j < outSequence.size() - 1; j++)
            res += Math.abs(outSequence.get(j) - outSequence.get(j + 1));
        return res;
    }

    public static int optimized(Vector<Integer> v, int st) {
        opt.clear();
        opt.add(st);
        Collections.sort(v);
        int res = 0;
        for (int i = 0; i < v.size(); i++) {
            res += Math.abs(v.get(i) - st);
            st = v.get(i);
            opt.add(v.get(i));
        }
        return res;
    }
}
