#pragma once

#include <inttypes.h>

/**
 * \brief SCE module information section
 * 
 * Can be found in an ELF file or loaded in 
 * memory.
 */
struct module_info // thanks roxfan
{
    uint16_t   modattribute;  // ??
    uint16_t   modversion;    // always 1,1?
    char       modname[27];   ///< Name of the module
    uint8_t    type;          // 6 = user-mode prx?
    uint32_t   gp_value;      // always 0 on ARM
    uint32_t   ent_top;       // beginning of the export list (sceModuleExports array)
    uint32_t   ent_end;       // end of same
    uint32_t   stub_top;      // beginning of the import list (sceModuleStubInfo array)
    uint32_t   stub_end;      // end of same
    uint32_t   module_nid;    // ID of the PRX? seems to be unused
    uint32_t   field_38;      // unused in samples
    uint32_t   field_3C;      // I suspect these may contain TLS info
    uint32_t   field_40;      //
    uint32_t   mod_start;     // module start function; can be 0 or -1; also present in exports
    uint32_t   mod_stop;      // module stop function
    uint32_t   exidx_start;   // ARM EABI style exception tables
    uint32_t   exidx_end;     //
    uint32_t   extab_start;   //
    uint32_t   extab_end;     //
};
