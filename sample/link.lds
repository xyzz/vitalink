OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(module_start)

SECTIONS
{
	. = 0x81000000;
	.text : { *(.text) }
	
	. = ALIGN(0x10);
	.sceModuleInfo.rodata : { *(.sceModuleInfo.rodata) }
	.sceLib.ent : { *(.sceLib.ent) }
	.sceLib.stub : { *(.sceLib.stub) }
	.sceExport.rodata : { *(.sceExport.rodata) }
	.sceImport.rodata : { *(.sceImport.rodata) }
	.sceFNID.rodata : { *(.sceFNID.rodata) }
	.sceFStub.rodata : { *(.sceFStub.rodata) }

	.rodata : { *(.rodata) }

	. = ALIGN(0x10000);
	.data : { *(.data) }
	.bss : { *(.bss) *(COMMON) }
}
