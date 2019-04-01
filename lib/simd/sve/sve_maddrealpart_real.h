#ifndef SVE_MADDREALPART_H
#define SVE_MADDREALPART_H

#pragma message("include sve_maddrealpart_real.h")

  struct MaddRealPart{
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b, const vec<T> &c){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v  = svld1(pg1, a.v);
      typename acle<T>::vt b_v  = svld1(pg1, b.v);
      typename acle<T>::vt c_v  = svld1(pg1, c.v);

      typename acle<T>::vt re_v = svtrn1(a_v, a_v);
      typename acle<T>::vt r_v  = svmad_x(pg1, re_v, b_v, c_v);

      svst1(pg1, out.v, r_v);

      return out;
    }
  };

#endif
