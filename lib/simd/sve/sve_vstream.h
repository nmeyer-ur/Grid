#ifndef SVE_VSTREAM_H
#define SVE_VSTREAM_H

#pragma message("include sve_vstream.h")

  struct Vstream{
    // Real
    template <typename T>
    inline void operator()(T * a, const vec<T> &b){

      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt b_v = svld1(pg1, b.v);
      // FIXME non-temporal store causes compiler crash  CAS-35230-H2H6T1
      //svstnt1(pg1, a, b_v);
      svst1(pg1, a, b_v);
    }
  };

#endif
