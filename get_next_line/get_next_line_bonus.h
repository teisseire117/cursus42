/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 07:45:37 by hateisse          #+#    #+#             */
/*   Updated: 2022/10/31 16:04:57 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# define GET_NEXT_LINE_BONUS_H

typedef struct s_gnl
{
	int				fd;
	char			*buf;
	char			*localbuf;
	struct s_gnl	*next;
	struct s_gnl	*prev;
}	t_gnl;

char	*ft_strncpy(char *dest, const char *src, size_t n);

t_gnl	*ft_lstnew(int fd);
t_gnl	*ft_lstadd_back(t_gnl **lst, t_gnl *new);
void	ft_lstfree(t_gnl **buflist, int fd);
t_gnl	*ft_lstsrch(t_gnl *lst, int fd);

short	gnl_check_buf(char **line, char *localbuf, t_gnl *buf_fd);
short	gnl_precheck(char **line, t_gnl **buflist, int fd);
short	gnl_readfile(char **line, t_gnl *buf_fd, int fd);
char	*gnl_expand(char **dest, char *src, char *to_add);
char	*get_next_line(int fd);

#endif
