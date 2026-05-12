#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
    // min & max
    double min, max;

    // static - class member (variable / method)
    // const - constant; not allowed to change
    static const interval empty, universe; // pre-defined useful intervals

    // own attempt: WRONG => refer to `CS_fundamentals/cpp/quick_notes.md` for more details why we cant do initialization here
    // static const interval empty = interval{+infinity, -infinity};
    // static const interval universe = interval{-infinity, +infinity};

    // constructors
    interval() : min(+infinity), max(-infinity) {}
    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    /**
     * @brief checks whether x is inside interval (interval is inclusive) [min, max]
     * used for when boundaries are valid (RGB intensities).
     */
    bool contains(double x) const {
        return !(x < min || x > max);
    }

    /**
     * @brief checks whether x is inside interval (interval is exclusive) (min, max)
     * used for when boundaries are NOT valid (ray tracing).
     */
    bool surrounds(double x) const {
        return !(x <= min || x >= max);
    }
};

// definition below:
const interval interval::empty = interval{+infinity, -infinity};
const interval interval::universe = interval{-infinity, +infinity};
// note that this potentially causes linker error if we include the header in multiple TUs
// but we only 1 TU so it doesnt cause linker error

#endif