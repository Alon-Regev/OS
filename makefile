kernel.bin: kernel_entry.o kernel.o
	@echo "linking"
	@ld -m elf_i386 -o $@ -Ttext=0x1000 $^ --oformat binary --entry 0
# align to sectors (multiples of 512 bytes)	
	@s0=`stat -c "%s" kernel.bin`;\
	s1=$$(((s0+511)/512*512));\
	head -c$$((s1 - s0)) /dev/zero >> kernel.bin;\
	echo kernel is $$((s1 / 512)) sectors

kernel_entry.o: kernel_entry.asm
	@nasm $< -f elf -o $@

kernel.o: kernel.c
	@echo "compiling something..."
	@gcc -m32 -ffreestanding -c $< -o $@ -fno-pic

boot_sector.bin: boot.asm boot_helper.asm boot_disk_helper.asm gdt.asm helper.asm protected_mode_switch.asm
	@nasm -f elf $< -f bin -o $@

os_image.bin: boot_sector.bin kernel.bin
	@cat $^ > $@

run: os_image.bin
	@qemu-system-x86_64 -drive format=raw,file=os_image.bin 2>/dev/null

clean: 
	@rm *.bin *.o
