// taken from LLVM
#pragma once

#include <inttypes.h>

typedef uint32_t Elf32_Addr; // Program address
typedef uint32_t Elf32_Off;  // File offset
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;
typedef int32_t  Elf32_Sword;

// e_ident size and indices.
enum {
  EI_MAG0       = 0,          // File identification index.
  EI_MAG1       = 1,          // File identification index.
  EI_MAG2       = 2,          // File identification index.
  EI_MAG3       = 3,          // File identification index.
  EI_CLASS      = 4,          // File class.
  EI_DATA       = 5,          // Data encoding.
  EI_VERSION    = 6,          // File version.
  EI_OSABI      = 7,          // OS/ABI identification.
  EI_ABIVERSION = 8,          // ABI version.
  EI_PAD        = 9,          // Start of padding bytes.
  EI_NIDENT     = 16          // Number of bytes in e_ident.
};

struct Elf32_Ehdr {
  unsigned char e_ident[EI_NIDENT]; // ELF Identification bytes
  Elf32_Half    e_type;      // Type of file (see ET_* below)
  Elf32_Half    e_machine;   // Required architecture for this file (see EM_*)
  Elf32_Word    e_version;   // Must be equal to 1
  Elf32_Addr    e_entry;     // Address to jump to in order to start program
  Elf32_Off     e_phoff;     // Program header table's file offset, in bytes
  Elf32_Off     e_shoff;     // Section header table's file offset, in bytes
  Elf32_Word    e_flags;     // Processor-specific flags
  Elf32_Half    e_ehsize;    // Size of ELF header, in bytes
  Elf32_Half    e_phentsize; // Size of an entry in the program header table
  Elf32_Half    e_phnum;     // Number of entries in the program header table
  Elf32_Half    e_shentsize; // Size of an entry in the section header table
  Elf32_Half    e_shnum;     // Number of entries in the section header table
  Elf32_Half    e_shstrndx;  // Sect hdr table index of sect name string table
};

// File types
enum {
  ET_NONE   = 0,      // No file type
  ET_REL    = 1,      // Relocatable file
  ET_EXEC   = 2,      // Executable file
  ET_DYN    = 3,      // Shared object file
  ET_CORE   = 4,      // Core file
  ET_LOPROC = 0xff00, // Beginning of processor-specific codes
  ET_HIPROC = 0xffff  // Processor-specific
};

// Versioning
enum {
  EV_NONE = 0,
  EV_CURRENT = 1
};

// Machine architectures
// See current registered ELF machine architectures at:
//    http://www.uxsglobal.com/developers/gabi/latest/ch4.eheader.html
enum {
  EM_ARM           = 40, // ARM
};

// ELF Relocation types for ARM
// Meets 2.08 ABI Specs.

