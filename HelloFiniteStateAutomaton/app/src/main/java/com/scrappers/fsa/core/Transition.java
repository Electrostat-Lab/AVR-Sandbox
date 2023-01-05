package com.scrappers.fsa.core;

import com.scrappers.fsa.core.state.AutoState;
import com.scrappers.fsa.core.state.NextStateNotFoundException;

/**
 * Represents a machine system transition with one next-state {@link Transition#nextState}.
 * 
 * @author pavl_g
 */
public final class Transition<S extends AutoState<?, ?>> {
    
    private S nextState;

    /**
     * Instantiates a transition with an empty next-state.
     */
    public Transition() {
    }

    /**
     * Instantiates a transition with a next-state.
     * 
     * @param nextState the next-state object to assign
     */
    public Transition(S nextState) {
        this.nextState = nextState;
    }

    /**
     * Assigns a next-state into your heap memory.
     * Default value is (null).
     * 
     * @param nextState the next-state object to assign
     */
    public void setNextState(S nextState) {
        this.nextState = nextState;
    }

    /**
     * Loads the state from your heap into your stack memory.
     * 
     * @return the next state of the transition system
     * @throws NextStateNotFoundException thrown if the {@link TransitionalManager#transit(Object, com.scrappers.fsa.core.state.TransitionListener)}
     * is called without assigning a next state
     */
    public S getNextState() throws NextStateNotFoundException {
        /* a business exception if there is no next-state assigned */
        if (nextState == null) {
            throw new NextStateNotFoundException();
        }
        return nextState;
    }

    /**
     * Removes the state from the heap memory.
     * 
     * @apiNote warning, this removes the deep copy aka. the real pointer
     * from your heap memory, so you might expect uneventful results.
     */
    public void remove() {
        nextState = null;
    }
}