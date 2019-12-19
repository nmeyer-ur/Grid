#ifndef SVE_ACLE_H
#define SVE_ACLE_H

#pragma message("include sve_acle.h")

// TODO use _x instead of _z in ACLE definitions !!!!
// TODO use matching types for predications

  /////////////////////////////////////////////////////
  // SVE ACLE
  /////////////////////////////////////////////////////
  template <typename T>
  struct acle{};

  template <>
  struct acle<double>{
    typedef svfloat64_t vt;
    typedef svfloat64x2_t vt2;
    typedef svfloat64x4_t vt4;
    typedef float64_t pt;
    typedef uint64_t uint;
    typedef svuint64_t svuint;

    //static inline svbool_t pg1(){return svptrue_b16();}
    static inline svbool_t pg1(){return svptrue_b64();}
    #if (GEN_SIMD_WIDTH == 64u)
    //static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL16);}
    static inline svbool_t pg2(){return svptrue_pat_b64(SV_VL4);}
    //static inline svbool_t pg4(){return svptrue_pat_b16(SV_VL8);}
    static inline svbool_t pg4(){return svptrue_pat_b64(SV_VL2);}
    // exchange neighboring elements
    static inline vec<uint64_t> tbl1(){
        const vec<uint64_t> t = {1, 0, 3, 2, 5, 4, 7, 6};
        return t;
    }
    #elif (GEN_SIMD_WIDTH == 32u)
    //static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL8);}
    static inline svbool_t pg2(){return svptrue_pat_b64(SV_VL2);}
    //static inline svbool_t pg4(){return svptrue_pat_b16(SV_VL4);}
    static inline svbool_t pg4(){return svptrue_pat_b64(SV_VL1);}
    #else
    static inline svbool_t pg2(){return svuzp1_b64(svptrue_b64(), svpfalse_b());}
    static inline svbool_t pg4(){return svwhilelt_b64((uint64_t)0, (uint64_t)(W<double>::c / 2u));}
    //static inline svbool_t pg4(){return svwhilelt_b16((uint64_t)0, (uint64_t)(4u * W<double>::c / 2u));}
    #endif
    //static inline svbool_t pg_even(){return svzip1_b16(svptrue_b16(), svpfalse_b());}
    //static inline svbool_t pg_odd() {return svzip1_b16(svpfalse_b(), svptrue_b16());}
    static inline svbool_t pg_even(){return svzip1_b64(svptrue_b64(), svpfalse_b());}
    static inline svbool_t pg_odd() {return svzip1_b64(svpfalse_b(), svptrue_b64());}
    static inline svfloat64_t zero(){return svdup_f64(0.);}
  };

  template <>
  struct acle<float>{
    typedef svfloat32_t vt;
    typedef svfloat32x2_t vt2;
    typedef float32_t pt;
    typedef uint32_t uint;
    typedef svuint32_t svuint;

    //static inline svbool_t pg1(){return svptrue_b16();}
    static inline svbool_t pg1(){return svptrue_b32();}
    #if (GEN_SIMD_WIDTH == 64u)
    //static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL16);}
    static inline svbool_t pg2(){return svptrue_pat_b32(SV_VL8);}
    // exchange neighboring elements
    static inline vec<uint32_t> tbl1(){
        const vec<uint32_t> t = {1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14};
        return t;
    }
    #elif (GEN_SIMD_WIDTH == 32u)
    //static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL8);}
    static inline svbool_t pg2(){return svptrue_pat_b32(SV_VL4);}
    #else
    //static inline svbool_t pg2(){return svuzp1_b16(svptrue_b16(), svpfalse_b());}
    static inline svbool_t pg2(){return svuzp1_b32(svptrue_b32(), svpfalse_b());}
    #endif
    static inline svbool_t pg_even(){return svzip1_b32(svptrue_b32(), svpfalse_b());}
    static inline svbool_t pg_odd() {return svzip1_b32(svpfalse_b(), svptrue_b32());}
    static inline svfloat32_t zero(){return svdup_f32(0.);}
  };

  template <>
  struct acle<uint16_t>{
    typedef svfloat16_t vt;
    typedef float16_t pt;
    typedef uint16_t uint;
    typedef svuint16_t svuint;

    static inline svbool_t pg1(){return svptrue_b16();}
    #if (GEN_SIMD_WIDTH == 64u)
    static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL16);}
    #elif (GEN_SIMD_WIDTH == 32u)
    static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL8);}
    #else
    static inline svbool_t pg2(){return svuzp1_b16(svptrue_b16(), svpfalse_b());}
    #endif
    static inline svbool_t pg_even(){return svzip1_b16(svptrue_b16(), svpfalse_b());}
    static inline svbool_t pg_odd() {return svzip1_b16(svpfalse_b(), svptrue_b16());}
    static inline svfloat16_t zero(){return svdup_f16(0.);}
  };

  template <>
  struct acle<Integer>{
    typedef svuint32_t vt;
    typedef svuint32x2_t vt2;
    typedef Integer pt;
    typedef uint32_t uint;
    typedef svuint32_t svuint;

    //static inline svbool_t pg1(){return svptrue_b16();}
    static inline svbool_t pg1(){return svptrue_b32();}
    #if (GEN_SIMD_WIDTH == 64u)
    //static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL16);}
    static inline svbool_t pg2(){return svptrue_pat_b32(SV_VL8);}
    #elif (GEN_SIMD_WIDTH == 32u)
    //static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL8);}
    static inline svbool_t pg2(){return svptrue_pat_b32(SV_VL4);}
    #else
    static inline svbool_t pg2(){return svuzp1_b16(svptrue_b32(), svpfalse_b());}
    #endif
    static inline svbool_t pg_even(){return svzip1_b32(svptrue_b32(), svpfalse_b());}
    static inline svbool_t pg_odd() {return svzip1_b32(svpfalse_b(), svptrue_b32());}
  };

#endif
