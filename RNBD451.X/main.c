/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC18F47Q10
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "stdio.h"
#include "power_config.h"
#define VDD                                 3.3
#define ADC_TO_CELSIUS(adcVal)              (int16_t) ((1241.4967 - VDD * (1024 - (adcVal))) / 2.70336)
#define ADC_TO_FAHRENHEIT(adcVal)           (int16_t) ((((1241.4967 - VDD * (1024 - (adcVal))) / 2.70336) * 1.8) + 32)

/*
                         Main application
 */
uint16_t volatile adcVal;
int16_t volatile celsiusValue;
int16_t volatile fahrenheitValue; 


MCP9808_i2c_params MCP9808;
MCP9600_alert_flags alert_flags;
float tempval;


void configRNBD451()
{
    //Initializing CMD Mode on the RF Transmitter
    printf("$$$"); 
    __delay_ms(100);
    
    //Set the device name
    printf("SN,LowPowerTemperatureSensor\n"); 
    __delay_ms(100);
    
    //Set the Transparent UART profile for the RF Transmitter
    printf("SS,C0\n");
    __delay_ms(100);
    
    //Reboot the device with new configuration
    printf("R,1\n"); 
    __delay_ms(100);
    
    //Initializing CMD Mode on the RF Transmitter
    printf("$$$"); 
    __delay_ms(100);
    
    //Set Low Power Mode Enable . In this configuration, the RNDB451 will not receive any other commands
    //RF Transmitter will remain in low power mode until RNBD451powerSaveDisable() is called
    printf("SO,1\n");

}

void readAndSendTemp(MCP9808_i2c_params MCPparams)
{
   
    ADCC_DischargeSampleCapacitor();  
    
    //Delay is necessary in order to insure a correct ADC reading 
    __delay_ms(1000);
    //Getting ADC reading and loading the temperature value in the appropiate variables
    adcVal = ADCC_GetSingleConversion(channel_Temp);     
    celsiusValue = ADC_TO_CELSIUS(adcVal); 
    fahrenheitValue = ADC_TO_FAHRENHEIT(adcVal);
    __delay_ms(1000);
    
    //Powering on the RF Transmitter and the Sensor
    RNBD451powerSaveDisable();
    MCP9808powerSaveDisable(MCPparams);
    
    //Turning on continous conversion in order to 
    MCP9808_EnableContinuousConversionMode(MCPparams);
    
    //Datasheet specifies a minimum delay in order to have a correct reading of the sensor.
    //Delay varies depending on the resolution of the sensor. For a granularity of 0.125, the necessary delay is 130ms 
    __delay_ms(135); 
    
    //Driver function used to load the temperature value in the global variable "tempval". MCParams 
    MCP9808_GetTemperatureValue(MCPparams, &alert_flags ,&tempval);  
    
    //Sending values through the RNDB451 
    printf("Internal sensor temperature in fahrenheit: %d \n", fahrenheitValue);
    printf("Internal sensor temperature in celsius: %d \n", celsiusValue); 
    printf("External sensor temperature: %f \n", tempval);
    
    //Enabling Power Saving Features
    MCP9808powerSaveEnable(MCPparams);
    RNBD451powerSaveEnable();
    powerSaveEnable(MCPparams);
    
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    //TRISEbits.TRISE0=0; //Pin ul de control low power mode RNDB

    float resolution = 0.125;
    MCP9808.i2cAddress = 0x18;
    MCP9808.i2cBusID = 0x01;
    MCP9808_SetResolutionValue(MCP9808, resolution);
    
   // MCP9808_EnableShutdownMode(MCP9808);

    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    int counter = 0;
    
    RNBD451powerSaveDisable();

    configRNBD451();

    RNBD451powerSaveEnable();

    
while (1)
    {
    
    readAndSendTemp(MCP9808);
    
 }
}

    

/**
 End of File
*/