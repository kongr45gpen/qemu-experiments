#include "device.h"
#include "interrupts.h"
#include "peripheral/mcan/plib_mcan_common.h"
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