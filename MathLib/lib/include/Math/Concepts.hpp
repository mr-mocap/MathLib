#pragma once

#include <type_traits>

namespace Concept
{

template <typename T, typename O>
concept SameUnqualified = std::is_same_v< std::remove_cv_t<T>, std::remove_cv_t<O> >;

}