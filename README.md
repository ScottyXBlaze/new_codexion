*This project has been created as part of the 42 curriculum by nyramana.*

# Codexion

> While loop is not enough .

## **Description**

**Codexion** is a multi threading project that simulate the Dinning-Philosopher Problem. It is a classic synchronization and concurrency problem that deals with resource sharing, deadlock, and starvation in systems where multiple processes require limited resources.

### Goal

The goal is to learn how these property can be handled with multithreading and mutexes. It also teach how to manage deadlock and starvation so that every thread can get their resources.

### Brief Overview

**Example:**

Input:

```bash
./codexion 4 1500 200 200 200 1 100 fifo
```

Output:

```bash
0 2 has taken a dongle
0 2 has taken a dongle
0 2 is compiling
0 1 has taken a dongle
200 2 is debugging
300 1 has taken a dongle
300 1 is compiling
300 3 has taken a dongle
300 3 has taken a dongle
300 3 is compiling
400 2 is refactoring
500 1 is debugging
500 3 is debugging
600 4 has taken a dongle
600 4 has taken a dongle
600 4 is compiling
700 1 is refactoring
700 3 is refactoring
800 4 is debugging
1000 4 is refactoring
```

## **Instructions**

### Compilation

### Execution

## **Resources**

### AI usage

## Extras

### Blocking cases handled

### Thread synchronization mechanisms
