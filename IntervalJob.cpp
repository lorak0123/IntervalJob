#include "IntervalJob.h"

// Initialize static members
IntervalJob* IntervalJob::instances[MAX_INSTANCES] = { nullptr };
int IntervalJob::instanceCount = 0;

/**
 * Constructor - Adds the instance to the static list.
 */
IntervalJob::IntervalJob(unsigned long interval, bool (*job)(), unsigned long untilFinishInterval, bool singleRun)
: interval(interval), jobBool(job), jobVoid(nullptr), untilFinishInterval(untilFinishInterval), singleRun(singleRun) {
    lastRun = millis();
    jobFinished = true;
    if (instanceCount < MAX_INSTANCES) {
        instances[instanceCount++] = this;
    }
}

/**
 * Constructor - Adds the instance to the static list.
 */
IntervalJob::IntervalJob(unsigned long interval, void (*job)(), unsigned long untilFinishInterval, bool singleRun)
: interval(interval), jobBool(nullptr), jobVoid(job), untilFinishInterval(untilFinishInterval), singleRun(singleRun) {
    lastRun = millis();
    jobFinished = true;
    if (instanceCount < MAX_INSTANCES) {
        instances[instanceCount++] = this;
    }
}

/**
 * Destructor - Removes the instance from the static list.
 */
IntervalJob::~IntervalJob() {
    for (int i = 0; i < instanceCount; i++) {
        if (instances[i] == this) {
            // Shift the remaining instances down the array
            for (int j = i; j < instanceCount - 1; j++) {
                instances[j] = instances[j + 1];
            }
            instanceCount--; // Decrease the instance count
            break;
        }
    }
}

/**
 * Executes the job if the specified interval has passed.
 */
void IntervalJob::run() {
    unsigned long currentMillis = millis();
    if (jobFinished && currentMillis - lastRun >= interval) {
        lastRun = currentMillis;
        if (jobBool) {
            jobFinished = jobBool();
        } else if (jobVoid) {
            jobVoid();
        }

        if (singleRun && jobFinished) {
            delete this;
        }
    }
    else if (!jobFinished && untilFinishInterval != 0 && currentMillis - lastRun >= untilFinishInterval) {
        lastRun = currentMillis;
        if (jobBool) {
            jobFinished = jobBool();
        } else if (jobVoid) {
            jobVoid();
        }

        if (singleRun && jobFinished) {
            delete this;
        }
    }
}

/**
 * Updates the interval between job executions.
 */
void IntervalJob::setInterval(unsigned long interval) {
    this->interval = interval;
}

/**
 * Retrieves the current interval between job executions.
 */
unsigned long IntervalJob::getInterval() {
    return interval;
}

/**
 * Static method to run all registered instances.
 */
void IntervalJob::runAll() {
    for (int i = 0; i < instanceCount; i++) {
        instances[i]->run();
    }
}
