

/////////////////////////////////////////////////////
// SVE ACLE
/////////////////////////////////////////////////////

#ifdef __ARM_FEATURE_SVE
  #ifdef __clang__
    #include <arm_sve.h>
  #endif
#else
  #pragma error "Missing SVE feature"
#endif /* __ARM_FEATURE_SVE */

#include "Grid_generic_types.h"

namespace Grid {
namespace Optimization {

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

  static inline svbool_t pg1(){return svptrue_b64();}
  static inline svbool_t pg2(){return svptrue_pat_b64(SV_VL4);}
  static inline svbool_t pg4(){return svptrue_pat_b64(SV_VL2);}
  static inline vec<uint64_t> tbl_swap(){
      const vec<uint64_t> t = {1, 0, 3, 2, 5, 4, 7, 6};
      return t;
  }
  static inline vec<uint64_t> tbl0(){
      const vec<uint64_t> t = {4, 5, 6, 7, 0, 1, 2, 3};
      return t;
  }
  static inline vec<uint64_t> tbl1(){
      const vec<uint64_t> t = {2, 3, 0, 1, 6, 7, 4, 5};
      return t;
  }
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

  static inline svbool_t pg1(){return svptrue_b32();}
  static inline svbool_t pg2(){return svptrue_pat_b32(SV_VL8);}
  // exchange neighboring elements
  static inline vec<uint32_t> tbl_swap(){
      const vec<uint32_t> t = {1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14};
      return t;
  }
  static inline vec<uint32_t> tbl0(){
      const vec<uint32_t> t = {8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7};
      return t;
  }
  static inline vec<uint32_t> tbl1(){
      const vec<uint32_t> t = {4, 5, 6, 7, 0, 1, 2, 3, 12, 13, 14, 15, 8, 9, 10, 11};
      return t;
  }
  static inline vec<uint32_t> tbl2(){
      const vec<uint32_t> t = {2, 3, 0, 1, 6, 7, 4, 5, 10, 11, 8, 9, 14, 15, 12, 13};
      return t;
  }
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
  static inline svbool_t pg2(){return svptrue_pat_b16(SV_VL16);}
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
  static inline svbool_t pg2(){return svptrue_pat_b32(SV_VL8);}
  static inline svbool_t pg_even(){return svzip1_b32(svptrue_b32(), svpfalse_b());}
  static inline svbool_t pg_odd() {return svzip1_b32(svpfalse_b(), svptrue_b32());}
};

// ---------------------------------------------------

struct Vsplat{
  // Complex float
  inline vec<float> operator()(vec<float> a, vec<float> b){

    vec<float> out;
    svbool_t pg1 = acle<float>::pg1();
    typename acle<float>::vt a_v = svdup_f32(a);
    typename acle<float>::vt b_v = svdup_f32(b);
    typename acle<float>::vt r_v = svzip1(a_v, b_v);
    svst1(pg1, out.v, r_v);
    return out;
  }

  // Real float
  inline vec<float> operator()(vec<float> a){

    vec<float> out;
    svbool_t pg1 = acle<float>::pg1();
    typename acle<float>::vt r_v = svdup_f32(a);
    svst1(pg1, out.v, r_v);
    return out;
  }

 // Complex double
  inline vec<double> operator()(vec<double> a, vec<double> b){

    vec<double> out;
    svbool_t pg1 = acle<double>::pg1();
    typename acle<double>::vt a_v = svdup_f64(a);
    typename acle<double>::vt b_v = svdup_f64(b);
    typename acle<double>::vt r_v = svzip1(a_v, b_v);
    svst1(pg1, out.v, r_v);
    return out;
  }

  // Real double
  inline vec<double> operator()(vec<double> a){

    vec<double> out;
    svbool_t pg1 = acle<double>::pg1();
    typename acle<double>::vt r_v = svdup_f64(a);
    svst1(pg1, out.v, r_v);
    return out;
  }

  // Integer
  inline vec<Integer> operator()(vec<Integer> a){

    vec<Integer> out;
    svbool_t pg1 = acle<Integer>::pg1();
    // Add check whether Integer is really a uint32_t???
    typename acle<Integer>::vt r_v = svdup_u32(a);
    svst1(pg1, out.v, r_v);
    return out;
  }
};

