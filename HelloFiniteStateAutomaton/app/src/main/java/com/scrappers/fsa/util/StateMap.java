package com.scrappers.fsa.util;

import com.scrappers.fsa.core.TransitionalManager;
import com.scrappers.fsa.core.state.AutoState;

/**
 * Provides a state-map composed of two states, a present-state and a next-state.
 * 
 * @author pavl_g
 * @see {@link TransitionalManager#transit(StateMap, com.scrappers.fsa.core.state.TransitionListener)}
 */
public final class StateMap<S extends AutoState<?, ?>> {

    private S presentState;
    private S nextState;

    /**
     * Instantiates a new state map with empty states
     */
    public StateMap() {
        this(null, null);
    }

    /**
     * Instantiates a new state map with a present-state and a next-state.
     * 
     * @param presentState a present-state to transit to
     * @param nextState a next-state to assign for the next transition
     */
    public StateMap(S presentState, S nextState) {
        this.presentState = presentState;
        this.nextState = nextState;
    }
    
    /**
     * 
     * 
     * @param presentState
     */
    public void assignPresentState(S presentState) {
        this.presentState = presentState;
    }
    
    public void assignNextState(S nextState) {
        this.nextState = nextState;
    }
    
    /**
     * Retains the next-state object from the heap memory.
     * 
     * @return the next-state object
     */
    public S getNextState() {
        return nextState;
    }

    /**
     * Retains the present-state object from the heap memory.
     * 
     * @return the present-state object
     */
    public S getPresentState() {
        return presentState;
    }

    public void removePresentState() {
        presentState = null;
    }

    public void removeNextState() {
        nextState = null;
    }

    public void removeAll() {
        removePresentState();
        removeNextState();
    }
}
