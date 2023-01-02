package com.scrappers.fsa.core.state;

import com.scrappers.fsa.core.TransitionalManager;

/**
 * Loaded into the stack and disptached as a result of trying to call {@link TransitionalManager#transit(Object, TransitionListener)}
 * without assigning a next state or as a result of removing the state from the heap before transitting the system.
 * 
 * @author pavl_g
 */
public class NextStateNotFoundException extends NullPointerException {
    
    /**
     * Instantiates a new exception as a result of transitting into an empty next-state.
     */
    public NextStateNotFoundException() {
        super("Next-State of the transition is not found !");
    }
}
