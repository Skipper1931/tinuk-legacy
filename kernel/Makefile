DEFAULT_HOST!=../toolchain/default-host.sh
HOST?=$(DEFAULT_HOST)
HOSTARCH!=../toolchain/target-triplet-to-arch.sh $(HOST)
 
CFLAGS?=-O2 -g 
CPPFLAGS?=
LDFLAGS?=
LIBS?=
 
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
 
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -mno-red-zone
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc
 
ARCHDIR=arch/$(HOSTARCH)
 
include $(ARCHDIR)/make.config
 
CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)
 
KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
boot/kmain.o \
boot/multiboot.o \
kpanic.o \

OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \
$(LOADER_OBJS)
 
LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR)/crtn.o \
$(ARCHDIR)/crtbegin.o \
$(ARCHDIR)/crtend.o
 
.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .cpp .asm .c .asm32
 
all: karyon.kernel loader32.elf

karyon.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CXX) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) -v $(LINK_LIST) -z max-page-size=4096

loader32.elf: $(LOADER_OBJS) $(ARCHDIR)/bootstrap/linker.ld
	~/opt/cross32/bin/i686-elf-gcc -T $(ARCHDIR)/bootstrap/linker.ld -o $@ $(CFLAGS) -v $(LOADER_OBJS) \
	$(LDFLAGS) -nostdlib -lgcc -m32 -z max-page-size=4096
	
	# check that the final binary is multiboot-compliant
	grub-file --is-x86-multiboot $@
 
$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CXX) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@
 
.c.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) -m32 -I $(SYSROOT)/usr/include

.cpp.o:
	$(CXX) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.asm.o:
	nasm -f elf64 -g $< -o $@ -g

.asm32.o:
	nasm -f elf32 -g $< -o $@ -g
 
clean:
	rm -f karyon.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d
 
install: install-headers install-kernel
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)/kernel
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/kernel/.
 
install-kernel: karyon.kernel loader32.elf
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp karyon.kernel $(DESTDIR)$(BOOTDIR)
	cp loader32.elf $(DESTDIR)$(BOOTDIR)
 
-include $(OBJS:.o=.d)