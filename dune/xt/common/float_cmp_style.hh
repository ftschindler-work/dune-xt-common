// This file is part of the dune-xt-common project:
//   https://github.com/dune-community/dune-xt-common
// The copyright lies with the authors of this file (see below).
// License: Dual licensed as  BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
//      or  GPL-2.0+ (http://opensource.org/licenses/gpl-license)
//          with "runtime exception" (http://www.dune-project.org/license.html)
// Authors:
//   Felix Schindler (2016)
//   Rene Milk       (2015)

#ifndef DUNE_XT_COMMON_FLOAT_CMP_STYLE_HH
#define DUNE_XT_COMMON_FLOAT_CMP_STYLE_HH

#include <type_traits>
#include <complex>

#include <dune/common/float_cmp.hh>
#include <dune/xt/common/type_traits.hh>

namespace Dune {
namespace XT {
namespace Common {
namespace FloatCmp {

enum class Style
{
  numpy,
  relativeWeak,
  relativeStrong,
  absolute,
  defaultStyle = numpy
};

namespace internal {

template <Style style>
struct ConvertStyle;

template <>
struct ConvertStyle<Style::relativeWeak>
{
  static const Dune::FloatCmp::CmpStyle value = Dune::FloatCmp::CmpStyle::relativeWeak;
};

template <>
struct ConvertStyle<Style::relativeStrong>
{
  static const Dune::FloatCmp::CmpStyle value = Dune::FloatCmp::CmpStyle::relativeStrong;
};

template <>
struct ConvertStyle<Style::absolute>
{
  static const Dune::FloatCmp::CmpStyle value = Dune::FloatCmp::CmpStyle::absolute;
};

} // namespace internal

} // namespace FloatCmp
} // namespace Common
} // namespace XT
} // namespace Dune

#endif // DUNE_XT_COMMON_FLOAT_CMP_STYLE_HH
