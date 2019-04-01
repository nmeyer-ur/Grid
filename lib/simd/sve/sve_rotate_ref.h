#ifndef SVE_ROTATE_H
#define SVE_ROTATE_H

#pragma message("include sve_rotate_ref.h using references")

  struct Rotate{

    template <int n, typename T> static inline vec<T> tRotate(const vec<T> &in){

      // using ptrs is UNSAFE here !!!
      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
/*
      typename acle<T>::vt *a_v = (typename acle<T>::vt*)&in.v;
      typename acle<T>::vt *r_v = (typename acle<T>::vt*)&out.v;
      *r_v = svext(*a_v, *a_v, (uint64_t)(n%W<T>::r));
*/
      typename acle<T>::vt a_v = svld1(pg1, in.v);
      typename acle<T>::vt r_v = svext(a_v, a_v, (uint64_t)(n%W<T>::r));
      svst1(pg1, out.v, r_v);

      return out;
    }

    template <typename T>
    static inline vec<T> rotate(const vec<T> &in, const int n){

      switch(n){
      case 0:  return tRotate<0,  T>(in); break;
      case 1:  return tRotate<1,  T>(in); break;
      case 2:  return tRotate<2,  T>(in); break;
      case 3:  return tRotate<3,  T>(in); break;
      case 4:  return tRotate<4,  T>(in); break;
      case 5:  return tRotate<5,  T>(in); break;
      case 6:  return tRotate<6,  T>(in); break;
      case 7:  return tRotate<7,  T>(in); break;

      case 8:  return tRotate<8,  T>(in); break;
      case 9:  return tRotate<9,  T>(in); break;
      case 10: return tRotate<10, T>(in); break;
      case 11: return tRotate<11, T>(in); break;
      case 12: return tRotate<12, T>(in); break;
      case 13: return tRotate<13, T>(in); break;
      case 14: return tRotate<14, T>(in); break;
      case 15: return tRotate<15, T>(in); break;
      default: assert(0);
      }
    }
  };


#endif
