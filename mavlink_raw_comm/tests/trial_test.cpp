#include "evaluation.hpp"

bool
trial_func(int value)
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