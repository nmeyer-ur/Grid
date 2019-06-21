#ifndef SVE_VSTORE_H
#define SVE_VSTORE_H

#pragma message("include sve_vstore.h")

  struct Vstore{
    // Real
    template <typename T>
    inline void operator()(const vec<T> &a, T *D){

      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, (typename acle<T>::pt*)&a.v);
    // NOTE illegal '&' here causes SIGBUS at runtime, related to  CAS-35230-H2H6T1
      // svst1(pg1, (typename acle<T>::pt*)&D, a_v);
      svst1(pg1, D, a_v);
      
      // non temporal version TO INTEGRATED
      //svstnt1(pg1, D, a_v);
    }
  };


#endif
