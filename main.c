#include <stdio.h>
#include <string.h>

int ft_strlen(char *);
char *ft_strcpy(char * dest, const char * src);
int ft_strcmp(const char * s1, const char * s2);

int main()
{
	char * str = "Hello world!";
	printf("%i\n", ft_strlen(str));

	char dest[13];
	ft_strcpy(dest, str);
	printf("%s\n", dest);

	char *str2 = "Hello world!";
	printf("%i\n", ft_strcmp(str, str2));

	return 0;
}
