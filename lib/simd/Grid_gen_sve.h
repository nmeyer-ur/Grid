    /*************************************************************************************

    Grid physics library, www.github.com/paboyle/Grid

    Source file: ./lib/simd/Grid_gen_sve.h

    Copyright (C) 2018

Author: Nils Meyer          <nils.meyer@ur.de>

    Copyright (C) 2015
    Copyright (C) 2017

Author: Antonin Portelli <antonin.portelli@me.com>
        Andrew Lawson    <andrew.lawson1991@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    See the full license in the file "LICENSE" in the top level distribution directory
    *************************************************************************************/
    /*  END LEGAL */

#include "Grid_generic_types.h"

#if defined(GENSVE)
#ifdef __ARM_FEATURE_SVE
#ifdef __clang__
#include <arm_sve.h>
#endif
#else
#pragma error "Missing SVE feature"
#endif /* __ARM_FEATURE_SVE */
#endif

namespace Grid {
namespace Optimization {

  #if defined(GENSVE) && defined(__clang__)
  #include "sve/sve_acle.h"

    #if defined(SVE_CPLX_LD1)
      #define SVE_GROUP_V
      #define SVE_GROUP_ARITH_CPLX_LD1
      #define SVE_GROUP_PREC
      #define SVE_GROUP_PERM
      #define SVE_GROUP_PREFETCH

    #elif defined(SVE_CPLX_REF)
      #define SVE_GROUP_V_REF
      #define SVE_GROUP_ARITH_CPLX_REF
      #define SVE_GROUP_PREC
      #define SVE_GROUP_PERM
      #define SVE_GROUP_PREFETCH

    #elif defined(SVE_REAL_LD1)
      #define SVE_GROUP_V
      #define SVE_GROUP_ARITH_REAL_LD1
      #define SVE_GROUP_PREC
      #define SVE_GROUP_PERM
      #define SVE_GROUP_PREFETCH

    #elif defined(SVE_REAL_REF)
      #define SVE_GROUP_V_REF
      #define SVE_GROUP_ARITH_REAL_REF
      #define SVE_GROUP_PREC
      // aliasing issues
      //#define SVE_GROUP_PERM_REF
      #define SVE_GROUP_PERM
      #define SVE_GROUP_PREFETCH

    #elif defined(SVE_REAL_LD2)
      #define SVE_GROUP_V
      #define SVE_GROUP_ARITH_REAL_LD2
      #define SVE_GROUP_PREC
      #define SVE_GROUP_PERM
      #define SVE_GROUP_PREFETCH

    #endif

    #if defined(SVE_GROUP_V)
      #pragma message("enabling SVE_GROUP_V")
      #define SVE_VSPLAT
      #define SVE_VSTORE
      #define SVE_VSTREAM
      #define SVE_VSET
    #endif

    #if defined(SVE_GROUP_V_REF)
      #pragma message("enabling SVE_GROUP_V_REF")
      #define SVE_VSPLAT_REF
      #define SVE_VSTORE_REF
      #define SVE_VSTREAM_REF
      #define SVE_VSET_REF
    #endif

    #if defined(SVE_GROUP_ARITH_CPLX_LD1)
      #pragma message("enabling SVE_GROUP_ARITH_CPLX_LD1")
      #define SVE_SUM
      #define SVE_SUB
      #define SVE_MULT
      #define SVE_MULTREALPART_CPLX_LD1
      #define SVE_MADDREALPART_CPLX_LD1
      #define SVE_MULTCOMPLEX_CPLX_LD1
      #define SVE_DIV
      #define SVE_CONJ
      #define SVE_TIMESMINUSI
      #define SVE_TIMESI
//  #define SVE_REDUCE
      #define SVE_REDUCE_REAL_LD2

    #elif defined(SVE_GROUP_ARITH_CPLX_REF)
      #pragma message("enabling SVE_GROUP_ARITH_CPLX_REF")
      #define SVE_SUM_REF
      #define SVE_SUB_REF
      #define SVE_MULT_REF
      #define SVE_MULTREALPART_CPLX_REF
      #define SVE_MADDREALPART_CPLX_REF
      #define SVE_MULTCOMPLEX_CPLX_REF
      #define SVE_DIV_REF
      #define SVE_CONJ_REF
      #define SVE_TIMESMINUSI_REF
      #define SVE_TIMESI_REF
      #define SVE_REDUCE_REF

