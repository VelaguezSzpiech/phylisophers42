
# Philosophers42

This repository contains a concurrency project written in C for the 42 Wolfsburg curriculum. The primary goal is to solve the “Dining Philosophers” (or similarly named) concurrency challenge by managing multiple threads (or processes) attempting to use limited shared resources without deadlock or starvation.

## Project Overview

- Written in C (91.9% according to the repository’s language composition).  
- Uses concurrency control mechanisms (e.g., mutexes or semaphores) to coordinate access to shared resources.  
- Includes a Makefile (8.1%) to build the program easily.

## How It Works

1. Each “philosopher” (a thread or process) alternates between thinking, picking up resources, and eating.  
2. Shared resources (forks/chopsticks) are protected by synchronization constructs to prevent conflicting access.  
3. To avoid deadlock, specific picking-up and putting-down strategies are implemented, ensuring safe resource usage.

## How to Build

1. Clone the repository (if you haven’t already):  
```bash
git clone https://github.com/VelaguezSzpiech/phylisophers42.git
```

2. Navigate to the project directory:  
```bash
cd phylisophers42
```

3. Run the Makefile to compile:  
```bash
make
```
This creates the executable (e.g., “philosophers” or similarly named binary).

## How to Run

1. Execute the compiled program:  
```bash
./philosophers [number_of_philosophers] [other_optional_args]
```
2. Adjust the parameters (like number of philosophers) based on the specific requirements of the 42 Wolfsburg project.

## Why This Code Was Used

- **Efficiency and Control**: C allows fine-grained control over memory management and thread synchronization, crucial for concurrency projects.  
- **Low-Level Synchronization**: The project uses standard POSIX threads and mutexes (or semaphores) to demonstrate clear concurrency patterns.  
- **Structured Approach**: By using a Makefile and organized source files, the build process is straightforward, helping maintain clarity in a multi-file project.

