#include "../LIB/STD.h"
#include "../LIB/ErrorStates.h"

#include "../HAL/LCD/LCD_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"

#include "VoltageDisplayer_Private.h"
#include "VoltageDisplayer_Config.h"

static Voltage_t str_VoltageValue;

//APIs' implementations
extern ErrorState_t VoltageDisplay_enu_Initialization (void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Initializing LCD
    LCD_enu_Initialization();

    //Configuring pins as read
    DIO_enu_SetPinDiretion(DIO_PIN_GROUP_A, DIO_PIN_0, DIO_PIN_READ);
    DIO_enu_SetPinState(DIO_PIN_GROUP_A, DIO_PIN_0, DIO_FLOAT);

    //Initializing ADC
    ADC_enu_Initialization();


    return Local_u8_ErrorFlag;
}

extern ErrorState_t VoltageDisplay_enu_Operate (void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    
    //Displaying static string
    enu_DisplayUnit();

    while (1)
    {

        //Printing acquired value
        enu_DisplayVoltage();
    }

    return Local_u8_ErrorFlag;
}

//Local functions' implementations 
static ErrorState_t enu_DisplayVoltage (void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Getting a new read from ACD0 pinSA
    ADC_enu_ReadPolling(ADC_ADC0, &(str_VoltageValue.VoltageLevel));
   
    LCD_enu_GoToPosition(LCD_ROW_1, LCD_COLUMN_8, LCD_PAGE_1);
    LCD_enu_SendString("    ");


    #if VOLTAGE_DISPLAY_UNIT == VOLTAGE_DISPLAY_MV 

        str_VoltageValue.VoltageLevel  = str_VoltageValue.VoltageLevel *((f32)5/1024*1000);

    #elif VOLTAGE_DISPLAY_UNIT == VOLTAGE_DISPLAY_V
        
        str_VoltageValue.VoltageLevel  = str_VoltageValue.VoltageLevel *(5/1024);

    #else
        #error "VOLTAGE_DISPLAY_UNIT is invalid"
    #endif

    LCD_enu_WriteIntegerNum(str_VoltageValue.VoltageLevel, LCD_ROW_1, LCD_COLUMN_8, LCD_PAGE_1);


    return Local_u8_ErrorFlag;

    
}

static ErrorState_t enu_DisplayUnit(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Placing Cursor
    LCD_enu_GoToPosition(LCD_ROW_1, LCD_COLUMN_1, LCD_PAGE_1);
    //Displaying 'Voltage = '
    LCD_enu_SendString("Volt = ");

     
    //Placing Cursor
    LCD_enu_GoToPosition(LCD_ROW_1, LCD_COLUMN_12, LCD_PAGE_1);
    
    #if VOLTAGE_DISPLAY_UNIT == VOLTAGE_DISPLAY_MV 

        //Displaying 'mV'
        LCD_enu_SendString("mV");

    #elif VOLTAGE_DISPLAY_UNIT == VOLTAGE_DISPLAY_V
        
        //Displaying 'V'
        LCD_enu_SendString("V");

    #else
        #error "VOLTAGE_DISPLAY_UNIT is invalid"
    #endif

    return Local_u8_ErrorFlag;

    
}