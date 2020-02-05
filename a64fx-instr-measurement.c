#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <complex.h>
#include <sys/time.h>

// ARM SVE
#ifdef __ARM_FEATURE_SVE
#ifdef __clang__
#include <arm_sve.h>
#endif
#else
#pragma error "Missing SVE feature"
#endif /* __ARM_FEATURE_SVE */


#define DEFAULT_NMAX (10000000ull)        // upper limit of array sizes
#define KERNELINSTR 32                        // instructions per kernel loop
#define FREQ 2.2                              // CPU frequency in GHz


// --- LD1D ---
static double ld1d_throughput(uint64_t R)
{
    double* a = (double *)aligned_alloc(128, 8*sizeof(double));

    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    asm volatile("ptrue   p5.d");

    unsigned long i;
    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z1.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z2.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z3.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z4.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z5.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z6.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z7.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z8.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z9.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z10.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z11.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z12.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z13.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z14.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z15.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z16.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z17.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z18.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z19.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z20.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z21.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z22.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z23.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z24.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z25.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z26.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z27.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z28.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z29.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z30.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z31.d, p5/z, [%[a], %[i], lsl #3]   "
            : [i] "=&r" (i)
            : "[i]" (0),
              [a] "r" (a)
            : "memory"
        );
    }

    gettimeofday(&tp, NULL);

    free(a);

    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double ld1d_latency(uint64_t R)
{
    double* a = (double *)aligned_alloc(128, 8*sizeof(double));

    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    asm volatile("ptrue   p5.d");

    unsigned long i;
    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   \n\
            ld1d z0.d, p5/z, [%[a], %[i], lsl #3]   "
            : [i] "=&r" (i)
            : "[i]" (0),
              [a] "r" (a)
            : "memory"
        );
    }

    gettimeofday(&tp, NULL);

    free(a);

    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

// --- ld2d ---
static double ld2d_throughput(uint64_t R)
{
    double* a = (double *)aligned_alloc(128, 2*8*sizeof(double));

    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    asm volatile("ptrue   p5.d");

    unsigned long i;
    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z3.d, z4.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z5.d, z6.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z7.d, z8.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z9.d, z10.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z11.d, z12.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z13.d, z14.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z15.d, z16.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z17.d, z18.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z19.d, z20.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z21.d, z22.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z23.d, z24.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z25.d, z26.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z27.d, z28.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z29.d, z30.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z3.d, z4.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z5.d, z6.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z7.d, z8.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z9.d, z10.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z11.d, z12.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z13.d, z14.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z15.d, z16.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z17.d, z18.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z19.d, z20.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z21.d, z22.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z23.d, z24.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z25.d, z26.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z27.d, z28.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z29.d, z30.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z3.d, z4.d }, p5/z, [%[a], %[i], lsl #3]   "
            : [i] "=&r" (i)
            : "[i]" (0),
              [a] "r" (a)
            : "memory"
        );
    }

    gettimeofday(&tp, NULL);

    free(a);

    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double ld2d_latency(uint64_t R)
{
    double* a = (double *)aligned_alloc(128, 2*8*sizeof(double));

    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    asm volatile("ptrue   p5.d");

    unsigned long i;
    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   \n\
            ld2d { z1.d, z2.d }, p5/z, [%[a], %[i], lsl #3]   "
            : [i] "=&r" (i)
            : "[i]" (0),
              [a] "r" (a)
            : "memory"
        );
    }

    gettimeofday(&tp, NULL);

    free(a);

    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

