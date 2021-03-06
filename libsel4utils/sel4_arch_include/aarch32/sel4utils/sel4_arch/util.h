/*
 * Copyright 2016, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(D61_BSD)
 */

#ifndef _SEL4UTILS_SEL4_ARCH_UTIL_H
#define _SEL4UTILS_SEL4_ARCH_UTIL_H

#include <sel4/sel4.h>

#define ARCH_SYSCALL_INSTRUCTION_SIZE 4

static inline int
sel4utils_is_read_fault(void)
{
    seL4_Word fsr = seL4_GetMR(seL4_VMFault_FSR);
#if defined(ARM_HYP)
    return (fsr & (1 << 6)) == 0;
#else
    return (fsr & (1 << 11)) == 0;
#endif
}


static inline void
sel4utils_set_instruction_pointer(seL4_UserContext *regs, seL4_Word value)
{
    regs->pc = value;
}

static inline seL4_Word
sel4utils_get_instruction_pointer(seL4_UserContext regs)
{
    return regs.pc;
}

static inline void
sel4utils_set_stack_pointer(seL4_UserContext *regs, seL4_Word value)
{
    regs->sp = value;
}

static inline void
sel4utils_set_arg0(seL4_UserContext *regs, seL4_Word value)
{
    regs->r0 = value;
}

static inline seL4_Word
sel4utils_get_sp(seL4_UserContext regs)
{
    return regs.sp;
}

#endif /* _SEL4UTILS_SEL4_ARCH_UTIL_H */
