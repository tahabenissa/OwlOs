void print (const char* str);
void kernel_main() {
    print("hello to my owlos");

    while (1) {
        __asm__ __volatile__("hlt");
    }
}
