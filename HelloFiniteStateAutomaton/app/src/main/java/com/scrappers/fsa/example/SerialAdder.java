package com.scrappers.fsa.example;

import com.scrappers.fsa.state.AutoState;
import java.util.logging.Logger;
import java.util.logging.Level;

public final class SerialAdder implements AutoState<Adder> {
    
    private final Logger LOGGER = Logger.getLogger(SerialAdder.class.getName());
    
    @Override
    public void invoke(Adder adder) {
        LOGGER.log(Level.INFO, "State invoked, shifted to a new present state !");
        LOGGER.log(Level.INFO, String.valueOf(adder.add()));
    }
    
    @Override
    public void revoke(Adder adder) {
        LOGGER.log(Level.INFO, "State revoked with no action !");
    }
}
