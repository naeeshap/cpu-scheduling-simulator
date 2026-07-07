# CPU Scheduler

A CPU scheduling simulator written in **C** that implements five classical operating system scheduling algorithms. This project simulates process execution while calculating key performance metrics used to evaluate scheduling efficiency.

---

## Features

- First Come First Served (FCFS)
- Shortest Job First (SJF)
- Priority Scheduling
- Round Robin (RR)
- Priority Round Robin (Priority RR)

Each scheduler computes:

- Average Waiting Time
- Average Turnaround Time
- Average Response Time

---

## Technologies

- C
- GCC
- Make
- Linked Lists

---

## Project Structure

```
.
├── cpu.c
├── cpu.h
├── driver.c
├── list.c
├── list.h
├── Makefile
├── schedule.txt
├── schedule_fcfs.c
├── schedule_priority.c
├── schedule_priority_rr.c
├── schedule_rr.c
├── schedule_sjf.c
├── schedulers.h
└── task.h
```

---

## Scheduling Algorithms

| Algorithm | Description |
|-----------|-------------|
| FCFS | Executes processes in the order they arrive. |
| SJF | Selects the process with the shortest CPU burst. |
| Priority | Executes the highest-priority process first. |
| Round Robin | Uses a fixed time quantum to fairly distribute CPU time. |
| Priority Round Robin | Applies Round Robin scheduling among processes with the same priority. |

---

## Performance Metrics

For every scheduling algorithm, the simulator reports:

- Waiting Time
- Turnaround Time
- Response Time

These metrics allow direct comparison of scheduling behaviour under different algorithms.

---

## Building

Compile a scheduler using the provided Makefile.

Example:

```bash
make fcfs
```

Run with:

```bash
./fcfs schedule.txt
```

Other supported targets:

```bash
make sjf
make rr
make priority
make priority_rr
```

---

## Sample Output

```text
Running task = [P4] [10] [40] for 10 units.
Running task = [P6] [10] [5] for 5 units.
Running task = [P7] [10] [50] for 10 units.
...

Average waiting time = 289.16
Average turnaround time = 313.68
Average response time = 241.32
```

---

## Concepts Demonstrated

- Operating System Scheduling
- Linked List Data Structures
- Algorithm Design
- Process Scheduling Simulation
- Performance Analysis
- Memory Management in C

---

## Future Improvements

- Interactive scheduler selection
- Custom scheduling quantum
- Process arrival times
- Priority aging
- Gantt chart visualization
- Additional scheduling algorithms (MLFQ, Lottery Scheduling)

---

## Author

**Naeesha Puri**
