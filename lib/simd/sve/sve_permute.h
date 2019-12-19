#ifndef SVE_PERMUTE_H
#define SVE_PERMUTE_H

#pragma message("include sve_permute.h")

  struct Permute{

    // Permute0 is valid for any SVE vector width
    template <typename T>
    static inline vec<T> Permute0(const vec<T> &in) {

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, in.v);
      typename acle<T>::vt r_v = svext(a_v, a_v, (uint64_t)(W<T>::r / 2u));
      svst1(pg1, out.v, r_v);
      return out;
    }

    // specialization for SVE 512-bit vector length
    #if (GEN_SIMD_WIDTH == 64u)
    #pragma message("specialize permute for 512 bit vector length")

    template <typename T>
    static inline vec<T> Permute1(const vec<T> &in) {

      vec<T> out;
      svbool_t pg1 = acle<double>::pg1();
      typename acle<double>::vt a_v = svld1(pg1, (typename acle<double>::pt*)in.v);
      a_v = svrev(a_v);
      a_v = svext(a_v, a_v, (uint64_t)W<double>::c);
      typename acle<double>::vt b_v = svtrn2(a_v, a_v);
      typename acle<double>::vt r_v = svtrn1(b_v, a_v);
      svst1(pg1, (typename acle<double>::pt*)out.v, r_v);

      return out;
    }

    template <typename T>
    static inline vec<T> Permute2(const vec<T> &in) {

/*
      vec<T> out;
      svbool_t pg1 = acle<double>::pg1();
      typename acle<double>::vt a_v = svld1(pg1, (typename acle<double>::pt*)in.v);
      typename acle<double>::vt b_v = svtrn2(a_v, a_v);
      typename acle<double>::vt r_v = svtrn1(b_v, a_v);
      svst1(pg1, (typename acle<double>::pt*)out.v, r_v);
*/
      vec<T> out;
      const vec<typename acle<double>::uint> tbl1 = acle<double>::tbl1();
      svbool_t pg1 = acle<double>::pg1();

      typename acle<double>::svuint tbl1_v = svld1(pg1, tbl1.v);
      typename acle<double>::vt a_v = svld1(pg1, a.v);
      typename acle<double>::vt r_v = svtbl(a_v, tbl1_v);
      svst1(pg1, (typename acle<double>::pt*)out.v, r_v);

      return out;
    }

    static inline vec<float> Permute3(const vec<float> &in) {

/*
      vec<float> out;
      svbool_t pg1 = acle<float>::pg1();
      typename acle<float>::vt a_v = svld1(pg1, in.v);
      typename acle<float>::vt b_v = svtrn2(a_v, a_v);
      typename acle<float>::vt r_v = svtrn1(b_v, a_v);
      svst1(pg1, out.v, r_v);
*/
      vec<T> out;
      const vec<typename acle<float>::uint> tbl1 = acle<float>::tbl1();
      svbool_t pg1 = acle<float>::pg1();

      typename acle<float>::svuint tbl1_v = svld1(pg1, tbl1.v);
      typename acle<float>::vt a_v = svld1(pg1, a.v);
      typename acle<float>::vt r_v = svtbl(a_v, tbl1_v);
      svst1(pg1, (typename acle<float>::pt*)out.v, r_v);

      return out;
    }

    static inline vec<double> Permute3(const vec<double> &in) {
      return in;
    }

    // specialization for SVE 512-bit vector length
    #elif (GEN_SIMD_WIDTH == 32u)
    #pragma message("specialize permute for 256 bit vector length")

    template <typename T>
    static inline vec<T> Permute1(const vec<T> &in) {

      vec<T> out;
      svbool_t pg1 = acle<double>::pg1();
      typename acle<double>::vt a_v = svld1(pg1, (typename acle<double>::pt*)in.v);
      typename acle<double>::vt b_v = svtrn2(a_v, a_v);
      typename acle<double>::vt r_v = svtrn1(b_v, a_v);
      svst1(pg1, (typename acle<double>::pt*)out.v, r_v);

      return out;
    }

    static inline vec<float> Permute2(const vec<float> &in) {

      vec<float> out;
      svbool_t pg1 = acle<float>::pg1();
      typename acle<float>::vt a_v = svld1(pg1, in.v);
      typename acle<float>::vt b_v = svtrn2(a_v, a_v);
      typename acle<float>::vt r_v = svtrn1(b_v, a_v);
      svst1(pg1, out.v, r_v);

      return out;
    }

    static inline vec<double> Permute2(const vec<double> &in) {
      return in;
    }

    static inline vec<double> Permute3(const vec<double> &in) {
      return in;
    }

    static inline vec<float> Permute3(const vec<float> &in) {
      return in;
    }

    #else

    #define perm(l, n, w)\
    unsigned int _mask = w >> (n + 1);\
    VECTOR_FOR(i, w, 1)\
    {\
      l[i] = i^_mask;\
    }

    #define DECL_PERMUTE_N(n)\
    template <typename T>\
    static inline vec<T> Permute##n(const vec<T> &in) {\
      typename acle<T>::uint lut[W<T>::r];\
      vec<T> out;\
      svbool_t pg1 = acle<T>::pg1();\
      perm(lut, n, W<T>::r);\
      typename acle<T>::vt a_v = svld1(pg1, (typename acle<T>::pt*)&in.v);\
      typename acle<T>::svuint lut_v = svld1(pg1, (typename acle<T>::uint*)lut);\
      a_v = svtbl(a_v, lut_v);\
      svst1(pg1, (typename acle<T>::pt*)&out.v, a_v);\
      return out;\
    }

//    DECL_PERMUTE_N(0);
    DECL_PERMUTE_N(1);
    DECL_PERMUTE_N(2);
    DECL_PERMUTE_N(3);

    #undef perm
    #undef perm_org

    #undef DECL_PERMUTE_N

    #endif
  };

#endif
