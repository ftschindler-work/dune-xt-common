// This file is part of the dune-stuff project:
//   https://github.com/wwu-numerik/dune-stuff
// Copyright holders: Rene Milk, Felix Schindler
// License: BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)

#warning Will be removed soon, file an issue on https://github.com/wwu-numerik/dune-stuff/issues if you need this (09.02.2015)!

#ifndef STUFF_LOCALMASSMATRIX_HH
#define STUFF_LOCALMASSMATRIX_HH

#if HAVE_DUNE_FEM

#include <dune/common/deprecated.hh>
#include <dune/common/version.hh>

#include <dune/fem/operator/1order/localmassmatrix.hh>

namespace Dune {
namespace Stuff {
namespace Fem {

//! create yet another child class just in case fem actually implements something in LocalMassMatrix in addition to its
//! base
template <class DiscreteFunctionSpaceImp, class VolumeQuadratureImp>
struct DUNE_DEPRECATED_MSG("Will be removed soon, file an issue on https://github.com/wwu-numerik/dune-stuff/issues if "
                           "you need this (09.02.2015)!") LocalMassMatrix
    : public Dune::Fem::LocalMassMatrix<DiscreteFunctionSpaceImp, VolumeQuadratureImp>
{
  LocalMassMatrix(const DiscreteFunctionSpaceImp& spc, const int volQuadOrd = -1)
    : Dune::Fem::LocalMassMatrix<DiscreteFunctionSpaceImp, VolumeQuadratureImp>(spc, volQuadOrd)
  {
  }
};

} // namespace Fem
} // namespace Stuff
} // namespace Dune

#endif // HAVE_DUNE_FEM

#endif // STUFF_LOCALMASSMATRIX_HH
