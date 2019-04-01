#ifndef SVE_EXCHANGE_H
#define SVE_EXCHANGE_H

#pragma message("include sve_exchange_ref.h")

  struct Exchange{

    // Exchange0 is valid for arbitrary SVE vector length
    template <typename T>
    static inline void Exchange0(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){

      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt *a1_v = (typename acle<T>::vt*)&in1.v;
      typename acle<T>::vt *a2_v = (typename acle<T>::vt*)&in2.v;
      typename acle<T>::vt *r1_v = (typename acle<T>::vt*)&out1.v;
      typename acle<T>::vt *r2_v = (typename acle<T>::vt*)&out2.v;

      typename acle<T>::vt t1_v = svext(*a1_v, *a1_v, (uint64_t)W<T>::c);
      *r1_v = svext(t1_v, *a2_v, (uint64_t)W<T>::c);

      typename acle<T>::vt t2_v = svext(*a2_v, *a2_v, (uint64_t)W<T>::c);
      *r2_v = svext(*a1_v, t2_v, (uint64_t)W<T>::c);
    };

    // specialization for SVE 512 bit vector length
    #if (GEN_SIMD_WIDTH == 64u)
    #pragma message("specialize exchange for 512 bit vector length")

    template <typename T>
    static inline void Exchange1(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){

      svbool_t pg4 = acle<double>::pg4();
      typename acle<double>::vt4 in1_v4 = svld4(pg4, (typename acle<double>::pt*)in1.v);
      typename acle<double>::vt4 in2_v4 = svld4(pg4, (typename acle<double>::pt*)in2.v);
      typename acle<double>::vt4 out1_v4;
      typename acle<double>::vt4 out2_v4;
      out1_v4.v0 = in1_v4.v0;
      out1_v4.v1 = in1_v4.v1;
      out1_v4.v2 = in2_v4.v0;
      out1_v4.v3 = in2_v4.v1;
      out2_v4.v0 = in1_v4.v2;
      out2_v4.v1 = in1_v4.v3;
      out2_v4.v2 = in2_v4.v2;
      out2_v4.v3 = in2_v4.v3;
      svst4(pg4, (typename acle<double>::pt*)out1.v, out1_v4);
      svst4(pg4, (typename acle<double>::pt*)out2.v, out2_v4);
    };

    template <typename T>
    static inline void Exchange2(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){

      // UNSAFE ??
      svbool_t pg1 = acle<double>::pg1();
/*
      typename acle<double>::vt a1_v = svld1(pg1, (typename acle<double>::pt*)in1.v);
      typename acle<double>::vt a2_v = svld1(pg1, (typename acle<double>::pt*)in2.v);
      typename acle<double>::vt r1_v = svtrn1(a1_v, a2_v);
      typename acle<double>::vt r2_v = svtrn2(a1_v, a2_v);
      svst1(pg1, (typename acle<double>::pt*)out1.v, r1_v);
      svst1(pg1, (typename acle<double>::pt*)out2.v, r2_v);
*/
      typename acle<double>::vt *a1_v = (typename acle<double>::vt*)&in1.v;
      typename acle<double>::vt *a2_v = (typename acle<double>::vt*)&in2.v;
      typename acle<double>::vt *r1_v = (typename acle<double>::vt*)&out1.v;
      typename acle<double>::vt *r2_v = (typename acle<double>::vt*)&out2.v;

      *r1_v = svtrn1(*a1_v, *a2_v);
      *r2_v = svtrn2(*a1_v, *a2_v);
    };

    static inline void Exchange3(vec<float> &out1, vec<float> &out2, const vec<float> &in1, const vec<float> &in2){

      svbool_t pg1 = acle<float>::pg1();
      typename acle<float>::vt *a1_v = (typename acle<float>::vt*)&in1.v;
      typename acle<float>::vt *a2_v = (typename acle<float>::vt*)&in2.v;
      typename acle<float>::vt *r1_v = (typename acle<float>::vt*)&out1.v;
      typename acle<float>::vt *r2_v = (typename acle<float>::vt*)&out2.v;

      *r1_v = svtrn1(*a1_v, *a2_v);
      *r2_v = svtrn2(*a1_v, *a2_v);
    };

    static inline void Exchange3(vec<double> &out1, vec<double> &out2, const vec<double> &in1, const vec<double> &in2){
      assert(0);
      return;
    };

    // specialization for SVE 256-bit vector length
    #elif (GEN_SIMD_WIDTH == 32u)
    #pragma message("specialize exchange for 256 bit vector length")

    static inline void Exchange1(vec<double> &out1, vec<double> &out2, const vec<double> &in1, const vec<double> &in2){

      svbool_t pg1 = acle<double>::pg1();
      typename acle<double>::vt *a1_v = (typename acle<double>::vt*)&in1.v;
      typename acle<double>::vt *a2_v = (typename acle<double>::vt*)&in2.v;
      typename acle<double>::vt *r1_v = (typename acle<double>::vt*)&out1.v;
      typename acle<double>::vt *r2_v = (typename acle<double>::vt*)&out2.v;

      *r1_v = svtrn1(*a1_v, *a2_v);
      *r2_v = svtrn2(*a1_v, *a2_v);
    };

    static inline void Exchange1(vec<float> &out1, vec<float> &out2, const vec<float> &in1, const vec<float> &in2){

      svbool_t pg4 = acle<double>::pg4();
      typename acle<double>::vt4 in1_v4 = svld4(pg4, (typename acle<double>::pt*)in1.v);
      typename acle<double>::vt4 in2_v4 = svld4(pg4, (typename acle<double>::pt*)in2.v);
      typename acle<double>::vt4 out1_v4;
      typename acle<double>::vt4 out2_v4;
      out1_v4.v0 = in1_v4.v0;
      out1_v4.v1 = in1_v4.v1;
      out1_v4.v2 = in2_v4.v0;
      out1_v4.v3 = in2_v4.v1;
      out2_v4.v0 = in1_v4.v2;
      out2_v4.v1 = in1_v4.v3;
      out2_v4.v2 = in2_v4.v2;
      out2_v4.v3 = in2_v4.v3;
      svst4(pg4, (typename acle<double>::pt*)out1.v, out1_v4);
      svst4(pg4, (typename acle<double>::pt*)out2.v, out2_v4);
    };

    static inline void Exchange2(vec<double> &out1, vec<double> &out2, const vec<double> &in1, const vec<double> &in2){
      assert(0);
      return;
    };

    static inline void Exchange2(vec<float> &out1, vec<float> &out2, const vec<float> &in1, const vec<float> &in2){

      svbool_t pg1 = acle<float>::pg1();
      typename acle<float>::vt *a1_v = (typename acle<float>::vt*)&in1.v;
      typename acle<float>::vt *a2_v = (typename acle<float>::vt*)&in2.v;
      typename acle<float>::vt *r1_v = (typename acle<float>::vt*)&out1.v;
      typename acle<float>::vt *r2_v = (typename acle<float>::vt*)&out2.v;

      *r1_v = svtrn1(*a1_v, *a2_v);
      *r2_v = svtrn2(*a1_v, *a2_v);
    };

    template <typename T>
    static inline void Exchange3(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){
      assert(0);
      return;
    };

    #else
    #pragma message("generic exchange")

    template <typename T,int n>
    static inline void ExchangeN(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){
      const int w = W<T>::r;
      unsigned int mask = w >> (n + 1);
      //      std::cout << " Exchange "<<n<<" nsimd "<<w<<" mask 0x" <<std::hex<<mask<<std::dec<<std::endl;
      VECTOR_FOR(i, w, 1) {
	int j1 = i&(~mask);
	if  ( (i&mask) == 0 ) { out1.v[i]=in1.v[j1];}
	else                  { out1.v[i]=in2.v[j1];}
	int j2 = i|mask;
	if  ( (i&mask) == 0 ) { out2.v[i]=in1.v[j2];}
	else                  { out2.v[i]=in2.v[j2];}
      }
    }
    template <typename T>
    static inline void Exchange1(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){
      ExchangeN<T,1>(out1,out2,in1,in2);
    };
    template <typename T>
    static inline void Exchange2(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){
      ExchangeN<T,2>(out1,out2,in1,in2);
    };
    template <typename T>
    static inline void Exchange3(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){
      ExchangeN<T,3>(out1,out2,in1,in2);
    };

    #endif
  };


#endif
