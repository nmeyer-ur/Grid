#ifndef SVE_MADDREALPART_H
#define SVE_MADDREALPART_H

#pragma message("include sve_maddrealpart_real_ref.h")

  struct MaddRealPart{
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b, const vec<T> &c){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();

      typename acle<T>::vt *a_v = (typename acle<T>::vt*)&a.v;
      typename acle<T>::vt *b_v = (typename acle<T>::vt*)&b.v;
      typename acle<T>::vt *c_v = (typename acle<T>::vt*)&c.v;
      typename acle<T>::vt *r_v = (typename acle<T>::vt*)&out.v;

      typename acle<T>::vt re_v = svtrn1(*a_v, *a_v);
      *r_v  = svmad_x(pg1, re_v, *b_v, *c_v);

      return out;
    }
  };

#endif