// --- FADD ---
static double fadd_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z1.d, p0/m, z1.d, z1.d");
        asm volatile("fadd   z2.d, p0/m, z2.d, z2.d");
        asm volatile("fadd   z3.d, p0/m, z3.d, z3.d");
        asm volatile("fadd   z4.d, p0/m, z4.d, z4.d");
        asm volatile("fadd   z5.d, p0/m, z5.d, z5.d");
        asm volatile("fadd   z6.d, p0/m, z6.d, z6.d");
        asm volatile("fadd   z7.d, p0/m, z7.d, z7.d");
        asm volatile("fadd   z8.d, p0/m, z8.d, z8.d");
        asm volatile("fadd   z9.d, p0/m, z9.d, z9.d");
        asm volatile("fadd   z10.d, p0/m, z10.d, z10.d");
        asm volatile("fadd   z11.d, p0/m, z11.d, z11.d");
        asm volatile("fadd   z12.d, p0/m, z12.d, z12.d");
        asm volatile("fadd   z13.d, p0/m, z13.d, z13.d");
        asm volatile("fadd   z14.d, p0/m, z14.d, z14.d");
        asm volatile("fadd   z15.d, p0/m, z15.d, z15.d");
        asm volatile("fadd   z16.d, p0/m, z16.d, z16.d");
        asm volatile("fadd   z17.d, p0/m, z17.d, z17.d");
        asm volatile("fadd   z18.d, p0/m, z18.d, z18.d");
        asm volatile("fadd   z19.d, p0/m, z19.d, z19.d");
        asm volatile("fadd   z20.d, p0/m, z20.d, z20.d");
        asm volatile("fadd   z21.d, p0/m, z21.d, z21.d");
        asm volatile("fadd   z22.d, p0/m, z22.d, z22.d");
        asm volatile("fadd   z23.d, p0/m, z23.d, z23.d");
        asm volatile("fadd   z24.d, p0/m, z24.d, z24.d");
        asm volatile("fadd   z25.d, p0/m, z25.d, z25.d");
        asm volatile("fadd   z26.d, p0/m, z26.d, z26.d");
        asm volatile("fadd   z27.d, p0/m, z27.d, z27.d");
        asm volatile("fadd   z28.d, p0/m, z28.d, z28.d");
        asm volatile("fadd   z29.d, p0/m, z29.d, z29.d");
        asm volatile("fadd   z30.d, p0/m, z30.d, z30.d");
        asm volatile("fadd   z31.d, p0/m, z31.d, z31.d");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double fadd_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fadd   z0.d, p0/m, z0.d, z0.d");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

// --- FMUL ---
static double fmul_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z1.d, p0/m, z1.d, z1.d");
        asm volatile("fmul   z2.d, p0/m, z2.d, z2.d");
        asm volatile("fmul   z3.d, p0/m, z3.d, z3.d");
        asm volatile("fmul   z4.d, p0/m, z4.d, z4.d");
        asm volatile("fmul   z5.d, p0/m, z5.d, z5.d");
        asm volatile("fmul   z6.d, p0/m, z6.d, z6.d");
        asm volatile("fmul   z7.d, p0/m, z7.d, z7.d");
        asm volatile("fmul   z8.d, p0/m, z8.d, z8.d");
        asm volatile("fmul   z9.d, p0/m, z9.d, z9.d");
        asm volatile("fmul   z10.d, p0/m, z10.d, z10.d");
        asm volatile("fmul   z11.d, p0/m, z11.d, z11.d");
        asm volatile("fmul   z12.d, p0/m, z12.d, z12.d");
        asm volatile("fmul   z13.d, p0/m, z13.d, z13.d");
        asm volatile("fmul   z14.d, p0/m, z14.d, z14.d");
        asm volatile("fmul   z15.d, p0/m, z15.d, z15.d");
        asm volatile("fmul   z16.d, p0/m, z16.d, z16.d");
        asm volatile("fmul   z17.d, p0/m, z17.d, z17.d");
        asm volatile("fmul   z18.d, p0/m, z18.d, z18.d");
        asm volatile("fmul   z19.d, p0/m, z19.d, z19.d");
        asm volatile("fmul   z20.d, p0/m, z20.d, z20.d");
        asm volatile("fmul   z21.d, p0/m, z21.d, z21.d");
        asm volatile("fmul   z22.d, p0/m, z22.d, z22.d");
        asm volatile("fmul   z23.d, p0/m, z23.d, z23.d");
        asm volatile("fmul   z24.d, p0/m, z24.d, z24.d");
        asm volatile("fmul   z25.d, p0/m, z25.d, z25.d");
        asm volatile("fmul   z26.d, p0/m, z26.d, z26.d");
        asm volatile("fmul   z27.d, p0/m, z27.d, z27.d");
        asm volatile("fmul   z28.d, p0/m, z28.d, z28.d");
        asm volatile("fmul   z29.d, p0/m, z29.d, z29.d");
        asm volatile("fmul   z30.d, p0/m, z30.d, z30.d");
        asm volatile("fmul   z31.d, p0/m, z31.d, z31.d");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double fmul_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmul   z0.d, p0/m, z0.d, z0.d");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

