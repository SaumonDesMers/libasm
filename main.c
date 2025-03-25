#include <stdio.h>

int ft_strlen(char *);
char *ft_strcpy(char * dest, const char * src);

int main()
{
	char * str = "Hello world!";
	printf("%i\n", ft_strlen(str));

	char dest[13];
	ft_strcpy(dest, str);
	printf("%s\n", dest);

	return 0;
}
