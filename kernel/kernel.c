#include "print.h"
#include "gdt.h"
#include "idt.h"
void kernel_main() {
    idt_init();
    gdt_init();
    print("hello to my owlos");
    

    while (1) {
        __asm__ __volatile__("hlt");
    }
}