// --- FMLA ---
static double fmla_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fmla   z16.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z1.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z2.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z3.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z4.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z5.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z6.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z7.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z8.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z9.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z10.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z11.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z12.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z13.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z14.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z15.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z16.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z17.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z18.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z19.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z20.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z21.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z22.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z23.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z24.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z25.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z26.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z27.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z28.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z29.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z30.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z31.d, p0/m, z0.d, z0.d");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double fmla_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");

        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
        asm volatile("fmla   z0.d, p0/m, z0.d, z0.d");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

// --- FCMLA ---
static double fcmla_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z1.d, p0/m, z1.d, z1.d, #0");
        asm volatile("fcmla   z2.d, p0/m, z2.d, z2.d, #0");
        asm volatile("fcmla   z3.d, p0/m, z3.d, z3.d, #0");
        asm volatile("fcmla   z4.d, p0/m, z4.d, z5.d, #0");
        asm volatile("fcmla   z5.d, p0/m, z5.d, z5.d, #0");
        asm volatile("fcmla   z6.d, p0/m, z6.d, z6.d, #0");
        asm volatile("fcmla   z7.d, p0/m, z7.d, z7.d, #0");
        asm volatile("fcmla   z8.d, p0/m, z8.d, z8.d, #0");
        asm volatile("fcmla   z9.d, p0/m, z9.d, z9.d, #0");
        asm volatile("fcmla   z10.d, p0/m, z10.d, z10.d, #0");
        asm volatile("fcmla   z11.d, p0/m, z11.d, z11.d, #0");
        asm volatile("fcmla   z12.d, p0/m, z12.d, z12.d, #0");
        asm volatile("fcmla   z13.d, p0/m, z13.d, z13.d, #0");
        asm volatile("fcmla   z14.d, p0/m, z14.d, z14.d, #0");
        asm volatile("fcmla   z15.d, p0/m, z15.d, z15.d, #0");

        asm volatile("fcmla   z16.d, p0/m, z16.d, z16.d, #0");
        asm volatile("fcmla   z17.d, p0/m, z17.d, z17.d, #0");
        asm volatile("fcmla   z18.d, p0/m, z18.d, z18.d, #0");
        asm volatile("fcmla   z19.d, p0/m, z19.d, z19.d, #0");
        asm volatile("fcmla   z20.d, p0/m, z20.d, z20.d, #0");
        asm volatile("fcmla   z21.d, p0/m, z21.d, z21.d, #0");
        asm volatile("fcmla   z22.d, p0/m, z22.d, z22.d, #0");
        asm volatile("fcmla   z23.d, p0/m, z23.d, z23.d, #0");
        asm volatile("fcmla   z24.d, p0/m, z24.d, z24.d, #0");
        asm volatile("fcmla   z25.d, p0/m, z25.d, z25.d, #0");
        asm volatile("fcmla   z26.d, p0/m, z26.d, z26.d, #0");
        asm volatile("fcmla   z27.d, p0/m, z27.d, z27.d, #0");
        asm volatile("fcmla   z28.d, p0/m, z28.d, z28.d, #0");
        asm volatile("fcmla   z29.d, p0/m, z29.d, z29.d, #0");
        asm volatile("fcmla   z30.d, p0/m, z30.d, z30.d, #0");
        asm volatile("fcmla   z31.d, p0/m, z31.d, z31.d, #0");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double fcmla_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");

        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #90");
        asm volatile("fcmla   z0.d, p0/m, z0.d, z0.d, #0");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

