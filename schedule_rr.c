/*
 * Name: Naeesha Puri
 * Student ID: 219567320
 *
 * File: schedule_rr.c
 * Description: 
 * Implements the Round Robin (RR) scheduling algorithm using a fixed time quantum.
 * Tasks are executed in cyclic order until all bursts complete.
 * Computes average waiting time, turnaround time, and response time.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

static struct node *head = NULL;
static int next_tid = 0;

static void append(Task *task) {
    struct node *n = malloc(sizeof(struct node));
    n->task = task;
    n->next = NULL;

    if (head == NULL) {
        head = n;
        return;
    }

    struct node *cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = n;
}

// Adds a new task to the scheduling list, tasks are appended to preserve input order.
void add(char *name, int priority, int burst) {
    Task *t = malloc(sizeof(Task));
    t->name = strdup(name);
    t->tid = next_tid++;
    t->priority = priority;
    t->burst = burst;

    append(t);
}

void schedule() {
    int n = 0;
    for (struct node *cur = head; cur != NULL; cur = cur->next) n++;

    Task **tasks = malloc(sizeof(Task*) * n);
    int *orig = malloc(sizeof(int) * n);
    int *rem = malloc(sizeof(int) * n);
    int *first = malloc(sizeof(int) * n);       
    int *completion = malloc(sizeof(int) * n);  

    int i = 0;
    for (struct node *cur = head; cur != NULL; cur = cur->next) {
        tasks[i] = cur->task;
        orig[i] = cur->task->burst;
        rem[i] = cur->task->burst;
        first[i] = -1;
        completion[i] = -1;
        i++;
    }

    int time = 0;
    int finished = 0;

    // Continues cycling through tasks until all have completed
    while (finished < n) {
        for (int j = 0; j < n; j++) {
            if (rem[j] <= 0) continue;

            // Records first time the task gets response time
            if (first[j] == -1) first[j] = time;

            // Runs task for one quantum or remaining burst, whichever is smaller
            int slice = (rem[j] > QUANTUM) ? QUANTUM : rem[j];

            int saved = tasks[j]->burst;
            tasks[j]->burst = rem[j];

            run(tasks[j], slice);

            tasks[j]->burst = saved;

            time += slice;
            rem[j] -= slice;

            if (rem[j] == 0) {
                completion[j] = time;
                finished++;
            }
        }
    }

    double total_wait = 0, total_turn = 0, total_resp = 0;

    for (int j = 0; j < n; j++) {
        int turnaround = completion[j];
        int waiting = turnaround - orig[j];
        int response = first[j];

        total_wait += waiting;
        total_turn += turnaround;
        total_resp += response;
    }

    printf("\nAverage waiting time = %.2f\n", total_wait / n);
    printf("Average turnaround time = %.2f\n", total_turn / n);
    printf("Average response time = %.2f\n", total_resp / n);

    free(tasks);
    free(orig);
    free(rem);
    free(first);
    free(completion);
}