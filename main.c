#include "get_next_line.h"
#include <stdio.h>

int	main()
{
	char *line;
	int	ret;

	ret = get_next_line(&line);
	while (ret == 1)
	{
//		printf("ret: %d\n", ret);
		printf("%s\n", line);
		free(line);
		ret = get_next_line(&line);
	}
	if (ret == -1)
		return (1);
//	printf("ret: %d\n", ret);
	printf("%s", line);
	free(line);
}
