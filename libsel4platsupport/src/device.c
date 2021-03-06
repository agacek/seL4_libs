/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */
#include <autoconf.h>
#include <sel4platsupport/device.h>
#include <sel4platsupport/platsupport.h>
#include <stddef.h>
#include <vka/capops.h>
#include <utils/util.h>

seL4_Error
sel4platsupport_copy_irq_cap(vka_t *vka, simple_t *simple, seL4_Word irq_number, cspacepath_t *dest)
{
    seL4_CPtr irq;

    /* allocate a cslot for the irq cap */
    int error = vka_cspace_alloc(vka, &irq);
    if (error != 0) {
        ZF_LOGE("Failed to allocate cslot for irq");
        return error;
    }

    vka_cspace_make_path(vka, irq, dest);

    error = simple_get_IRQ_handler(simple, irq_number, *dest);
    if  (error != seL4_NoError) {
        ZF_LOGE("Failed to get cap to irq_number %zu", irq_number);
        vka_cspace_free(vka, irq);
        return error;
    }

    return seL4_NoError;
}

seL4_Error
sel4platsupport_alloc_frame_at(vka_t *vka, uintptr_t paddr, size_t size_bits, vka_object_t *frame)
{
    /* find the physical frame */
    int error = vka_alloc_frame_at(vka, size_bits, paddr, frame);
    if (error) {
        ZF_LOGE("Failed to find frame at paddr %p", (void*)paddr);
    }

    return error;
}

void *
sel4platsupport_map_frame_at(vka_t *vka, vspace_t *vspace, uintptr_t paddr, size_t size_bits, vka_object_t *frame)
{
    int error;
    error = sel4platsupport_alloc_frame_at(vka, paddr, size_bits, frame);
    if (error) {
        return NULL;
    }
    void *vaddr = vspace_map_pages(vspace, &frame->cptr, &frame->ut, seL4_AllRights, 1, size_bits, 0);
    if (!vaddr) {
        ZF_LOGE("Failed to map frame at paddr %p", (void*)paddr);
        vka_free_object(vka, frame);
    }
    return vaddr;
}
