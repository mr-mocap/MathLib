#pragma once

#include <type_traits>

namespace Concept
{

/** Determines whether two types are the same after stripping const & volatile from them both
 *   
 *  @tparam T The main type you are comparing
 *  @tparam O The other type to compare against
 */
template <typename T, typename O>
concept SameUnqualified = std::is_same_v< std::remove_cv_t<T>, std::remove_cv_t<O> >;

}