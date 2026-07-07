/*
 * Name: Naeesha Puri
 * Student ID: 219567320
 *
 * File: schedule_fcfs.c
 * Description:
 * Implements the First-Come, First-Served (FCFS) scheduling algorithm.
 * Tasks are executed in the order they appear in the input file.
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
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = task;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct node *cur = head;
    while (cur->next != NULL)
        cur = cur->next;

    cur->next = newNode;
}

// Adds a new task to the scheduling list, tasks are appended to preserve input order.
void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    newTask->name = strdup(name);
    newTask->tid = next_tid++;
    newTask->priority = priority;
    newTask->burst = burst;

    append(newTask);
}

void schedule() {
    struct node *cur = head;
    int time = 0;
    double total_wait = 0;
    double total_turn = 0;
    double total_resp = 0;
    int count = 0;

    // Executes tasks in input order (non-preemptive FCFS)
    while (cur != NULL) {
        Task *task = cur->task;

        int start = time;

        run(task, task->burst);

        time += task->burst;
        int finish = time;

        total_wait += start;
        total_resp += start;
        total_turn += finish;

        count++;
        cur = cur->next;
    }

    printf("\nAverage waiting time = %.2f\n", total_wait / count);
    printf("Average turnaround time = %.2f\n", total_turn / count);
    printf("Average response time = %.2f\n", total_resp / count);
}

