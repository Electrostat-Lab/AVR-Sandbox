package com.scrappers.fsa.example;

import java.util.NoSuchElementException;
import java.util.logging.Logger;

import com.scrappers.fsa.TransitionalManager;

public final class TestFiniteStateAutomaton extends Thread {

    private TransitionalManager transitionalManager;

    public TestFiniteStateAutomaton() {
        super("Test-Finite-State-Automaton");
    }
    
    public void init() {
        /* initialize the manager on the first update */
        if (transitionalManager == null) {
            transitionalManager = TransitionalManager.initialize();
        }

        final SerialAdder adder0 = new SerialAdder();
        final SerialAdder adder1 = new SerialAdder();

        transitionalManager.assignNextState(adder0);
        transitionalManager.assignNextState(adder1);
    }
    
    @Override
    public void run() {
        try {
            transitionalManager.transit(500, new Adder(2, 6));
            transitionalManager.transit(100, new Adder(3, 10));
        } catch (InterruptedException e) {
            e.printStackTrace();
        } 
        
        Logger.getLogger(getName()).info("Finite state finishes !");
    }
}
