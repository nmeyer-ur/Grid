#ifndef SVE_SUM_H
#define SVE_SUM_H

#pragma message("include sve_sum.h")

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
      svbool_t pg1 = acle<double>::pg1();
      svfloat64_t a_v = svld1(pg1, a.v);
      svfloat64_t b_v = svld1(pg1, b.v);
      svfloat64_t r_v = svadd_x(pg1, a_v, b_v);
      svst1(pg1, out.v, r_v);

      return out;
    }
    inline vecf operator()(const vecf &a, const vecf &b){

      vecf out;
      svbool_t pg1 = acle<float>::pg1();
      svfloat32_t a_v = svld1(pg1, a.v);
      svfloat32_t b_v = svld1(pg1, b.v);
      svfloat32_t r_v = svadd_x(pg1, a_v, b_v);
      svst1(pg1, out.v, r_v);

      return out;
    }
    inline veci operator()(const veci &a, const veci &b){

      veci out;
      svbool_t pg1 = svptrue_b32();
      svuint32_t a_v = svld1(pg1, a.v);
      svuint32_t b_v = svld1(pg1, b.v);
      svuint32_t r_v = svadd_x(pg1, a_v, b_v);
      svst1(pg1, out.v, r_v);

      return out;
    }

  };

#endif
