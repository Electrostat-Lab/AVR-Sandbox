package com.scrappers.fsa.state;

/**
 * Represents an automaton system state.
 * 
 * @author pavl_g.
 */
public interface AutoState<T> {
    void invoke(T input);
}