enum {
  R_ARM_NONE                  = 0x00,
  R_ARM_PC24                  = 0x01,
  R_ARM_ABS32                 = 0x02,
  R_ARM_REL32                 = 0x03,
  R_ARM_LDR_PC_G0             = 0x04,
  R_ARM_ABS16                 = 0x05,
  R_ARM_ABS12                 = 0x06,
  R_ARM_THM_ABS5              = 0x07,
  R_ARM_ABS8                  = 0x08,
  R_ARM_SBREL32               = 0x09,
  R_ARM_THM_CALL              = 0x0a,
  R_ARM_THM_PC8               = 0x0b,
  R_ARM_BREL_ADJ              = 0x0c,
  R_ARM_TLS_DESC              = 0x0d,
  R_ARM_THM_SWI8              = 0x0e,
  R_ARM_XPC25                 = 0x0f,
  R_ARM_THM_XPC22             = 0x10,
  R_ARM_TLS_DTPMOD32          = 0x11,
  R_ARM_TLS_DTPOFF32          = 0x12,
  R_ARM_TLS_TPOFF32           = 0x13,
  R_ARM_COPY                  = 0x14,
  R_ARM_GLOB_DAT              = 0x15,
  R_ARM_JUMP_SLOT             = 0x16,
  R_ARM_RELATIVE              = 0x17,
  R_ARM_GOTOFF32              = 0x18,
  R_ARM_BASE_PREL             = 0x19,
  R_ARM_GOT_BREL              = 0x1a,
  R_ARM_PLT32                 = 0x1b,
  R_ARM_CALL                  = 0x1c,
  R_ARM_JUMP24                = 0x1d,
  R_ARM_THM_JUMP24            = 0x1e,
  R_ARM_BASE_ABS              = 0x1f,
  R_ARM_ALU_PCREL_7_0         = 0x20,
  R_ARM_ALU_PCREL_15_8        = 0x21,
  R_ARM_ALU_PCREL_23_15       = 0x22,
  R_ARM_LDR_SBREL_11_0_NC     = 0x23,
  R_ARM_ALU_SBREL_19_12_NC    = 0x24,
  R_ARM_ALU_SBREL_27_20_CK    = 0x25,
  R_ARM_TARGET1               = 0x26,
  R_ARM_SBREL31               = 0x27,
  R_ARM_V4BX                  = 0x28,
  R_ARM_TARGET2               = 0x29,
  R_ARM_PREL31                = 0x2a,
  R_ARM_MOVW_ABS_NC           = 0x2b,
  R_ARM_MOVT_ABS              = 0x2c,
  R_ARM_MOVW_PREL_NC          = 0x2d,
  R_ARM_MOVT_PREL             = 0x2e,
  R_ARM_THM_MOVW_ABS_NC       = 0x2f,
  R_ARM_THM_MOVT_ABS          = 0x30,
  R_ARM_THM_MOVW_PREL_NC      = 0x31,
  R_ARM_THM_MOVT_PREL         = 0x32,
  R_ARM_THM_JUMP19            = 0x33,
  R_ARM_THM_JUMP6             = 0x34,
  R_ARM_THM_ALU_PREL_11_0     = 0x35,
  R_ARM_THM_PC12              = 0x36,
  R_ARM_ABS32_NOI             = 0x37,
  R_ARM_REL32_NOI             = 0x38,
  R_ARM_ALU_PC_G0_NC          = 0x39,
  R_ARM_ALU_PC_G0             = 0x3a,
  R_ARM_ALU_PC_G1_NC          = 0x3b,
  R_ARM_ALU_PC_G1             = 0x3c,
  R_ARM_ALU_PC_G2             = 0x3d,
  R_ARM_LDR_PC_G1             = 0x3e,
  R_ARM_LDR_PC_G2             = 0x3f,
  R_ARM_LDRS_PC_G0            = 0x40,
  R_ARM_LDRS_PC_G1            = 0x41,
  R_ARM_LDRS_PC_G2            = 0x42,
  R_ARM_LDC_PC_G0             = 0x43,
  R_ARM_LDC_PC_G1             = 0x44,
  R_ARM_LDC_PC_G2             = 0x45,
  R_ARM_ALU_SB_G0_NC          = 0x46,
  R_ARM_ALU_SB_G0             = 0x47,
  R_ARM_ALU_SB_G1_NC          = 0x48,
  R_ARM_ALU_SB_G1             = 0x49,
  R_ARM_ALU_SB_G2             = 0x4a,
  R_ARM_LDR_SB_G0             = 0x4b,
  R_ARM_LDR_SB_G1             = 0x4c,
  R_ARM_LDR_SB_G2             = 0x4d,
  R_ARM_LDRS_SB_G0            = 0x4e,
  R_ARM_LDRS_SB_G1            = 0x4f,
  R_ARM_LDRS_SB_G2            = 0x50,
  R_ARM_LDC_SB_G0             = 0x51,
  R_ARM_LDC_SB_G1             = 0x52,
  R_ARM_LDC_SB_G2             = 0x53,
  R_ARM_MOVW_BREL_NC          = 0x54,
  R_ARM_MOVT_BREL             = 0x55,
  R_ARM_MOVW_BREL             = 0x56,
  R_ARM_THM_MOVW_BREL_NC      = 0x57,
  R_ARM_THM_MOVT_BREL         = 0x58,
  R_ARM_THM_MOVW_BREL         = 0x59,
  R_ARM_TLS_GOTDESC           = 0x5a,
  R_ARM_TLS_CALL              = 0x5b,
  R_ARM_TLS_DESCSEQ           = 0x5c,
  R_ARM_THM_TLS_CALL          = 0x5d,
  R_ARM_PLT32_ABS             = 0x5e,
  R_ARM_GOT_ABS               = 0x5f,
  R_ARM_GOT_PREL              = 0x60,
  R_ARM_GOT_BREL12            = 0x61,
  R_ARM_GOTOFF12              = 0x62,
  R_ARM_GOTRELAX              = 0x63,
  R_ARM_GNU_VTENTRY           = 0x64,
  R_ARM_GNU_VTINHERIT         = 0x65,
  R_ARM_THM_JUMP11            = 0x66,
  R_ARM_THM_JUMP8             = 0x67,
  R_ARM_TLS_GD32              = 0x68,
  R_ARM_TLS_LDM32             = 0x69,
  R_ARM_TLS_LDO32             = 0x6a,
  R_ARM_TLS_IE32              = 0x6b,
  R_ARM_TLS_LE32              = 0x6c,
  R_ARM_TLS_LDO12             = 0x6d,
  R_ARM_TLS_LE12              = 0x6e,
  R_ARM_TLS_IE12GP            = 0x6f,
  R_ARM_PRIVATE_0             = 0x70,
  R_ARM_PRIVATE_1             = 0x71,
  R_ARM_PRIVATE_2             = 0x72,
  R_ARM_PRIVATE_3             = 0x73,
  R_ARM_PRIVATE_4             = 0x74,
  R_ARM_PRIVATE_5             = 0x75,
  R_ARM_PRIVATE_6             = 0x76,
  R_ARM_PRIVATE_7             = 0x77,
  R_ARM_PRIVATE_8             = 0x78,
  R_ARM_PRIVATE_9             = 0x79,
  R_ARM_PRIVATE_10            = 0x7a,
  R_ARM_PRIVATE_11            = 0x7b,
  R_ARM_PRIVATE_12            = 0x7c,
  R_ARM_PRIVATE_13            = 0x7d,
  R_ARM_PRIVATE_14            = 0x7e,
  R_ARM_PRIVATE_15            = 0x7f,
  R_ARM_ME_TOO                = 0x80,
  R_ARM_THM_TLS_DESCSEQ16     = 0x81,
  R_ARM_THM_TLS_DESCSEQ32     = 0x82
};

