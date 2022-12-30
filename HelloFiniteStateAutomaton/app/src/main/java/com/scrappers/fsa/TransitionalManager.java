package com.scrappers.fsa;

import java.util.logging.Logger;
import java.util.ArrayList;
import java.util.List;
import java.lang.Thread;
import com.scrappers.fsa.state.AutoState;

public final class TransitionalManager {
    
    public static final Logger LOGGER = Logger.getLogger(TransitionalManager.class.getName());
    public final List<AutoState<?>> autostates = new ArrayList<>();
    
    private static TransitionalManager INSTANCE;
    
    private TransitionalManager() {
    }
    
    public static TransitionalManager initialize() {
        synchronized (TransitionalManager.class) {
            /* sanity check the input */
            if (INSTANCE != null) {
                return INSTANCE;
            }
            INSTANCE = new TransitionalManager();
        }
        return INSTANCE;
    }
     
    public void assignNextState(AutoState<?> autostate) { 
        autostates.add(autostate);
    }
    
    public <T> void transit(final long time, final T input) throws InterruptedException {
        Thread.sleep(time);
        transitNow(input);
    }
    
    public <T> void transitNow(final T input) {
        final AutoState<T> autoState = (AutoState<T>) autostates.iterator().next();
        /* sanity check the input */
        assert autostates.contains(input);
        autoState.invoke(input);
        autostates.remove(autoState);
    }
}
