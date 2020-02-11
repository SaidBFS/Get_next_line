/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboufou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:09:56 by saboufou          #+#    #+#             */
/*   Updated: 2019/12/01 16:28:38 by saboufou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_stock_i(char *stock)
{
	int	i;

	i = 0;
	while (stock[i] != '\n')
		i++;
	return (i);
}

static char	*ft_line(char *line, char **stock)
{
	int		i;
	char	*tmp;

	if (!ft_strchr(*stock, '\n'))
	{
		if (!(line = ft_strdup(*stock)))
			return (NULL);
		free(*stock);
		*stock = NULL;
	}
	else
	{
		i = ft_stock_i(*stock);
		if (!(line = ft_substr(*stock, 0, i)))
			return (NULL);
		tmp = *stock;
		if (!(*stock = ft_strdup(tmp + i + 1)))
			return (NULL);
		free(tmp);
	}
	return (line);
}

int			get_next_line(int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*stock = NULL;

	if (fd < 0 || !line
			|| (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	while (!ft_strchr(stock, '\n') && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		stock = ft_strjoin_free(stock, buf);
	}
	free(buf);
	if (!(*line = ft_line(*line, &stock)))
		return (-1);
	return ((!stock && !ret) ? 0 : 1);
}
