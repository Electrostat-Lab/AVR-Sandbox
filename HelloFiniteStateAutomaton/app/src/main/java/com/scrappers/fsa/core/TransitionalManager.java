package com.scrappers.fsa.core;

import java.util.logging.Logger;
import java.util.ArrayList;
import java.util.List;
import java.lang.Thread;
import com.scrappers.fsa.core.state.AutoState;
import com.scrappers.fsa.core.state.TransitionListener;

public class TransitionalManager {
    
    public static final Logger LOGGER = Logger.getLogger(TransitionalManager.class.getName());
    public final List<AutoState<?, ?>> autostates = new ArrayList<>();
     
    public <I, O> void assignNextState(AutoState<I, O> autostate) { 
        autostates.add(autostate);
    }
    
    public <I> void transit(final long time, final I input, final TransitionListener transitionListener) throws InterruptedException {
        Thread.sleep(time);
        transit(input, transitionListener);
    }
    
    public <I, O> void transit(final I input, final TransitionListener transitionListener) {
        final AutoState<I, O> autoState = (AutoState<I, O>) autostates.iterator().next();
        /* sanity check the input */
        autoState.invoke(input);
        transitionListener.onTransition(autoState);
        autoState.onFinish();
        autostates.remove(autoState);
    }
}