// Section header.
struct Elf32_Shdr {
  Elf32_Word sh_name;      // Section name (index into string table)
  Elf32_Word sh_type;      // Section type (SHT_*)
  Elf32_Word sh_flags;     // Section flags (SHF_*)
  Elf32_Addr sh_addr;      // Address where section is to be loaded
  Elf32_Off  sh_offset;    // File offset of section data, in bytes
  Elf32_Word sh_size;      // Size of section, in bytes
  Elf32_Word sh_link;      // Section type-specific header table index link
  Elf32_Word sh_info;      // Section type-specific extra information
  Elf32_Word sh_addralign; // Section address alignment
  Elf32_Word sh_entsize;   // Size of records contained within the section
};

// Section types.
enum : unsigned {
  SHT_NULL          = 0,  // No associated section (inactive entry).
  SHT_PROGBITS      = 1,  // Program-defined contents.
  SHT_SYMTAB        = 2,  // Symbol table.
  SHT_STRTAB        = 3,  // String table.
  SHT_RELA          = 4,  // Relocation entries; explicit addends.
  SHT_HASH          = 5,  // Symbol hash table.
  SHT_DYNAMIC       = 6,  // Information for dynamic linking.
  SHT_NOTE          = 7,  // Information about the file.
  SHT_NOBITS        = 8,  // Data occupies no space in the file.
  SHT_REL           = 9,  // Relocation entries; no explicit addends.
  SHT_SHLIB         = 10, // Reserved.
  SHT_DYNSYM        = 11, // Symbol table.
  SHT_INIT_ARRAY    = 14, // Pointers to initialization functions.
  SHT_FINI_ARRAY    = 15, // Pointers to termination functions.
  SHT_PREINIT_ARRAY = 16, // Pointers to pre-init functions.
  SHT_GROUP         = 17, // Section group.
  SHT_SYMTAB_SHNDX  = 18, // Indices for SHN_XINDEX entries.
  SHT_LOOS          = 0x60000000, // Lowest operating system-specific type.
  SHT_GNU_ATTRIBUTES= 0x6ffffff5, // Object attributes.
  SHT_GNU_HASH      = 0x6ffffff6, // GNU-style hash table.
  SHT_GNU_verdef    = 0x6ffffffd, // GNU version definitions.
  SHT_GNU_verneed   = 0x6ffffffe, // GNU version references.
  SHT_GNU_versym    = 0x6fffffff, // GNU symbol versions table.
  SHT_HIOS          = 0x6fffffff, // Highest operating system-specific type.
  SHT_LOPROC        = 0x70000000, // Lowest processor arch-specific type.
  // Fixme: All this is duplicated in MCSectionELF. Why??
  // Exception Index table
  SHT_ARM_EXIDX           = 0x70000001U,
  // BPABI DLL dynamic linking pre-emption map
  SHT_ARM_PREEMPTMAP      = 0x70000002U,
  //  Object file compatibility attributes
  SHT_ARM_ATTRIBUTES      = 0x70000003U,
  SHT_ARM_DEBUGOVERLAY    = 0x70000004U,
  SHT_ARM_OVERLAYSECTION  = 0x70000005U,
  SHT_HEX_ORDERED         = 0x70000000, // Link editor is to sort the entries in
                                        // this section based on their sizes
  SHT_X86_64_UNWIND       = 0x70000001, // Unwind information

