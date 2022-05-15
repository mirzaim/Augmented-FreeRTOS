# Real-Time Task Scheduler Simulation

This repository contains a simulation of real-time task scheduling using the FreeRTOS framework. The project implements various task scheduling algorithms, including:

- **Rate Monotonic (RM) Scheduling**
- **First-Come, First-Served (FCFS) Scheduling**
- **Task Management with Periodic and Sporadic Tasks**

## Features

1. **Task Creation and Scheduling**:
   - Tasks with different execution times, periods, and deadlines are created using FreeRTOS.
   - Scheduling is handled by either the RM or FCFS scheduler, with tests included for both implementations.

2. **Task Suspension and Resumption**:
   - A mechanism to suspend and resume tasks dynamically, demonstrated in the handling of "Task 1."

3. **Sporadic Task Management**:
   - The system also supports sporadic tasks, which are created with randomized intervals and managed with high priority to simulate interrupts.

4. **Real-Time Simulation**:
   - The project simulates real-time task execution, providing detailed logging of task start, end, and missed deadlines.

## Branches

The codebase is organized across different branches to facilitate switching between different implementations:

- **master**: Initial setup and project formatting.
- **task_sim**: Contains the core task simulation, including periodic tasks and sporadic task implementation.
- **fcfs_scheduler**: Implements the FCFS scheduling algorithm and its test cases.
- **rm_scheduler**: Implements the Rate Monotonic scheduling algorithm and its test cases.

## Task Overview

- **Periodic Tasks**:  
  Four tasks with different priorities and periods (e.g., 250ms, 500ms, 750ms, and 1000ms) simulate real-world periodic task execution.

- **Sporadic Task**:  
  A high-priority sporadic task is implemented to simulate interrupts or randomly occurring tasks in the system.

- **Task Manager**:  
  The Task Manager oversees task suspension and resumption, managing task states dynamically.

## Usage

1. **Cloning the repository**:
   ```bash
   git clone https://github.com/username/repository-name.git
   ```

2. **Switching between branches**:  
   Each branch contains a specific scheduling algorithm or task simulation feature. Switch between them as necessary:
   ```bash
   git checkout fcfs_scheduler
   git checkout rm_scheduler
   ```

3. **Building the project**:  
   The main file is `main.c` in the `Project` directory. After making any changes, you can build the project using the following command:
   ```bash
   make
   ```

4. **Running the simulation**:  
   Once built, you can run your FreeRTOS simulation with:
   ```bash
   ./FreeRTOS-Sim
   ```

