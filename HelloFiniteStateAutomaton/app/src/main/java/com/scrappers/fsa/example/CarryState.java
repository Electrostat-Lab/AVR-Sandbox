package com.scrappers.fsa.example;

import com.scrappers.fsa.core.state.AutoState;
import java.util.logging.Logger;
import java.util.logging.Level;

public final class CarryState implements AutoState<BitsAdder, Integer> {
    
    private BitsAdder adder;
    private Integer carry = Integer.valueOf(0);
    private final Logger LOGGER = Logger.getLogger(CarryState.class.getName());
    
    @Override
    public void invoke(BitsAdder adder) {
        this.adder = adder;
        adder.output = adder.add() + 1;

        /* sanity update output and carry */
        if (adder.output == 2) {
            // output = 0 and carry = 1
            adder.output = 0;
            carry = Integer.valueOf(1);
        } else if (adder.output == 3) {
            // output = 1 and carry = 1
            adder.output = 1;
            carry = Integer.valueOf(1);
        } /* else, carry = 0 :-) */

        LOGGER.log(Level.INFO, "Present-State = CarryState ; " + "X1/X2 = Z" + " ; " + adder.input0 + "/" + adder.input1 + " = " + adder.output);
    }

    @Override
    public BitsAdder getInput() {
        return this.adder;
    }

    @Override
    public Integer getStateTracer() {
        return carry;
    }

    @Override
    public void onFinish() {
        // reset values and/or release resoureces
        carry = Integer.valueOf(0);
        this.adder = null;
    }

    @Override
    public void onStart() {
        
    }
}
