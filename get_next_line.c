/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalkhas <lmalkhas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:57:45 by lmalkhas          #+#    #+#             */
/*   Updated: 2022/03/20 21:56:37 by lmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include <fcntl.h>

static char	*ft_check_backup(char **backup)
{
	char	*newline;
	char	*temp;
	size_t	n;

	if (!(*backup))
		return (NULL);
	newline = NULL;
	if (ft_strchr(*backup, '\n'))
	{
		n = ft_strchr(*backup, '\n') - *backup + 1;
		newline = ft_substr(*backup, 0, n);
		temp = ft_strdup((*backup) + n);
		if (*temp == '\0')
		{
			free(temp);
			temp = NULL;
		}
		free(*backup);
		*backup = temp;
	}
	return (newline);
}

// char	*ft_check_readbytes(size_t read_bytes, char **backup, char *temp_line)
// {
// 	char	*newline;

// 	if (read_bytes == -1)
// 		return (NULL);
// 	else if (read_bytes > 0)
// 	{
// 		*backup = ft_strjoin(*backup, temp_line);
// 		newline = ft_check_backup(&backup);
// 		if (newline != NULL)
// 			return (newline);
// 	}
// 	else if (read_bytes == 0)
// 	{
// 		newline = ft_strjoin(backup, temp_line);
// 		free(backup);
// 		return (newline);
// 	}
// }

char	*get_next_line(int fd)
{
	char			temp_line[BUFFER_SIZE + 1];
	static char		*backup = NULL;
	ssize_t			read_bytes;
	char			*line;

	if (fd < 0 || fd > 65536 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_check_backup(&backup);
	if (line == NULL)
	{
		while (1)
		{
			read_bytes = read(fd, temp_line, BUFFER_SIZE);
			temp_line[read_bytes] = '\0';
			// ft_check_readbytes(read_bytes, &backup, temp_line);
			if (read_bytes == -1)
				return (NULL);
			else if (read_bytes > 0)
			{
				backup = ft_strjoin(backup, temp_line);
				if (!backup)
					return (NULL);
				line = ft_check_backup(&backup);
				if (line != NULL)
					return (line);
			}
			else if (read_bytes == 0)
			{
				line = ft_strdup(backup);
				free(backup);
				backup = NULL;
				return (line);
			}
		}
	}
	return (line);
}

// int	main(void)
// {
// 	char	*a;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	printf("fd = %d\n", fd);
// 	if (fd == -1)
// 	{
// 		printf("Program Error");
// 	}
// 	a = get_next_line(fd);
// 	printf("my line1:%s\n", a); // 1
// 	if (a != NULL)
// 		free(a);
// 	a = get_next_line(fd);
// 	printf("my line2:%s\n", a);
// 	if (a != NULL)
// 		free(a);
// 	a = get_next_line(fd);
// 	printf("my line3:%s\n", a);
// 	if (a != NULL)
// 		free(a);
// 	a = get_next_line(fd);
// 	printf("my line4:%s\n", a);
// 	if (a != NULL)
// 		free(a);
// 	a = get_next_line(fd);
// 	printf("my line5:%s\n", a);
// 	if (a != NULL)
// 		free(a);
// 	a = get_next_line(fd);
// 	printf("my line6:%s\n", a);
// 	if (a != NULL)
// 		free(a);
// 	if (close(fd) < 0)
// 	{
// 		perror("c1");
// 		exit(1);
// 	}
// 	return (0);
// }
