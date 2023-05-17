#include "superlib/superlib.h"
#include <stdio.h>

int main(void)
{
	char **splitted;

	splitted = ft_split("*", '*');
	int i = -1;
	while (splitted[++i])
		printf("%s\n", splitted[i]);
}