#ifndef SVE_MULTCOMPLEX_REAL_H
#define SVE_MULTCOMPLEX_REAL_H

#pragma message("include sve_multcomplex_real.h")

  struct MultComplex{
    // Complex
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){

      // complex multiplication using ld1/st1 and real arithmetics
      vec<T> out;
      typename acle<T>::vt r0_v, r1_v, r2_v, r3_v, r4_v, r5_v, r6_v;
      svbool_t pg1 = acle<T>::pg1();

      // a = ar ai Ar Ai ...
      // b = br bi Br Bi ...
      // collect real/imag part, negate bi and Bi
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      r0_v = svtrn1(b_v, b_v);       //  br  br  Br  Br
      r1_v = svneg_x(pg1, b_v);      // -br -bi -Br -Bi
      r2_v = svtrn2(b_v, r1_v);      //  bi -bi  Bi -Bi
      r3_v = svmul_x(pg1, r2_v, a_v);//  bi*ar -bi*ai ...

      // swap real and imag parts
      r4_v = svtrn2(r3_v, r3_v);
      r5_v = svtrn1(r4_v, r3_v);

      // svrev64 does not exist for 64-bit floats, only for 32-bit floats
      //r4 = svrev64q_f32(r3); // -bi*ai  bi*ar ...
      r6_v = svmla_x(pg1, r5_v, r0_v, a_v);     //  ar*br-ai*bi ai*br+ar*bi ...

      svst1(pg1, out.v, r6_v);

      return out;
    }
  };

#endif