    #elif defined(SVE_GROUP_ARITH_REAL_LD1)
      #pragma message("enabling SVE_GROUP_ARITH_REAL_LD1")
      #define SVE_SUM
      #define SVE_SUB
      #define SVE_MULT
      #define SVE_MULTREALPART_REAL_LD1
      #define SVE_MADDREALPART_REAL_LD1
      #define SVE_MULTCOMPLEX_REAL_LD1
      #define SVE_DIV
      #define SVE_CONJ
      #define SVE_TIMESMINUSI
      #define SVE_TIMESI
  //  #define SVE_REDUCE
      #define SVE_REDUCE_REAL_LD2

    #elif defined(SVE_GROUP_ARITH_REAL_LD2)
      #pragma message("enabling SVE_GROUP_ARITH_REAL_LD2")
      #define SVE_SUM_LD2
      #define SVE_SUB
      #define SVE_MULT
      #define SVE_MULTREALPART_REAL_LD2
      #define SVE_MADDREALPART_REAL_LD2
      #define SVE_MULTCOMPLEX_REAL_LD2
      #define SVE_DIV
      #define SVE_CONJ_REAL_LD2
      #define SVE_TIMESMINUSI_REAL_LD2
      #define SVE_TIMESI_REAL_LD2
      #define SVE_REDUCE_REAL_LD2

    #elif defined(SVE_GROUP_ARITH_REAL_REF)
      #pragma message("enabling SVE_GROUP_ARITH_REAL_REF")
      #define SVE_SUM_REF
      #define SVE_SUB_REF
      #define SVE_MULT_REF
      #define SVE_MULTREALPART_REAL_REF
      #define SVE_MADDREALPART_REAL_REF
      #define SVE_MULTCOMPLEX_REAL_REF
      #define SVE_DIV_REF
      #define SVE_CONJ_REF
      #define SVE_TIMESMINUSI_REF
      #define SVE_TIMESI_REF
      #define SVE_REDUCE_REF

    #endif

    #if defined(SVE_GROUP_PREC)
      #pragma message("enabling SVE_GROUP_PREC")
      #define SVE_PREC
    #endif

    #if defined(SVE_GROUP_PERM)
      #pragma message("enabling SVE_GROUP_PERM")
      #define SVE_ROTATE
      #define SVE_PERMUTE
      #define SVE_EXCHANGE

    #elif defined(SVE_GROUP_PERM_REF)
      #pragma message("enabling SVE_GROUP_PERM_REF")
      #define SVE_ROTATE_REF
      #define SVE_PERMUTE_REF
      #define SVE_EXCHANGE_REF
    #endif

    #if defined(SVE_GROUP_PREFETCH)
      #pragma message("enabling SVE_GROUP_PREFETCH")
      #define SVE_PREFETCH
    #endif

  #endif // GENSVE

  #if defined(GENSVE) && defined(SVE_VSPLAT)
  #include "sve/sve_vsplat.h"
  #elif defined(GENSVE) && defined(SVE_VSPLAT_REF)
  #include "sve/sve_vsplat_ref.h"
  #else
  #pragma message("generic Vsplat")
  struct Vsplat{
    // Complex
    template <typename T>
    inline vec<T> operator()(const T a, const T b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::r, 2)
      {
        out.v[i]   = a;
        out.v[i+1] = b;
      }

      return out;
    }

    // Real
    template <typename T>
    inline vec<T> operator()(const T a){
      vec<T> out;

      VECTOR_FOR(i, W<T>::r, 1)
      {
        out.v[i] = a;
      }

      return out;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_VSTORE)
  #include "sve/sve_vstore.h"
  #elif defined(GENSVE) && defined(SVE_VSTORE_REF)
  #include "sve/sve_vstore_ref.h"
  #else
  #pragma message("generic Vstore")
  struct Vstore{
    // Real
    template <typename T>
    inline void operator()(const vec<T> &a, T *D){
      *((vec<T> *)D) = a;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_VSTREAM)
  #include "sve/sve_vstream.h"
  #elif defined(GENSVE) && defined(SVE_VSTREAM_REF)
  #include "sve/sve_vstream_ref.h"
  #else
  #pragma message("generic Vstream")
  struct Vstream{
    // Real
    template <typename T>
    inline void operator()(T * a, const vec<T> &b){
      *((vec<T> *)a) = b;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_VSET)
  #include "sve/sve_vset.h"
  #elif defined(GENSVE) && defined(SVE_VSET_REF)
  #include "sve/sve_vset_ref.h"
  #else
  #pragma message("generic Vset")
  struct Vset{
    // Complex
    template <typename T>
    inline vec<T> operator()(const std::complex<T> *a){
      vec<T> out;

      VECTOR_FOR(i, W<T>::c, 1)
      {
        out.v[2*i]   = a[i].real();
        out.v[2*i+1] = a[i].imag();
      }

      return out;
    }

