///////////////////////////////////////////////////////////////////////////////
//
// Module      :  ST.hh
// Copyright   :  (c) Andy Arvanitis 2015
// License     :  MIT
//
// Maintainer  :  Andy Arvanitis <andy.arvanitis@gmail.com>
// Stability   :  experimental
// Portability :
//
// ST FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#ifndef STFFI_HH
#define STFFI_HH

#include "PureScript/PureScript.hh"

namespace Control_Monad_ST {
  using namespace PureScript;

  struct STObject {
    any data;
    STObject(const any& d) : data(d) {}
  };

  inline auto newSTRef(const any& val) -> any {
    return [=]() -> any {
      return any::make_shared<STObject>(val);
    };
  }

  inline auto readSTRef(const any& ref) -> any {
    return [=]() -> any {
      const STObject& object = cast<STObject>(ref);
      return object.data;
    };
  }

  inline auto modifySTRef(const any& ref, const any& f) -> any {
    return [=]() -> any {
      STObject& object = cast<STObject>(ref);
      object.data = f(object.data);
      return ref;
    };
  }

  inline auto writeSTRef(const any& ref, const any& a) -> any {
    return [=]() -> any {
      STObject& object = cast<STObject>(ref);
      object.data = a;
      return ref;
    };
  }

  inline auto runST(const any& f) -> any {
    return f;
  }

}

#endif // STFFI_HH
