#ifndef SVE_PREFETCH_H
#define SVE_PREFETCH_H

#pragma message("include sve_prefetch.h")

  // this is never used anywhere !
  inline void v_prefetch0(int size, const char *ptr){};

  inline void prefetch_HINT_T0(const char *ptr){

    // not sure which one to pick, so disabling

    //svbool_t pg1 = Optimization::acle<double>::pg1();
    //svprfb(pg1, (const signed char*)ptr, SV_PLDL1KEEP);

    //svprfd(pg1, ptr, SV_PLDL1STRM);
  };

#endif
