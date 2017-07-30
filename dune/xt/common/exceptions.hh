// This file is part of the dune-xt-common project:
//   https://github.com/dune-community/dune-xt-common
// Copyright 2009-2017 dune-xt-common developers and contributors. All rights reserved.
// License: Dual licensed as BSD 2-Clause License (http://opensource.org/licenses/BSD-2-Clause)
//      or  GPL-2.0+ (http://opensource.org/licenses/gpl-license)
//          with "runtime exception" (http://www.dune-project.org/license.html)
// Authors:
//   Felix Schindler (2013 - 2017)
//   Rene Milk       (2014 - 2017)
//   Tobias Leibner  (2014, 2017)

#ifndef DUNE_XT_COMMON_EXCEPTIONS_HH
#define DUNE_XT_COMMON_EXCEPTIONS_HH

#include <dune/common/exceptions.hh>
#include <dune/common/parallel/mpihelper.hh>
#include <dune/common/deprecated.hh>

#ifdef DUNE_THROW
#undef DUNE_THROW
#endif

#if HAVE_TBB
namespace tbb {
class tbb_exception;
}
#endif
/**
 *  \brief Macro to throw a colorfull exception.
 *
 *  Example:
\code
#include <dune/xt/common/exceptions.hh>

if (a.size() != b.size())
  DUNE_THROW(Exceptions::shapes_do_not_match,
             "size of a (" << a.size() << ") does not match the size of b (" << b.size() << ")!");
\endcode
 *  This macro is essentially copied from dune-common with added color functionality and rank information.
 *  \param  E Exception class, derived from Dune::Exception.
 *  \param  m Message in ostream notation.
 *  \see Dune::Exception
 */
#define DUNE_THROW(E, m)                                                                                               \
  do {                                                                                                                 \
    const std::string th__red = "\033[31m";                                                                            \
    const std::string th__brown = "\033[33m";                                                                          \
    const std::string th__clear = "\033[0m";                                                                           \
    E th__ex;                                                                                                          \
    std::ostringstream th__msg;                                                                                        \
    th__msg << m;                                                                                                      \
    std::ostringstream th__out;                                                                                        \
    th__out << th__red << #E << th__clear;                                                                             \
    if (Dune::MPIHelper::getCollectiveCommunication().size() > 1)                                                      \
      th__out << " (on rank " << Dune::MPIHelper::getCollectiveCommunication().rank() << ")";                          \
    th__out << "\n";                                                                                                   \
    th__out << th__brown << "[" << th__clear;                                                                          \
    th__out << th__red << __func__ << th__clear;                                                                       \
    th__out << th__brown << "|" << th__clear;                                                                          \
    th__out << __FILE__ << th__brown << ":" << th__clear << th__red << __LINE__ << th__clear << th__brown << "]"       \
            << th__clear;                                                                                              \
    if (!th__msg.str().empty())                                                                                        \
      th__out << "\n" << th__brown << "=>" << th__clear << " " << th__msg.str();                                       \
    th__ex.message(th__out.str());                                                                                     \
    throw th__ex;                                                                                                      \
  } while (0)
// DUNE_THROW

namespace Dune {
namespace XT {
namespace Common {
namespace Exceptions {

class CRTP_check_failed : public Dune::Exception
{
};

class shapes_do_not_match : public Dune::Exception
{
};

class index_out_of_range : public Dune::Exception
{
};

class you_are_using_this_wrong : public Dune::Exception
{
};

class wrong_input_given : public you_are_using_this_wrong
{
};

class requirements_not_met : public you_are_using_this_wrong
{
};

class configuration_error : public Dune::Exception
{
};

class conversion_error : public Dune::Exception
{
};

class results_are_not_as_expected : public Dune::Exception
{
};

class internal_error : public Dune::Exception
{
};

class external_error : public Dune::Exception
{
};

class you_have_to_implement_this : public Dune::NotImplemented
{
};

class reinterpretation_error : public Dune::Exception
{
};

class parameter_error : public Dune::Exception
{
};

class spe10_data_file_missing : public Dune::IOError
{
};

} // namespace Exceptions

int handle_exception(const Dune::Exception& exp);
int handle_exception(const std::exception& exp);
#if HAVE_TBB
int handle_exception(const tbb::tbb_exception& exp);
#endif
} // namespace Common
} // namespace XT
} // namespace Dune

#endif // DUNE_XT_COMMON_EXCEPTIONS_HH
