package com.scrappers.fsa.example;

/**
 * Application entry point.
 * 
 * @auhor pavl_g.
 */
public final class Launcher {
    public static void main(String[] args) {
        final TestFiniteStateAutomaton finiteStateAutomataTest = new TestFiniteStateAutomaton();
        finiteStateAutomataTest.init();
        finiteStateAutomataTest.start();
    }
}
