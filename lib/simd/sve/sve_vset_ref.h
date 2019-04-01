#ifndef SVE_VSET_H
#define SVE_VSET_H

#pragma message("include sve_vset_ref.h")

  struct Vset{
    // Complex
    template <typename T>
    inline vec<T> operator()(const std::complex<T> *a){

      vec<T> out;
      typename acle<T>::vt *r_v = (typename acle<T>::vt*)&out.v;
      *r_v = (typename acle<T>::vt*)a;

      return out;
    }

    // Real
    template <typename T>
    inline vec<T> operator()(T * a){

      vec<T> out;
      typename acle<T>::vt *r_v = (typename acle<T>::vt*)&out.v;
      *r_v = (typename acle<T>::vt*)a;

      return out;
    }
  };

#endif
