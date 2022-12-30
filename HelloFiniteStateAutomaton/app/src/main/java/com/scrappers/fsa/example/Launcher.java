package com.scrappers.fsa.example;

public final class Launcher {
    public static void main(String[] args) {
        final TestFiniteStateAutomaton finiteStateAutomataTest = new TestFiniteStateAutomaton();
        finiteStateAutomataTest.init();
        finiteStateAutomataTest.start();
    }
}
