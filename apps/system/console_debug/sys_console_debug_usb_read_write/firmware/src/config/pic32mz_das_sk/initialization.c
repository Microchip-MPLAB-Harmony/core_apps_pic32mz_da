/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************

/*** DEVCFG0 ***/
#pragma config DEBUG =      OFF
#pragma config JTAGEN =     OFF
#pragma config ICESEL =     ICS_PGx2
#pragma config TRCEN =      OFF
#pragma config BOOTISA =    MIPS32
#pragma config FECCCON =    OFF_UNLOCKED
#pragma config FSLEEP =     OFF
#pragma config DBGPER =     PG_ALL
#pragma config SMCLR =      MCLR_NORM
#pragma config SOSCGAIN =   GAIN_2X
#pragma config SOSCBOOST =  ON
#pragma config POSCGAIN =   GAIN_2X
#pragma config POSCBOOST =  ON
#pragma config POSCFGAIN =  GAIN_G3
#pragma config POSCAGCDLY = POSCAGCDLY1
#pragma config POSCAGC =      OFF
#pragma config EJTAGBEN =   NORMAL

/*** DEVCFG1 ***/
#pragma config FNOSC =      SPLL
#pragma config DMTINTV =    WIN_127_128
#pragma config FSOSCEN =    OFF
#pragma config IESO =       ON
#pragma config POSCMOD =    EC
#pragma config OSCIOFNC =   OFF
#pragma config FCKSM =      CSECME
#pragma config WDTPS =      PS1048576
#pragma config WDTSPGM =    STOP
#pragma config WINDIS =     NORMAL
#pragma config FWDTEN =     OFF
#pragma config FWDTWINSZ =  WINSZ_25
#pragma config DMTCNT =     DMT31
#pragma config FDMTEN =     OFF

/*** DEVCFG2 ***/
#pragma config FPLLIDIV =   DIV_1
#pragma config FPLLRNG =    RANGE_5_10_MHZ
#pragma config FPLLICLK =   PLL_FRC
#pragma config FPLLMULT =   MUL_50
#pragma config FPLLODIV =   DIV_2
#pragma config VBATBOREN =  ON
#pragma config DSBOREN =    ON
#pragma config DSWDTPS =    DSPS32
#pragma config DSWDTOSC =   LPRC
#pragma config DSWDTEN =    OFF
#pragma config FDSEN =      ON
#pragma config UPLLFSEL =   FREQ_24MHZ

/*** DEVCFG3 ***/
#pragma config USERID =     0xffff
#pragma config FMIIEN =     ON
#pragma config FETHIO =     ON
#pragma config PGL1WAY =    ON
#pragma config PMDL1WAY =   ON
#pragma config IOL1WAY =    ON

/*** DEVCFG4 ***/
#pragma config SWDTPS = SPS1048576

/*** BF1SEQ0 ***/
#pragma config TSEQ =       0x0
#pragma config CSEQ =       0xffff





// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
/* Following MISRA-C rules are deviated in the below code block */
/* MISRA C-2012 Rule 11.1 */
/* MISRA C-2012 Rule 11.3 */
/* MISRA C-2012 Rule 11.8 */



// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
/******************************************************
 * USB Driver Initialization
 ******************************************************/

const DRV_USBHS_INIT drvUSBInit =
{
    /* Interrupt Source for USB module */
    .interruptSource = INT_SOURCE_USB,

	/* Interrupt Source for USB module */
    .interruptSourceUSBDma = INT_SOURCE_USB_DMA,
	
    /* System module initialization */
    .moduleInit = {0},

    /* USB Controller to operate as USB Device */
    .operationMode = DRV_USBHS_OPMODE_DEVICE,

	/* Enable High Speed Operation */
    .operationSpeed = USB_SPEED_HIGH,
    
    /* Stop in idle */
    .stopInIdle = true,

    /* Suspend in sleep */
    .suspendInSleep = false,

    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USBHS_ID_0,
	
};




// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="SYS_CONSOLE Instance 1 Initialization Data">


/* These buffers are passed to the USB CDC Function Driver */
static uint8_t CACHE_ALIGN sysConsole1USBCdcRdBuffer[SYS_CONSOLE_USB_CDC_READ_WRITE_BUFFER_SIZE];
static uint8_t CACHE_ALIGN sysConsole1USBCdcWrBuffer[SYS_CONSOLE_USB_CDC_READ_WRITE_BUFFER_SIZE];

/* These are the USB CDC Ring Buffers. Data received from USB layer are copied to these ring buffer. */
static uint8_t sysConsole1USBCdcRdRingBuffer[SYS_CONSOLE_USB_CDC_RD_BUFFER_SIZE_IDX1];
static uint8_t sysConsole1USBCdcWrRingBuffer[SYS_CONSOLE_USB_CDC_WR_BUFFER_SIZE_IDX1];

const SYS_CONSOLE_USB_CDC_INIT_DATA sysConsole1USBCdcInitData =
{
    .cdcInstanceIndex           = 1,
    .cdcReadBuffer              = sysConsole1USBCdcRdBuffer,
    .cdcWriteBuffer             = sysConsole1USBCdcWrBuffer,
    .consoleReadBuffer          = sysConsole1USBCdcRdRingBuffer,
    .consoleWriteBuffer         = sysConsole1USBCdcWrRingBuffer,
    .consoleReadBufferSize      = SYS_CONSOLE_USB_CDC_RD_BUFFER_SIZE_IDX1,
    .consoleWriteBufferSize     = SYS_CONSOLE_USB_CDC_WR_BUFFER_SIZE_IDX1,
};