    // Real
    template <typename T>
    inline vec<T> operator()(T *a){
      vec<T> out;

      out = *((vec<T> *)a);

      return out;
    }
  };

  #endif

  /////////////////////////////////////////////////////
  // Arithmetic operations
  /////////////////////////////////////////////////////

  #if defined(GENSVE) && defined(SVE_SUM_REF)
  #include "sve/sve_sum_ref.h"
  #elif defined(GENSVE) && defined(SVE_SUM_LD2)
  #include "sve/sve_sum_sls.h"
  #elif defined(GENSVE) && defined(SVE_SUM)
  #include "sve/sve_sum.h"
  #else
  #pragma message("generic Sum")
  struct Sum{
    // Complex/Real
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::r, 1)
      {
        out.v[i] = a.v[i] + b.v[i];
      }

      return out;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_SUB_REF)
  #include "sve/sve_sub_ref.h"
  #elif defined(GENSVE) && defined(SVE_SUB)
  #include "sve/sve_sub.h"
  #else
  #pragma message("generic Sub")
  struct Sub{
    // Complex/Real
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::r, 1)
      {
        out.v[i] = a.v[i] - b.v[i];
      }

      return out;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_MULT_REF)
  #include "sve/sve_mult_ref.h"
  #elif defined(GENSVE) && defined(SVE_MULT)
  #include "sve/sve_mult.h"
  #else
  #pragma message("generic Mult")
  struct Mult{
    // Real
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::r, 1)
      {
        out.v[i] = a.v[i]*b.v[i];
      }

      return out;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_MULTREALPART_CPLX_REF)
  #include "sve/sve_multrealpart_ref.h"
  #elif defined(GENSVE) && defined(SVE_MULTREALPART_CPLX_LD1)
  #include "sve/sve_multrealpart.h"
  #elif defined(GENSVE) && defined(SVE_MULTREALPART_REAL_LD1)
  #include "sve/sve_multrealpart_real.h"
  #elif defined(GENSVE) && defined(SVE_MULTREALPART_REAL_LD2)
  #include "sve/sve_multrealpart_sls.h"
  #elif defined(GENSVE) && defined(SVE_MULTREALPART_REAL_REF)
  #include "sve/sve_multrealpart_real_ref.h"
  #else
  #pragma message("generic MultRealPart")
  struct MultRealPart{
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::c, 1)
      {
         out.v[2*i]   = a.v[2*i]*b.v[2*i];
         out.v[2*i+1] = a.v[2*i]*b.v[2*i+1];
      }
      return out;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_MADDREALPART_REF)
  #include "sve/sve_maddrealpart_ref.h"
  #elif defined(GENSVE) && defined(SVE_MADDREALPART_REAL_REF)
  #include "sve/sve_maddrealpart_real_ref.h"
  #elif defined(GENSVE) && defined(SVE_MADDREALPART_REAL_LD1)
  #include "sve/sve_maddrealpart_real.h"
  #elif defined(GENSVE) && defined(SVE_MADDREALPART_REAL_LD2)
  #include "sve/sve_maddrealpart_sls.h"
  #elif defined(GENSVE) && defined(SVE_MADDREALPART_CPLX_LD1)
  #include "sve/sve_maddrealpart.h"
  #else
  #pragma message("generic MaddRealPart")
  struct MaddRealPart{
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b, const vec<T> &c){
      vec<T> out;

      VECTOR_FOR(i, W<T>::c, 1)
      {
         out.v[2*i]   = a.v[2*i]*b.v[2*i] + c.v[2*i];
         out.v[2*i+1] = a.v[2*i]*b.v[2*i+1] + c.v[2*i+1];
      }
      return out;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_MULTCOMPLEX_CPLX_LD1)
  #include "sve/sve_multcomplex.h"
  #elif defined(GENSVE) && defined(SVE_MULTCOMPLEX_CPLX_REF)
  #include "sve/sve_multcomplex_ref.h"
  #elif defined(GENSVE) && defined(SVE_MULTCOMPLEX_REAL_LD2)
  #include "sve/sve_multcomplex_sls.h"
  #elif defined(GENSVE) && defined(SVE_MULTCOMPLEX_REAL_LD1)
  #include "sve/sve_multcomplex_real.h"
  #elif defined(GENSVE) && defined(SVE_MULTCOMPLEX_REAL_REF)
  #include "sve/sve_multcomplex_real_ref.h"
  #else

  #pragma message("generic MultComplex")
  #define cmul(a, b, c, i)\
  c[i]   = a[i]*b[i]   - a[i+1]*b[i+1];\
  c[i+1] = a[i]*b[i+1] + a[i+1]*b[i];

  struct MultComplex{
    // Complex
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::c, 1)
      {
        cmul(a.v, b.v, out.v, 2*i);
      }

      return out;
    }
  };

  #undef cmul

  #endif

