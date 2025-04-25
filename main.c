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
ssize_t ft_read(int fd, void * buf, size_t count);
char * ft_strdup(const char * src);

int ft_atoi_base(char * str, char * base);

typedef struct s_list
{
	void * data;
	struct s_list * next;
} t_list;

void ft_list_push_front(t_list ** begin_list, void * data);
int ft_list_size(t_list * begin_list);
void ft_list_sort(t_list ** begin_list, int (*cmp)());
void ft_list_remove_if(t_list ** begin_list, void * data_ref, int (*cmp)(), void (*free_fct)(void *));


#define test(tested_func, tester) \
	printf("Testing \033[1;32m%s\033[0m...\n", #tested_func); \
	tester(tested_func);


void test_strlen(size_t (*test_func)(const char *))
{
	{
		char *str = "";
		int len = test_func(str);
		printf("Length of '%s' is %d\n", str, len);
	}
	{
		char *str = "Hello, World!";
		int len = test_func(str);
		printf("Length of '%s' is %d\n", str, len);
	}
	{
		char *str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue. Ut in risus volutpat libero pharetra tempor. Cras vestibulum bibendum augue. Praesent egestas leo in pede. Praesent blandit odio eu enim. Pellentesque sed dui ut augue blandit sodales. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aliquam nibh. Mauris ac mauris sed pede pellentesque fermentum. Maecenas adipiscing ante non diam sodales hendrerit. Ut velit mauris, egestas sed, gravida nec, ornare ut, mi. Aenean ut orci vel massa suscipit pulvinar. Nulla sollicitudin. Fusce varius, ligula non tempus aliquam, nunc turpis ullamcorper nibh, in tempus sapien eros vitae ligula. Pellentesque rhoncus nunc et augue. Integer id felis. Curabitur aliquet pellentesque diam. Integer quis metus vitae elit lobortis egestas. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Morbi vel erat non mauris convallis vehicula. Nulla et sapien. Integer tortor tellus, aliquam faucibus, convallis id, congue eu, quam. Mauris ullamcorper felis vitae erat. Proin feugiat, augue non elementum posuere, metus purus iaculis lectus, et tristique ligula justo vitae magna. Aliquam convallis sollicitudin purus. Praesent aliquam, enim at fermentum mollis, ligula massa adipiscing nisl, ac euismod nibh nisl eu lectus. Fusce vulputate sem at sapien. Vivamus leo. Aliquam euismod libero eu enim. Nulla nec felis sed leo placerat imperdiet. Aenean suscipit nulla in justo. Suspendisse cursus rutrum augue. Nulla tincidunt tincidunt mi. Curabitur iaculis, lorem vel rhoncus faucibus, felis magna fermentum augue, et ultricies lacus lorem varius purus. Curabitur eu amet.";
		int len = test_func(str);
		printf("Length of '%s' is %d\n", str, len);
	}
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

	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Failed to open file");
		return;
	}
	errno = 0;
	ret = test_func(fd, str, 13);
	err = errno;
	printf("Wrote %d bytes to file with error code %d (%s)\n", ret, err, strerror(err));
	close(fd);

	errno = 0;
	ret = test_func(fd, NULL, 14);
	err = errno;
	printf("Wrote %d bytes to NULL buffer with error code %d (%s)\n", ret, err, strerror(err));

	errno = 0;
	ret = test_func(-1, str, 14);
	err = errno;
	printf("Wrote %d bytes to invalid fd with error code %d (%s)\n", ret, err, strerror(err));

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

void test_read(ssize_t (*test_func)(int, void *, size_t))
{
	char buf[50];
	int fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open file");
		return;
	}
	buf[0] = '\0';
	errno = 0;
	ssize_t ret = test_func(fd, buf, sizeof(buf));
	buf[ret] = '\0';
	int err = errno;
	printf("Read '%s' (%ld bytes) from file with error code %d (%s)\n", buf, ret, err, strerror(err));
	close(fd);
	
	buf[0] = '\0';
	errno = 0;
	ret = test_func(fd, NULL, sizeof(buf));
	err = errno;
	printf("Read '%s' (%ld bytes) from NULL buffer with error code %d (%s)\n", buf, ret, err, strerror(err));

	buf[0] = '\0';
	errno = 0;
	ret = test_func(-1, buf, sizeof(buf));
	err = errno;
	printf("Read '%s' (%ld bytes) from invalid fd with error code %d (%s)\n", buf, ret, err, strerror(err));

	fd = open("test.txt", O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("Failed to open file");
		return;
	}
	buf[0] = '\0';
	errno = 0;
	ret = test_func(fd, buf, sizeof(buf));
	err = errno;
	printf("Read '%s' (%ld bytes) from write-only file with error code %d (%s)\n", buf, ret, err, strerror(err));
	close(fd);
}

