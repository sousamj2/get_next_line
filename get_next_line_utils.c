/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:16:55 by marisous          #+#    #+#             */
/*   Updated: 2026/11/13 18:53:14 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* size_t	ft_strlen(const char *s); */
/* char	*ft_strjoin(char const *s1, char const *s2); */
/* char	*ft_strchr(const char *s, int c); */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*retval;
	size_t	size_alloc;

	if (!s1 || !s2)
		return (NULL);
	size_alloc = ft_strlen(s1) + ft_strlen(s2);
	retval = malloc((1 + size_alloc) * sizeof(char));
	if (!retval)
		return (NULL);
	while (*s1 != '\0')
	{
		*retval = *s1;
		retval++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*retval = *s2;
		retval++;
		s2++;
	}
	*retval = '\0';
	return (retval - size_alloc);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ichar;
	char	search;

	if (s == NULL)
		return (NULL);
	ichar = (char *) s;
	search = (char) c;
	if (search == '\0')
		return (ichar + ft_strlen(s));
	while (*ichar != '\0')
	{
		if (*ichar == search)
			return (ichar);
		ichar++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

unsigned char	*ft_split2(const unsigned char *s, const unsigned char c, unsigned char **submem2, size_t *sizestr2);

unsigned char	*ft_split2(const unsigned char *s, const unsigned char c, unsigned char **submem2, size_t *sizestr3)
{
	size_t index;

	if (s == NULL)
		return (NULL);
	index = 0;
	submem2[0] = (unsigned char *) s;
	while (index < sizestr3[0])
	{
		index++;
		if (*s == c || index + 1 < sizestr3[0])
			break ;
		s++;
	}
	sizestr3[1] = index;
	sizestr3[2] = sizestr3[0] - index;
	if (sizestr3[2])
		submem2[1] = (unsigned char *) s;
	else
		submem2[1] = NULL;
	return (submem2[0]);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	if (dst == NULL || src == NULL)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	index = 0;
	if (src[index] == '\0' || size == 1)
		dst[index] = '\0';
	while (index < size - 1 && src[index] != '\0')
	{
		dst[index] = src[index];
		dst[index + 1] = '\0';
		index++;
	}
	return (ft_strlen(src));
}


void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ibyte;
	size_t			index;

	ibyte = (unsigned char *) s;
	index = 0;
	while (index < n)
	{
		if (*ibyte == (unsigned char) c)
			return (ibyte);
		ibyte++;
		index++;
	}
	return (NULL);
}

unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2, size_t ss1, size_t ss2, int opt);

unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2, size_t ss1, size_t ss2, int opt)
{
	unsigned char	*retval;
	size_t	iter;

	iter = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (opt == 0)
		retval = malloc((ss1 + ss2) * sizeof(unsigned char));
	else
		retval = s2;
	if (!retval)
		return (NULL);
	while (iter < ss1)
	{
		retval[iter] = s1[iter];
		iter++;
	}
	free(s1);
	while (iter < ss1+ss2 && opt == 0)
	{
		retval[iter] = s2[iter-ss1];
		iter++;
	}
	return (retval);
}


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;
	size_t				index;

	ptr_dest = (unsigned char *) dest;
	ptr_src = (const unsigned char *) src;
	index = 0;
	while (index < n)
	{
		*ptr_dest = *ptr_src;
		ptr_src++;
		ptr_dest++;
		index++;
	}
	return (dest);
}

char	*ft_memmove(char *dest, const char *src, size_t n)
{
	size_t	iter;

	if (dest > src)
	{
		iter = n;
		while (iter > 0)
		{
			iter--;
			*(dest + iter) = *(src + iter);
		}
	}
	else
	{
		iter = 0;
		while (iter < n)
		{
			*(dest + iter) = *(src + iter);
			iter++;
		}
	}
	return (dest);
}
