package com.scrappers.fsa.core.state;

public interface TransitionListener {
    <I, O> void onTransition(final AutoState<I, O> presentState);
}
