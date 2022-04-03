#include <iostream>

#define IS_TRUE(x)																							\
{                                                               \
	if (!(x))                                              				\
	{         																										\
		throw std::runtime_error(			                              \
			std::string(__FUNCTION__) +																\
			std::string(" failed on line ") +                   			\
			std::to_string(__LINE__ ) + std::string("\n")							\
		);                                 													\
	}                                                             \
}