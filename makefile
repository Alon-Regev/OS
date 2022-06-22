ASSEMBLY_FILES = boot.asm boot_helper.asm
MAIN_ASSEMBLY = boot.asm
BOOT_NAME = boot.bin

ASSEMBLER = nasm
ASSEMBLER_FLAGS = -f bin

EMULATOR = qemu-system-x86_64
EMULATOR_FLAGS = -drive format=raw,file=$(BOOT_NAME)


$(BOOT_NAME): $(ASSEMBLY_FILES)
	@$(ASSEMBLER) $(ASSEMBLER_FLAGS) $(MAIN_ASSEMBLY) -o $(BOOT_NAME)

run: $(BOOT_NAME)
	@$(EMULATOR) $(EMULATOR_FLAGS)
