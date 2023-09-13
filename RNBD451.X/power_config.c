/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "power_config.h"
#include "mcc_generated_files/pin_manager.h"
#include <stdint.h>
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

//#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
#define _XTAL_FREQ 12000000

/** 
  @Function
    void powerSaveEnable()

  @Summary
    Enables all power saving features for the MCU, RNBD451 sensor, as well as the temperature MCP9808 sensor
 */
void powerSaveEnable(MCP9808_i2c_params i2cParams){

    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

 
    //set the SHDN bit to on
    writeBuffer[1] = writeBuffer[1] | MCP9808_SHUTDOWN_MODE;
    
    //write back the register
    errorCode = MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));
    
     IO_RE1_SetHigh();
    __delay_ms(10);//The RNBD451 specifies the need for a minimum of 2 ms of delay between chaning power states. 
    
    SLEEP();
}


/** 
  @Function
    void powerSaveEnable()

  @Summary
     Disables all power saving features for the MCU, RNBD451 sensor, as well as the temperature MCP9808 sensor
 */
void powerSaveDisable(MCP9808_i2c_params i2cParams){

    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

    //set the SHDN bit to on
    writeBuffer[1] = writeBuffer[1] & 0xfe; 
    
    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));
    
     IO_RE1_SetLow();
    __delay_ms(10);//The RNBD451 specifies the need for a minimum of 2 ms of delay between chaning power states.

    
}


/** 
  @Function
    void MCP9808powerSaveEnable()

  @Summary
    Enables power saving features MCP9808 sensor.
 */
void MCP9808powerSaveEnable(MCP9808_i2c_params i2cParams){

    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

 
    //set the SHDN bit to on
    writeBuffer[1] = writeBuffer[1] | MCP9808_SHUTDOWN_MODE;
    
    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));
   
}


/** 
  @Function
    void MCP9808powerSaveDisable()

  @Summary
    Disables power saving features MCP9808 sensor.
 */
void MCP9808powerSaveDisable(MCP9808_i2c_params i2cParams){

    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

    //set the SHDN bit to on
    writeBuffer[1] = writeBuffer[1] & 0xfe; 
    
    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));
    
}


/** 
  @Function
    void  RNBD451powerSaveEnable()

  @Summary
    Enables power saving features RNBD451 module.
 */
void RNBD451powerSaveEnable(void){
    
    IO_RE1_SetHigh();
    __delay_ms(100);//The RNBD451 specifies the need for a minimum of 2 ms of delay between chaning power states. 
}




/** 
  @Function
    RNBD451powerSaveDisable()

  @Summary
    Disables power saving features RNBD451 module.
 */
void RNBD451powerSaveDisable(void){

     IO_RE1_SetLow();
    __delay_ms(100);//The RNBD451 specifies the need for a minimum of 2 ms of delay between chaning power states.

}


/* *****************************************************************************
 End of File
 */
