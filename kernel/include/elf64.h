#ifndef _H_ELF64
#define _H_ELF64 1

// Taken semi-verbatim from https://www.uclibc.org/docs/elf-64-gen.pdf (Information and names from there but I wrote the structs and stuff myself)
// TODO: Maybe beautify this by indent-aligning everything

#include <stdint.h>

#define ELF64_R_SYM(i)		((i) >> 32)
#define ELF64_R_TYPE(i)		((i) & 0xffffffffL)
#define ELF64_R_INFO(s, t)	(((s) << 32) + ((t) & 0xffffffffL))

#define ELFCLASS32 1
#define ELFCLASS64 2

#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define ELFOSABI_SYSV 0
#define ELFOSABI_HPUX 1
#define ELFOSABI_STANDALONE 255

#define ET_NONE 0
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4
#define ET_LOOS 0xFE00
#define ET_HIOS 0xFEFF
#define ET_LOPROC 0xFF00
#define ET_HIPROC 0xFFFF

#define SHN_UNDEF 0
#define SHN_LOPROC 0xFF00
#define SHN_HIPROC 0xFF1F
#define SHN_LOOS 0xFF20
#define SHN_HIOS 0xFF3F
#define SHN_ABS 0xFFF1
#define SHN_COMMON 0xFFF2

#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_LOOS 0x60000000
#define SHT_HIOS 0x6FFFFFFF
#define SHT_LOPROC 0x70000000
#define SHT_HIPROC 0x7FFFFFFF

#define SHF_WRITE 0x1
#define SHF_ALLOC 0x2
#define SHF_EXECINSTR 0x4
#define SHF_MASKOS 0x0F000000
#define SHF_MASKPROC 0xF0000000

#define STB_LOCAL 0
#define STB_GLOBAL 1
#define STB_WEAK 2
#define STB_LOOS 10
#define STB_HIOS 12
#define STB_LOPROC 13
#define STB_HIPROC 15

#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC 2
#define STT_SECTION 3
#define STT_FILE 4
#define STT_LOOS 10
#define STT_HIOS 12
#define STT_LOPROC 13
#define STT_HIPROC 15

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_LOOS 0x60000000
#define PT_HIOS 0x6FFFFFFF
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7FFFFFFF

#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x4
#define PF_MASKOS 0x00FF0000
#define PF_MASKPROC 0xFF000000

typedef uint64_t    Elf64_Addr;
typedef uint64_t    Elf64_Off;
typedef uint16_t    Elf64_Half;
typedef uint32_t    Elf64_Word;
typedef int32_t     Elf64_Sword;
typedef uint64_t    Elf64_Xword;
typedef int64_t     Elf64_Sxword;


struct Elf64_Ident {
    unsigned char El_MAG0;      // Should be 0x7F
    unsigned char El_MAG1;      // Should be 'E'
    unsigned char El_MAG2;      // Should be 'L'
    unsigned char El_MAG3;      // Should be 'F'
    unsigned char El_CLASS;     // File Class
    unsigned char El_DATA;      // Data encoding
    unsigned char El_VERSION;   // File Version
    unsigned char El_OSABI;     // OS/ABI Identification
    unsigned char El_ABIVERSION;// ABI version
    unsigned char El_PAD[6];    // Padding
    unsigned char El_NIDENT;    // Size of the struct
};

typedef struct{
    struct Elf64_Ident e_ident; // ELF identification
    Elf64_Half 	e_type;			// Object file type
    Elf64_Half 	e_machine;		// Machine type
    Elf64_Word 	e_version;		// Object file version
    Elf64_Addr 	e_entry;		// Entry point address
    Elf64_Off 	e_phoff;		// Program header offset
    Elf64_Off 	e_shoff;		// Section header offset
    Elf64_Word 	e_flags;		// Processor-specific flags
    Elf64_Half 	e_ehsize;		// ELF header size
    Elf64_Half 	e_phentsize;	// Size of program header entry
    Elf64_Half 	e_phnum;		// Number of program header entries
    Elf64_Half 	e_shentsize;	// Size of section header entry
    Elf64_Half 	e_shnum;		// Number of section header entries
    Elf64_Half 	e_shstrndx;		// Section name string table index
} Elf64_Ehdr;

typedef struct {
    Elf64_Word 	sh_name;		// Section name  
    Elf64_Word 	sh_type;		// Section type  
    Elf64_Xword sh_flags;		// Section attributes  
    Elf64_Addr 	sh_addr;		// Virtual address in memory  
    Elf64_Off 	sh_offset;		// Offset in file  
    Elf64_Xword sh_size;		// Size of section  
    Elf64_Word 	sh_link;		// Link to other  section  
    Elf64_Word 	sh_info;		// Miscellaneous information  
    Elf64_Xword sh_addralign;	// Address alignment boundary  
    Elf64_Xword sh_entsize;		// Size of entries, if section has table  
} Elf64_Shdr;

typedef struct {
	Elf64_Word		st_name;	// Symbol name
	unsigned char	st_info;	// Type and Binding attributes 
	unsigned char	st_other;	// Reserved 
	Elf64_Half		st_shndx;	// Section table index 
	Elf64_Addr		st_value;	// Symbol value 
	Elf64_Xword		st_size;	// Size of object (e.g., common) 
} Elf64_Sym;

typedef struct {
	Elf64_Addr		r_offset;	// Address of reference  
	Elf64_Xword		r_info;		// Symbol index and type of relocation  
} Elf64_Rel;

typedef struct {
	Elf64_Addr		r_offset;	// Address of reference  
	Elf64_Xword		r_info;		// Symbol index and type of relocation  
	Elf64_Sxword	r_addend;	// Constant part of expression  
} Elf64_Rela;

typedef struct {
	Elf64_Word		p_type;		// Type of segment 
	Elf64_Word		p_flags;	// Segment attributes 
	Elf64_Off		p_offset;	// Offset in file 
	Elf64_Addr		p_vaddr; 	// Virtual address in memory 
	Elf64_Addr		p_paddr; 	// Reserved 
	Elf64_Xword		p_filesz;	// Size of segment in file 
	Elf64_Xword		p_memsz;	// Size of segment in memory 
	Elf64_Xword		p_align;	// Alignment of segment 
} Elf64_Phdr;

#endif