  SHT_MIPS_REGINFO        = 0x70000006, // Register usage information
  SHT_MIPS_OPTIONS        = 0x7000000d, // General options
  SHT_MIPS_ABIFLAGS       = 0x7000002a, // ABI information.

  SHT_HIPROC        = 0x7fffffff, // Highest processor arch-specific type.
  SHT_LOUSER        = 0x80000000, // Lowest type reserved for applications.
  SHT_HIUSER        = 0xffffffff  // Highest type reserved for applications.
};

// Section flags.
enum : unsigned {
  // Section data should be writable during execution.
  SHF_WRITE = 0x1,

  // Section occupies memory during program execution.
  SHF_ALLOC = 0x2,

  // Section contains executable machine instructions.
  SHF_EXECINSTR = 0x4,

  // The data in this section may be merged.
  SHF_MERGE = 0x10,

  // The data in this section is null-terminated strings.
  SHF_STRINGS = 0x20,

  // A field in this section holds a section header table index.
  SHF_INFO_LINK = 0x40U,

  // Adds special ordering requirements for link editors.
  SHF_LINK_ORDER = 0x80U,

  // This section requires special OS-specific processing to avoid incorrect
  // behavior.
  SHF_OS_NONCONFORMING = 0x100U,

  // This section is a member of a section group.
  SHF_GROUP = 0x200U,

  // This section holds Thread-Local Storage.
  SHF_TLS = 0x400U,

  // This section is excluded from the final executable or shared library.
  SHF_EXCLUDE = 0x80000000U,

  // Start of target-specific flags.

  /// XCORE_SHF_CP_SECTION - All sections with the "c" flag are grouped
  /// together by the linker to form the constant pool and the cp register is
  /// set to the start of the constant pool by the boot code.
  XCORE_SHF_CP_SECTION = 0x800U,

  /// XCORE_SHF_DP_SECTION - All sections with the "d" flag are grouped
  /// together by the linker to form the data section and the dp register is
  /// set to the start of the section by the boot code.
  XCORE_SHF_DP_SECTION = 0x1000U,

  SHF_MASKOS   = 0x0ff00000,

  // Bits indicating processor-specific flags.
  SHF_MASKPROC = 0xf0000000,

  // If an object file section does not have this flag set, then it may not hold
  // more than 2GB and can be freely referred to in objects using smaller code
  // models. Otherwise, only objects using larger code models can refer to them.
  // For example, a medium code model object can refer to data in a section that
  // sets this flag besides being able to refer to data in a section that does
  // not set it; likewise, a small code model object can refer only to code in a
  // section that does not set this flag.
  SHF_X86_64_LARGE = 0x10000000,

