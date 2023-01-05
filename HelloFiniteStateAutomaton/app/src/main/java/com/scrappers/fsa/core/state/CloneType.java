package com.scrappers.fsa.core.state;

/**
 * Describes a clone type, either superficial clone or deep clone.
 * 
 * @author pavl_g
 */
public enum CloneType {
    /**
     * Delegate to perform a superficial clone -- memory reference object.
     */
    SUPERFICIAL(0b00010000), 
    
    /**
     * Delegates to perform a deep clone -- new memory chunk with the same data.
     */
    DEEP(0b100000000);

    final int code;

    /**
     * Instantiates a new clone type.
     * 
     * @param code the code for the clone type
     */
    CloneType(final int code) {
        this.code = code;
    }

    /**
     * Retreives the clone type code from the heap into the stack.
     * 
     * @return the clone type code in integers
     */
    public int getCode() {
        return code;
    }
}
