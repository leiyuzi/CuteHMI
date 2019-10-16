#ifndef REGISTERCONTROLLERTRAITS_HPP
#define REGISTERCONTROLLERTRAITS_HPP

#include <QtGlobal>

namespace cutehmi {
namespace modbus {

class Register16Controller;
class Register1Controller;

namespace internal {

template <typename R>
struct RegisterControllerTraits
{
};

template <>
struct RegisterControllerTraits<Register16Controller>
{
	typedef qreal ValueType;
};

template <>
struct RegisterControllerTraits<Register1Controller>
{
	typedef bool ValueType;
};

}
}
}

#endif // REGISTERCONTROLLERTRAITS_HPP