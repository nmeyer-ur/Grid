#ifndef SVE_SUM_H
#define SVE_SUM_H

#pragma message("include sve_sum_sls.h")
/*
  struct Sum{
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      typename acle<T>::vt r_v = svadd_x(pg1, a_v, b_v);
      svst1(pg1, out.v, r_v);

      return out;
    }
*/

  struct Sum{
    inline vecd operator()(const vecd &a, const vecd &b){

      vecd out;
      svbool_t pg2 = acle<double>::pg2();
      typename acle<T>::vt2 a_v = svld2(pg2, a.v);
      typename acle<T>::vt2 b_v = svld2(pg2, b.v);
      typename acle<T>::vt2 r_v;
      r_v.v0 = svadd_x(pg2, a_v.v0, b_v.v0);
      r_v.v1 = svadd_x(pg2, a_v.v0, b_v.v1);
      svst2(pg2, out.v, r_v);

      return out;
    }
    inline vecf operator()(const vecf &a, const vecf &b){

      vecf out;
      svbool_t pg2 = acle<float>::pg2();
      typename acle<T>::vt2 a_v = svld2(pg2, a.v);
      typename acle<T>::vt2 b_v = svld2(pg2, b.v);
      typename acle<T>::vt2 r_v;
      r_v.v0 = svadd_x(pg2, a_v.v0, b_v.v0);
      r_v.v1 = svadd_x(pg2, a_v.v0, b_v.v1);
      svst2(pg2, out.v, r_v);

      return out;
    }
    inline veci operator()(const veci &a, const veci &b){

      veci out;
      svbool_t pg2 = acle<float>::pg2();
      typename acle<T>::vt2 a_v = svld2(pg2, a.v);
      typename acle<T>::vt2 b_v = svld2(pg2, b.v);
      typename acle<T>::vt2 r_v;
      r_v.v0 = svadd_x(pg2, a_v.v0, b_v.v0);
      r_v.v1 = svadd_x(pg2, a_v.v0, b_v.v1);
      svst2(pg2, out.v, r_v);

      return out;
    }

  };

#endif
