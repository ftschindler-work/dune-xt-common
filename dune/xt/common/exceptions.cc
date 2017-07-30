// This file is part of the dune-xt-common project:
//   https://github.com/dune-community/dune-xt-common
// Copyright 2009-2017 dune-xt-common developers and contributors. All rights reserved.
// License: Dual licensed as BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
//      or  GPL-2.0+ (http://opensource.org/licenses/gpl-license)
//          with "runtime exception" (http://www.dune-project.org/license.html)
// Authors:
//   Felix Schindler (2017)
//   Rene Milk       (2017)
//   Tobias Leibner  (2017)

#include <config.h>

#include "exceptions.hh"

#include <dune/xt/common/timings.hh>
#include <dune/xt/common/memory.hh>
#include <dune/xt/common/parallel/helper.hh>

#if HAVE_TBB
#include <tbb/tbb_exception.h>
#endif
namespace Dune {
namespace XT {
namespace Common {

int handle_exception(const Dune::Exception& exp)
{
  std::cerr << "Failed with Dune::Exception: " << exp.what();
  DXTC_TIMINGS.output_per_rank("profiler");
  mem_usage();
  return abort_all_mpi_processes();
}

int handle_exception(const std::exception& exp)
{
  std::cerr << "Failed with std::exception: " << exp.what();
  DXTC_TIMINGS.output_per_rank("profiler");
  mem_usage();
  return abort_all_mpi_processes();
}
#if HAVE_TBB
int handle_exception(const tbb::tbb_exception& exp)
{
  std::cerr << "Failed with tbb::exception" << exp.name() << ": " << exp.what();
  DXTC_TIMINGS.output_per_rank("profiler");
  mem_usage();
  return abort_all_mpi_processes();
}
#endif
} // namespace Common
} // namespace XT
} // namespace Dune
