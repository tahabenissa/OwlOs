#include "gdt.h"

gdt_entry_t gdt[3];
gdt_ptr_t gdtp;

extern void gdt_load(uint32_t);

void gdt_set_entry(int num, uint32_t base, uint32_t limit,
                   uint8_t access, uint8_t gran) {

    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}

void gdt_init() {

    gdtp.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdtp.base  = (uint32_t)&gdt;

    // NULL descriptor
    gdt_set_entry(0, 0, 0, 0, 0);

    // Code segment
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Data segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_load((uint32_t)&gdtp);
}
