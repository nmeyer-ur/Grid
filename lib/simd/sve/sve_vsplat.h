#ifndef SVE_VSPLAT_H
#define SVE_VSPLAT_H

#pragma message("include sve_vsplat.h")

  struct Vsplat{
    // Complex float
    inline vec<float> operator()(const float a, const float b){

      vec<float> out;
      svbool_t pg1 = acle<float>::pg1();
      typename acle<float>::vt a_v = svdup_f32(a);
      typename acle<float>::vt b_v = svdup_f32(b);
      typename acle<float>::vt r_v = svzip1(a_v, b_v);
      svst1(pg1, out.v, r_v);
      return out;
    }

    // Real float
    inline vec<float> operator()(const float a){

      vec<float> out;
      svbool_t pg1 = acle<float>::pg1();
      typename acle<float>::vt r_v = svdup_f32(a);
      svst1(pg1, out.v, r_v);
      return out;
    }

   // Complex double
    inline vec<double> operator()(const double a, const double b){

      vec<double> out;
      svbool_t pg1 = acle<double>::pg1();
      typename acle<double>::vt a_v = svdup_f64(a);
      typename acle<double>::vt b_v = svdup_f64(b);
      typename acle<double>::vt r_v = svzip1(a_v, b_v);
      svst1(pg1, out.v, r_v);
      return out;
    }

    // Real double
    inline vec<double> operator()(const double a){

      vec<double> out;
      svbool_t pg1 = acle<double>::pg1();
      typename acle<double>::vt r_v = svdup_f64(a);
      svst1(pg1, out.v, r_v);
      return out;
    }

    // Integer
    inline vec<Integer> operator()(const Integer a){

      vec<Integer> out;
      svbool_t pg1 = acle<Integer>::pg1();
      // Add check whether Integer is really a uint32_t???
      typename acle<Integer>::vt r_v = svdup_u32(a);
      svst1(pg1, out.v, r_v);
      return out;
    }
  };



#endif