  // All sections with the GPREL flag are grouped into a global data area
  // for faster accesses
  SHF_HEX_GPREL = 0x10000000,

  // Section contains text/data which may be replicated in other sections.
  // Linker must retain only one copy.
  SHF_MIPS_NODUPES = 0x01000000,

  // Linker must generate implicit hidden weak names.
  SHF_MIPS_NAMES   = 0x02000000,

  // Section data local to process.
  SHF_MIPS_LOCAL   = 0x04000000,

  // Do not strip this section.
  SHF_MIPS_NOSTRIP = 0x08000000,

  // Section must be part of global data area.
  SHF_MIPS_GPREL   = 0x10000000,

  // This section should be merged.
  SHF_MIPS_MERGE   = 0x20000000,

  // Address size to be inferred from section entry size.
  SHF_MIPS_ADDR    = 0x40000000,

  // Section data is string data by default.
  SHF_MIPS_STRING  = 0x80000000
};


// Symbol table entries for ELF32.
struct Elf32_Sym {
  Elf32_Word    st_name;  // Symbol name (index into string table)
  Elf32_Addr    st_value; // Value or address associated with the symbol
  Elf32_Word    st_size;  // Size of the symbol
  unsigned char st_info;  // Symbol's type and binding attributes
  unsigned char st_other; // Must be zero; reserved
  Elf32_Half    st_shndx; // Which section (header table index) it's defined in

  // These accessors and mutators correspond to the ELF32_ST_BIND,
  // ELF32_ST_TYPE, and ELF32_ST_INFO macros defined in the ELF specification:
  unsigned char getBinding() const { return st_info >> 4; }
  unsigned char getType() const { return st_info & 0x0f; }
  void setBinding(unsigned char b) { setBindingAndType(b, getType()); }
  void setType(unsigned char t) { setBindingAndType(getBinding(), t); }
  void setBindingAndType(unsigned char b, unsigned char t) {
    st_info = (b << 4) + (t & 0x0f);
  }
};

// Symbol bindings.
enum {
  STB_LOCAL = 0,   // Local symbol, not visible outside obj file containing def
  STB_GLOBAL = 1,  // Global symbol, visible to all object files being combined
  STB_WEAK = 2,    // Weak symbol, like global but lower-precedence
  STB_LOOS   = 10, // Lowest operating system-specific binding type
  STB_HIOS   = 12, // Highest operating system-specific binding type
  STB_LOPROC = 13, // Lowest processor-specific binding type
  STB_HIPROC = 15  // Highest processor-specific binding type
};

// Symbol types.
enum {
  STT_NOTYPE  = 0,   // Symbol's type is not specified
  STT_OBJECT  = 1,   // Symbol is a data object (variable, array, etc.)
  STT_FUNC    = 2,   // Symbol is executable code (function, etc.)
  STT_SECTION = 3,   // Symbol refers to a section
  STT_FILE    = 4,   // Local, absolute symbol that refers to a file
  STT_COMMON  = 5,   // An uninitialized common block
  STT_TLS     = 6,   // Thread local data object
  STT_LOOS    = 7,   // Lowest operating system-specific symbol type
  STT_HIOS    = 8,   // Highest operating system-specific symbol type
  STT_GNU_IFUNC = 10, // GNU indirect function
  STT_LOPROC  = 13,  // Lowest processor-specific symbol type
  STT_HIPROC  = 15   // Highest processor-specific symbol type
};

// Symbol number.
enum {
  STN_UNDEF = 0
};

// Program header for ELF32.
struct Elf32_Phdr {
  Elf32_Word p_type;   // Type of segment
  Elf32_Off  p_offset; // File offset where segment is located, in bytes
  Elf32_Addr p_vaddr;  // Virtual address of beginning of segment
  Elf32_Addr p_paddr;  // Physical address of beginning of segment (OS-specific)
  Elf32_Word p_filesz; // Num. of bytes in file image of segment (may be zero)
  Elf32_Word p_memsz;  // Num. of bytes in mem image of segment (may be zero)
  Elf32_Word p_flags;  // Segment flags
  Elf32_Word p_align;  // Segment alignment constraint
};
