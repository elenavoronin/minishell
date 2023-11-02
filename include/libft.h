/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:29:23 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/01 16:02:06 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define ANSI_COL_RED "\x1b[31m"
# define ANSI_COL_GREEN "\x1b[32m"
# define ANSI_COL_YELLOW "\x1b[33m"
# define ANSI_COL_BLUE "\x1b[34m"
# define ANSI_COL_MAGENTA "\x1b[35m"
# define ANSI_COL_CYAN "\x1b[36m"
# define ANSI_COL_RESET "\x1b[0m"

typedef struct a_list
{
	void			*content;
	struct a_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *node);
void		ft_lstadd_back(t_list **lst, t_list *node);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

typedef struct s_print
{
	va_list		argsp;
	t_list		*plist;
	int			count;
	int			isneg;
	int			iszero;
	int			plus;
	int			hash;
	int			space;
	int			dash;
	int			zero;
	int			dot;
	int			w_min;
	int			w_precise;
}				t_print;

int			ft_printf(const char *s, ...);
int			set_flags(t_print *tab, const char *format);
int			add_node(t_print *tab, char *content, const int addback);
char		*ft_strrep(const char c, const size_t len);
void		print_char(t_print *tab, const char c);
void		print_string(t_print *tab);
void		print_int(t_print *tab, const char c);
void		print_hex(t_print *tab, const char c);
void		print_pnt(t_print *tab);
void		apply_flags_chars(t_print *tab);
void		apply_flags_num(t_print *tab);
void		apply_flags_hex(t_print *tab);
void		check_write(t_print *tab);

char		*get_next_line(int fd);

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putstr_col_fd(char *color, char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);

int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
int			ft_toupper(int c);
int			ft_tolower(int c);

void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memset(void *str, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);

size_t		ft_strlen(const char *s);
size_t		ft_strarray_count(char **s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char*needle, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strrep(const char c, const size_t len);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strrev(char *string);

char		**ft_split(const char *s, char c);
char		**ft_split2(char *s);
char		*ft_joinstrs(int count, ...);

char		*ft_itoa(int n);
char		*ft_lltoa_base(long long n, int base);
char		*ft_ltoa_unsigned_base(unsigned long num, int base);

bool		ft_valid_atoi(char *check_me, int *num);
int			ft_atoi_validate(char *check_me, int *num);

int			ft_abs(int num);
int			ft_smallest(int a, int b);
int			ft_biggest(int a, int b);
int			ft_numlen(long long n, int base);
size_t		ft_distance(int a, int b);

void		ft_error(char *errstr);
void		ft_perror(char *progname, char *funcname, char *messsage);

void		ft_free(void *content);
void		ft_free_strarr(char **array);
void		ft_free_strarrarr(char ***arrarr);
void		ft_free_strnarr(char **array, size_t n);
void		ft_free_intarrarr(int **intarrarr);

#endif