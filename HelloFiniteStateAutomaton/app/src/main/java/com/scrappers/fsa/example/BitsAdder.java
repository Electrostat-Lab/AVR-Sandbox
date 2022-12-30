package com.scrappers.fsa.example;

/**
 * An action that adds 2 numbers.
 * 
 * @author pavl_g.
 */
public final class BitsAdder {
    public final int input0;
    public final int input1;
    public int output;
    
    public BitsAdder(int input0, int input1) {
        this.input0 = input0;
        this.input1 = input1;
    }
    
    public int add() {
        output = input0 + input1;
        return output;
    }
}
