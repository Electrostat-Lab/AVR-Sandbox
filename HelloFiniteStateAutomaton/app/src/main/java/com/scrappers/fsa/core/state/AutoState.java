package com.scrappers.fsa.core.state;

/**
 * Represents an automaton system state.
 * 
 * @param <I> type-generic for the state-input.
 * @param <O> type-generic for the state-tracer object.
 * @author pavl_g.
 */
public interface AutoState<I, O> {
    void invoke(I input);
    void onFinish();
    I getInput();
    O getStateTracer();
}