void test_strdup(char *(*test_func)(const char *))
{
	const char *str1 = "Hello, World!";
	char *dup_str1 = test_func(str1);
	printf("Duplicated string: '%s'\n", dup_str1);
	free(dup_str1);
	
	const char *str2 = "";
	char *dup_str2 = test_func(str2);
	printf("Duplicated string: '%s'\n", dup_str2);
	free(dup_str2);
}



void unit_test_atoi_base(char * str, char * base)
{
	int result = ft_atoi_base(str, base);
	printf("Converted '%s' to %d in base '%s'\n", str, result, base);
}

void test_atoi_base()
{
	printf("Testing \033[1;32matoi_base\033[0m...\n");
	unit_test_atoi_base(NULL, "0123456789");
	unit_test_atoi_base("42", NULL);
	unit_test_atoi_base("42", "+");
	unit_test_atoi_base("42", "-");
	unit_test_atoi_base("42", "oo");
	unit_test_atoi_base("42", "v");
	unit_test_atoi_base("42", "0123456789");
	unit_test_atoi_base("101010", "01");
}


void print_list_int(t_list * list)
{
	printf("List: ");
	while (list)
	{
		printf("%d -> ", *((int*)list->data));
		list = list->next;
	}
	printf("NULL\n");
}

void print_list_str(t_list * list)
{
	printf("List: ");
	while (list)
	{
		printf("%s -> ", (char*)list->data);
		list = list->next;
	}
	printf("NULL\n");
}

void test_list_push_front()
{
	printf("Testing \033[1;32mlist_push_front\033[0m...\n");

	t_list * list = NULL;
	int data1 = 42;
	int data2 = 21;

	print_list_int(list);

	ft_list_push_front(&list, &data1);
	print_list_int(list);

	ft_list_push_front(&list, &data2);
	print_list_int(list);

	free(list->next);
	free(list);
}

void test_list_size()
{
	printf("Testing \033[1;32mlist_size\033[0m...\n");

	int data5 = 42; t_list list5 = {&data5, NULL};
	int data4 = 21; t_list list4 = {&data4, &list5};
	int data3 = 84; t_list list3 = {&data3, &list4};
	int data2 = 63; t_list list2 = {&data2, &list3};
	int data1 = 105; t_list list1 = {&data1, &list2};

	t_list * begin_list = &list1;
	int size = ft_list_size(begin_list);
	print_list_int(begin_list);
	printf("List size: %d\n\n", size);

	begin_list = &list3;
	size = ft_list_size(begin_list);
	print_list_int(begin_list);
	printf("List size: %d\n\n", size);

	begin_list = NULL;
	size = ft_list_size(begin_list);
	print_list_int(begin_list);
	printf("List size: %d\n", size);
}

int cmp_int(void * a, void * b)
{
	return (*(int*)a - *(int*)b);
}

void test_list_sort_int()
{
	printf("Testing \033[1;32mlist_sort\033[0m with integers...\n");

	int data5 = 42; t_list list5 = {&data5, NULL};
	int data4 = 21; t_list list4 = {&data4, &list5};
	int data3 = 84; t_list list3 = {&data3, &list4};
	int data2 = 63; t_list list2 = {&data2, &list3};
	int data1 = 105; t_list list1 = {&data1, &list2};
	t_list * begin_list = &list1;

	printf("Before sorting:\n");
	print_list_int(begin_list);
	ft_list_sort(&begin_list, cmp_int);
	printf("After sorting:\n");
	print_list_int(begin_list);
	printf("\n");

	begin_list = NULL;
	printf("Before sorting:\n");
	print_list_int(begin_list);
	ft_list_sort(&begin_list, cmp_int);
	printf("After sorting:\n");
	print_list_int(begin_list);
	printf("\n");

	begin_list = &list5;
	printf("Before sorting:\n");
	print_list_int(begin_list);
	ft_list_sort(&begin_list, cmp_int);
	printf("After sorting:\n");
	print_list_int(begin_list);
}

void test_list_sort_str()
{
	printf("Testing \033[1;32mlist_sort\033[0m with strings...\n");

	char * data5 = "Hello"; t_list list5 = {data5, NULL};
	char * data4 = "World"; t_list list4 = {data4, &list5};
	char * data3 = "Yes"; t_list list3 = {data3, &list4};
	char * data2 = "no"; t_list list2 = {data2, &list3};
	char * data1 = "Foo"; t_list list1 = {data1, &list2};
	t_list * begin_list = &list1;

	printf("Before sorting:\n");
	print_list_str(begin_list);
	ft_list_sort(&begin_list, strcmp);
	printf("After sorting:\n");
	print_list_str(begin_list);
}

