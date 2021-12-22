/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:14:11 by hashly            #+#    #+#             */
/*   Updated: 2021/12/22 14:26:37 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

size_t	ft_strlen(const char *str )
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	n;

	if (!src)
		return (0);
	len = ft_strlen(src);
	if (!dst || !size)
		return (len);
	if (size)
	{
		if (len < size)
			n = len;
		else
			n = size - 1;
		while (n--)
			*dst++ = *src++;
		*dst = 0;
	}
	return (len);
}

static char	*ft_strdup(const char *src)
{
	int		len;
	char	*ptr;

	len = ft_strlen(src);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == (void *)0)
		return ((void *)0);
	ft_strlcpy(ptr, src, len + 1);
	return (ptr);
}

static size_t	ft_find_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648\0"));
	i = 0;
	len = ft_find_len(n);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		ptr[i++] = '-';
		n *= -1;
	}
	ptr[len] = 0;
	while (len > i)
	{
		ptr[--len] = n % 10 + 48;
		n = n / 10;
	}
	return (ptr);
}
