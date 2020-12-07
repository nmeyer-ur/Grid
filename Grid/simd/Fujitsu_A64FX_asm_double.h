/*************************************************************************************

    Grid physics library, www.github.com/paboyle/Grid

    Source file: Fujitsu_A64FX_asm_double.h

    Copyright (C) 2020

Author: Nils Meyer <nils.meyer@ur.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    See the full license in the file "LICENSE" in the top level distribution directory
*************************************************************************************/
/*  END LEGAL */
#define LOAD_CHIMU(base)               LOAD_CHIMU_INTERLEAVED_A64FXd(base)  
#define PREFETCH_CHIMU_L1(A)           PREFETCH_CHIMU_L1_INTERNAL_A64FXd(A)  
#define PREFETCH_GAUGE_L1(A)           PREFETCH_GAUGE_L1_INTERNAL_A64FXd(A)  
#define PREFETCH_CHIMU_L2(A)           PREFETCH_CHIMU_L2_INTERNAL_A64FXd(A)  
#define PREFETCH_GAUGE_L2(A)           PREFETCH_GAUGE_L2_INTERNAL_A64FXd(A)  
#define PF_GAUGE(A)  
#define PREFETCH_RESULT_L2_STORE(A)    PREFETCH_RESULT_L2_STORE_INTERNAL_A64FXd(A)  
#define PREFETCH_RESULT_L1_STORE(A)    PREFETCH_RESULT_L1_STORE_INTERNAL_A64FXd(A)  
#define PREFETCH1_CHIMU(A)             PREFETCH_CHIMU_L1(A)  
#define PREFETCH_CHIMU(A)              PREFETCH_CHIMU_L1(A)  
#define LOCK_GAUGE(A)  
#define UNLOCK_GAUGE(A)  
#define MASK_REGS                      DECLARATIONS_A64FXd  
#define SAVE_RESULT(A,B)               RESULT_A64FXd(A);  
#define MULT_2SPIN_1(Dir)              MULT_2SPIN_1_A64FXd(Dir)  
#define MULT_2SPIN_2                   MULT_2SPIN_2_A64FXd  
#define LOAD_CHI(base)                 LOAD_CHI_A64FXd(base)  
#define ZERO_PSI                       ZERO_PSI_A64FXd  
#define ADD_RESULT(base,basep)         LOAD_CHIMU(base); ADD_RESULT_INTERNAL_A64FXd; RESULT_A64FXd(base)  
#define XP_PROJ                        XP_PROJ_A64FXd  
#define YP_PROJ                        YP_PROJ_A64FXd  
#define ZP_PROJ                        ZP_PROJ_A64FXd  
#define TP_PROJ                        TP_PROJ_A64FXd  
#define XM_PROJ                        XM_PROJ_A64FXd  
#define YM_PROJ                        YM_PROJ_A64FXd  
#define ZM_PROJ                        ZM_PROJ_A64FXd  
#define TM_PROJ                        TM_PROJ_A64FXd  
#define XP_RECON                       XP_RECON_A64FXd  
#define XM_RECON                       XM_RECON_A64FXd  
#define XM_RECON_ACCUM                 XM_RECON_ACCUM_A64FXd  
#define YM_RECON_ACCUM                 YM_RECON_ACCUM_A64FXd  
#define ZM_RECON_ACCUM                 ZM_RECON_ACCUM_A64FXd  
#define TM_RECON_ACCUM                 TM_RECON_ACCUM_A64FXd  
#define XP_RECON_ACCUM                 XP_RECON_ACCUM_A64FXd  
#define YP_RECON_ACCUM                 YP_RECON_ACCUM_A64FXd  
#define ZP_RECON_ACCUM                 ZP_RECON_ACCUM_A64FXd  
#define TP_RECON_ACCUM                 TP_RECON_ACCUM_A64FXd  
#define PERMUTE_DIR0                   0  
#define PERMUTE_DIR1                   1  
#define PERMUTE_DIR2                   2  
#define PERMUTE_DIR3                   3  
#define PERMUTE                        PERMUTE_A64FXd;  
#define LOAD_TABLE(Dir)                if (Dir == 0) { LOAD_TABLE0; } else if (Dir == 1) { LOAD_TABLE1; } else if (Dir == 2) { LOAD_TABLE2; }  
#define MAYBEPERM(Dir,perm)            if (Dir != 3) { if (perm) { PERMUTE; } }  
// DECLARATIONS
#define DECLARATIONS_A64FXd  \
    uint64_t baseU; \
    const uint64_t lut[4][8] = { \
        {4, 5, 6, 7, 0, 1, 2, 3}, \
        {2, 3, 0, 1, 6, 7, 4, 5}, \
        {1, 0, 3, 2, 5, 4, 7, 6}, \
        {0, 1, 2, 4, 5, 6, 7, 8} };\