  struct Vstore{
    // Real
    template <typename T>
    inline void operator()(vec<T> a, T *D){

      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, (typename acle<T>::pt*)&a.v);
    // NOTE illegal '&' here causes SIGBUS at runtime, related to  CAS-35230-H2H6T1
      // svst1(pg1, (typename acle<T>::pt*)&D, a_v);
      svst1(pg1, D, a_v);

      // non temporal version TO INTEGRATED
      //svstnt1(pg1, D, a_v);
    }
  };

  struct Vstream{
    // Real
    template <typename T>
    inline void operator()(T * a, vec<T> b){

      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      // FIXME non-temporal store causes compiler crash  CAS-35230-H2H6T1
      svstnt1(pg1, a, b_v);
      //svst1(pg1, a, b_v);
    }
  };

  struct Vset{
    // Complex
    template <typename T>
    inline vec<T> operator()(std::complex<T> *a){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, (T*)a);
      svst1(pg1, out.v, a_v);

      return out;
    }

    // Real
    template <typename T>
    inline vec<T> operator()(T *a){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a);
      svst1(pg1, out.v, a_v);

      return out;
    }
  };

  /////////////////////////////////////////////////////
  // Arithmetic operations
  /////////////////////////////////////////////////////


  struct Sum{
    template <typename T>
    inline vec<T> operator()(vec<T> a, vec<T> b){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      typename acle<T>::vt r_v = svadd_x(pg1, a_v, b_v);
      svst1(pg1, out.v, r_v);

      return out;
    }


  struct Sub{
    template <typename T>
    inline vec<T> operator()(vec<T> a, vec<T> b){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      typename acle<T>::vt r_v = svsub_x(pg1, a_v, b_v);
      svst1(pg1, out.v, r_v);

      return out;
    }
  };


struct Mult{
  template <typename T>
  inline vec<T> operator()(vec<T> a, vec<T> b){

    vec<T> out;
    svbool_t pg1 = acle<T>::pg1();
    typename acle<T>::vt a_v = svld1(pg1, a.v);
    typename acle<T>::vt b_v = svld1(pg1, b.v);
    typename acle<T>::vt r_v = svmul_x(pg1, a_v, b_v);
    svst1(pg1, out.v, r_v);

    return out;
  }
};

struct MultRealPart{
  template <typename T>
  inline vec<T> operator()(vec<T> a, vec<T> b){

    vec<T> out;
    svbool_t pg1 = acle<T>::pg1();
    typename acle<T>::vt a_v  = svld1(pg1, a.v);
    typename acle<T>::vt b_v  = svld1(pg1, b.v);

    // using FCMLA
    typename acle<T>::vt z_v = acle<T>::zero();
    typename acle<T>::vt r_v = svcmla_x(pg1, z_v, a_v, b_v, 0);

    svst1(pg1, out.v, r_v);

    return out;
  }
};

struct MaddRealPart{
  template <typename T>
  inline vec<T> operator()(vec<T> a, vec<T> b, vec<T> c){

    vec<T> out;
    svbool_t pg1 = acle<T>::pg1();
    typename acle<T>::vt a_v  = svld1(pg1, a.v);
    typename acle<T>::vt b_v  = svld1(pg1, b.v);
    typename acle<T>::vt c_v  = svld1(pg1, c.v);

    // using FCMLA
    typename acle<T>::vt r_v = svcmla_x(pg1, c_v, a_v, b_v, 0);

    svst1(pg1, out.v, r_v);

    return out;
  }
};

struct MultComplex{
  // Complex a*b
  template <typename T>
  inline vec<T> operator()(vec<T> a, vec<T> b){

    vec<T> out;
    svbool_t pg1 = acle<T>::pg1();
    typename acle<T>::vt a_v = svld1(pg1, a.v);
    typename acle<T>::vt b_v = svld1(pg1, b.v);
    typename acle<T>::vt z_v = __svzero(z_v);

    // using FCMLA
    typename acle<T>::vt r_v = svcmla_x(pg1, z_v, a_v, b_v, 90);
    r_v = svcmla_x(pg1, r_v, a_v, b_v, 0);

    svst1(pg1, out.v, r_v);

    return out;
  }
};

struct Div{
  // Real
  template <typename T>
  inline vec<T> operator()(vec<T> a, vec<T> b){

    vec<T> out;
    svbool_t pg1 = acle<T>::pg1();
    typename acle<T>::vt a_v = svld1(pg1, a.v);
    typename acle<T>::vt b_v = svld1(pg1, b.v);
    typename acle<T>::vt r_v = svdiv_x(pg1, a_v, b_v);
    svst1(pg1, out.v, r_v);

    return out;
  }
};

struct Conj{
  // Complex
  template <typename T>
  inline vec<T> operator()(const vec<T> &a){

    vec<T> out;
    svbool_t pg1 = acle<T>::pg1();
    svbool_t pg_odd = acle<T>::pg_odd();
    typename acle<T>::vt a_v = svld1(pg1, a.v);
    typename acle<T>::vt r_v = svneg_x(pg_odd, a_v);
    svst1(pg1, out.v, r_v);

    return out;
  }
};


  struct TimesMinusI{
    // Complex
    template <typename T>
    inline vec<T> operator()(vec<T> a, vec<T> b){

      vec<T> out;
      const vec<typename acle<T>::uint> tbl_swap = acle<T>::tbl_swap();
      svbool_t pg1 = acle<T>::pg1();
      svbool_t pg_odd = acle<T>::pg_odd();

      typename acle<T>::svuint tbl_swap_v = svld1(pg1, tbl_swap.v);
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      a_v = svtbl(a_v, tbl_swap_v);
      typename acle<T>::vt r_v = svneg_x(pg_odd, a_v);
      svst1(pg1, out.v, r_v);

      return out;
    }
  };

  struct TimesI{
    // Complex
    template <typename T>
    inline vec<T> operator()(vec<T> a, vec<T> b){

      vec<T> out;
      const vec<typename acle<T>::uint> tbl_swap = acle<T>::tbl_swap();
      svbool_t pg1 = acle<T>::pg1();
      svbool_t pg_even = acle<T>::pg_even();

      typename acle<T>::svuint tbl_swap_v = svld1(pg1, tbl_swap.v);
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      a_v = svtbl(a_v, tbl_swap_v);
      typename acle<T>::vt r_v = svneg_x(pg_even, a_v);
      svst1(pg1, out.v, r_v);

      return out;
    }
  };


    struct PrecisionChange {
      static inline vech StoH (const vecf &sa,const vecf &sb) {

        vech ret;
        svbool_t pg1s = acle<float>::pg1();
        svbool_t pg1h = acle<uint16_t>::pg1();
        typename acle<float>::vt sa_v = svld1(pg1s, sa.v);
        typename acle<float>::vt sb_v = svld1(pg1s, sb.v);
        typename acle<uint16_t>::vt ha_v = svcvt_f16_x(pg1s, sa_v);
        typename acle<uint16_t>::vt hb_v = svcvt_f16_x(pg1s, sb_v);
        typename acle<uint16_t>::vt r_v = svuzp1(ha_v, hb_v);
        svst1(pg1h, (typename acle<uint16_t>::pt*)&ret.v, r_v);
        return ret;
      }
      static inline void HtoS(vech h,vecf &sa,vecf &sb) {

        svbool_t pg1h = acle<uint16_t>::pg1();
        svbool_t pg1s = acle<float>::pg1();
        typename acle<uint16_t>::vt h_v = svld1(pg1h, (typename acle<uint16_t>::pt*)&h.v);
        typename acle<uint16_t>::vt ha_v = svzip1(h_v, h_v);
        typename acle<uint16_t>::vt hb_v = svzip2(h_v, h_v);
        typename acle<float>::vt sa_v = svcvt_f32_x(pg1s, ha_v);
        typename acle<float>::vt sb_v = svcvt_f32_x(pg1s, hb_v);
        svst1(pg1s, sa.v, sa_v);
        svst1(pg1s, sb.v, sb_v);
      }
      static inline vecf DtoS (vecd a,vecd b) {

        vecf ret;
        svbool_t pg1d = acle<double>::pg1();
        svbool_t pg1s = acle<float>::pg1();
        typename acle<double>::vt a_v = svld1(pg1d, a.v);
        typename acle<double>::vt b_v = svld1(pg1d, b.v);
        typename acle<float>::vt sa_v = svcvt_f32_x(pg1d, a_v);
        typename acle<float>::vt sb_v = svcvt_f32_x(pg1d, b_v);
        typename acle<float>::vt r_v = svuzp1(sa_v, sb_v);
        svst1(pg1s, ret.v, r_v);
        return ret;
      }
      static inline void StoD (vecf s,vecd &a,vecd &b) {

        svbool_t pg1s = acle<float>::pg1();
        svbool_t pg1d = acle<double>::pg1();
        typename acle<float>::vt s_v = svld1(pg1s, s.v);
        typename acle<float>::vt sa_v = svzip1(s_v, s_v);
        typename acle<float>::vt sb_v = svzip2(s_v, s_v);
        typename acle<double>::vt a_v = svcvt_f64_x(pg1d, sa_v);
        typename acle<double>::vt b_v = svcvt_f64_x(pg1d, sb_v);
        svst1(pg1d, a.v, a_v);
        svst1(pg1d, b.v, b_v);
      }
      static inline vech DtoH (vecd a,vecd b,vecd c,vecd d) {

        vech ret;
        svbool_t pg1d = acle<double>::pg1();
        svbool_t pg1h = acle<uint16_t>::pg1();
        typename acle<double>::vt a_v = svld1(pg1d, a.v);
        typename acle<double>::vt b_v = svld1(pg1d, b.v);
        typename acle<double>::vt c_v = svld1(pg1d, c.v);
        typename acle<double>::vt d_v = svld1(pg1d, d.v);
        typename acle<uint16_t>::vt ha_v = svcvt_f16_x(pg1d, a_v);
        typename acle<uint16_t>::vt hb_v = svcvt_f16_x(pg1d, b_v);
        typename acle<uint16_t>::vt hc_v = svcvt_f16_x(pg1d, c_v);
        typename acle<uint16_t>::vt hd_v = svcvt_f16_x(pg1d, d_v);
        typename acle<uint16_t>::vt hab_v = svuzp1(ha_v, hb_v);
        typename acle<uint16_t>::vt hcd_v = svuzp1(hc_v, hd_v);
        typename acle<uint16_t>::vt r_v = svuzp1(hab_v, hcd_v);
        svst1(pg1h, (typename acle<uint16_t>::pt*)&ret.v, r_v);

        return ret;
  /*
        vecf sa,sb;
        sa = DtoS(a,b);
        sb = DtoS(c,d);
        return StoH(sa,sb);
  */
      }
      static inline void HtoD(vech h,vecd &a,vecd &b,vecd &c,vecd &d) {

        svbool_t pg1h = acle<uint16_t>::pg1();
        svbool_t pg1d = acle<double>::pg1();
        typename acle<uint16_t>::vt h_v = svld1(pg1h, (typename acle<uint16_t>::pt*)&h.v);
        typename acle<uint16_t>::vt sa_v = svzip1(h_v, h_v);
        typename acle<uint16_t>::vt sb_v = svzip2(h_v, h_v);
        typename acle<uint16_t>::vt da_v = svzip1(sa_v, sa_v);
        typename acle<uint16_t>::vt db_v = svzip2(sa_v, sa_v);
        typename acle<uint16_t>::vt dc_v = svzip1(sb_v, sb_v);
        typename acle<uint16_t>::vt dd_v = svzip2(sb_v, sb_v);
        typename acle<double>::vt a_v = svcvt_f64_x(pg1d, da_v);
        typename acle<double>::vt b_v = svcvt_f64_x(pg1d, db_v);
        typename acle<double>::vt c_v = svcvt_f64_x(pg1d, dc_v);
        typename acle<double>::vt d_v = svcvt_f64_x(pg1d, dd_v);
        svst1(pg1d, a.v, a_v);
        svst1(pg1d, b.v, b_v);
        svst1(pg1d, c.v, c_v);
        svst1(pg1d, d.v, d_v);
  /*
        vecf sa,sb;
        HtoS(h,sa,sb);
        StoD(sa,a,b);
        StoD(sb,c,d);
  */
      }
    };


  struct Exchange{

    // Exchange0 is valid for arbitrary SVE vector length
    template <typename T>
    static inline void Exchange0(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){

      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a1_v = svld1(pg1, in1.v);
      typename acle<T>::vt a2_v = svld1(pg1, in2.v);
      typename acle<T>::vt r1_v = svext(a1_v, a1_v, (uint64_t)W<T>::c);
      r1_v = svext(r1_v, a2_v, (uint64_t)W<T>::c);
      typename acle<T>::vt r2_v = svext(a2_v, a2_v, (uint64_t)W<T>::c);
      r2_v = svext(a1_v, r2_v, (uint64_t)W<T>::c);
      svst1(pg1, out1.v, r1_v);
      svst1(pg1, out2.v, r2_v);
    };


    template <typename T>
    static inline void Exchange1(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){

      svbool_t pg4 = acle<double>::pg4();
      typename acle<double>::vt4 in1_v4 = svld4(pg4, (typename acle<double>::pt*)in1.v);
      typename acle<double>::vt4 in2_v4 = svld4(pg4, (typename acle<double>::pt*)in2.v);
      typename acle<double>::vt4 out1_v4;
      typename acle<double>::vt4 out2_v4;
      out1_v4.v0 = in1_v4.v0;
      out1_v4.v1 = in1_v4.v1;
      out1_v4.v2 = in2_v4.v0;
      out1_v4.v3 = in2_v4.v1;
      out2_v4.v0 = in1_v4.v2;
      out2_v4.v1 = in1_v4.v3;
      out2_v4.v2 = in2_v4.v2;
      out2_v4.v3 = in2_v4.v3;
      svst4(pg4, (typename acle<double>::pt*)out1.v, out1_v4);
      svst4(pg4, (typename acle<double>::pt*)out2.v, out2_v4);
    };

    template <typename T>
    static inline void Exchange2(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){

      svbool_t pg1 = acle<double>::pg1();
      typename acle<double>::vt a1_v = svld1(pg1, (typename acle<double>::pt*)in1.v);
      typename acle<double>::vt a2_v = svld1(pg1, (typename acle<double>::pt*)in2.v);
      typename acle<double>::vt r1_v = svtrn1(a1_v, a2_v);
      typename acle<double>::vt r2_v = svtrn2(a1_v, a2_v);
      svst1(pg1, (typename acle<double>::pt*)out1.v, r1_v);
      svst1(pg1, (typename acle<double>::pt*)out2.v, r2_v);
    };

    static inline void Exchange3(vec<float> &out1, vec<float> &out2, const vec<float> &in1, const vec<float> &in2){

      svbool_t pg1 = acle<float>::pg1();
      typename acle<float>::vt a1_v = svld1(pg1, in1.v);
      typename acle<float>::vt a2_v = svld1(pg1, in2.v);
      typename acle<float>::vt r1_v = svtrn1(a1_v, a2_v);
      typename acle<float>::vt r2_v = svtrn2(a1_v, a2_v);
      svst1(pg1, out1.v, r1_v);
      svst1(pg1, out2.v, r2_v);
    };

    static inline void Exchange3(vec<double> &out1, vec<double> &out2, const vec<double> &in1, const vec<double> &in2){
      assert(0);
      return;
    };


struct Permute{

  // Permute0 is valid for any SVE vector width
  template <typename T>
  static inline vec<T> Permute0(vec<T> in) {

    vec<T> out;
    svbool_t pg1 = acle<T>::pg1();
    typename acle<T>::vt a_v = svld1(pg1, in.v);
    typename acle<T>::vt r_v = svext(a_v, a_v, (uint64_t)(W<T>::r / 2u));
    svst1(pg1, out.v, r_v);
    return out;
  }

  static inline vec<double> Permute1(vec<double> in) {

    vec<double> out;
    const vec<typename acle<double>::uint> tbl_swap = acle<double>::tbl1();
    svbool_t pg1 = acle<double>::pg1();
    typename acle<double>::vt a_v = svld1(pg1, in.v);
    typename acle<double>::svuint tbl_swap_v = svld1(pg1, tbl_swap.v);
    typename acle<double>::vt r_v = svtbl(a_v, tbl_swap_v);
    svst1(pg1, out.v, r_v);

    return out;
  }

  static inline vec<float> Permute1(vec<float> in) {

    vec<float> out;
    const vec<typename acle<float>::uint> tbl_swap = acle<float>::tbl1();
    svbool_t pg1 = acle<float>::pg1();
    typename acle<float>::vt a_v = svld1(pg1, in.v);
    typename acle<float>::svuint tbl_swap_v = svld1(pg1, tbl_swap.v);
    typename acle<float>::vt r_v = svtbl(a_v, tbl_swap_v);
    svst1(pg1, out.v, r_v);

    return out;
  }

  static inline vec<double> Permute2(vec<double> in) {

    vec<double> out;
    const vec<typename acle<double>::uint> tbl_swap = acle<double>::tbl_swap();
    svbool_t pg1 = acle<double>::pg1();
    typename acle<double>::vt a_v = svld1(pg1, in.v);
    typename acle<double>::svuint tbl_swap_v = svld1(pg1, tbl_swap.v);
    typename acle<double>::vt r_v = svtbl(a_v, tbl_swap_v);
    svst1(pg1, out.v, r_v);

    return out;
  }

  static inline vec<float> Permute2(vec<float> in) {

    vec<float> out;
    const vec<typename acle<float>::uint> tbl_swap = acle<float>::tbl2();
    svbool_t pg1 = acle<float>::pg1();
    typename acle<float>::vt a_v = svld1(pg1, in.v);
    typename acle<float>::svuint tbl_swap_v = svld1(pg1, tbl_swap.v);
    typename acle<float>::vt r_v = svtbl(a_v, tbl_swap_v);
    svst1(pg1, out.v, r_v);

    return out;
  }

  static inline vec<float> Permute3(vec<float> in) {

    vec<float> out;
    const vec<typename acle<float>::uint> tbl_swap = acle<float>::tbl_swap();
    svbool_t pg1 = acle<float>::pg1();
    typename acle<float>::vt a_v = svld1(pg1, in.v);
    typename acle<float>::svuint tbl_swap_v = svld1(pg1, tbl_swap.v);
    typename acle<float>::vt r_v = svtbl(a_v, tbl_swap_v);
    svst1(pg1, out.v, r_v);

    return out;
  }

  static inline vec<double> Permute3(vec<double> in) {
    return in;
  }



struct Rotate{

  template <int n, typename T> static inline vec<T> tRotate(vec<T> in){

    vec<T> out;
    svbool_t pg1 = acle<T>::pg1();
    typename acle<T>::vt a_v = svld1(pg1, in.v);
    typename acle<T>::vt r_v = svext(a_v, a_v, (uint64_t)(n%W<T>::r));
    svst1(pg1, out.v, r_v);

    return out;
  }

  template <typename T>
  static inline vec<T> rotate(vec<T> in, int n){

    switch(n){
    case 0:  return tRotate<0,  T>(in); break;
    case 1:  return tRotate<1,  T>(in); break;
    case 2:  return tRotate<2,  T>(in); break;
    case 3:  return tRotate<3,  T>(in); break;
    case 4:  return tRotate<4,  T>(in); break;
    case 5:  return tRotate<5,  T>(in); break;
    case 6:  return tRotate<6,  T>(in); break;
    case 7:  return tRotate<7,  T>(in); break;

    case 8:  return tRotate<8,  T>(in); break;
    case 9:  return tRotate<9,  T>(in); break;
    case 10: return tRotate<10, T>(in); break;
    case 11: return tRotate<11, T>(in); break;
    case 12: return tRotate<12, T>(in); break;
    case 13: return tRotate<13, T>(in); break;
    case 14: return tRotate<14, T>(in); break;
    case 15: return tRotate<15, T>(in); break;
    default: assert(0);
    }
  }
};


// tree-based reduction
#define svred(pg, v)\
svaddv(pg, v);

// left-to-right reduction
// #define svred(pg, v)\
// svadda(pg, 0, v)

template <typename Out_type, typename In_type>
struct Reduce{
  //Need templated class to overload output type
  //General form must generate error if compiled
  inline Out_type operator()(const In_type &in){
    printf("Error, using wrong Reduce function\n");
    exit(1);
    return 0;
  }
};

//Complex float Reduce
template <>
inline Grid::ComplexF Reduce<Grid::ComplexF, vecf>::operator()(vecf in){

  svbool_t pg1 = acle<float>::pg1();
  svbool_t pg_even = acle<float>::pg_even();
  svbool_t pg_odd  = acle<float>::pg_odd();
  typename acle<float>::vt a_v = svld1(pg1, in.v);
  float a = svred(pg_even, a_v);
  float b = svred(pg_odd, a_v);

  return Grid::ComplexF(a, b);

/* LD2: tested, working
  svbool_t pg2 = acle<float>::pg2();
  typename acle<float>::vt2 a_v = svld2(pg2, in.v);
  typename acle<float>::pt a = (typename acle<float>::pt)svred(pg2, a_v.v0);
  typename acle<float>::pt b = (typename acle<float>::pt)svred(pg2, a_v.v1);

  return Grid::ComplexF(a, b);
*/
}

//Real float Reduce
template <>
inline Grid::RealF Reduce<Grid::RealF, vecf>::operator()(vecf in){

  svbool_t pg1 = acle<float>::pg1();
  typename acle<float>::vt a_v = svld1(pg1, in.v);
  float a = svred(pg1, a_v);

  return a;
}

//Complex double Reduce
template <>
inline Grid::ComplexD Reduce<Grid::ComplexD, vecd>::operator()(vecd in){

  svbool_t pg1 = acle<double>::pg1();
  svbool_t pg_even = acle<double>::pg_even();
  svbool_t pg_odd  = acle<double>::pg_odd();
  typename acle<double>::vt a_v = svld1(pg1, in.v);
  double a = svred(pg_even, a_v);
  double b = svred(pg_odd, a_v);

  return Grid::ComplexD(a, b);

/* LD2: tested, working
  svbool_t pg2 = acle<double>::pg2();
  typename acle<double>::vt2 a_v = svld2(pg2, in.v);
  typename acle<double>::pt a = (typename acle<double>::pt)svred(pg2, a_v.v0);
  typename acle<double>::pt b = (typename acle<double>::pt)svred(pg2, a_v.v1);

  return Grid::ComplexD(a, b);
*/
}

//Real double Reduce
template <>
inline Grid::RealD Reduce<Grid::RealD, vecd>::operator()(vecd in){

  svbool_t pg1 = acle<double>::pg1();
  typename acle<double>::vt a_v = svld1(pg1, in.v);
  double a = svred(pg1, a_v);

  return a;
}

//Integer Reduce
template <>
inline Integer Reduce<Integer, veci>::operator()(veci in){

  svbool_t pg1 = acle<Integer>::pg1();
  typename acle<Integer>::vt a_v = svld1(pg1, in.v);
  Integer a = svred(pg1, a_v);

  return a;
}

#undef svred

}

//////////////////////////////////////////////////////////////////////////////////////
// Here assign types

  typedef Optimization::vech SIMD_Htype; // Reduced precision type
  typedef Optimization::vecf SIMD_Ftype; // Single precision type
  typedef Optimization::vecd SIMD_Dtype; // Double precision type
  typedef Optimization::veci SIMD_Itype; // Integer type

  // prefetch utilities
  inline void v_prefetch0(int size, const char *ptr){};
  inline void prefetch_HINT_T0(const char *ptr){};

  // Function name aliases
  typedef Optimization::Vsplat   VsplatSIMD;
  typedef Optimization::Vstore   VstoreSIMD;
  typedef Optimization::Vset     VsetSIMD;
  typedef Optimization::Vstream  VstreamSIMD;
  template <typename S, typename T> using ReduceSIMD = Optimization::Reduce<S,T>;

  // Arithmetic operations
  typedef Optimization::Sum         SumSIMD;
  typedef Optimization::Sub         SubSIMD;
  typedef Optimization::Div         DivSIMD;
  typedef Optimization::Mult        MultSIMD;
  typedef Optimization::MultComplex MultComplexSIMD;
  typedef Optimization::MultRealPart MultRealPartSIMD;
  typedef Optimization::MaddRealPart MaddRealPartSIMD;
  typedef Optimization::Conj        ConjSIMD;
  typedef Optimization::TimesMinusI TimesMinusISIMD;
  typedef Optimization::TimesI      TimesISIMD;

}
