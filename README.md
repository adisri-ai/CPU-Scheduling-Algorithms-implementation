# Overview  
CPU scheduling algorithms are used for scheduling various processes in an Operating Systems that performs more than one task at a time.  
The are important for the following reasons:  
1. Improve CPU utilization.
2. Reduce CPU Idle Time.
3. Enable priority-based execution.
4. Help in avoiding Process starvation.
This repository implements each of the following CPU scheduling Algorithms using C++:
1. **First Come First Serve(FCFS)** : The most basic algorithm executing each process serially in order of arrival.
2. **Shortest Job First(SJF)**      : Executes the process having the shortest burst time without any premption by other processes.
3. **Shortest Remaining Job First(SRJF)** : Executes the process with lowest remaining burst time at any point. Also Enables Premption.
4. **Priority-based Execution** :  Executes the process having highest priority at any point of time without premption.
5. **Premptive Priority-based Execution** : Executes the process having highest priority with premption.
6. **Round-Robin** : Gives equal to time each process to avoid starvation, performing context switching at every time quantum interval.
