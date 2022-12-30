package com.scrappers.fsa.core;

import java.util.logging.Logger;
import java.util.ArrayList;
import java.util.List;
import java.lang.Thread;
import com.scrappers.fsa.core.state.AutoState;
import com.scrappers.fsa.core.state.TransitionListener;

public final class TransitionalManager {
    
    public static final Logger LOGGER = Logger.getLogger(TransitionalManager.class.getName());
    public final List<AutoState<?, ?>> autostates = new ArrayList<>();
    
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
     
    public void assignNextState(AutoState<?, ?> autostate) { 
        autostates.add(autostate);
    }
    
    public <T> void transit(final long time, final T input, final TransitionListener transitionListener) throws InterruptedException {
        Thread.sleep(time);
        transitNow(input, transitionListener);
    }
    
    public <I> void transitNow(final I input, final TransitionListener transitionListener) {
        final AutoState<I, ?> autoState = (AutoState<I, ?>) autostates.iterator().next();
        /* sanity check the input */
        assert autostates.contains(input);
        autoState.invoke(input);
        transitionListener.onTransition(autoState);
        autostates.remove(autoState);
    }
}
