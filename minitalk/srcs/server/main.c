/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:32:01 by hateisse          #+#    #+#             */
/*   Updated: 2022/12/08 09:55:48 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    display_pid(void)
{
    printf("%d\n", getpid());
}

int main(void)
{
   display_pid();
   return (0);
}