// --- FNEG ---
static double fneg_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z1.d, p0/m, z1.d");
        asm volatile("fneg   z2.d, p0/m, z2.d");
        asm volatile("fneg   z3.d, p0/m, z3.d");
        asm volatile("fneg   z4.d, p0/m, z4.d");
        asm volatile("fneg   z5.d, p0/m, z5.d");
        asm volatile("fneg   z6.d, p0/m, z6.d");
        asm volatile("fneg   z7.d, p0/m, z7.d");
        asm volatile("fneg   z8.d, p0/m, z8.d");
        asm volatile("fneg   z9.d, p0/m, z9.d");
        asm volatile("fneg   z10.d, p0/m, z10.d");
        asm volatile("fneg   z11.d, p0/m, z11.d");
        asm volatile("fneg   z12.d, p0/m, z12.d");
        asm volatile("fneg   z13.d, p0/m, z13.d");
        asm volatile("fneg   z14.d, p0/m, z14.d");
        asm volatile("fneg   z15.d, p0/m, z15.d");
        asm volatile("fneg   z16.d, p0/m, z16.d");
        asm volatile("fneg   z17.d, p0/m, z17.d");
        asm volatile("fneg   z18.d, p0/m, z18.d");
        asm volatile("fneg   z19.d, p0/m, z19.d");
        asm volatile("fneg   z20.d, p0/m, z20.d");
        asm volatile("fneg   z21.d, p0/m, z21.d");
        asm volatile("fneg   z22.d, p0/m, z22.d");
        asm volatile("fneg   z23.d, p0/m, z23.d");
        asm volatile("fneg   z24.d, p0/m, z24.d");
        asm volatile("fneg   z25.d, p0/m, z25.d");
        asm volatile("fneg   z26.d, p0/m, z26.d");
        asm volatile("fneg   z27.d, p0/m, z27.d");
        asm volatile("fneg   z28.d, p0/m, z28.d");
        asm volatile("fneg   z29.d, p0/m, z29.d");
        asm volatile("fneg   z30.d, p0/m, z30.d");
        asm volatile("fneg   z31.d, p0/m, z31.d");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double fneg_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
        asm volatile("fneg   z0.d, p0/m, z0.d");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}



// --- FADDA ---
/*
static double fadda_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fadda   d15, p0, z0.d");
        asm volatile("fadda   d15, p0, z1.d");
        asm volatile("fadda   d15, p0, z2.d");
        asm volatile("fadda   d15, p0, z3.d");
        asm volatile("fadda   d15, p0, z4.d");
        asm volatile("fadda   d15, p0, z5.d");
        asm volatile("fadda   d15, p0, z6.d");
        asm volatile("fadda   d15, p0, z7.d");
        asm volatile("fadda   d15, p0, z8.d");
        asm volatile("fadda   d15, p0, z9.d");
        asm volatile("fadda   d15, p0, z10.d");
        asm volatile("fadda   d15, p0, z11.d");
        asm volatile("fadda   d15, p0, z12.d");
        asm volatile("fadda   d15, p0, z13.d");
        asm volatile("fadda   d15, p0, z14.d");
        asm volatile("fadda   d15, p0, z15.d");
        asm volatile("fadda   d15, p0, z16.d");
        asm volatile("fadda   d15, p0, z17.d");
        asm volatile("fadda   d15, p0, z18.d");
        asm volatile("fadda   d15, p0, z19.d");
        asm volatile("fadda   d15, p0, z20.d");
        asm volatile("fadda   d15, p0, z21.d");
        asm volatile("fadda   d15, p0, z22.d");
        asm volatile("fadda   d15, p0, z23.d");
        asm volatile("fadda   d15, p0, z24.d");
        asm volatile("fadda   d15, p0, z25.d");
        asm volatile("fadda   d15, p0, z26.d");
        asm volatile("fadda   d15, p0, z27.d");
        asm volatile("fadda   d15, p0, z28.d");
        asm volatile("fadda   d15, p0, z29.d");
        asm volatile("fadda   d15, p0, z30.d");
        asm volatile("fadda   d15, p0, z31.d");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double fadda_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("fadda   d15, p0, z0.d");
        asm volatile("dup     z0.d, d15");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}
*/



