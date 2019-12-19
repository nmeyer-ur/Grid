#ifndef SVE_TIMESMINUSI_H
#define SVE_TIMESMINUSI_H

#pragma message("include sve_timesminusi.h")

  struct TimesMinusI{
    // Complex
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){

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

#endif