const SYS_CONSOLE_INIT sysConsole1Init =
{
    .deviceInitData = (const void*)&sysConsole1USBCdcInitData,
    .consDevDesc = &sysConsoleUSBCdcDevDesc,
    .deviceIndex = 1,
};


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

static const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)CORETIMER_CallbackSet,
    .timerStart = (SYS_TIME_PLIB_START)CORETIMER_Start,
    .timerStop = (SYS_TIME_PLIB_STOP)CORETIMER_Stop ,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)CORETIMER_FrequencyGet,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)NULL,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)CORETIMER_CompareSet,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)CORETIMER_CounterGet,
};

static const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = 0,
};

// </editor-fold>

static const SYS_DEBUG_INIT debugInit =
{
    .moduleInit = {0},
    .errorLevel = SYS_DEBUG_GLOBAL_ERROR_LEVEL,
    .consoleIndex = 0,
};


// <editor-fold defaultstate="collapsed" desc="SYS_CONSOLE Instance 0 Initialization Data">


/* These buffers are passed to the USB CDC Function Driver */
static uint8_t CACHE_ALIGN sysConsole0USBCdcRdBuffer[SYS_CONSOLE_USB_CDC_READ_WRITE_BUFFER_SIZE];
static uint8_t CACHE_ALIGN sysConsole0USBCdcWrBuffer[SYS_CONSOLE_USB_CDC_READ_WRITE_BUFFER_SIZE];

/* These are the USB CDC Ring Buffers. Data received from USB layer are copied to these ring buffer. */
static uint8_t sysConsole0USBCdcRdRingBuffer[SYS_CONSOLE_USB_CDC_RD_BUFFER_SIZE_IDX0];
static uint8_t sysConsole0USBCdcWrRingBuffer[SYS_CONSOLE_USB_CDC_WR_BUFFER_SIZE_IDX0];

const SYS_CONSOLE_USB_CDC_INIT_DATA sysConsole0USBCdcInitData =
{
    .cdcInstanceIndex           = 0,
    .cdcReadBuffer              = sysConsole0USBCdcRdBuffer,
    .cdcWriteBuffer             = sysConsole0USBCdcWrBuffer,
    .consoleReadBuffer          = sysConsole0USBCdcRdRingBuffer,
    .consoleWriteBuffer         = sysConsole0USBCdcWrRingBuffer,
    .consoleReadBufferSize      = SYS_CONSOLE_USB_CDC_RD_BUFFER_SIZE_IDX0,
    .consoleWriteBufferSize     = SYS_CONSOLE_USB_CDC_WR_BUFFER_SIZE_IDX0,
};

const SYS_CONSOLE_INIT sysConsole0Init =
{
    .deviceInitData = (const void*)&sysConsole0USBCdcInitData,
    .consDevDesc = &sysConsoleUSBCdcDevDesc,
    .deviceIndex = 0,
};


// </editor-fold>




// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************

/* MISRAC 2012 deviation block end */

/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{

    /* MISRAC 2012 deviation block start */
    /* MISRA C-2012 Rule 2.2 deviated in this file.  Deviation record ID -  H3_MISRAC_2012_R_2_2_DR_1 */

    /* Start out with interrupts disabled before configuring any modules */
    (void)__builtin_disable_interrupts();

  
    CLK_Initialize();
    /* Configure Prefetch, Wait States and ECC */
    PRECONbits.PREFEN = 3;
    PRECONbits.PFMWS = 2;
    CFGCONbits.ECCCON = 3;



	GPIO_Initialize();

    CORETIMER_Initialize();
	BSP_Initialize();


    /* MISRAC 2012 deviation block start */
    /* Following MISRA-C rules deviated in this block  */
    /* MISRA C-2012 Rule 11.3 - Deviation record ID - H3_MISRAC_2012_R_11_3_DR_1 */
    /* MISRA C-2012 Rule 11.8 - Deviation record ID - H3_MISRAC_2012_R_11_8_DR_1 */


    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
     H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        sysObj.sysConsole1 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_1, (SYS_MODULE_INIT *)&sysConsole1Init);
   /* MISRAC 2012 deviation block end */
    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
    H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        
    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);
    
    /* MISRAC 2012 deviation block end */
    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
     H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        
    sysObj.sysDebug = SYS_DEBUG_Initialize(SYS_DEBUG_INDEX_0, (SYS_MODULE_INIT*)&debugInit);

    /* MISRAC 2012 deviation block end */
    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
     H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        sysObj.sysConsole0 = SYS_CONSOLE_Initialize(SYS_CONSOLE_INDEX_0, (SYS_MODULE_INIT *)&sysConsole0Init);
   /* MISRAC 2012 deviation block end */


    /* Initialize the USB device layer */
    sysObj.usbDevObject0 = USB_DEVICE_Initialize (USB_DEVICE_INDEX_0 , ( SYS_MODULE_INIT* ) & usbDevInitData);


	/* Initialize USB Driver */ 
    sysObj.drvUSBHSObject = DRV_USBHS_Initialize(DRV_USBHS_INDEX_0, (SYS_MODULE_INIT *) &drvUSBInit);	


    /* MISRAC 2012 deviation block end */
    APP_Initialize();


    EVIC_Initialize();

	/* Enable global interrupts */
    (void)__builtin_enable_interrupts();



    /* MISRAC 2012 deviation block end */
}

/*******************************************************************************
 End of File
*/
