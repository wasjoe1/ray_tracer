#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
    // min & max
    double min, max;
    // pre-defined useful intervals
    static const interval empty, universe;

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

const interval interval::empty = interval{+infinity, -infinity};
const interval interval::universe = interval{-infinity, +infinity};

#endif