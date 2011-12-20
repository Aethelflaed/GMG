#ifndef GP_STRINGS_CASE_H
#define GP_STRINGS_CASE_H

#ifdef __cplusplus
extern "C"
{
#endif

char* strtolower(char* string);

char* strtoupper(char* string);

#ifdef __cplusplus
} /* extern "C" */

#include <string>

namespace GP
{
namespace Strings
{

	std::string stringToLower(std::string& string);
	std::string stringToUppder(std::string& string);

}
}
#endif

#endif /* GP_STRINGS_CASE_H */

