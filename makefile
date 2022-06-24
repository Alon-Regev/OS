BOOT_DIR := boot
BOOT_MAIN := $(BOOT_DIR)/boot.asm

KERNEL_DIR := kernel
KERNEL_MAIN := $(KERNEL_DIR)/kernel.c


# --- KERNEL
kernel_entry.o: kernel/kernel_entry.asm
	@nasm $< -f elf -o $@

KERNEL_SRC_FILES := $(shell find $(KERNEL_DIR) -name "*.c")
kernel.o: $(KERNEL_SRC_FILES)
	@gcc -m32 -ffreestanding -c $< -o $@ -fno-pic

kernel.bin: kernel_entry.o kernel.o
	@ld -m elf_i386 -o $@ -Ttext=0x1000 $^ --oformat binary --entry 0
# align to sectors (multiples of 512 bytes)	
	@s0=`stat -c "%s" kernel.bin`;\
	s1=$$(((s0+511)/512*512));\
	head -c$$((s1 - s0)) /dev/zero >> kernel.bin;\
	echo kernel is $$((s1 / 512)) sectors


# --- BOOT
BOOT_ASM_FILES := $(shell find $(BOOT_DIR) -name "*.asm")
boot_sector.bin: $(BOOT_ASM_FILES)
	@nasm -f elf $(BOOT_MAIN) -f bin -o $@


# --- OS-IMAGE
os_image.bin: boot_sector.bin kernel.bin
	@cat $^ > $@


# --- COMMANDS
run: os_image.bin
	-@qemu-system-x86_64 -drive format=raw,file=os_image.bin 2>/dev/null

clean: 
	-@rm *.bin *.o
