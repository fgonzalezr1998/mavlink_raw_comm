#include <iostream>

#define IS_TRUE(x)                                                                          \
{                                                                                           \
    if (!(x))                                                                               \
    {                                                                                       \
        throw std::runtime_error(                                                           \
            std::string(__FUNCTION__) + std::string(" failed on line ") +                   \
            std::to_string(__LINE__ ) + std::string("\n"));                                 \
    }                                                                                       \
}

bool trial_func(int value)
{
    return value < 5;
}

int
main(int argc, char ** argv)
{
    IS_TRUE(trial_func(0));
    IS_TRUE(trial_func(-2));
    IS_TRUE(trial_func(4));
    exit(EXIT_SUCCESS);
}