/*
 * Name: Naeesha Puri
 * Student ID: 219567320
 *
 * File: schedule_priority.c
 * Description: 
 * Implements the Priority scheduling algorithm.
 * Tasks are executed in descending priority order.
 * Ties are resolved using input order.
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
    int *done = calloc(n, sizeof(int));

    int i = 0;
    for (struct node *cur = head; cur != NULL; cur = cur->next) {
        tasks[i++] = cur->task;
    }

    int time = 0;
    double total_wait = 0, total_turn = 0, total_resp = 0;

    // Processes tasks in descending priority order
    for (int p = MAX_PRIORITY; p >= MIN_PRIORITY; p--) {
        for (int j = 0; j < n; j++) {
            if (done[j]) continue;
            if (tasks[j]->priority != p) continue;

            Task *t = tasks[j];

            int start = time;
            run(t, t->burst); // Runs task to completion using non-preemptive priority scheduling
            time += t->burst;
            int finish = time;

            total_wait += start;
            total_resp += start;
            total_turn += finish;

            done[j] = 1;
        }
    }

    printf("\nAverage waiting time = %.2f\n", total_wait / n);
    printf("Average turnaround time = %.2f\n", total_turn / n);
    printf("Average response time = %.2f\n", total_resp / n);

    free(tasks);
    free(done);
}