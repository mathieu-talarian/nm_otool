/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoullec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:12:22 by mmoullec          #+#    #+#             */
/*   Updated: 2016/06/03 19:42:27 by mmoullec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFF_SIZE 1024

typedef struct			s_list_mem
{
	int					fd;
	char				*tmp;
	struct s_list_mem	*next;
}						t_list_mem;

typedef struct			s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}						t_list;

void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *d, const void *s, size_t n);
void					*ft_memccpy(void *dest, const void *src, int c, \
					size_t n);
void					*ft_memmove(void *d, const void *s, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);

size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *s);
char					*ft_strcpy(char *dest, const char *str);
char					*ft_strncpy(char *dest, const char *str, \
					unsigned int num);
char					*ft_strcat(char *dest, const char *str);
char					*ft_strncat(char *dest, const char *str, int num);
size_t					ft_strlcat(char *d, const char *s, size_t n);
char					*ft_strchr(const char *src, int c);
char					*ft_strrchr(const char *src, int c);
char					*ft_strstr(const char *src, const char *to_find);
char					*ft_strnstr(const char *src, const char *to_find, \
					size_t num);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t num);

int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isspace(int c);
int						ft_isprint(int c);
int						ft_tolower(int c);
int						ft_toupper(int c);

void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *str);
void					ft_striter(char *s, void(*f)(char *));
void					ft_striteri(char *s, void(*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, \
					char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strsub(const char *s, unsigned int stert, \
					size_t len);
char					*ft_strtrim(const char *s);
char					**ft_strsplit(const char *s, char c);
void					ft_strrev(char *str);

void					ft_putchar(char c);
void					ft_putstr(const char *str);
void					ft_putendl(const char *str);
void					ft_putnbr(int n);
void 					ft_putnbr_ull(unsigned long long nbr);
void 					ft_putnbr_ull_endl(unsigned long long nbr);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(const char *str, int fd);
void					ft_putendl_fd(const char *str, int fd);
int						ft_putendl_fd_int(const char *str, int fd, int ret);
void					ft_putnbr_fd(int n, int fd);
void					ft_putnbr_endl(int nbr);
void					ft_putstr_sp(char *str);
void					ft_putendl_sp(char *str);

int						ft_atoi(char *nbr);
char					*ft_itoa(int nbr);

t_list					*ft_lstnew(const void *content, size_t content_size);
void					ft_lstdelone(t_list **alst, \
					void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					ft_lstsort(t_list **lst, int (*f)(t_list *el1, t_list *el2));
void 					ft_lstswap(t_list *l, t_list *next);

int						ft_char_cmp(char a, char b);
int						ft_count_words(const char *s, char c, \
					int (*f)(char, char));

int						get_next_line(const int fd, char **line);
int						ft_atoi_base(char *nbr, char *base_from);
size_t					ft_len_nb(int nb);
char					*ft_convert_base(char *nbr, char *base_from, \
							char *base_to);

#endif
