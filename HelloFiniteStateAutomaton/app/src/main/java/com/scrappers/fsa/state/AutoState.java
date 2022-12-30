package com.scrappers.fsa.state;

/**
 * @author pavl_g.
 */
public interface AutoState<T> {
    void invoke(T input);
    void revoke(T input);
}
