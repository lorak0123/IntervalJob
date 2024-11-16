#ifndef INTERVALJOB_H
#define INTERVALJOB_H

#include <Arduino.h>

#define MAX_INSTANCES 20 // Maximum number of instances allowed

/**
 * Class IntervalJob
 * Manages timed execution of a job with optional completion tracking.
 */
class IntervalJob {
  private:
    unsigned long lastRun;              // Timestamp of the last run
    bool (*jobBool)();                  // Pointer to a function that returns a bool
    void (*jobVoid)();                  // Pointer to a function that returns void
    bool jobFinished;                   // Indicates if the job is finished
    unsigned long untilFinishInterval;  // Interval to complete a job
    unsigned long interval;             // Interval between job executions
    bool singleRun;                     // Flag to run the job only once

    // Static array to hold pointers to all instances of IntervalJob
    static IntervalJob* instances[MAX_INSTANCES];
    static int instanceCount; // Number of currently active instances

  public:
    /**
     * Constructor - Adds the instance to the static list.
     * @param interval Interval between job executions (ms)
     * @param job Pointer to the job function
     * @param untilFinishInterval Optional interval to retry until completion (default: 0)
     * @param singleRun Flag to run the job only once (default: false)
     */
    IntervalJob(unsigned long interval, bool (*job)(), unsigned long untilFinishInterval = 0, bool singleRun = false);

    /**
     * Constructor - Adds the instance to the static list.
     * @param interval Interval between job executions (ms)
     * @param job Pointer to the job function
     * @param untilFinishInterval Optional interval to retry until completion (default: 0)
     * @param singleRun Flag to run the job only once (default: false)
     */
    IntervalJob(unsigned long interval, void (*job)(), unsigned long untilFinishInterval = 0, bool singleRun = false);

    /**
     * Destructor - Removes the instance from the static list.
     */
    ~IntervalJob();

    /**
     * Executes the job if the specified interval has passed.
     */
    void run();

    /**
     * Updates the interval between job executions.
     * @param interval New interval (ms)
     */
    void setInterval(unsigned long interval);

    /**
     * Retrieves the current interval between job executions.
     * @return Current interval (ms)
     */
    unsigned long getInterval();

    /**
     * Static method to run all registered instances.
     */
    static void runAll();
};

#endif