asm ( \
    "ptrue p5.d \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
asm ( \
    "fmov z31.d , 0 \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// RESULT
#define RESULT_A64FXd(base)  \
{ \
asm ( \
    "str z0, [%[storeptr], -6, mul vl] \n\t" \
    "str z1, [%[storeptr], -5, mul vl] \n\t" \
    "str z2, [%[storeptr], -4, mul vl] \n\t" \
    "str z3, [%[storeptr], -3, mul vl] \n\t" \
    "str z4, [%[storeptr], -2, mul vl] \n\t" \
    "str z5, [%[storeptr], -1, mul vl] \n\t" \
    "str z6, [%[storeptr], 0, mul vl] \n\t" \
    "str z7, [%[storeptr], 1, mul vl] \n\t" \
    "str z8, [%[storeptr], 2, mul vl] \n\t" \
    "str z9, [%[storeptr], 3, mul vl] \n\t" \
    "str z10, [%[storeptr], 4, mul vl] \n\t" \
    "str z11, [%[storeptr], 5, mul vl] \n\t" \
    :  \
    : [storeptr] "r" (base + 2 * 3 * 64) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// PREFETCH_CHIMU_L2 (prefetch to L2)
#define PREFETCH_CHIMU_L2_INTERNAL_A64FXd(base)  \
{ \
asm ( \
    "prfd PLDL2STRM, p5, [%[fetchptr], 0, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 4, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 8, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (base) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// PREFETCH_CHIMU_L1 (prefetch to L1)
#define PREFETCH_CHIMU_L1_INTERNAL_A64FXd(base)  \
{ \
asm ( \
    "prfd PLDL1STRM, p5, [%[fetchptr], 0, mul vl] \n\t" \
    "prfd PLDL1STRM, p5, [%[fetchptr], 4, mul vl] \n\t" \
    "prfd PLDL1STRM, p5, [%[fetchptr], 8, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (base) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// PREFETCH_GAUGE_L2 (prefetch to L2)
#define PREFETCH_GAUGE_L2_INTERNAL_A64FXd(A)  \
{ \
    const auto & ref(U[sUn](A)); baseU = (uint64_t)&ref + 3 * 3 * 64; \
asm ( \
    "prfd PLDL2STRM, p5, [%[fetchptr], -4, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 0, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 4, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 8, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 12, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 16, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 20, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 24, mul vl] \n\t" \
    "prfd PLDL2STRM, p5, [%[fetchptr], 28, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (baseU) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// PREFETCH_GAUGE_L1 (prefetch to L1)
#define PREFETCH_GAUGE_L1_INTERNAL_A64FXd(A)  \
{ \
    const auto & ref(U[sU](A)); baseU = (uint64_t)&ref; \
asm ( \
    "prfd PLDL1STRM, p5, [%[fetchptr], 0, mul vl] \n\t" \
    "prfd PLDL1STRM, p5, [%[fetchptr], 4, mul vl] \n\t" \
    "prfd PLDL1STRM, p5, [%[fetchptr], 8, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (baseU) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// LOAD_CHI
#define LOAD_CHI_A64FXd(base)  \
{ \
asm ( \
    "ld1d { z12.d }, p5/z, [%[fetchptr], 0, mul vl] \n\t" \
    "ld1d { z13.d }, p5/z, [%[fetchptr], 1, mul vl] \n\t" \
    "ld1d { z14.d }, p5/z, [%[fetchptr], 2, mul vl] \n\t" \
    "ld1d { z15.d }, p5/z, [%[fetchptr], 3, mul vl] \n\t" \
    "ld1d { z16.d }, p5/z, [%[fetchptr], 4, mul vl] \n\t" \
    "ld1d { z17.d }, p5/z, [%[fetchptr], 5, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (base) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// LOAD_CHIMU
#define LOAD_CHIMU_INTERLEAVED_A64FXd(base)  \
{ \
asm ( \
    "ld1d { z12.d }, p5/z, [%[fetchptr], -6, mul vl] \n\t" \
    "ld1d { z21.d }, p5/z, [%[fetchptr], 3, mul vl] \n\t" \
    "ld1d { z15.d }, p5/z, [%[fetchptr], -3, mul vl] \n\t" \
    "ld1d { z18.d }, p5/z, [%[fetchptr], 0, mul vl] \n\t" \
    "ld1d { z13.d }, p5/z, [%[fetchptr], -5, mul vl] \n\t" \
    "ld1d { z22.d }, p5/z, [%[fetchptr], 4, mul vl] \n\t" \
    "ld1d { z16.d }, p5/z, [%[fetchptr], -2, mul vl] \n\t" \
    "ld1d { z19.d }, p5/z, [%[fetchptr], 1, mul vl] \n\t" \
    "ld1d { z14.d }, p5/z, [%[fetchptr], -4, mul vl] \n\t" \
    "ld1d { z23.d }, p5/z, [%[fetchptr], 5, mul vl] \n\t" \
    "ld1d { z17.d }, p5/z, [%[fetchptr], -1, mul vl] \n\t" \
    "ld1d { z20.d }, p5/z, [%[fetchptr], 2, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (base + 2 * 3 * 64) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// LOAD_CHIMU_0213
#define LOAD_CHIMU_0213_A64FXd  \
{ \
    const SiteSpinor & ref(in[offset]); \
asm ( \
    "ld1d { z12.d }, p5/z, [%[fetchptr], -6, mul vl] \n\t" \
    "ld1d { z18.d }, p5/z, [%[fetchptr], 0, mul vl] \n\t" \
    "ld1d { z13.d }, p5/z, [%[fetchptr], -5, mul vl] \n\t" \
    "ld1d { z19.d }, p5/z, [%[fetchptr], 1, mul vl] \n\t" \
    "ld1d { z14.d }, p5/z, [%[fetchptr], -4, mul vl] \n\t" \
    "ld1d { z20.d }, p5/z, [%[fetchptr], 2, mul vl] \n\t" \
    "ld1d { z15.d }, p5/z, [%[fetchptr], -3, mul vl] \n\t" \
    "ld1d { z21.d }, p5/z, [%[fetchptr], 3, mul vl] \n\t" \
    "ld1d { z16.d }, p5/z, [%[fetchptr], -2, mul vl] \n\t" \
    "ld1d { z22.d }, p5/z, [%[fetchptr], 4, mul vl] \n\t" \
    "ld1d { z17.d }, p5/z, [%[fetchptr], -1, mul vl] \n\t" \
    "ld1d { z23.d }, p5/z, [%[fetchptr], 5, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (&ref[2][0]) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// LOAD_CHIMU_0312
#define LOAD_CHIMU_0312_A64FXd  \
{ \
    const SiteSpinor & ref(in[offset]); \
asm ( \
    "ld1d { z12.d }, p5/z, [%[fetchptr], -6, mul vl] \n\t" \
    "ld1d { z21.d }, p5/z, [%[fetchptr], 3, mul vl] \n\t" \
    "ld1d { z13.d }, p5/z, [%[fetchptr], -5, mul vl] \n\t" \
    "ld1d { z22.d }, p5/z, [%[fetchptr], 4, mul vl] \n\t" \
    "ld1d { z14.d }, p5/z, [%[fetchptr], -4, mul vl] \n\t" \
    "ld1d { z23.d }, p5/z, [%[fetchptr], 5, mul vl] \n\t" \
    "ld1d { z15.d }, p5/z, [%[fetchptr], -3, mul vl] \n\t" \
    "ld1d { z18.d }, p5/z, [%[fetchptr], 0, mul vl] \n\t" \
    "ld1d { z16.d }, p5/z, [%[fetchptr], -2, mul vl] \n\t" \
    "ld1d { z19.d }, p5/z, [%[fetchptr], 1, mul vl] \n\t" \
    "ld1d { z17.d }, p5/z, [%[fetchptr], -1, mul vl] \n\t" \
    "ld1d { z20.d }, p5/z, [%[fetchptr], 2, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (&ref[2][0]) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// LOAD_TABLE0
#define LOAD_TABLE0  \
asm ( \
    "ldr z30, [%[tableptr], %[index], mul vl] \n\t" \
    :  \
    : [tableptr] "r" (&lut[0]),[index] "i" (0) \
    : "memory","cc","p5","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// LOAD_TABLE1
#define LOAD_TABLE1  \
asm ( \
    "ldr z30, [%[tableptr], %[index], mul vl] \n\t" \
    :  \
    : [tableptr] "r" (&lut[0]),[index] "i" (1) \
    : "memory","cc","p5","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// LOAD_TABLE2
#define LOAD_TABLE2  \
asm ( \
    "ldr z30, [%[tableptr], %[index], mul vl] \n\t" \
    :  \
    : [tableptr] "r" (&lut[0]),[index] "i" (2) \
    : "memory","cc","p5","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// LOAD_TABLE3
#define LOAD_TABLE3  \
asm ( \
    "ldr z30, [%[tableptr], %[index], mul vl] \n\t" \
    :  \
    : [tableptr] "r" (&lut[0]),[index] "i" (3) \
    : "memory","cc","p5","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// PERMUTE
#define PERMUTE_A64FXd  \
asm ( \
    "tbl z12.d, { z12.d }, z30.d \n\t"  \
    "tbl z13.d, { z13.d }, z30.d \n\t"  \
    "tbl z14.d, { z14.d }, z30.d \n\t"  \
    "tbl z15.d, { z15.d }, z30.d \n\t"  \
    "tbl z16.d, { z16.d }, z30.d \n\t"  \
    "tbl z17.d, { z17.d }, z30.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// LOAD_GAUGE
#define LOAD_GAUGE(A)  \
{ \
    const auto & ref(U[sU](A)); baseU = (uint64_t)&ref; \
asm ( \
    "ld1d { z24.d }, p5/z, [%[fetchptr], -6, mul vl] \n\t" \
    "ld1d { z25.d }, p5/z, [%[fetchptr], -3, mul vl] \n\t" \
    "ld1d { z26.d }, p5/z, [%[fetchptr], 0, mul vl] \n\t" \
    "ld1d { z27.d }, p5/z, [%[fetchptr], -5, mul vl] \n\t" \
    "ld1d { z28.d }, p5/z, [%[fetchptr], -2, mul vl] \n\t" \
    "ld1d { z29.d }, p5/z, [%[fetchptr], 1, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (baseU + 2 * 3 * 64) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// MULT_2SPIN
#define MULT_2SPIN_1_A64FXd(A)  \
{ \
    const auto & ref(U[sU](A)); baseU = (uint64_t)&ref; \
asm ( \
    "ld1d { z24.d }, p5/z, [%[fetchptr], -6, mul vl] \n\t" \
    "ld1d { z25.d }, p5/z, [%[fetchptr], -3, mul vl] \n\t" \
    "ld1d { z26.d }, p5/z, [%[fetchptr], 0, mul vl] \n\t" \
    "ld1d { z27.d }, p5/z, [%[fetchptr], -5, mul vl] \n\t" \
    "ld1d { z28.d }, p5/z, [%[fetchptr], -2, mul vl] \n\t" \
    "ld1d { z29.d }, p5/z, [%[fetchptr], 1, mul vl] \n\t" \
    "movprfx z18.d, p5/m, z31.d \n\t" \
    "fcmla z18.d, p5/m, z24.d, z12.d, 0 \n\t" \
    "movprfx z21.d, p5/m, z31.d \n\t" \
    "fcmla z21.d, p5/m, z24.d, z15.d, 0 \n\t" \
    "movprfx z19.d, p5/m, z31.d \n\t" \
    "fcmla z19.d, p5/m, z25.d, z12.d, 0 \n\t" \
    "movprfx z22.d, p5/m, z31.d \n\t" \
    "fcmla z22.d, p5/m, z25.d, z15.d, 0 \n\t" \
    "movprfx z20.d, p5/m, z31.d \n\t" \
    "fcmla z20.d, p5/m, z26.d, z12.d, 0 \n\t" \
    "movprfx z23.d, p5/m, z31.d \n\t" \
    "fcmla z23.d, p5/m, z26.d, z15.d, 0 \n\t" \
    "fcmla z18.d, p5/m, z24.d, z12.d, 90 \n\t" \
    "fcmla z21.d, p5/m, z24.d, z15.d, 90 \n\t" \
    "fcmla z19.d, p5/m, z25.d, z12.d, 90 \n\t" \
    "fcmla z22.d, p5/m, z25.d, z15.d, 90 \n\t" \
    "fcmla z20.d, p5/m, z26.d, z12.d, 90 \n\t" \
    "fcmla z23.d, p5/m, z26.d, z15.d, 90 \n\t" \
    "ld1d { z24.d }, p5/z, [%[fetchptr], -4, mul vl] \n\t" \
    "ld1d { z25.d }, p5/z, [%[fetchptr], -1, mul vl] \n\t" \
    "ld1d { z26.d }, p5/z, [%[fetchptr], 2, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (baseU + 2 * 3 * 64) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// MULT_2SPIN_BACKEND
#define MULT_2SPIN_2_A64FXd  \
{ \
asm ( \
    "fcmla z18.d, p5/m, z27.d, z13.d, 0 \n\t" \
    "fcmla z21.d, p5/m, z27.d, z16.d, 0 \n\t" \
    "fcmla z19.d, p5/m, z28.d, z13.d, 0 \n\t" \
    "fcmla z22.d, p5/m, z28.d, z16.d, 0 \n\t" \
    "fcmla z20.d, p5/m, z29.d, z13.d, 0 \n\t" \
    "fcmla z23.d, p5/m, z29.d, z16.d, 0 \n\t" \
    "fcmla z18.d, p5/m, z27.d, z13.d, 90 \n\t" \
    "fcmla z21.d, p5/m, z27.d, z16.d, 90 \n\t" \
    "fcmla z19.d, p5/m, z28.d, z13.d, 90 \n\t" \
    "fcmla z22.d, p5/m, z28.d, z16.d, 90 \n\t" \
    "fcmla z20.d, p5/m, z29.d, z13.d, 90 \n\t" \
    "fcmla z23.d, p5/m, z29.d, z16.d, 90 \n\t" \
    "fcmla z18.d, p5/m, z24.d, z14.d, 0 \n\t" \
    "fcmla z21.d, p5/m, z24.d, z17.d, 0 \n\t" \
    "fcmla z19.d, p5/m, z25.d, z14.d, 0 \n\t" \
    "fcmla z22.d, p5/m, z25.d, z17.d, 0 \n\t" \
    "fcmla z20.d, p5/m, z26.d, z14.d, 0 \n\t" \
    "fcmla z23.d, p5/m, z26.d, z17.d, 0 \n\t" \
    "fcmla z18.d, p5/m, z24.d, z14.d, 90 \n\t" \
    "fcmla z21.d, p5/m, z24.d, z17.d, 90 \n\t" \
    "fcmla z19.d, p5/m, z25.d, z14.d, 90 \n\t" \
    "fcmla z22.d, p5/m, z25.d, z17.d, 90 \n\t" \
    "fcmla z20.d, p5/m, z26.d, z14.d, 90 \n\t" \
    "fcmla z23.d, p5/m, z26.d, z17.d, 90 \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// XP_PROJ
#define XP_PROJ_A64FXd  \
{ \
asm ( \
    "fcadd z12.d, p5/m, z12.d, z21.d, 90 \n\t" \
    "fcadd z13.d, p5/m, z13.d, z22.d, 90 \n\t" \
    "fcadd z14.d, p5/m, z14.d, z23.d, 90 \n\t" \
    "fcadd z15.d, p5/m, z15.d, z18.d, 90 \n\t" \
    "fcadd z16.d, p5/m, z16.d, z19.d, 90 \n\t" \
    "fcadd z17.d, p5/m, z17.d, z20.d, 90 \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// XP_RECON
#define XP_RECON_A64FXd  \
asm ( \
    "movprfx z6.d, p5/m, z31.d \n\t" \
    "fcadd z6.d, p5/m, z6.d, z21.d, 270 \n\t" \
    "movprfx z7.d, p5/m, z31.d \n\t" \
    "fcadd z7.d, p5/m, z7.d, z22.d, 270 \n\t" \
    "movprfx z8.d, p5/m, z31.d \n\t" \
    "fcadd z8.d, p5/m, z8.d, z23.d, 270 \n\t" \
    "movprfx z9.d, p5/m, z31.d \n\t" \
    "fcadd z9.d, p5/m, z9.d, z18.d, 270 \n\t" \
    "movprfx z10.d, p5/m, z31.d \n\t" \
    "fcadd z10.d, p5/m, z10.d, z19.d, 270 \n\t" \
    "movprfx z11.d, p5/m, z31.d \n\t" \
    "fcadd z11.d, p5/m, z11.d, z20.d, 270 \n\t" \
    "mov z0.d, p5/m, z18.d \n\t" \
    "mov z1.d, p5/m, z19.d \n\t" \
    "mov z2.d, p5/m, z20.d \n\t" \
    "mov z3.d, p5/m, z21.d \n\t" \
    "mov z4.d, p5/m, z22.d \n\t" \
    "mov z5.d, p5/m, z23.d \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// XP_RECON_ACCUM
#define XP_RECON_ACCUM_A64FXd  \
asm ( \
    "fcadd z9.d, p5/m, z9.d, z18.d, 270 \n\t" \
    "fadd z0.d, p5/m, z0.d, z18.d \n\t"  \
    "fcadd z10.d, p5/m, z10.d, z19.d, 270 \n\t" \
    "fadd z1.d, p5/m, z1.d, z19.d \n\t"  \
    "fcadd z11.d, p5/m, z11.d, z20.d, 270 \n\t" \
    "fadd z2.d, p5/m, z2.d, z20.d \n\t"  \
    "fcadd z6.d, p5/m, z6.d, z21.d, 270 \n\t" \
    "fadd z3.d, p5/m, z3.d, z21.d \n\t"  \
    "fcadd z7.d, p5/m, z7.d, z22.d, 270 \n\t" \
    "fadd z4.d, p5/m, z4.d, z22.d \n\t"  \
    "fcadd z8.d, p5/m, z8.d, z23.d, 270 \n\t" \
    "fadd z5.d, p5/m, z5.d, z23.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// YP_PROJ
#define YP_PROJ_A64FXd  \
{ \
asm ( \
    "fsub z12.d, p5/m, z12.d, z21.d \n\t" \
    "fsub z13.d, p5/m, z13.d, z22.d \n\t" \
    "fsub z14.d, p5/m, z14.d, z23.d \n\t" \
    "fadd z15.d, p5/m, z15.d, z18.d \n\t"  \
    "fadd z16.d, p5/m, z16.d, z19.d \n\t"  \
    "fadd z17.d, p5/m, z17.d, z20.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// ZP_PROJ
#define ZP_PROJ_A64FXd  \
{ \
asm ( \
    "fcadd z12.d, p5/m, z12.d, z18.d, 90 \n\t" \
    "fcadd z13.d, p5/m, z13.d, z19.d, 90 \n\t" \
    "fcadd z14.d, p5/m, z14.d, z20.d, 90 \n\t" \
    "fcadd z15.d, p5/m, z15.d, z21.d, 270 \n\t" \
    "fcadd z16.d, p5/m, z16.d, z22.d, 270 \n\t" \
    "fcadd z17.d, p5/m, z17.d, z23.d, 270 \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// TP_PROJ
#define TP_PROJ_A64FXd  \
{ \
asm ( \
    "fadd z12.d, p5/m, z12.d, z18.d \n\t"  \
    "fadd z13.d, p5/m, z13.d, z19.d \n\t"  \
    "fadd z14.d, p5/m, z14.d, z20.d \n\t"  \
    "fadd z15.d, p5/m, z15.d, z21.d \n\t"  \
    "fadd z16.d, p5/m, z16.d, z22.d \n\t"  \
    "fadd z17.d, p5/m, z17.d, z23.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// XM_PROJ
#define XM_PROJ_A64FXd  \
{ \
asm ( \
    "fcadd z12.d, p5/m, z12.d, z21.d, 270 \n\t" \
    "fcadd z13.d, p5/m, z13.d, z22.d, 270 \n\t" \
    "fcadd z14.d, p5/m, z14.d, z23.d, 270 \n\t" \
    "fcadd z15.d, p5/m, z15.d, z18.d, 270 \n\t" \
    "fcadd z16.d, p5/m, z16.d, z19.d, 270 \n\t" \
    "fcadd z17.d, p5/m, z17.d, z20.d, 270 \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// XM_RECON
#define XM_RECON_A64FXd  \
asm ( \
    "movprfx z6.d, p5/m, z31.d \n\t" \
    "fcadd z6.d, p5/m, z6.d, z21.d, 90 \n\t" \
    "movprfx z7.d, p5/m, z31.d \n\t" \
    "fcadd z7.d, p5/m, z7.d, z22.d, 90 \n\t" \
    "movprfx z8.d, p5/m, z31.d \n\t" \
    "fcadd z8.d, p5/m, z8.d, z23.d, 90 \n\t" \
    "movprfx z9.d, p5/m, z31.d \n\t" \
    "fcadd z9.d, p5/m, z9.d, z18.d, 90 \n\t" \
    "movprfx z10.d, p5/m, z31.d \n\t" \
    "fcadd z10.d, p5/m, z10.d, z19.d, 90 \n\t" \
    "movprfx z11.d, p5/m, z31.d \n\t" \
    "fcadd z11.d, p5/m, z11.d, z20.d, 90 \n\t" \
    "mov z0.d, p5/m, z18.d \n\t" \
    "mov z1.d, p5/m, z19.d \n\t" \
    "mov z2.d, p5/m, z20.d \n\t" \
    "mov z3.d, p5/m, z21.d \n\t" \
    "mov z4.d, p5/m, z22.d \n\t" \
    "mov z5.d, p5/m, z23.d \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// YM_PROJ
#define YM_PROJ_A64FXd  \
{ \
asm ( \
    "fadd z12.d, p5/m, z12.d, z21.d \n\t"  \
    "fadd z13.d, p5/m, z13.d, z22.d \n\t"  \
    "fadd z14.d, p5/m, z14.d, z23.d \n\t"  \
    "fsub z15.d, p5/m, z15.d, z18.d \n\t" \
    "fsub z16.d, p5/m, z16.d, z19.d \n\t" \
    "fsub z17.d, p5/m, z17.d, z20.d \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// ZM_PROJ
#define ZM_PROJ_A64FXd  \
{ \
asm ( \
    "fcadd z12.d, p5/m, z12.d, z18.d, 270 \n\t" \
    "fcadd z13.d, p5/m, z13.d, z19.d, 270 \n\t" \
    "fcadd z14.d, p5/m, z14.d, z20.d, 270 \n\t" \
    "fcadd z15.d, p5/m, z15.d, z21.d, 90 \n\t" \
    "fcadd z16.d, p5/m, z16.d, z22.d, 90 \n\t" \
    "fcadd z17.d, p5/m, z17.d, z23.d, 90 \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// TM_PROJ
#define TM_PROJ_A64FXd  \
{ \
asm ( \
    "fsub z12.d, p5/m, z12.d, z18.d \n\t" \
    "fsub z13.d, p5/m, z13.d, z19.d \n\t" \
    "fsub z14.d, p5/m, z14.d, z20.d \n\t" \
    "fsub z15.d, p5/m, z15.d, z21.d \n\t" \
    "fsub z16.d, p5/m, z16.d, z22.d \n\t" \
    "fsub z17.d, p5/m, z17.d, z23.d \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); \
}
// XM_RECON_ACCUM
#define XM_RECON_ACCUM_A64FXd  \
asm ( \
    "fcadd z9.d, p5/m, z9.d, z18.d, 90 \n\t" \
    "fcadd z10.d, p5/m, z10.d, z19.d, 90 \n\t" \
    "fcadd z11.d, p5/m, z11.d, z20.d, 90 \n\t" \
    "fcadd z6.d, p5/m, z6.d, z21.d, 90 \n\t" \
    "fcadd z7.d, p5/m, z7.d, z22.d, 90 \n\t" \
    "fcadd z8.d, p5/m, z8.d, z23.d, 90 \n\t" \
    "fadd z0.d, p5/m, z0.d, z18.d \n\t"  \
    "fadd z1.d, p5/m, z1.d, z19.d \n\t"  \
    "fadd z2.d, p5/m, z2.d, z20.d \n\t"  \
    "fadd z3.d, p5/m, z3.d, z21.d \n\t"  \
    "fadd z4.d, p5/m, z4.d, z22.d \n\t"  \
    "fadd z5.d, p5/m, z5.d, z23.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// YP_RECON_ACCUM
#define YP_RECON_ACCUM_A64FXd  \
asm ( \
    "fadd z0.d, p5/m, z0.d, z18.d \n\t"  \
    "fsub z9.d, p5/m, z9.d, z18.d \n\t" \
    "fadd z1.d, p5/m, z1.d, z19.d \n\t"  \
    "fsub z10.d, p5/m, z10.d, z19.d \n\t" \
    "fadd z2.d, p5/m, z2.d, z20.d \n\t"  \
    "fsub z11.d, p5/m, z11.d, z20.d \n\t" \
    "fadd z3.d, p5/m, z3.d, z21.d \n\t"  \
    "fadd z6.d, p5/m, z6.d, z21.d \n\t"  \
    "fadd z4.d, p5/m, z4.d, z22.d \n\t"  \
    "fadd z7.d, p5/m, z7.d, z22.d \n\t"  \
    "fadd z5.d, p5/m, z5.d, z23.d \n\t"  \
    "fadd z8.d, p5/m, z8.d, z23.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// YM_RECON_ACCUM
#define YM_RECON_ACCUM_A64FXd  \
asm ( \
    "fadd z0.d, p5/m, z0.d, z18.d \n\t"  \
    "fadd z9.d, p5/m, z9.d, z18.d \n\t"  \
    "fadd z1.d, p5/m, z1.d, z19.d \n\t"  \
    "fadd z10.d, p5/m, z10.d, z19.d \n\t"  \
    "fadd z2.d, p5/m, z2.d, z20.d \n\t"  \
    "fadd z11.d, p5/m, z11.d, z20.d \n\t"  \
    "fadd z3.d, p5/m, z3.d, z21.d \n\t"  \
    "fsub z6.d, p5/m, z6.d, z21.d \n\t" \
    "fadd z4.d, p5/m, z4.d, z22.d \n\t"  \
    "fsub z7.d, p5/m, z7.d, z22.d \n\t" \
    "fadd z5.d, p5/m, z5.d, z23.d \n\t"  \
    "fsub z8.d, p5/m, z8.d, z23.d \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// ZP_RECON_ACCUM
#define ZP_RECON_ACCUM_A64FXd  \
asm ( \
    "fcadd z6.d, p5/m, z6.d, z18.d, 270 \n\t" \
    "fadd z0.d, p5/m, z0.d, z18.d \n\t"  \
    "fcadd z7.d, p5/m, z7.d, z19.d, 270 \n\t" \
    "fadd z1.d, p5/m, z1.d, z19.d \n\t"  \
    "fcadd z8.d, p5/m, z8.d, z20.d, 270 \n\t" \
    "fadd z2.d, p5/m, z2.d, z20.d \n\t"  \
    "fcadd z9.d, p5/m, z9.d, z21.d, 90 \n\t" \
    "fadd z3.d, p5/m, z3.d, z21.d \n\t"  \
    "fcadd z10.d, p5/m, z10.d, z22.d, 90 \n\t" \
    "fadd z4.d, p5/m, z4.d, z22.d \n\t"  \
    "fcadd z11.d, p5/m, z11.d, z23.d, 90 \n\t" \
    "fadd z5.d, p5/m, z5.d, z23.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// ZM_RECON_ACCUM
#define ZM_RECON_ACCUM_A64FXd  \
asm ( \
    "fcadd z6.d, p5/m, z6.d, z18.d, 90 \n\t" \
    "fadd z0.d, p5/m, z0.d, z18.d \n\t"  \
    "fcadd z7.d, p5/m, z7.d, z19.d, 90 \n\t" \
    "fadd z1.d, p5/m, z1.d, z19.d \n\t"  \
    "fcadd z8.d, p5/m, z8.d, z20.d, 90 \n\t" \
    "fadd z2.d, p5/m, z2.d, z20.d \n\t"  \
    "fcadd z9.d, p5/m, z9.d, z21.d, 270 \n\t" \
    "fadd z3.d, p5/m, z3.d, z21.d \n\t"  \
    "fcadd z10.d, p5/m, z10.d, z22.d, 270 \n\t" \
    "fadd z4.d, p5/m, z4.d, z22.d \n\t"  \
    "fcadd z11.d, p5/m, z11.d, z23.d, 270 \n\t" \
    "fadd z5.d, p5/m, z5.d, z23.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// TP_RECON_ACCUM
#define TP_RECON_ACCUM_A64FXd  \
asm ( \
    "fadd z0.d, p5/m, z0.d, z18.d \n\t"  \
    "fadd z6.d, p5/m, z6.d, z18.d \n\t"  \
    "fadd z1.d, p5/m, z1.d, z19.d \n\t"  \
    "fadd z7.d, p5/m, z7.d, z19.d \n\t"  \
    "fadd z2.d, p5/m, z2.d, z20.d \n\t"  \
    "fadd z8.d, p5/m, z8.d, z20.d \n\t"  \
    "fadd z3.d, p5/m, z3.d, z21.d \n\t"  \
    "fadd z9.d, p5/m, z9.d, z21.d \n\t"  \
    "fadd z4.d, p5/m, z4.d, z22.d \n\t"  \
    "fadd z10.d, p5/m, z10.d, z22.d \n\t"  \
    "fadd z5.d, p5/m, z5.d, z23.d \n\t"  \
    "fadd z11.d, p5/m, z11.d, z23.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// TM_RECON_ACCUM
#define TM_RECON_ACCUM_A64FXd  \
asm ( \
    "fadd z0.d, p5/m, z0.d, z18.d \n\t"  \
    "fsub z6.d, p5/m, z6.d, z18.d \n\t" \
    "fadd z1.d, p5/m, z1.d, z19.d \n\t"  \
    "fsub z7.d, p5/m, z7.d, z19.d \n\t" \
    "fadd z2.d, p5/m, z2.d, z20.d \n\t"  \
    "fsub z8.d, p5/m, z8.d, z20.d \n\t" \
    "fadd z3.d, p5/m, z3.d, z21.d \n\t"  \
    "fsub z9.d, p5/m, z9.d, z21.d \n\t" \
    "fadd z4.d, p5/m, z4.d, z22.d \n\t"  \
    "fsub z10.d, p5/m, z10.d, z22.d \n\t" \
    "fadd z5.d, p5/m, z5.d, z23.d \n\t"  \
    "fsub z11.d, p5/m, z11.d, z23.d \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// ZERO_PSI
#define ZERO_PSI_A64FXd  \
asm ( \
    "fmov z0.d , 0 \n\t" \
    "fmov z1.d , 0 \n\t" \
    "fmov z2.d , 0 \n\t" \
    "fmov z3.d , 0 \n\t" \
    "fmov z4.d , 0 \n\t" \
    "fmov z5.d , 0 \n\t" \
    "fmov z6.d , 0 \n\t" \
    "fmov z7.d , 0 \n\t" \
    "fmov z8.d , 0 \n\t" \
    "fmov z9.d , 0 \n\t" \
    "fmov z10.d , 0 \n\t" \
    "fmov z11.d , 0 \n\t" \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

// PREFETCH_RESULT_L2_STORE (uses DC ZVA for cache line zeroing)
#define PREFETCH_RESULT_L2_STORE_INTERNAL_A64FXd(base)  \
{ \
asm ( \
    "dc zva, %[fetchptr]\n\t" \
    "dc zva, %[fetchptr]\n\t" \
    "dc zva, %[fetchptr]\n\t" \
    :  \
    : [fetchptr] "r" (base) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// PREFETCH_RESULT_L1_STORE (prefetch store to L1)
#define PREFETCH_RESULT_L1_STORE_INTERNAL_A64FXd(base)  \
{ \
asm ( \
    "prfd PSTL1STRM, p5, [%[fetchptr], 0, mul vl] \n\t" \
    "prfd PSTL1STRM, p5, [%[fetchptr], 4, mul vl] \n\t" \
    "prfd PSTL1STRM, p5, [%[fetchptr], 8, mul vl] \n\t" \
    :  \
    : [fetchptr] "r" (base) \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31","memory" \
); \
}
// ADD_RESULT_INTERNAL
#define ADD_RESULT_INTERNAL_A64FXd  \
asm ( \
    "fadd z0.d, p5/m, z0.d, z12.d \n\t"  \
    "fadd z1.d, p5/m, z1.d, z13.d \n\t"  \
    "fadd z2.d, p5/m, z2.d, z14.d \n\t"  \
    "fadd z3.d, p5/m, z3.d, z15.d \n\t"  \
    "fadd z4.d, p5/m, z4.d, z16.d \n\t"  \
    "fadd z5.d, p5/m, z5.d, z17.d \n\t"  \
    "fadd z6.d, p5/m, z6.d, z18.d \n\t"  \
    "fadd z7.d, p5/m, z7.d, z19.d \n\t"  \
    "fadd z8.d, p5/m, z8.d, z20.d \n\t"  \
    "fadd z9.d, p5/m, z9.d, z21.d \n\t"  \
    "fadd z10.d, p5/m, z10.d, z22.d \n\t"  \
    "fadd z11.d, p5/m, z11.d, z23.d \n\t"  \
    :  \
    :  \
    : "p5","cc","z0","z1","z2","z3","z4","z5","z6","z7","z8","z9","z10","z11","z12","z13","z14","z15","z16","z17","z18","z19","z20","z21","z22","z23","z24","z25","z26","z27","z28","z29","z30","z31" \
); 

