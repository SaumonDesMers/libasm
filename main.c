#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

size_t ft_strlen(const char *);
char *ft_strcpy(char * dest, const char * src);
int ft_strcmp(const char * s1, const char * s2);
ssize_t ft_write(int fd, const void * buf, size_t count);


#define test(tested_func, tester) \
	printf("Testing \033[1;32m%s\033[0m...\n", #tested_func); \
	tester(tested_func);

void test_strlen(size_t (*test_func)(const char *))
{
	char *str = "Hello, World!";
	int len = test_func(str);
	printf("Length of '%s' is %d\n", str, len);
}

void test_strcpy(char *(*test_func)(char *, const char *))
{
	char dest[50];
	const char *src = "Hello, World!";
	test_func(dest, src);
	printf("Copied string: %s\n", dest);
}

void test_strcmp(int (*test_func)(const char *, const char *))
{
	const char *str = "Hello, World!";
	const char *same_str = "Hello, World!";
	const char *diff_str = "Hello, Universe!";
	int cmp = test_func(str, same_str);
	printf("Comparing '%s' and '%s': %d\n", str, same_str, cmp);
	cmp = test_func(str, diff_str);
	printf("Comparing '%s' and '%s': %d\n", str, diff_str, cmp);
}

void test_write(ssize_t (*test_func)(int, const void *, size_t))
{
	const char *str = "Hello, World!\n";
	errno = 0;
	int ret = test_func(1, str, 14);
	int err = errno;
	printf("Wrote %d bytes to stdout with error code %d (%s)\n", ret, err, strerror(err));

	errno = 0;
	ret = test_func(-1, str, 14);
	err = errno;
	printf("Wrote %d bytes to invalid fd with error code %d (%s)\n", ret, err, strerror(err));

	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Failed to open file");
		return;
	}
	errno = 0;
	ret = test_func(fd, str, 14);
	err = errno;
	printf("Wrote %d bytes to file with error code %d (%s)\n", ret, err, strerror(err));
	close(fd);

	errno = 0;
	ret = test_func(fd, NULL, 14);
	err = errno;
	printf("Wrote %d bytes to NULL buffer with error code %d (%s)\n", ret, err, strerror(err));

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open file");
		return;
	}
	errno = 0;
	ret = test_func(fd, str, 14);
	err = errno;
	printf("Wrote %d bytes to read-only file with error code %d (%s)\n", ret, err, strerror(err));
	close(fd);
}

int main()
{
	test(strlen, test_strlen);
	printf("\n");
	test(ft_strlen, test_strlen);
	printf("\n\n");

	test(strcpy, test_strcpy);
	printf("\n");
	test(ft_strcpy, test_strcpy);
	printf("\n\n");

	test(strcmp, test_strcmp);
	printf("\n");
	test(ft_strcmp, test_strcmp);
	printf("\n\n");

	test(write, test_write);
	printf("\n");
	test(ft_write, test_write);
	printf("\n\n");

	return 0;
}
