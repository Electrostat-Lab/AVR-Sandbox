package com.scrappers.fsa.core;

import java.util.logging.Level;
import java.util.logging.Logger;
import java.lang.Thread;
import com.scrappers.fsa.core.state.AutoState;
import com.scrappers.fsa.core.state.TransitionListener;
import com.scrappers.fsa.util.StateMap;

/**
 * Represents the core component that drives and controls the flow of the Finite-State pattern by selectively assigning a new state, 
 * transitting into the newly assigned state and executing the state action.
 * 
 * Each transitional-manager object owns a transition object, the transition object describes a state in terms of memory.
 * 
 * @author pavl_g
 */
public class TransitionalManager {
    
    /**
     * The system transition. 
     */
    protected final Transition<AutoState<?, ?>> transition = new Transition<>();
    private static final Logger LOGGER = Logger.getLogger(TransitionalManager.class.getName());
    
    /**
     * Assigns a new next state.
     * Warning: calling this multiple times on different objects
     * will override the previous one !
     * 
     * @param <I> the state input type
     * @param <O> the tracer object type
     * @param autostate the target state
     */
    public <I, O> void assignNextState(AutoState<I, O> autostate) { 
        transition.setNextState(autostate);
        LOGGER.log(Level.INFO, "Assigned a new state " + autostate);
    }

    /**
     * Assigns a new next state from a system transition.
     * Warning: calling this multiple times on different objects
     * will override the previous one !
     * 
     * @param <I> the state input type
     * @param <O> the tracer object type
     * @param transition the target transition
     */
    public <I, O> void assignNextState(final Transition<AutoState<I, O>> transition) { 
        assignNextState(transition.getNextState());
    }
    
    /**
     * Transits to the next-state from a state-map.
     * 
     * @param <I> the state input type
     * @param <O> the state tracer object type
     * @param map the system state-map holding a presentstate and a nextstate
     * @param transitionListener an event driven interface object that fires {@link TransitionListener#onTransition(AutoState)} 
     *                           after the {@link AutoState#invoke(Object)} is invoked when the transition completes
     * @throws InterruptedException thrown if the application has interrupted the system during the latency period
     */
    public <I, O> void transit(final StateMap<AutoState<I, O>> map, final TransitionListener transitionListener) {
        transit(map.getPresentState().getInput(), transitionListener);
        assignNextState(map.getNextState());
        map.removePresentState();
    }

    /**
     * Transits to the next-state from a state-map with a latency period.
     * 
     * @param <I> the state input type
     * @param <O> the state tracer object type
     * @param time the latency after which the transition starts
     * @param map the system state-map holding a presentstate and a nextstate
     * @param transitionListener an event driven interface object that fires {@link TransitionListener#onTransition(AutoState)} 
     *                           after the {@link AutoState#invoke(Object)} is invoked when the transition completes
     * @throws InterruptedException thrown if the application has interrupted the system during the latency period
     */
    public <I, O> void transit(final long time, final StateMap<AutoState<I, O>> map, final TransitionListener transitionListener) throws InterruptedException {
        transit(time, map.getPresentState().getInput(), transitionListener);
        assignNextState(map.getNextState());
        map.removePresentState();
    }

    /**
     * Transits to the next-state after a latency time in milliseconds.
     * 
     * @param <I> the state input type
     * @param time the latency after which the transition starts
     * @param input the state input argument
     * @param transitionListener an event driven interface object that fires {@link TransitionListener#onTransition(AutoState)} 
     *                           after the {@link AutoState#invoke(Object)} is invoked when the transition completes
     * @throws InterruptedException thrown if the application has interrupted the system during the latency period
     */
    public <I> void transit(final long time, final I input, final TransitionListener transitionListener) throws InterruptedException {
        Thread.sleep(time);
        transit(input, transitionListener);
    }
    
    /**
     * Transits to the next assigned state
     * 
     * @param <I> the state input type
     * @param <O> the tracer object type
     * @param input the state input
     * @param transitionListener an event driven interface object that fires {@link TransitionListener#onTransition(AutoState)} 
     *                           after the {@link AutoState#invoke(Object)} is invoked when the transition completes
     * @throws InterruptedException thrown if the application has interrupted the system during the latency period
     */
    public <I, O> void transit(final I input, final TransitionListener transitionListener) throws NullPointerException {
        final AutoState<I, O> autostate = (AutoState<I, O>) transition.getNextState();
        LOGGER.log(Level.INFO, "Transitting into a new state " + autostate);
        autostate.onStart();
        autostate.invoke(input);
        transitionListener.onTransition(autostate);
        autostate.onFinish();
    }

    /**
     * Retrieves the system transition for debugging purposes only.
     * 
     * @return the transition object holding the next-state (if assigned)
     */
    public Transition<AutoState<?, ?>> getTransition() {
        return transition;
    }
}