// --- ZIP ---
static double zip_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z1.d, z1.d, z1.d");
        asm volatile("zip1   z2.d, z2.d, z2.d");
        asm volatile("zip1   z3.d, z3.d, z3.d");
        asm volatile("zip1   z4.d, z4.d, z4.d");
        asm volatile("zip1   z5.d, z5.d, z5.d");
        asm volatile("zip1   z6.d, z6.d, z6.d");
        asm volatile("zip1   z7.d, z7.d, z7.d");
        asm volatile("zip1   z8.d, z8.d, z8.d");
        asm volatile("zip1   z9.d, z9.d, z9.d");
        asm volatile("zip1   z10.d, z10.d, z10.d");
        asm volatile("zip1   z11.d, z11.d, z11.d");
        asm volatile("zip1   z12.d, z12.d, z12.d");
        asm volatile("zip1   z13.d, z13.d, z13.d");
        asm volatile("zip1   z14.d, z14.d, z14.d");
        asm volatile("zip1   z15.d, z15.d, z15.d");
        asm volatile("zip1   z16.d, z16.d, z16.d");
        asm volatile("zip1   z17.d, z17.d, z17.d");
        asm volatile("zip1   z18.d, z18.d, z18.d");
        asm volatile("zip1   z19.d, z19.d, z19.d");
        asm volatile("zip1   z20.d, z20.d, z20.d");
        asm volatile("zip1   z21.d, z21.d, z21.d");
        asm volatile("zip1   z22.d, z22.d, z22.d");
        asm volatile("zip1   z23.d, z23.d, z23.d");
        asm volatile("zip1   z24.d, z24.d, z24.d");
        asm volatile("zip1   z25.d, z25.d, z25.d");
        asm volatile("zip1   z26.d, z26.d, z26.d");
        asm volatile("zip1   z27.d, z27.d, z27.d");
        asm volatile("zip1   z28.d, z28.d, z28.d");
        asm volatile("zip1   z29.d, z29.d, z29.d");
        asm volatile("zip1   z30.d, z30.d, z30.d");
        asm volatile("zip1   z31.d, z31.d, z31.d");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double zip_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
        asm volatile("zip1   z0.d, z0.d, z0.d");
    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

// --- TRN ---
static double trn_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z1.d, z1.d, z1.d");
        asm volatile("trn1   z2.d, z2.d, z2.d");
        asm volatile("trn1   z3.d, z3.d, z3.d");
        asm volatile("trn1   z4.d, z4.d, z4.d");
        asm volatile("trn1   z5.d, z5.d, z5.d");
        asm volatile("trn1   z6.d, z6.d, z6.d");
        asm volatile("trn1   z7.d, z7.d, z7.d");

        asm volatile("trn1   z8.d, z8.d, z8.d");
        asm volatile("trn1   z9.d, z9.d, z9.d");
        asm volatile("trn1   z10.d, z10.d, z10.d");
        asm volatile("trn1   z11.d, z11.d, z11.d");
        asm volatile("trn1   z12.d, z12.d, z12.d");
        asm volatile("trn1   z13.d, z13.d, z13.d");
        asm volatile("trn1   z14.d, z14.d, z14.d");
        asm volatile("trn1   z15.d, z15.d, z15.d");

        asm volatile("trn1   z16.d, z16.d, z16.d");
        asm volatile("trn1   z17.d, z17.d, z17.d");
        asm volatile("trn1   z18.d, z18.d, z18.d");
        asm volatile("trn1   z19.d, z19.d, z19.d");
        asm volatile("trn1   z20.d, z20.d, z20.d");
        asm volatile("trn1   z21.d, z21.d, z21.d");
        asm volatile("trn1   z22.d, z22.d, z22.d");
        asm volatile("trn1   z23.d, z23.d, z23.d");

        asm volatile("trn1   z24.d, z24.d, z24.d");
        asm volatile("trn1   z25.d, z25.d, z25.d");
        asm volatile("trn1   z26.d, z26.d, z26.d");
        asm volatile("trn1   z27.d, z27.d, z27.d");
        asm volatile("trn1   z28.d, z28.d, z28.d");
        asm volatile("trn1   z29.d, z29.d, z29.d");
        asm volatile("trn1   z30.d, z30.d, z30.d");
        asm volatile("trn1   z31.d, z31.d, z31.d");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double trn_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");

        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");
        asm volatile("trn1   z0.d, z0.d, z0.d");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

