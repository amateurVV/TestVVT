NASM = nasm
GCC = gcc

VDISK = E:/GitVMX/UEVM/vdisk.vhd

VMWARE = "D:/VMware/vmrun.exe"
VMWARE_FLAGS = start "E:/VM/Win10x64.vmx" 

VBOX = "D:/VirtualBox/VBoxManage.exe"
VBOX_FLAGS = startvm TestVT --type gui

STD = std/
UEVM = uevm/
VMX = vmx/
DISASM = ../disasm/

ENTRY = -e UefiMain 

CFLAGS += -nostdinc 
CFLAGS += -nostdlib
#CFLAGS += -fno-builtin 

#关闭这个就没有符号
CFLAGS += -shared

CFLAGS += -m64

CFLAGS += -s

UEFI_DRV = -Wl,--subsystem=12
UEFI_APP = -Wl,--subsystem=10

# DEBUG += -DDEBUG
# DEBUG += -DVMWARE


INCLUDE += -I E:/GitVMX/UEVM/uefi/ 
INCLUDE += -I E:/GitVMX/UEVM/uefi/Guid/ 
INCLUDE += -I E:/GitVMX/UEVM/uefi/IndustryStandard/ 
INCLUDE += -I E:/GitVMX/UEVM/uefi/Pi/ 
INCLUDE += -I E:/GitVMX/UEVM/uefi/Protocol/ 
INCLUDE += -I E:/GitVMX/UEVM/uefi/Uefi/ 
INCLUDE += -I E:/GitVMX/UEVM/uefi/X64/ 
INCLUDE += -I E:/GitVMX/UEVM/uefi/Util/  

INCLUDE += -I D:/SuperVT/std/ 
INCLUDE += -I D:/SuperVT/uevm/ 
INCLUDE += -I D:/SuperVT/vmx/ 
INCLUDE += -I D:/SuperVT/winpe/ 
INCLUDE += -I D:/SuperVT/disasm/ 

nothing:
	make clean2

efi: vmx.lib Bootx64.efi
	make LoaderEFI
	make clean2

drv:vmx.lib Bootx64.efi
	make LoaderDRV
	make clean2

Bootx64.efi:bootx64.o std.o util.o
	@$(GCC) $(ENTRY) $(CFLAGS) $(DEBUG) $(UEFI_APP) $(INCLUDE) $^ -o $@ 

LoaderDRV:loaderDRV.o std.o util.o pe64.o hook.o first.o ept.o intel.o
	@$(GCC) $(ENTRY) $(CFLAGS) $(DEBUG) $(UEFI_DRV) $(INCLUDE) $^ -o Loader.efi -L./ -lvmx

LoaderEFI:loaderEFI.o std.o util.o pe64.o hook.o first.o ept.o intel.o
	@$(GCC) $(ENTRY) $(CFLAGS) $(DEBUG) $(UEFI_DRV) $(INCLUDE) $^ -o Loader.efi -L./ -lvmx

vmx.lib:std.o vmx.o intel.o pe64.o vasm.o handler.o vmcall.o debug.o winsys.o file.o disasm.o syscall64.o winfunc.o winasm.o vad.o ept.o 
	@ar cr $@ $^


%.o:$(STD)%.c 
	@$(GCC)  $(INCLUDE) $(CFLAGS) $(DEBUG) -c $< -o $@ 
%.o:$(STD)%.asm 
	@$(NASM) $(DEBUG) -f win64 $< -o $@ 

%.o:$(UEVM)%.c 
	@$(GCC)  $(INCLUDE) $(CFLAGS) $(DEBUG) -c $< -o $@ 
%.o:$(UEVM)%.asm 
	@$(NASM) $(DEBUG) -f win64 $< -o $@ 

%.o:$(VMX)%.asm 
	@$(NASM) $(DEBUG) -f win64 $< -o $@ 
%.o:$(VMX)%.c 
	@$(GCC) $(INCLUDE) $(CFLAGS) $(DEBUG) -c $< -o $@ 

pe64.o:winpe/pe64.c 
	@$(GCC) $(INCLUDE) $(DEBUG) -c $< -o $@ 


disasm.o:disasm/disasm.c
	@$(GCC) $(INCLUDE) -c $^ -o $@


dd.exe:win/dd.c
	@$(GCC) $(DEBUG) -m64 $< -o $@ 

copy.exe:winexe/copy.c
	@$(GCC) $(DEBUG) -m64 $< -o $@ 


Service.o:winexe/Service.asm
	@$(NASM) $(DEBUG) -f win64 $< -o $@ 

TestR3.exe:winexe/TestR3.c Service.o
	@$(GCC) $(DEBUG) -m64 $^ -o $@ 


copy:copy.exe Bootx64.efi Loader.efi TestR3.exe
	cmd /c"copy.exe"	



vbox:
	make efi copy
	$(VBOX) $(VBOX_FLAGS) 
	make clean2

vmwe:
	make efi copy
	@echo bios.forceSetupOnce = "TRUE">>"E:/VM/Win10x64.vmx" 
	$(VMWARE) $(VMWARE_FLAGS) 
	make clean2

vmwd:
	make drv copy
	@echo bios.forceSetupOnce = "TRUE">>"E:/VM/Win10x64.vmx" 
	$(VMWARE) $(VMWARE_FLAGS) 
	make clean2


clean:
	@del *.o *.efi *.exe *.lib

clean2:
	@del *.o 

