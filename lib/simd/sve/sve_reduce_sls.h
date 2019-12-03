#ifndef SVE_REDUCE_SLS_H
#define SVE_REDUCE_SLS_H

#pragma message("include sve_reduce_sls.h")

  // tree-based reduction
#define svred(pg,v) \
  svaddv(pg,v)

  // left-to-right reduction
  // #define svred(pg, v)\
  // svadda(pg, 0, v)

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

/*
    svbool_t pg1 = acle<float>::pg1();
    svbool_t pg_even = acle<float>::pg_even();
    svbool_t pg_odd  = acle<float>::pg_odd();
    typename acle<float>::vt a_v = svld1(pg1, in.v);
    float a = svred(pg_even, a_v);
    float b = svred(pg_odd, a_v);

    return Grid::ComplexF(a, b);
*/

// LD2: tested, working
    svbool_t pg2 = acle<float>::pg2();
    typename acle<float>::vt2 a_v = svld2(pg2, in.v);
    typename acle<float>::pt a = static_cast<typename acle<float>::pt>(svred(pg2, a_v.v0));
    typename acle<float>::pt b = static_cast<typename acle<float>::pt>(svred(pg2, a_v.v1));

    return Grid::ComplexF(a, b);

  }

  //Real float Reduce
  template <>
  inline Grid::RealF Reduce<Grid::RealF, vecf>::operator()(const vecf &in){

    svbool_t pg1 = acle<float>::pg1();
    typename acle<float>::vt a_v = svld1(pg1, in.v);
    float a = svred(pg1, a_v);

    return a;
  }

  //Complex double Reduce
  template <>
  inline Grid::ComplexD Reduce<Grid::ComplexD, vecd>::operator()(const vecd &in){
/*
    svbool_t pg1 = acle<double>::pg1();
    svbool_t pg_even = acle<double>::pg_even();
    svbool_t pg_odd  = acle<double>::pg_odd();
    typename acle<double>::vt a_v = svld1(pg1, in.v);
    double a = svred(pg_even, a_v);
    double b = svred(pg_odd, a_v);

    return Grid::ComplexD(a, b);
*/

// LD2: tested, working
    svbool_t pg2 = acle<double>::pg2();
    typename acle<double>::vt2 a_v = svld2(pg2, in.v);
    typename acle<double>::pt a = static_cast<typename acle<double>::pt>(svred(pg2, a_v.v0));
    typename acle<double>::pt b = static_cast<typename acle<double>::pt>(svred(pg2, a_v.v1));

    return Grid::ComplexD(a, b);
  }

  //Real double Reduce
  template <>
  inline Grid::RealD Reduce<Grid::RealD, vecd>::operator()(const vecd &in){

    svbool_t pg1 = acle<double>::pg1();
    typename acle<double>::vt a_v = svld1(pg1, in.v);
    double a = svred(pg1, a_v);

    return a;
  }

  //Integer Reduce
  template <>
  inline Integer Reduce<Integer, veci>::operator()(const veci &in){

    svbool_t pg1 = acle<Integer>::pg1();
    typename acle<Integer>::vt a_v = svld1(pg1, in.v);
    Integer a = svred(pg1, a_v);

    return a;
  }

  #undef svred

#endif