void test_list_remove_if_str()
{
	printf("Testing \033[1;32mlist_remove_if\033[0m with strings...\n");

	t_list * begin_list = NULL;
	char * data5 = "Hello"; ft_list_push_front(&begin_list, data5);
	char * data4 = "World"; ft_list_push_front(&begin_list, data4);
	char * data3 = "Yes"; ft_list_push_front(&begin_list, data3);
	char * data2 = "no"; ft_list_push_front(&begin_list, data2);
	char * data1 = "Foo"; ft_list_push_front(&begin_list, data1);

	printf("Remove middle element:\n");
	printf("Before removing:\n");
	print_list_str(begin_list);
	ft_list_remove_if(&begin_list, "no", strcmp, NULL);
	printf("After removing:\n");
	print_list_str(begin_list);
	printf("\n");

	printf("Remove first element:\n");
	printf("Before removing:\n");
	print_list_str(begin_list);
	ft_list_remove_if(&begin_list, "Foo", strcmp, NULL);
	printf("After removing:\n");
	print_list_str(begin_list);
	printf("\n");

	printf("Remove last element:\n");
	printf("Before removing:\n");
	print_list_str(begin_list);
	ft_list_remove_if(&begin_list, "Hello", strcmp, NULL);
	printf("After removing:\n");
	print_list_str(begin_list);

	while (begin_list)
	{
		t_list * tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp);
	}
}

void test_list_remove_if_int()
{
	printf("Testing \033[1;32mlist_remove_if\033[0m with integers...\n");
	
	t_list * begin_list = NULL;
	int data5 = 42; ft_list_push_front(&begin_list, &data5);
	int data4 = 42; ft_list_push_front(&begin_list, &data4);
	int data3 = 42; ft_list_push_front(&begin_list, &data3);
	int data2 = 42; ft_list_push_front(&begin_list, &data2);
	int data1 = 42; ft_list_push_front(&begin_list, &data1);

	printf("Remove all elements:\n");
	printf("Before removing:\n");
	print_list_int(begin_list);
	// ft_list_remove_if(&begin_list, &data1, cmp_int, NULL);
	printf("After removing:\n");
	print_list_int(begin_list);

	while (begin_list)
	{
		t_list * tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp);
	}
}

void test_list_remove_if_free()
{
	printf("Testing \033[1;32mlist_remove_if\033[0m with alloc/free...\n");

	t_list * begin_list = NULL;
	char * data5 = malloc(6); strcpy(data5, "Hello"); ft_list_push_front(&begin_list, data5);
	char * data4 = malloc(6); strcpy(data4, "World"); ft_list_push_front(&begin_list, data4);
	char * data3 = malloc(4); strcpy(data3, "Yes"); ft_list_push_front(&begin_list, data3);
	char * data2 = malloc(3); strcpy(data2, "no"); ft_list_push_front(&begin_list, data2);
	char * data1 = malloc(4); strcpy(data1, "Foo"); ft_list_push_front(&begin_list, data1);

	printf("Remove middle element:\n");
	printf("Before removing:\n");
	print_list_str(begin_list);
	ft_list_remove_if(&begin_list, "no", strcmp, free);
	printf("After removing:\n");
	print_list_str(begin_list);
	printf("\n");

	printf("Remove first element:\n");
	printf("Before removing:\n");
	print_list_str(begin_list);
	ft_list_remove_if(&begin_list, "Foo", strcmp, free);
	printf("After removing:\n");
	print_list_str(begin_list);
	printf("\n");

	printf("Remove last element:\n");
	printf("Before removing:\n");
	print_list_str(begin_list);
	ft_list_remove_if(&begin_list, "Hello", strcmp, free);
	printf("After removing:\n");
	print_list_str(begin_list);

	while (begin_list)
	{
		t_list * tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp->data);
		free(tmp);
	}
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

	test(read, test_read);
	printf("\n");
	test(ft_read, test_read);
	printf("\n\n");

	test(strdup, test_strdup);
	printf("\n");
	test(ft_strdup, test_strdup);
	printf("\n\n");

	test_atoi_base();
	printf("\n\n");

	test_list_push_front();
	printf("\n\n");

	test_list_size();
	printf("\n\n");

	test_list_sort_int();
	printf("\n\n");
	test_list_sort_str();
	printf("\n\n");

	test_list_remove_if_str();
	printf("\n\n");
	test_list_remove_if_int();
	printf("\n\n");
	test_list_remove_if_free();

	return 0;
}
