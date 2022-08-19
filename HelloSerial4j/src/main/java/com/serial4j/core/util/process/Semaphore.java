package com.serial4j.core.util.process;

import java.util.logging.Logger;

/**
 * A thread synchronizer utility using mutex data states.
 *
 * @see Semaphore.Mutex
 * @author pavl_g.
 */
public final class Semaphore {
    private final Mutex mutex;
    private static final Logger logger = Logger.getLogger(Semaphore.class.getName());

    public enum Mutex {
        SIMPLE_MUTEX(new Object(), new Object(), new Object());

        private Object lockData;
        private Object monitorObject;
        private Object unlockData;

        <O, LD, ULD> Mutex(final O monitorObject, final LD lockData, final ULD unlockData) {
            this.monitorObject = monitorObject;
            this.lockData = lockData;
            this.unlockData = unlockData;
        }

        public void setLockData(Object lockData) {
            this.lockData = lockData;
        }

        public void setMonitorObject(Object monitorObject) {
            this.monitorObject = monitorObject;
        }

        protected void setUnlockData(Object unlockData) {
            this.unlockData = unlockData;
        }

        public Object getLockData() {
            return lockData;
        }

        public Object getMonitorObject() {
            return monitorObject;
        }

        public Object getUnlockData() {
            return unlockData;
        }

        /**
         * Creates a 'no job' job to trick the java loop.
         * (a java loop must have something inside to act upon).
         *
         * @return a null job.
         */
        protected final Void NO_JOB() {
            return null;
        }
    }

    private Semaphore(Mutex mutex) {
        this.mutex = mutex;
    }

    public static Semaphore build(Mutex mutex) {
        logger.fine("Semaphore initialized with monitor " + mutex.getMonitorObject() + " and data object " + mutex.getLockData());
        return new Semaphore(mutex);
    }

    public <MO> void lock(final MO monitorObject) {
        // order for a lock
        this.mutex.setMonitorObject(monitorObject);
        // format the unlock data for a new lock dispatcher
        this.mutex.setUnlockData(new Object());
        logger.fine("Lock obtained with monitor " + monitorObject);
    }

    public void waitForUnlock() {
        while (mutex.getLockData() != mutex.getUnlockData()) {
            final Void NO_JOB = mutex.NO_JOB();
        }
    }

    public <O> void unlock(final O locker) {
        if (locker != mutex.getMonitorObject()) {
            throw new IllegalMonitorStateException("The current thread doesn't own this object !");
        }
        // release the lock
        mutex.setUnlockData(mutex.getLockData());
        logger.fine(locker + " Unlocked");
    }

    public Mutex getMutex() {
        return mutex;
    }
}