/*
  #if defined(GENSVE) && defined(SVE_MADDCOMPLEX)
  #include "sve/sve_maddcomplex.h"
  #endif
*/

  #if defined(GENSVE) && defined(SVE_DIV_REF)
  #include "sve/sve_div_ref.h"
  #elif defined(GENSVE) && defined(SVE_DIV)
  #include "sve/sve_div.h"
  #else
  #pragma message("generic Div")
  struct Div{
    // Real
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::r, 1)
      {
        out.v[i] = a.v[i]/b.v[i];
      }

      return out;
    }
  };

  #endif

  #if defined(GENSVE) && defined(SVE_CONJ_REF)
  #include "sve/sve_conj_ref.h"
  #elif defined(GENSVE) && defined(SVE_CONJ_REAL_LD2)
  #include "sve/sve_conj_sls.h"
  #elif defined(GENSVE) && defined(SVE_CONJ)
  #include "sve/sve_conj.h"
  #else
  #pragma message("generic Conj")
  #define conj(a, b, i)\
  b[i]   = a[i];\
  b[i+1] = -a[i+1];

  struct Conj{
    // Complex
    template <typename T>
    inline vec<T> operator()(const vec<T> &a){
      vec<T> out;

      VECTOR_FOR(i, W<T>::c, 1)
      {
        conj(a.v, out.v, 2*i);
      }

      return out;
    }
  };

  #undef conj

  #endif

  #if defined(GENSVE) && defined(SVE_TIMESMINUSI_REF)
  #include "sve/sve_timesminusi_ref.h"
  #elif defined(GENSVE) && defined(SVE_TIMESMINUSI_REAL_LD2)
  #include "sve/sve_timesminusi_sls.h"
  #elif defined(GENSVE) && defined(SVE_TIMESMINUSI)
  #include "sve/sve_timesminusi.h"
  #else
  #pragma message("generic TimesMi")
  #define timesmi(a, b, i)\
  b[i]   = a[i+1];\
  b[i+1] = -a[i];

  struct TimesMinusI{
    // Complex
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::c, 1)
      {
        timesmi(a.v, out.v, 2*i);
      }

      return out;
    }
  };

  #undef timesmi

  #endif

  #if defined(GENSVE) && defined(SVE_TIMESI_REF)
  #include "sve/sve_timesi_ref.h"
  #elif defined(GENSVE) && defined(SVE_TIMESI_REAL_LD2)
  #include "sve/sve_timesi_sls.h"
  #elif defined(GENSVE) && defined(SVE_TIMESI)
  #include "sve/sve_timesi.h"
  #else
  #pragma message("generic Timesi")
  #define timesi(a, b, i)\
  b[i]   = -a[i+1];\
  b[i+1] = a[i];

  struct TimesI{
    // Complex
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){
      vec<T> out;

      VECTOR_FOR(i, W<T>::c, 1)
      {
        timesi(a.v, out.v, 2*i);
      }

      return out;
    }
  };

  #undef timesi

  #endif

  #if defined(GENSVE) && defined(SVE_PREC)
  #include "sve/sve_prec.h"
  #else
  #pragma message("generic PrecisionChange")
  struct PrecisionChange {
    static inline vech StoH (const vecf &a, const vecf &b) {
      vech ret;
#ifdef USE_FP16
      vech *ha = (vech *)&a;
      vech *hb = (vech *)&b;
      const int nf = W<float>::r;
      //      VECTOR_FOR(i, nf,1){ ret.v[i]    = ( (uint16_t *) &a.v[i])[1] ; }
      //      VECTOR_FOR(i, nf,1){ ret.v[i+nf] = ( (uint16_t *) &b.v[i])[1] ; }
      VECTOR_FOR(i, nf,1){ ret.v[i]    = ha->v[2*i+1]; }
      VECTOR_FOR(i, nf,1){ ret.v[i+nf] = hb->v[2*i+1]; }
#else
      assert(0);
#endif
      return ret;
    }
    static inline void  HtoS (const vech &h, vecf &sa,vecf &sb) {
#ifdef USE_FP16
      const int nf = W<float>::r;
      const int nh = W<uint16_t>::r;
      vech *ha = (vech *)&sa;
      vech *hb = (vech *)&sb;
      VECTOR_FOR(i, nf, 1){ sb.v[i]= sa.v[i] = 0; }
      //      VECTOR_FOR(i, nf, 1){ ( (uint16_t *) (&sa.v[i]))[1] = h.v[i];}
      //      VECTOR_FOR(i, nf, 1){ ( (uint16_t *) (&sb.v[i]))[1] = h.v[i+nf];}
      VECTOR_FOR(i, nf, 1){ ha->v[2*i+1]=h.v[i]; }
      VECTOR_FOR(i, nf, 1){ hb->v[2*i+1]=h.v[i+nf]; }
#else
      assert(0);
#endif
    }
    static inline vecf DtoS (const vecd &a, const vecd &b) {
      const int nd = W<double>::r;
      const int nf = W<float>::r;
      vecf ret;
      VECTOR_FOR(i, nd,1){ ret.v[i]    = a.v[i] ; }
      VECTOR_FOR(i, nd,1){ ret.v[i+nd] = b.v[i] ; }
      return ret;
    }
    static inline void StoD (const vecf &s, vecd &a, vecd &b) {
      const int nd = W<double>::r;
      VECTOR_FOR(i, nd,1){ a.v[i] = s.v[i] ; }
      VECTOR_FOR(i, nd,1){ b.v[i] = s.v[i+nd] ; }
    }
    static inline vech DtoH (const vecd &a, const vecd &b, const vecd &c, const vecd &d) {
      vecf sa,sb;
      sa = DtoS(a,b);
      sb = DtoS(c,d);
      return StoH(sa,sb);
    }
    static inline void HtoD (const vech &h, vecd &a, vecd &b, vecd &c, vecd &d) {
      vecf sa,sb;
      HtoS(h,sa,sb);
      StoD(sa,a,b);
      StoD(sb,c,d);
    }
  };

  #endif

  //////////////////////////////////////////////
  // Exchange support

  #if defined(GENSVE) && defined(SVE_EXCHANGE)
  #include "sve/sve_exchange.h"
  #elif defined(GENSVE) && defined(SVE_EXCHANGE_REF)
  #include "sve/sve_exchange_ref.h"
  #else
  #pragma message("generic Exchange")
  struct Exchange{

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
    static inline void Exchange0(vec<T> &out1, vec<T> &out2, const vec<T> &in1, const vec<T> &in2){
      ExchangeN<T,0>(out1,out2,in1,in2);
    };
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
  };

  #endif


  #if defined(GENSVE) && defined(SVE_PERMUTE)
  #include "sve/sve_permute.h"
  #elif defined(GENSVE) && defined(SVE_PERMUTE_REF)
  #include "sve/sve_permute_ref.h"
  #else
  #pragma message("generic Permute")
  //////////////////////////////////////////////
  // Some Template specialization
  #define perm(a, b, n, w)\
  unsigned int _mask = w >> (n + 1);\
  VECTOR_FOR(i, w, 1)\
  {\
    b[i] = a[i^_mask];\
  }

  #define DECL_PERMUTE_N(n)\
  template <typename T>\
  static inline vec<T> Permute##n(vec<T> in) {\
    vec<T> out;\
    perm(in.v, out.v, n, W<T>::r);\
    return out;\
  }

  struct Permute{
    DECL_PERMUTE_N(0);
    DECL_PERMUTE_N(1);
    DECL_PERMUTE_N(2);
    DECL_PERMUTE_N(3);
  };

  #undef perm
  #undef DECL_PERMUTE_N

  #endif

  #if defined(GENSVE) && defined(SVE_ROTATE)
  #include "sve/sve_rotate.h"
  #elif defined(GENSVE) && defined(SVE_ROTATE_REF)
  #include "sve/sve_rotate_ref.h"
  #else
  #pragma message("generic Rotate")
  #define rot(a, b, n, w)\
  VECTOR_FOR(i, w, 1)\
  {\
    b[i] = a[(i + n)%w];\
  }

  struct Rotate{

    template <int n, typename T> static inline vec<T> tRotate(const vec<T> &in){
      return rotate(in, n);
    }

    template <typename T>
    static inline vec<T> rotate(const vec<T> &in, const int n){
      vec<T> out;

      rot(in.v, out.v, n, W<T>::r);

      return out;
    }
  };

  #undef rot

  #endif

  #if defined(GENSVE) && defined(SVE_REDUCE)
  #include "sve/sve_reduce.h"
  #elif defined(GENSVE) && defined(SVE_REDUCE_REF)
  #include "sve/sve_reduce_ref.h"
  #elif defined(GENSVE) && defined(SVE_REDUCE_REAL_LD2)
  #include "sve/sve_reduce_sls.h"
  #else
  #pragma message("generic Reduce")
  #define acc(v, a, off, step, n)\
  for (unsigned int i = off; i < n; i += step)\
  {\
    a += v[i];\
  }

  template <typename Out_type, typename In_type>
  struct Reduce{
    //Need templated class to overload output type
    //General form must generate error if compiled
    inline Out_type operator()(const In_type &in){
      printf("Error, using wrong Reduce function\n");
      exit(1);
      return 0;
    }
  };

  //Complex float Reduce
  template <>
  inline Grid::ComplexF Reduce<Grid::ComplexF, vecf>::operator()(const vecf &in){
    float a = 0.f, b = 0.f;

    acc(in.v, a, 0, 2, W<float>::r);
    acc(in.v, b, 1, 2, W<float>::r);

    return Grid::ComplexF(a, b);
  }

  //Real float Reduce
  template<>
  inline Grid::RealF Reduce<Grid::RealF, vecf>::operator()(const vecf &in){
    float a = 0.;

    acc(in.v, a, 0, 1, W<float>::r);

    return a;
  }

  //Complex double Reduce
  template<>
  inline Grid::ComplexD Reduce<Grid::ComplexD, vecd>::operator()(const vecd &in){
    double a = 0., b = 0.;

    acc(in.v, a, 0, 2, W<double>::r);
    acc(in.v, b, 1, 2, W<double>::r);

    return Grid::ComplexD(a, b);
  }

  //Real double Reduce
  template<>
  inline Grid::RealD Reduce<Grid::RealD, vecd>::operator()(const vecd &in){
    double a = 0.f;

    acc(in.v, a, 0, 1, W<double>::r);

    return a;
  }

  //Integer Reduce
  template<>
  inline Integer Reduce<Integer, veci>::operator()(const veci &in){
    Integer a = 0;

    acc(in.v, a, 0, 1, W<Integer>::r);

    return a;
  }

  #undef acc  // EIGEN compatibility

  #endif

  #if defined(GENSVE) && defined(__clang__)
  inline int sve_vector_width(){return svcntb();}
  #else
  inline int sve_vector_width(){return GEN_SIMD_WIDTH;}
  #endif
}

