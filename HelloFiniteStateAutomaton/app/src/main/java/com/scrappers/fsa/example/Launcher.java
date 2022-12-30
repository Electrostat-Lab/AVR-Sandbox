package com.scrappers.fsa.example;

/**
 * Application entry point.
 * 
 * @auhor pavl_g.
 */
public final class Launcher {
    public static void main(String[] args) {
        final SerialAdder finiteStateAutomataTest = new SerialAdder();
        finiteStateAutomataTest.init();
        finiteStateAutomataTest.start();
    }
}
