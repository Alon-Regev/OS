BOOT_DIR := boot
BOOT_MAIN := $(BOOT_DIR)/boot.asm

KERNEL_DIR := kernel
KERNEL_MAIN := $(KERNEL_DIR)/kernel.c

DRIVERS_DIR := drivers
HELPERS_DIR := helpers


# --- KERNEL
kernel_entry.o: kernel/kernel_entry.asm
	@nasm $< -f elf -o $@

KERNEL_SOURCES := $(wildcard $(KERNEL_DIR)/*.c $(DRIVERS_DIR)/*.c $(HELPERS_DIR)/*.c)
KERNEL_ASM := $(wildcard $(KERNEL_DIR)/*.asm)
KERNEL_HEADERS := $(wildcard $(KERNEL_DIR)/*.h $(DRIVERS_DIR)/*.h $(HELPERS_DIR)/*.h)
KERNEL_OBJECTS := $(KERNEL_SOURCES:.c=.o) $(KERNEL_ASM:.asm=.o)

%.o: %.c $(KERNEL_HEADERS)
	@gcc -g -m32 -nostdlib -ffreestanding -c $< -o $@ -fno-pic

%.o: %.asm
	@nasm $< -f elf -o $@

kernel.bin: kernel_entry.o $(KERNEL_OBJECTS)
	@ld -m elf_i386 -o $@ -Ttext=0x1000 $^ --oformat binary --entry 0
# align to sectors (multiples of 512 bytes)	
	@s0=`stat -c "%s" kernel.bin`;\
	s1=$$(((s0+511)/512*512));\
	head -c$$((s1 - s0)) /dev/zero >> kernel.bin;\
	echo kernel is $$((s1 / 512)) sectors

kernel.elf: kernel_entry.o $(KERNEL_OBJECTS)
	@ld -m elf_i386 -o $@ -Ttext=0x1000 $^ --entry 0

# --- BOOT
BOOT_ASM_FILES := $(shell find $(BOOT_DIR) -name "*.asm")
boot_sector.bin: $(BOOT_ASM_FILES)
	@nasm -f elf $(BOOT_MAIN) -f bin -o $@


# --- OS-IMAGE
os_image.bin: boot_sector.bin kernel.bin
	@cat $^ > $@


# --- COMMANDS
run: os_image.bin
	-@qemu-system-x86_64 -fda os_image.bin 2>/dev/null

clean: 
	-@find . -type f -name '*.o' -delete
	-@find . -type f -name '*.bin' -delete
	-@find . -type f -name '*.elf' -delete

debug: os_image.bin kernel.elf
	-@qemu-system-i386 -s -S -fda os_image.bin &
	-@gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"
