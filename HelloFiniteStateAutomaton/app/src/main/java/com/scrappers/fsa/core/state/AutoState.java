package com.scrappers.fsa.core.state;

import com.scrappers.fsa.core.TransitionalManager;

/**
 * Represents an automaton system state.
 * 
 * @param <I> type-generic for the state-input
 * @param <O> type-generic for the state-tracer object
 * @author pavl_g
 */
public interface AutoState<I, O> {
   
    /**
     * Dispatched as a start point at {@link TransitionalManager#transit(Object, TransitionListener)}.
     */
    void onStart();

    /**
     * Dispatched as a main invocation point at {@link TransitionalManager#transit(Object, TransitionListener)}.
     * 
     * @param input the input to the state
     */
    void invoke(I input);

    /**
     * Dispatched after {@link AutoState#invoke(Object)}.
     */
    void onFinish();

    /**
     * Loads the given state input to the current stack.
     * 
     * @return the state initial input
     */
    I getInput();

    /**
     * Loads the state tracer object to the current stack.
     * 
     * @return the state tracer object
     */
    O getStateTracer();

    /**
     * Clones object either deeply or superficially.
     * 
     * @apiNote use for debugging purposes only 
     * @param cloneType
     * @return
     */
    default AutoState<I, O> clone(final CloneType cloneType) {
        /* sanity perform a superficial copy */
        if (cloneType.getCode() == CloneType.SUPERFICIAL.getCode()) {
            return this;
        }

        /* perform a deep clone */
        final AutoState<I, O> clone = new AutoState<>() {
            
            public Object substrate = new Object();

            @Override
            public void onStart() {
                ((AutoState<I, O>) substrate).onStart();
            }

            @Override
            public void invoke(I input) {
                ((AutoState<I, O>) substrate).invoke(input);
            }

            @Override
            public void onFinish() {
                ((AutoState<I, O>) substrate).onFinish();
            }

            @Override
            public I getInput() {
                return ((AutoState<I, O>) substrate).getInput();
            }

            @Override
            public O getStateTracer() {
                return ((AutoState<I, O>) substrate).getStateTracer();
            }

            @Override
            public void setCloneSubstrate(AutoState<I, O> substrate) {
                this.substrate = (AutoState<I, O>) substrate;
            }
        };
        clone.setCloneSubstrate((AutoState<I, O>) this);

        return clone;
    }
    
    /**
     * @apiNote internal use-only !
     */
    default void setCloneSubstrate(final AutoState<I, O> substrate) {
    }
}
