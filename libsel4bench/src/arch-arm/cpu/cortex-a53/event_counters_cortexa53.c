/*
 * Copyright 2016, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include "../../event_counters.h"

#define NAME_EVENT(id, name) EVENT_COUNTER_FORMAT(SEL4BENCH_CORTEXA53_EVENT_##id, name)

const char* const sel4bench_cpu_event_counter_data[] = {
    NAME_EVENT(BUS_ACCESS_LD        , "Bus access, read"),
    NAME_EVENT(BUS_ACCESS_ST        , "Bus access, write"),
    NAME_EVENT(BR_INDIRECT_SPEC     , "Branch speculatively executed, indirect branch"),
    NAME_EVENT(EXC_IRQ              , "Exception taken, IRQ"),
    NAME_EVENT(EXC_FIQ              , "Exception taken, FIQ")
};

int
sel4bench_cpu_get_num_counters(void)
{
    return ARRAY_SIZE(sel4bench_cpu_event_counter_data);
}
