#ifndef STAN__ERROR_HANDLING_CHECK_POSITIVE_HPP
#define STAN__ERROR_HANDLING_CHECK_POSITIVE_HPP

#include <boost/type_traits/is_unsigned.hpp>
#include <stan/error_handling/scalar/dom_err.hpp>
#include <stan/error_handling/scalar/dom_err_vec.hpp>
#include <stan/math/meta/value_type.hpp>
#include <stan/meta/traits.hpp>

namespace stan {

  namespace error_handling {

    namespace {

      template <typename T_y, typename T_result, bool is_vec>
      struct positive {
        static bool check(const char* function,
                          const T_y& y,
                          const char* name,
                          T_result* result) {
          // have to use not is_unsigned. is_signed will be false
          // floating point types that have no unsigned versions.
          if (!boost::is_unsigned<T_y>::value && !(y > 0)) 
            return dom_err(function,y,name,
                           " is %1%, but must be > 0!","",
                           result);
          return true;
        }
      };
    
      template <typename T_y, typename T_result>
      struct positive<T_y, T_result, true> {
        static bool check(const char* function,
                          const T_y& y,
                          const char* name,
                          T_result* result) {
          using stan::math::value_type;
          using stan::length;
          for (size_t n = 0; n < length(y); n++) {
            if (!boost::is_unsigned<typename value_type<T_y>::type>::value
                && !(stan::get(y,n) > 0)) 
              return dom_err_vec(n,function,y,name,
                                 " is %1%, but must be > 0!","",
                                 result);
          }
          return true;
        }
      };

    }

    // throws if any element in y is nan
    template <typename T_y, typename T_result>
    inline bool check_positive(const char* function,
                               const T_y& y,
                               const char* name,
                               T_result* result) {
      return positive<T_y,T_result,is_vector_like<T_y>::value>
        ::check(function, y, name, result);
    }

  }
}
#endif