// --- EXT ---
static double ext_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z1.b, z1.b, z1.b, #32");
        asm volatile("ext   z2.b, z2.b, z2.b, #32");
        asm volatile("ext   z3.b, z3.b, z3.b, #32");
        asm volatile("ext   z4.b, z4.b, z4.b, #32");
        asm volatile("ext   z5.b, z5.b, z5.b, #32");
        asm volatile("ext   z6.b, z6.b, z6.b, #32");
        asm volatile("ext   z7.b, z7.b, z7.b, #32");

        asm volatile("ext   z8.b, z8.b, z8.b, #32");
        asm volatile("ext   z9.b, z9.b, z9.b, #32");
        asm volatile("ext   z10.b, z10.b, z10.b, #32");
        asm volatile("ext   z11.b, z11.b, z11.b, #32");
        asm volatile("ext   z12.b, z12.b, z12.b, #32");
        asm volatile("ext   z13.b, z13.b, z13.b, #32");
        asm volatile("ext   z14.b, z14.b, z14.b, #32");
        asm volatile("ext   z15.b, z15.b, z15.b, #32");

        asm volatile("ext   z16.b, z16.b, z16.b, #32");
        asm volatile("ext   z17.b, z17.b, z17.b, #32");
        asm volatile("ext   z18.b, z18.b, z18.b, #32");
        asm volatile("ext   z19.b, z19.b, z19.b, #32");
        asm volatile("ext   z20.b, z20.b, z20.b, #32");
        asm volatile("ext   z21.b, z21.b, z21.b, #32");
        asm volatile("ext   z22.b, z22.b, z22.b, #32");
        asm volatile("ext   z23.b, z23.b, z23.b, #32");

        asm volatile("ext   z24.b, z24.b, z24.b, #32");
        asm volatile("ext   z25.b, z25.b, z25.b, #32");
        asm volatile("ext   z26.b, z26.b, z26.b, #32");
        asm volatile("ext   z27.b, z27.b, z27.b, #32");
        asm volatile("ext   z28.b, z28.b, z28.b, #32");
        asm volatile("ext   z29.b, z29.b, z29.b, #32");
        asm volatile("ext   z30.b, z30.b, z30.b, #32");
        asm volatile("ext   z31.b, z31.b, z31.b, #32");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double ext_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");

        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");
        asm volatile("ext   z0.b, z0.b, z0.b, #32");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}


// --- TBL ---
static double tbl_throughput(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("tbl   z16.d, z0.d, z0.d");
        asm volatile("tbl   z1.d, z0.d, z0.d");
        asm volatile("tbl   z2.d, z0.d, z0.d");
        asm volatile("tbl   z3.d, z0.d, z0.d");
        asm volatile("tbl   z4.d, z0.d, z0.d");
        asm volatile("tbl   z5.d, z0.d, z0.d");
        asm volatile("tbl   z6.d, z0.d, z0.d");
        asm volatile("tbl   z7.d, z0.d, z0.d");
        asm volatile("tbl   z8.d, z0.d, z0.d");
        asm volatile("tbl   z9.d, z0.d, z0.d");
        asm volatile("tbl   z10.d, z0.d, z0.d");
        asm volatile("tbl   z11.d, z0.d, z0.d");
        asm volatile("tbl   z12.d, z0.d, z0.d");
        asm volatile("tbl   z13.d, z0.d, z0.d");
        asm volatile("tbl   z14.d, z0.d, z0.d");
        asm volatile("tbl   z15.d, z0.d, z0.d");
        asm volatile("tbl   z16.d, z0.d, z0.d");
        asm volatile("tbl   z17.d, z0.d, z0.d");
        asm volatile("tbl   z18.d, z0.d, z0.d");
        asm volatile("tbl   z19.d, z0.d, z0.d");
        asm volatile("tbl   z20.d, z0.d, z0.d");
        asm volatile("tbl   z21.d, z0.d, z0.d");
        asm volatile("tbl   z22.d, z0.d, z0.d");
        asm volatile("tbl   z23.d, z0.d, z0.d");
        asm volatile("tbl   z24.d, z0.d, z0.d");
        asm volatile("tbl   z25.d, z0.d, z0.d");
        asm volatile("tbl   z26.d, z0.d, z0.d");
        asm volatile("tbl   z27.d, z0.d, z0.d");
        asm volatile("tbl   z28.d, z0.d, z0.d");
        asm volatile("tbl   z29.d, z0.d, z0.d");
        asm volatile("tbl   z30.d, z0.d, z0.d");
        asm volatile("tbl   z31.d, z0.d, z0.d");


    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}

