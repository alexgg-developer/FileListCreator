#include "QtGlobals.h"

QtGlobals* QtGlobals::single = nullptr;
QtGlobals* QtGlobals::getInstance()
{
    if(!single) {
        single = new QtGlobals();
    }
    return single;
}
