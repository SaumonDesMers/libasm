#include <stdio.h>
#include <string.h>
#include <errno.h>

int ft_strlen(char *);
char *ft_strcpy(char * dest, const char * src);
int ft_strcmp(const char * s1, const char * s2);
int ft_write(int fd, const void *buf, size_t count);  

int main()
{
	char * str = "Hello world!";
	printf("%i\n", ft_strlen(str));

	char dest[13];
	ft_strcpy(dest, str);
	printf("%s\n", dest);

	char *str2 = "Hello world!";
	printf("%i\n", ft_strcmp(str, str2));

	int count = ft_write(0, str, 13);
	printf("ft_write return: %d", count);

	return 0;
}
