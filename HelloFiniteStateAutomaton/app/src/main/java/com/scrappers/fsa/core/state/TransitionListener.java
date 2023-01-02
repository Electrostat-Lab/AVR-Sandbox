package com.scrappers.fsa.core.state;

import com.scrappers.fsa.core.TransitionalManager;

/**
 * An event-driven functional interface which handles the call to {@link TransitionListener#onTransition(AutoState)},
 * the call is loaded into the stack by invoking {@link TransitionalManager#transit(Object, TransitionListener)}.
 * 
 * Applications should implement this interface to listen for the invocation of the system transition.
 * 
 * @author pavl_g
 */
public interface TransitionListener {
    
    /**
     * Dispatched as a result of commiting a call to {@link TransitionalManager#transit(Object, TransitionListener)}.
     * 
     * Applications should decide how they want to transit to other states from here by selectively assigning them 
     * based on some system conditions, the API provides a carrier for these system conditions on the tracer object
     * {@link AutoState#getStateTracer()} utilizing the abstract factory pattern.
     * 
     * @param <I> the type for the state input
     * @param <O> the type for the state tracer object
     * @param presentState the current running state
     */
    <I, O> void onTransition(final AutoState<I, O> presentState);
}
