#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
    double min, max;
    // pre-defined useful intervals: declaration
    static const interval empty, universe;

    interval() : min(+infinity), max(-infinity) {}
    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return !(x < min || x > max);
    }

    bool surrounds(double x) const {
        return !(x <= min || x >= max);
    }

    double clamp(double x) const {
        if (x > max) return max;
        if (x < min) return min;
        return x;
    }

};

// pre-defined useful intervals: definition
const interval interval::empty = interval{+infinity, -infinity};
const interval interval::universe = interval{-infinity, +infinity};
#endif