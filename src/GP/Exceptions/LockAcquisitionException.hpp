#ifndef GP_EXCEPTIONS_LOCKACQUISITIONEXCEPTION_HPP
#define GP_EXCEPTIONS_LOCKACQUISITIONEXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace GP
{
	namespace Exceptions
	{
		class LockAcquisitionException : public std::runtime_error
		{
		public:
			explicit LockAcquisitionException(const std::string& what_arg)
				: std::runtime_error{what_arg}
			{
			}
		};
	}
}

#endif /* GP_EXCEPTIONS_LOCKACQUISITIONEXCEPTION_HPP */

