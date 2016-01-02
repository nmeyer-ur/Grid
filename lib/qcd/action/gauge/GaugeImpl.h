#ifndef  GRID_QCD_GAUGE_IMPL_H
#define  GRID_QCD_GAUGE_IMPL_H

namespace Grid {

  namespace QCD {

    
    ////////////////////////////////////////////////////////////////////////
    // Implementation dependent gauge types
    ////////////////////////////////////////////////////////////////////////

template<class Gimpl> class WilsonLoops;

#define INHERIT_GIMPL_TYPES(GImpl) \
    typedef typename GImpl::Simd                           Simd;\
    typedef typename GImpl::GaugeLinkField       GaugeLinkField;\
    typedef typename GImpl::GaugeField               GaugeField;	

    
    // Composition with smeared link, bc's etc.. probably need multiple inheritance
    // Variable precision "S" and variable Nc
    template<class S,int Nrepresentation=Nc>
    class PeriodicGaugeImpl { 
    public:
    
      typedef S Simd;
    
      template<typename vtype> using iImplGaugeLink          = iScalar<iScalar<iMatrix<vtype, Nrepresentation> > >;
      template<typename vtype> using iImplGaugeField         = iVector<iScalar<iMatrix<vtype, Nrepresentation> >, Nd  >;
    
      typedef iImplGaugeLink    <Simd>           SiteGaugeLink;
      typedef iImplGaugeField   <Simd>           SiteGaugeField;
    
      typedef Lattice<SiteGaugeLink>                GaugeLinkField; // bit ugly naming; polarised gauge field, lorentz... all ugly
      typedef Lattice<SiteGaugeField>                   GaugeField;
     
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Support needed for the assembly of loops including all boundary condition effects such as conjugate bcs
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
      template<class covariant>  static inline
      Lattice<covariant> CovShiftForward (const GaugeLinkField &Link, int mu, const Lattice<covariant> &field) {
	return PeriodicBC::CovShiftForward(Link,mu,field);
      }

      template<class covariant> static inline
      Lattice<covariant> CovShiftBackward(const GaugeLinkField &Link, int mu,const Lattice<covariant> &field) {
	return PeriodicBC::CovShiftBackward(Link,mu,field);
      }
      static inline
      GaugeLinkField CovShiftIdentityBackward(const GaugeLinkField &Link, int mu) {
	return Cshift(adj(Link),mu,-1);
      }
      static inline
      GaugeLinkField CovShiftIdentityForward(const GaugeLinkField &Link, int mu) {
	return Link;
      }
      static inline
      GaugeLinkField ShiftStaple(const GaugeLinkField &Link, int mu) {
	return Cshift(Link,mu,1);
      }

      static inline bool isPeriodicGaugeField(void) {
	return true;
      }


    };

    
    // Composition with smeared link, bc's etc.. probably need multiple inheritance
    // Variable precision "S" and variable Nc
    template<class S,int Nrepresentation=Nc>
    class ConjugateGaugeImpl { 
    public:
    
      typedef S Simd;
    
      template<typename vtype> using iImplGaugeLink          = iScalar<iScalar<iMatrix<vtype, Nrepresentation> > >;
      template<typename vtype> using iImplGaugeField         = iVector<iScalar<iMatrix<vtype, Nrepresentation> >, Nd  >;
    
      typedef iImplGaugeLink    <Simd>           SiteGaugeLink;
      typedef iImplGaugeField   <Simd>           SiteGaugeField;
    
      typedef Lattice<SiteGaugeLink>                GaugeLinkField; // bit ugly naming; polarised gauge field, lorentz... all ugly
      typedef Lattice<SiteGaugeField>                   GaugeField;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Support needed for the assembly of loops including all boundary condition effects such as Gparity.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class covariant>  static
    Lattice<covariant> CovShiftForward (const GaugeLinkField &Link, int mu, const Lattice<covariant> &field) {
      return GparityBC::CovShiftForward(Link,mu,field);
    }

    template<class covariant> static
    Lattice<covariant> CovShiftBackward(const GaugeLinkField &Link, int mu,const Lattice<covariant> &field) {
      return GparityBC::CovShiftBackward(Link,mu,field);
    }

    static inline
    GaugeLinkField CovShiftIdentityBackward(const GaugeLinkField &Link, int mu) {
      GridBase *grid = Link._grid;
      int Lmu = grid->GlobalDimensions()[mu]-1;
      
      Lattice<iScalar<vInteger> > coor(grid);    LatticeCoordinate(coor,mu);

      GaugeLinkField tmp (grid);
      tmp=adj(Link);
      tmp = where(coor==Lmu,conjugate(tmp),tmp);
      return Cshift(tmp,mu,-1);// moves towards positive mu
    }
    static inline
    GaugeLinkField CovShiftIdentityForward(const GaugeLinkField &Link, int mu) {
      return Link;
    }

    static inline
    GaugeLinkField ShiftStaple(const GaugeLinkField &Link, int mu) {
      GridBase *grid = Link._grid;
      int Lmu = grid->GlobalDimensions()[mu]-1;
      
      Lattice<iScalar<vInteger> > coor(grid);    LatticeCoordinate(coor,mu);

      GaugeLinkField tmp (grid);
      tmp=Cshift(Link,mu,1);
      tmp=where(coor==Lmu,conjugate(tmp),tmp);
      return tmp;
    }

    static inline bool isPeriodicGaugeField(void) {
      return false;
    }
    
    };


    typedef PeriodicGaugeImpl<vComplex ,Nc> PeriodicGimplR; // Real.. whichever prec
    typedef PeriodicGaugeImpl<vComplexF,Nc> PeriodicGimplF; // Float
    typedef PeriodicGaugeImpl<vComplexD,Nc> PeriodicGimplD; // Double

    typedef ConjugateGaugeImpl<vComplex ,Nc> ConjugateGimplR; // Real.. whichever prec
    typedef ConjugateGaugeImpl<vComplexF,Nc> ConjugateGimplF; // Float
    typedef ConjugateGaugeImpl<vComplexD,Nc> ConjugateGimplD; // Double

  }
}

#endif