/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:33:37 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 08:04:47 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_safe {
	char	*data;
	int		type;
}	t_safe;

int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int a);
int				ft_isalpha(int a);
int				ft_isascii(int a);
int				ft_isdigit(int a);
int				ft_isprint(int a);
void			*ft_memchr(const void *buf, int c, size_t count);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
void			*ft_memcpy(void *destination, const void *source, size_t num);
void			*ft_memmove(void *dest, const void *src, size_t count);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strchr(const char *string, int c);
char			*ft_strdup(const char *string);
char			*ft_strjoin(char const *s1, char const *s2);
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
size_t			ft_strlen(const char *str);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			*ft_strrchr(const char *string, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
int				ft_printf(const char *str, ...);
int				gnl_bufchr(t_safe buffer, char c);
int				gnl_strlen(char *str);
int				gnl_bufflen(t_safe buffer);
char			*gnl_plant(char *s1, t_safe buffer, int n_len);
char			*get_next_line(int fd);
int				buffer_read(int fd, t_safe *buffer);
char			*buffer_plant(char *go, t_safe buffer);
t_safe			buffer_clear(t_safe buffer);
t_safe			buffer_set(t_safe buffer);
#endif