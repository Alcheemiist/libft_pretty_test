#ifndef TEST_H
# define TEST_H

# include <stddef.h>
# include <signal.h>
# include <stdbool.h>

int orginal_crash;
int ft_crash;
pid_t pid;
bool has_segfault;

# define TEST_SEGFAULT(x) do { \
	if ((pid = fork()) < 0) \
		exit(EXIT_FAILURE); \
	if (pid == 0) { \
		do { x } while(0); \
		exit(EXIT_SUCCESS); \
	} else { \
		wait(&pid); \
		has_segfault = WIFSIGNALED(pid); \
	} \
} while(0);

// # define GENERATE_TEST(name, arg_format, ...) do { \
// 	fflush(stdout); \
// 	TEST_SEGFAULT((void)#name(s, n);); \
// 	orginal_crash = has_segfault; \
// 	TEST_SEGFAULT((void)ft_#name(s, n);); \
// 	ft_crash = has_segfault; \
// 	if (orginal_crash && !ft_crash) \
//         print_ko("#name", false, "%u, %zu", s, n); \
// 	else if (!orginal_crash && ft_crash) \
//         print_ko("#name", true, "%u, %zu", s, n); \
// 	else if (!orginal_crash && !ft_crash) \
//         print_ok(); \
// 	else if (orginal_crash && ft_crash) \
//         print_ok(); \
// } while(0);

# define N 50000

void test_memset(char *s, int c, int len);
void test_bzero(void *s, size_t n);
void test_memcpy(void *dst, const void *src, size_t n);
void test_memccpy(void *dst, const void *src, int c, size_t n);
void test_memmove(void *dst, const void *src, size_t len);
void test_memchr(const void *s, int c, size_t n);
void test_memcmp(const void *s1, const void *s2, size_t n);
void test_strlen(const char *s);
void test_strchr(const char *s, int c);
void test_strrchr(const char *s, int c);
void test_strncmp(const char *s1, const char *s2, size_t n);
void test_strlcpy(char *dst, const	char *src, size_t size);
void test_strlcat(char *dst, const char *src, size_t size);
void test_strnstr(const char *haystack, const char *needle, size_t len);
void test_atoi(const char *str);
void test_strdup(const char *str);
void test_calloc(unsigned int s, size_t n);
void random_test (void);

void print_ok(void);
void print_ko(char *name, bool crash, char *format, ...);

#endif
