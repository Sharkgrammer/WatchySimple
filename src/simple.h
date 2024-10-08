#ifndef WATCHY_SIMPLE_H
#define WATCHY_SIMPLE_H

#ifdef WATCHY_SIM
#include "..\..\Watchy.h"
#else // WATCHY_SIM
#include <Watchy.h>
#endif // WATCHY_SIM
#include "Seven_Segment10pt7b.h"
#include "DSEG7_Classic_Regular_15.h"
#include "DSEG7_Classic_Bold_25.h"
#include "DSEG7_Classic_Regular_39.h"
#include "icons.h"

class WatchySimple : public Watchy {
    using Watchy::Watchy;
public:
    void drawWatchFace();
    void drawTime();
    void drawDate();
    void drawSteps();
    void drawBattery();
};

#endif