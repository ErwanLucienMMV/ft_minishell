/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:42:53 by abarthes          #+#    #+#             */
/*   Updated: 2026/01/22 15:06:40 by abarthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
int		ft_atoi(const char *c);
int		ft_isspace(char c);
int		ft_isalnum(int a);
int		ft_isalpha(int a);
int		ft_isascii(int a);
int		ft_isdigit(int a);
int		ft_isprint(int a);
int		ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *c);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_memcmp(const void *b1, const void *b2, size_t count);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_bzero(void *ptr, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *ptr, int value, size_t count);
void	*ft_memchr(const void *src, int c, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t size);
char	*ft_itoa(int n);
char	*ft_strchr(const char *str, int schar);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *bigstr, const char *littlestr, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strrchr(const char *str, int schar);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

char	*get_next_line(int fd);
char	*ft_get_buffer(int fd, char *buffer);
char	*ft_clear_buffer(char *str, int n);
char	*ft_get_line(char *buffer);
int		ft_is_newline(char *buffer);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_get_newline(char *buffer);

int		ft_printf(const char *str, ...);
int		ft_printf_fd(int fd, const char *str, ...);
int		ft_print_with_param(int fd, int c, va_list params);
int		ft_putchar(int fd, char c);
int		ft_putstr(int fd, char *str);
int		ft_putnbr_base(int fd, int nbr, char *base);
int		ft_putnbr_base_unsigned(int fd, unsigned int nbr, char *base);
int		ft_putpointer(int fd, unsigned long long n, char *base);

#endif
