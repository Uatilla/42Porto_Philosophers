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
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

//How to pass more than one argument in this function?
void*   routine(void *arg)
{
    sleep(1);
    int index = *(int*)arg;
    int sum = 0;
    for (int j = 0; j < 5; j++)
    {
        sum += primes[index + j];
    }
    printf("Local Sum: %d\n", sum);
    *(int *)arg = sum;
    return arg;
}

int main()
{
    pthread_t th[2];
    for (int i = 0; i < 2; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
            return 1;
    }
    int globalSum = 0;
    for (int i = 0; i < 2; i++)
    {
        //Why?
        int *r;
        if (pthread_join(th[i], (void **) &r) != 0)
            return 2;
        globalSum += *r;
        free(r);
    }
    printf("Global Sum: %d\n", globalSum);
    return (0);
}
