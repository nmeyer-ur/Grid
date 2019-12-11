#ifndef SVE_MULTADDCOMPLEX_H
#define SVE_MULTADDCOMPLEX_H

#pragma message("include sve_multaddcomplex.h")

  struct MultAddComplex{
    // Complex a*b+c
    template <typename T>
    inline vec<T> mac(const vec<T> &a, const vec<T> &b, const vec<T> &c){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      typename acle<T>::vt c_v = svld1(pg1, c.v);;

      // using FCMLA
      typename acle<T>::vt r_v = svcmla_x(pg1, c_v, a_v, b_v, 90);
      r_v = svcmla_x(pg1, r_v, a_v, b_v, 0);

      svst1(pg1, out.v, r_v);

      return out;
    }
  };

#endif
