#ifndef VOLTAGEDISP_CONFIG_FILE
#define VOLTAGEDISP_CONFIG_FILE

#include "../LIB/STD.h"
#include "../LIB/ErrorStates.h"


//Options: VOLTAGE_DISPLAY_MV and VOLTAGE_DISPLAY_V
#define VOLTAGE_DISPLAY_UNIT  VOLTAGE_DISPLAY_MV


typedef struct
{
    u16 VoltageLevel;

}Voltage_t;


#endif