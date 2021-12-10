/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:39:54 by hashly            #+#    #+#             */
/*   Updated: 2021/12/10 15:16:41 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>

int main(int argc, char **argv)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i <= 13)
	{
		if (fd == 0)
			fd = fork();
		i++;
	}
	if (fd == 0)
		printf("Hello from child proc id: %d\n", fd);
	else
		printf("Hello from main proc id: %d\n", fd);
}