static double tbl_latency(uint64_t R)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    double elaps = -(double)(tp.tv_sec + tp.tv_usec/1000000.0);

    for(uint64_t j=0; j<R; ++j)
    {
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");

        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");

        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");

        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");

        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");

        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");

        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");

        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");
        asm volatile("tbl   z0.d, z0.d, z0.d");

    }

    gettimeofday(&tp, NULL);
    return (elaps + ((double)(tp.tv_sec + tp.tv_usec/1000000.0)));
}


void display(uint64_t R, double elaps, char* name)
{
    printf("=========================================================\n");
    printf("%s\n", name);
    printf("=========================================================\n");
    printf("Runtime = %lf s\n", elaps);

    double cycles = elaps * (1e9 * FREQ);
    printf("Cycles = %lf\n", cycles);

    double ipc = (R * KERNELINSTR) / cycles;
    printf("Instructions per cycle  = %lf\n", ipc);
    printf("Cycles per instruction  = %lf\n", 1/ipc);
}

int main(int argc, char* argv[])
{
    const uint64_t R = argc > 1 ? atoll(argv[1]) : DEFAULT_NMAX;

    double elaps = 0.;

    printf("#kernel instructions = %d\n", KERNELINSTR);
    printf("N = %" PRIu64 "\n", R);
    printf("Total instruction count each (negl. loop overhead) = %" PRIu64 "\n", R * KERNELINSTR);

    // warm up
    elaps = fmla_throughput(R);
    elaps = fmla_throughput(R);
    elaps = fmla_throughput(R);

    // measurement
    elaps = ld1d_throughput(R);
    display(R, elaps, "LD1D throughput");

    elaps = ld1d_latency(R);
    display(R, elaps, "LD1D latency");

    elaps = ld2d_throughput(R);
    display(R, elaps, "LD2D throughput");

    elaps = ld2d_latency(R);
    display(R, elaps, "LD2D latency");

    elaps = fadd_throughput(R);
    display(R, elaps, "FADD throughput");

    elaps = fadd_latency(R);
    display(R, elaps, "FADD latency");

    elaps = fmul_throughput(R);
    display(R, elaps, "FMUL throughput");

    elaps = fmul_latency(R);
    display(R, elaps, "FMUL latency");

    elaps = fmla_throughput(R);
    display(R, elaps, "FMLA throughput");

    elaps = fmla_latency(R);
    display(R, elaps, "FMLA latency");

    elaps = fcmla_throughput(R);
    display(R, elaps, "FCMLA throughput");

    elaps = fcmla_latency(R);
    display(R, elaps, "FCMLA latency");

    elaps = fneg_throughput(R);
    display(R, elaps, "FNEG throughput");

    elaps = fneg_latency(R);
    display(R, elaps, "FNEG latency");
/*
    elaps = fadda_throughput(R);
    display(R, elaps, "FADDA throughput");

    elaps = fadda_latency(R);
    display(R, elaps, "FADDA latency (incl. DUP from scalar to vector)");
*/
    elaps = zip_throughput(R);
    display(R, elaps, "ZIP throughput");

    elaps = zip_latency(R);
    display(R, elaps, "ZIP latency");

    elaps = trn_throughput(R);
    display(R, elaps, "TRN throughput");

    elaps = trn_latency(R);
    display(R, elaps, "TRN latency");

    elaps = ext_throughput(R);
    display(R, elaps, "EXT throughput");

    elaps = ext_latency(R);
    display(R, elaps, "EXT latency");

    elaps = tbl_throughput(R);
    display(R, elaps, "TBL throughput");

    elaps = tbl_latency(R);
    display(R, elaps, "TBL latency");

    return 0;
}
