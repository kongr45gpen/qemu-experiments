// DOM-IGNORE-BEGIN
/*******************************************************************************
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
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

#include "definitions.h" /* for potential custom handler names */
// #include "samv71q21b.h"

/* Initialize segments */
extern uint32_t _sfixed;
extern uint32_t _etext;
extern uint32_t _ezero;
// extern uint32_t __vector_table;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t data_size;

extern void initialise_monitor_handles(void);

/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
/** \endcond */

void __libc_init_array(void);

/* Default empty handler */
void Dummy_Handler(void);

static inline void FPU_Enable(void)
{
    uint32_t prim;
    prim = __get_PRIMASK();
    __disable_irq();

    SCB->CPACR |= (0xFu << 20);
    __DSB();
    __ISB();

    if (!prim)
    {
        __enable_irq();
    }
}

/* These magic symbols are provided by the linker.  */
extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));
extern void _init(void);

void SystemInit(void)
{

    /* Set the vector table base address */
    uint32_t *pSrc = (uint32_t *)&_sfixed;
    SCB->VTOR = ((uint32_t)pSrc & SCB_VTOR_TBLOFF_Msk);

    /* Enable the floating point unit */
#if (__ARM_FP == 14) || (__ARM_FP == 4)
    FPU_Enable();
#endif

    /* Change default QOS values to have the best performance and correct USB behaviour */
    // SBMATRIX_REGS->HMATRIXB_SFR[4] = 2;
    // DMAC_REGS->DMAC_QOSCTRL = 0x2A;

    /* Overwriting the default value of the NVMCTRL.CTRLB.MANW bit (errata reference 13134) */
    // NVMCTRL_REGS->NVMCTRL_CTRLB |= 1 << 7;

    // Force exception
    // volatile uint32_t *pSrc2 = (uint32_t *)(0xDEADBEEF);
    // *pSrc2 = 0xDEADBEEF;

    // Enable trap on division by zero
    SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
    // volatile int toastinator = 5 / 1;

    // fuckery();

    /* Initialize the C library */
    __libc_init_array();

    initialise_monitor_handles();
    printf("  [QEMU] SystemInit\n");
    printf("  [QEMU] LibC init OK\n");
}
