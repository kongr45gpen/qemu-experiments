#include "device.h"
#include "interrupts.h"
#include "peripheral/mcan/plib_mcan_common.h"
#include "peripheral/afec/plib_afec0.h"
#include <stdint.h>
#include <stdbool.h>

void MCAN0_Initialize( void )
{
    // Do nothing
}

MCAN_ERROR MCAN0_ErrorGet(void)
{
    return 0;
}

bool MCAN0_MessageTransmitFifo(uint8_t numberOfMessage, MCAN_TX_BUFFER *txBuffer)
{
    return true;
}

void MCAN0_MessageRAMConfigSet(uint8_t *msgRAMConfigBaseAddress)
{
    // Do nothing        
}

void MCAN0_RxFifoCallbackRegister(MCAN_RX_FIFO_NUM rxFifoNum, MCAN_RX_FIFO_CALLBACK callback, uintptr_t contextHandle)
{
    // Do nothing
}

bool MCAN0_MessageReceiveFifo(MCAN_RX_FIFO_NUM rxFifoNum, uint8_t numberOfMessage, MCAN_RX_BUFFER *rxBuffer)
{
    return false;
}

void MCAN0_TxFifoCallbackRegister(MCAN_TX_FIFO_CALLBACK callback, uintptr_t contextHandle)
{
    // Do nothing
}

void MCAN1_Initialize( void )
{
    // Do nothing
}

MCAN_ERROR MCAN1_ErrorGet(void)
{
    return 0;
}

bool MCAN1_MessageTransmitFifo(uint8_t numberOfMessage, MCAN_TX_BUFFER *txBuffer)
{
    return true;
}

void MCAN1_MessageRAMConfigSet(uint8_t *msgRAMConfigBaseAddress)
{
    // Do nothing
}

void MCAN1_RxFifoCallbackRegister(MCAN_RX_FIFO_NUM rxFifoNum, MCAN_RX_FIFO_CALLBACK callback, uintptr_t contextHandle)
{
    // Do nothing
}

bool MCAN1_MessageReceiveFifo(MCAN_RX_FIFO_NUM rxFifoNum, uint8_t numberOfMessage, MCAN_RX_BUFFER *rxBuffer)
{
    return false;
}

void MCAN1_TxFifoCallbackRegister(MCAN_TX_FIFO_CALLBACK callback, uintptr_t contextHandle)
{
    // Do nothing
}

static AFEC_CALLBACK_OBJECT AFEC0_CallbackObj_Mock;

void AFEC0_Initialize()
{
}

uint16_t AFEC0_ChannelResultGet(AFEC_CHANNEL_NUM channel)
{
    // AFEC0_REGS->AFEC_CSELR = channel;
    // return (AFEC0_REGS->AFEC_CDR);
    return 12000;
}

void AFEC0_CallbackRegister(AFEC_CALLBACK callback, uintptr_t context)
{
    printf("callbackresgisterset %p!!!\n", callback);

    AFEC0_CallbackObj_Mock.callback_fn = callback;
    AFEC0_CallbackObj_Mock.context = context;
}

void AFEC0_ConversionStart(void)
{
    uint32_t status = 0;

    AFEC0_CallbackObj_Mock.callback_fn(status, AFEC0_CallbackObj_Mock.context);
}