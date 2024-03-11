/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:31:06 by uviana-a          #+#    #+#             */
/*   Updated: 2024/03/02 15:31:08 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

void*   roll_dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    printf("Address local:%p\n", result);
    return (void *) result;
}

int main()
{
    int *res;
    srand(time(NULL));
    pthread_t th;

    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
        return 1;
    if (pthread_join(th, (void **) &res) != 0)
        return 2;
    printf("Address global: %p\n", res);
    free(res);
    return (0);
}
