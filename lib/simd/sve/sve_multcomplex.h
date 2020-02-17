#ifndef SVE_MULTCOMPLEX_H
#define SVE_MULTCOMPLEX_H

#pragma message("include sve_multcomplex.h")

  struct MultComplex{
    // Complex a*b
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      //typename acle<T>::vt z_v = acle<T>::zero();
      typename acle<T>::vt z_v = __svzero(z_v);

      // using FCMLA
      // FIXME
      /*
      typename acle<T>::vt r_v = svcmla_x(pg1, z_v, a_v, b_v, 90);
      r_v = svcmla_x(pg1, r_v, a_v, b_v, 0);
      */

      typename acle<T>::vt z_v2 = __svzero(z_v2);
      z_v = svcmla_x(pg1, z_v, a_v, b_v, 90);
      typename acle<T>::vt z_v2 = svcmla_x(pg1, z_v2, a_v, b_v, 90);
      typename acle<T>::vt r_v = svadd_x(z_v, z_v2);

      svst1(pg1, out.v, r_v);

      return out;
    }
  };

  struct MultAddComplex{
    // Complex a*b+c
    template <typename T>
    static inline vec<T> mac(const vec<T> &a, const vec<T> &b, const vec<T> &c){

/*
      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      typename acle<T>::vt c_v = svld1(pg1, c.v);

      // using FCMLA
      typename acle<T>::vt r_v = svcmla_x(pg1, c_v, a_v, b_v, 90);
      r_v = svcmla_x(pg1, r_v, a_v, b_v, 0);

      svst1(pg1, out.v, r_v);
*/

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      typename acle<T>::vt c_v = svld1(pg1, c.v);
      typename acle<T>::vt z_v = __svzero(z_v);

      // using FCMLA
      a_v = svcmla_x(pg1, c_v, a_v, b_v, 90);
      z_v = svcmla_x(pg1, z_v, a_v, b_v, 0);
      typename acle<T>::vt r_v = svadd_x(a_v, z_v);

      svst1(pg1, out.v, r_v);

      return out;
    }

    // Complex a*b+c
    template <typename T>
    static inline vec<T> mac0(const vec<T> &a, const vec<T> &b, const vec<T> &c){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      typename acle<T>::vt c_v = svld1(pg1, c.v);

      // using FCMLA
      typename acle<T>::vt r_v = svcmla_x(pg1, c_v, a_v, b_v, 90);

      svst1(pg1, out.v, r_v);

      return out;
    }

    // Complex a*b+c
    template <typename T>
    static inline vec<T> mac1(const vec<T> &a, const vec<T> &b, const vec<T> &c){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      typename acle<T>::vt c_v = svld1(pg1, c.v);

      // using FCMLA
      typename acle<T>::vt r_v = svcmla_x(pg1, c_v, a_v, b_v, 0);

      svst1(pg1, out.v, r_v);

      return out;
    }

  };


#endif
