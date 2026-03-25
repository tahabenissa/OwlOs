all:
	nasm -f elf32 boot/multiboot.asm -o multiboot.o
	nasm -f elf32 boot/boot.asm -o boot.o
	nasm -f elf32 kernel/gdt.asm -o gdt_asm.o
	nasm -f elf32 kernel/idt.asm -o idt_asm.o
	i686-elf-gcc -c kernel/gdt.c -o gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/idt.c -o idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c kernel/print.c -o print.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib multiboot.o boot.o kernel.o print.o gdt.o idt.o gdt_asm.o idt_asm.o -lgcc
	cp kernel.bin isodir/boot/kernel.bin
	grub-mkrescue -o OwlOs.iso isodir

run: all
	qemu-system-i386 -cdrom OwlOs.iso
run-kernel: all
	qemu-system-i386 -kernel kernel.bin
