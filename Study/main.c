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
#include <unistd.h>

int num = 0;
pthread_mutex_t mutex;

void    *routine()
{
    int i = 0;
    
    while (i < 100)
    {
        pthread_mutex_lock(&mutex);
        num++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

int main()
{
    pthread_t t[4];
    int i = 0;

    pthread_mutex_init(&mutex, NULL);
    while (i < 4)
    {
        if(pthread_create(&t[i], NULL, &routine, NULL) != 0)
        {
            return 1;
        }
        printf("Thread %d: Started\n", i);
        i++;  
    }
    i = 0;
    pthread_detach(t[3]);
    while (i < 4)
    {
        if(pthread_join(t[i], NULL) != 0)
        {
            perror("Error\n");
        }
        printf("Thread %d: Finished\n", i);
        i++;  
    }
    pthread_mutex_destroy(&mutex);
    printf("Num Value is: %d\n", num);
    return (0);
}
