/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:58:56 by rcammaro          #+#    #+#             */
/*   Updated: 2021/05/06 19:42:08 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

int	line_len(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0' && *str != '\n')
	{
		str++;
		len++;
	}
	return (len);
}

void	mem_shift(char *buffer, int n)
{
	char	*src;

	src = buffer + n;
	while (*src)
		*buffer++ = *src++;
	*buffer = '\0';
}

void	ft_strncat(char *dest, char *src, int n)
{
	while (*dest)
		dest++;
	while (n--)
		*dest++ = *src++;
	*dest = '\0';
}

void	ft_strcpy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

int	transfer_buf2new_line(char *buffer, char *new_line, int len)
{
	ft_strncat(new_line, buffer, len);
	if (buffer[len] == '\0')
	{
		buffer[0] = '\0';
		return (0);
	}
	mem_shift(buffer, len + 1);
	return (1);
}

// transfers from buffer to line (append) chars up to a \n or \0
// returns -1 if malloc error
// 1 if line has been read (\n found)
// 0 if buffer has been emptied and has to be reloaded
int	append_buffer_to_line(char *buffer, char **line)
{
	int		new_segm_len;
	char	*new_line;

	new_segm_len = line_len(buffer);
	new_line = malloc(line_len(*line) + new_segm_len + 1);
	if (!new_line)
		return (-1);
	ft_strcpy(new_line, *line);
	free(*line);
	*line = new_line;
	return (transfer_buf2new_line(buffer, new_line, new_segm_len));
}

// if buffer is empty, call read into buffer, terminate string with '\0'
// return -1 if read returns error
// return 0 if read returns 0
// return a number greater than 0 otherwise
int	load_buffer(char *buffer)
{
	int	ret;

	if (buffer[0] != '\0')
		return (1);
	ret = read(0, buffer, BUFFER_SIZE);
	if (ret == -1)
		return (-1);
	buffer[ret] = '\0';
	return (ret);
}

int	get_empty_str(char **line)
{
	*line = malloc(1);
	if (!*line)
		return (-1);
	**line = '\0';
	return (1);
}

int	get_next_line(char **line)
{
	static char buffer[BUFFER_SIZE + 1] = {'\0'};
	int			ret;

	if (!line || get_empty_str(line) == -1)
		return (-1);
	ret = 0;
	while (ret == 0)
	{
		ret = load_buffer(buffer);
		if (ret < 1)
			break ;
		ret = append_buffer_to_line(buffer, line);
	}
	if (ret == -1)
		free(*line);
	return (ret);
}
