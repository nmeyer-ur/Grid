/*************************************************************************************

    Grid physics library, www.github.com/paboyle/Grid 

    Source file: ./lib/tensors/Tensor_extract_merge.h

    Copyright (C) 2015

Author: Azusa Yamaguchi <ayamaguc@staffmail.ed.ac.uk>
Author: Peter Boyle <paboyle@ph.ed.ac.uk>
Author: neo <cossu@post.kek.jp>
Author: paboyle <paboyle@ph.ed.ac.uk>
Author: Christopher Kelly <ckelly@phys.columbia.edu>

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
#pragma once 

NAMESPACE_BEGIN(Grid);

/////////////////////////////////////////////////////////////////
// Generic extract/merge/permute
/////////////////////////////////////////////////////////////////

template<class __T> using ExtractPointerArray = AcceleratorVector<__T *,GRID_MAX_SIMD>;
template<class __T> using ExtractBuffer       = AcceleratorVector<__T  ,GRID_MAX_SIMD>;

//void extract(const vobj &vec,ExtractBuffer<typename vobj::scalar_object> &extracted);
//void extract(const vobj &vec,ExtractPointerArray<sobj> &extracted, int offset);
//void   merge(vobj &vec,ExtractBuffer<typename vobj::scalar_object> &extracted)
//void   merge(vobj &vec,ExtractPointerArray<typename vobj::scalar_object> &extracted)
//

////////////////////////////////////////////////////////////////////////
// Extract to contiguous array scalar object
////////////////////////////////////////////////////////////////////////
template<class vobj,class sobj> accelerator
void extract(const vobj &vec,ExtractBuffer<sobj> &extracted)
{
  typedef typename GridTypeMapper<sobj>::scalar_type sobj_scalar_type;
  typedef typename GridTypeMapper<vobj>::scalar_type scalar_type;
  typedef typename GridTypeMapper<vobj>::vector_type vector_type;

  const int words=sizeof(vobj)/sizeof(vector_type);
  const int Nsimd=vector_type::Nsimd();
  const int Nextr=extracted.size();
  const int s=Nsimd/Nextr;

  sobj_scalar_type *sp = (sobj_scalar_type *)&extracted[0];
  scalar_type *vp = (scalar_type *)&vec;
  for(int w=0;w<words;w++){
    for(int i=0;i<Nextr;i++){
      sp[i*words+w] = vp[w*Nsimd+i*s] ;
    }
  }
  return;
}

////////////////////////////////////////////////////////////////////////
// Merge a contiguous array of scalar objects
////////////////////////////////////////////////////////////////////////
template<class vobj,class sobj> accelerator
void   merge(vobj &vec,ExtractBuffer<sobj> &extracted)
{
  typedef typename GridTypeMapper<sobj>::scalar_type sobj_scalar_type;
  typedef typename GridTypeMapper<vobj>::scalar_type scalar_type;
  typedef typename GridTypeMapper<vobj>::vector_type vector_type;

  const int words=sizeof(vobj)/sizeof(vector_type);
  const int Nsimd=vector_type::Nsimd();
  const int Nextr = extracted.size();
  const int s=Nsimd/Nextr;

  sobj_scalar_type *sp = (sobj_scalar_type *)&extracted[0];
  scalar_type *vp = (scalar_type *)&vec;
  for(int w=0;w<words;w++){
    for(int i=0;i<Nextr;i++){
      for(int ii=0;ii<s;ii++){
	vp[w*Nsimd+i*s+ii] = sp[i*words+w] ;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////
// Extract to a bunch of scalar object pointers of different scalar type, with offset. Useful for precision change
////////////////////////////////////////////////////////////////////////
template<class vobj, class sobj> accelerator
void extract(const vobj &vec,ExtractPointerArray<sobj> &extracted, int offset)
{
  typedef typename GridTypeMapper<sobj>::scalar_type sobj_scalar_type;
  typedef typename GridTypeMapper<vobj>::scalar_type scalar_type;
  typedef typename GridTypeMapper<vobj>::vector_type vector_type;

  const int words=sizeof(vobj)/sizeof(vector_type);
  const int Nsimd=vector_type::Nsimd();
  const int Nextr=extracted.size();
  const int s = Nsimd/Nextr;

  scalar_type * vp = (scalar_type *)&vec;
  
  for(int w=0;w<words;w++){
    for(int i=0;i<Nextr;i++){
      sobj_scalar_type * pointer = (sobj_scalar_type *)& extracted[i][offset];
      scalar_type tmp =vp[w*Nsimd+i*s];
      //      assert(w*sizeof(sobj_scalar_type)<sizeof(sobj));
      pointer[w] = tmp; // may do a precision conversion
    }
  }
}

////////////////////////////////////////////////////////////////////////
// Merge bunch of scalar object pointers of different scalar type, with offset. Useful for precision change
////////////////////////////////////////////////////////////////////////
template<class vobj, class sobj> accelerator
void merge(vobj &vec,ExtractPointerArray<sobj> &extracted, int offset)
{
  typedef typename GridTypeMapper<sobj>::scalar_type sobj_scalar_type;
  typedef typename GridTypeMapper<vobj>::scalar_type scalar_type;
  typedef typename GridTypeMapper<vobj>::vector_type vector_type;

  const int words=sizeof(vobj)/sizeof(vector_type);
  const int Nsimd=vector_type::Nsimd();
  const int Nextr=extracted.size();
  const int s = Nsimd/Nextr;

  scalar_type * vp = (scalar_type *)&vec;
  for(int w=0;w<words;w++){
    for(int i=0;i<Nextr;i++){
      sobj_scalar_type * pointer = (sobj_scalar_type *)& extracted[i][offset];
      for(int ii=0;ii<s;ii++){
	vp[w*Nsimd+i*s+ii] = pointer[w] ;
      }
    }
  }
}


NAMESPACE_END(Grid);