//////////////////////////////////////////////////////////////////////////////////////
// Here assign types

  typedef Optimization::vech SIMD_Htype; // Reduced precision type
  typedef Optimization::vecf SIMD_Ftype; // Single precision type
  typedef Optimization::vecd SIMD_Dtype; // Double precision type
  typedef Optimization::veci SIMD_Itype; // Integer type

  // prefetch utilities

  #if defined(GENSVE) && defined (SVE_PREFETCH)
  #include "sve/sve_prefetch.h"
  #else
  inline void v_prefetch0(int size, const char *ptr){};
  inline void prefetch_HINT_T0(const char *ptr){};
  #endif

  // Function name aliases
  typedef Optimization::Vsplat   VsplatSIMD;
  typedef Optimization::Vstore   VstoreSIMD;
  typedef Optimization::Vset     VsetSIMD;
  typedef Optimization::Vstream  VstreamSIMD;
  template <typename S, typename T> using ReduceSIMD = Optimization::Reduce<S,T>;

  // Arithmetic operations
  typedef Optimization::Sum         SumSIMD;
  typedef Optimization::Sub         SubSIMD;
  typedef Optimization::Div         DivSIMD;
  typedef Optimization::Mult        MultSIMD;
  typedef Optimization::MultComplex MultComplexSIMD;
  typedef Optimization::MultRealPart MultRealPartSIMD;
  typedef Optimization::MaddRealPart MaddRealPartSIMD;
/*
  #if defined (GENSVE) && defined(SVE_MULTCOMPLEX)
  typedef Optimization::MaddComplex MaddComplexSIMD;
  #endif
*/
  typedef Optimization::Conj        ConjSIMD;
  typedef Optimization::TimesMinusI TimesMinusISIMD;
  typedef Optimization::TimesI      TimesISIMD;
}
