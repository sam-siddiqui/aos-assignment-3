#ifndef TEXT_H_
#define TEXT_H_

#define VERSION_NUMBER "1.5"

#define WELCOME_MAIN_TEXT "AUBatch " VERSION_NUMBER "\nCLI Ready!\nType help or ? to find more about the commands\n"
#define WELCOME_SCHEDULER_TEXT "Scheduler Thread... Ready \n"
#define WELCOME_DISPATCHER_TEXT "Executor Thread... Ready \n"

#define QUIT_MAIN_TEXT "Quitting AUBatch...\n"
#define QUIT_CLI_TEXT "Exiting AUBatch CLI...\n"
#define QUIT_SCHEDULER_TEXT "Quitting Scheduler...\n"
#define REMAINING_JOBS_SCHEDULER_TEXT "Dispatcher will wait till jobs are completed...\n"
#define QUIT_DISPATCHER_TEXT "Quitting Dispatcher...\n"

#define SCHEDULER_COLOR "\033[0;31m"        // Red
#define DISPATCHER_COLOR "\033[0;33m"       // Yellow
#define EXTERNAL_P_COLOR "\033[0;34m"       // Blue
#define DEFAULT_COLOR "\033[0m"             // Default

/*-------------------------------------------- CLIParser ----------------------------------------------------------------*/

#define OUTPUT_BUFFER_FAILED_TEXT "Memory allocation failed for outputBuffer.\n"

#define NO_CMD_TEXT "No command entered!\n"
#define UNKNOWN_CMD_TEXT "Unknown command entered! Try help or ?\n"

#define CMD_HANDLE "[? for help]> "

#define CMD_INDEX 0
#define RUN_BURSTTIME_INDEX 1
#define RUN_PRI_INDEX 2
#define RUN_JOBNAME_INDEX 3
#define RUN_MIN_ARGS_COUNT 4

/*-------------------------------------------- Help Command ----------------------------------------------------------------*/

// Don't forget to change the indexes above if you're changing the format of run command!
#define RUN_HELP_TEXT "Run JOB: \n" \
                         "\trun <time> <pri> <job> <...args for job> : submit a job named <job>, \n" \
                         "\t\t\t<time> is execution time, \n" \
                         "\t\t\t<pri> is  it's priority. \n" 
           
#define LIST_HELP_TEXT "List Waiting and Completed Jobs : \n" \
                         "\tlist: display the job status. \n" \
                         "\tlist -r: display the job status live whilst jobs running in background. \n" 

#define POLICY_HELP_TEXT "Scheduling policy: \n" \
                              "\tset_policy <policy> : change the scheduling policy to <policy>. \n" \
                              "\t<policy> can be fcfs or sjf or pri. \n" 

#define TEST_HELP_TEXT "Automated Test File: \n" \
                        "Simulate multiple jobs at once for benchmark testing \n" \
                        "\ttest <benchmark_file_name> <scheduling_policy> <numJobs> <priority_levels_from_0>\n " \
                        "\t<minCPUtime> <maxCPUtime> <arrival_rate>\n" 

#define QUIT_HELP_TEXT "Quit Program: \n" \
                         "\tquit\n" \
                         "\texit\n" 

#define ERROR_HELP_TEXT "Error: Undefined param for help \n""Try help (list || run || set_policy || test || quit || exit) \n"

#define HELP_TEXT RUN_HELP_TEXT LIST_HELP_TEXT POLICY_HELP_TEXT TEST_HELP_TEXT QUIT_HELP_TEXT

/*-------------------------------------------- Set Policy Command ----------------------------------------------------------*/

#define ERROR_WRONG_POLICY_TEXT "Error - set_policy <policy>: <policy> can only be exactly one of - fcfs or sjf or pri\n"
#define ERROR_WRONG_NUM_ARGS_POLICY_TEXT "Error - set_policy <policy>: Exactly 1 argument, one of fcfs or sjf or pri\n"
#define ERROR_TEST_RUNNING_FORMAT "Error - %s: Test running. Try later\n"
#define POLICY_CHANGE_SUCCESS_FORMAT "Changed Schedule Policy to %s\n"

/*-------------------------------------------- List Command ----------------------------------------------------------------*/

#define READY_QUEUE_TITLE_FORMAT "Total number of jobs submitted: %-3d  \t\t\t    Number of jobs waiting in queue: %3d\n"
#define READY_QUEUE_HEADER_FORMAT "Ready Queue: \t\t\t\t\t\t\t Current Scheduling Policy: %-4s\n"
#define READY_QUEUE_TABLEHEADER_FORMAT "S.No \t Name \t\t CPUBurstTime \t  Arr. Q.No \tPriority \tArrivalTime \tProgress \n"
#define READY_QUEUE_TABLEROW_FORMAT "%-8s %-15s %-16d %-13d %-7d %10d:%-2d:%-8d %s \n"
#define RUNNINGJOB_TABLEROW_FORMAT READY_QUEUE_TABLEROW_FORMAT

#define COMPLETED_QUEUE_TITLE_FORMAT "Completed Queue:       \t\t\t\t\t\t\t    Total completed: %3d\n"
#define COMPLETED_QUEUE_TABLEHEADER_FORMAT "S.No \t Name \t\t CPUBurstTime \t ExecutionTime \tPriority \tArrivalTime \tProgress \n"
#define COMPLETED_QUEUE_TABLEROW_FORMAT "%-8d %-15s %-15d %-14d %-8d%10d:%-2d:%-9d %-10s  \n"

#define REMAINING_JOBS_FORMAT "Remaining jobs: %d, Expected waiting time: %d\n"

#define LIST_ERROR_TEXT "list command takes no arguments! or only -r for repeat\n"

/*---------------------------------------------Run Command ------------------------------------------------------------------*/

#define ERROR_RUN_SCHEDULER_BUSY "Error - Run: \n " \
                                 "Scheduler is busy! run is not available till then \n"

#define ERROR_RUN_TEXT_FORMAT "Error - Run: %d params given instead of 4\n" \
                              "run <job:str> <time:int> <pri:int> : submit a job named <job> with execution " \
                              "time <time> and priority <pri>\n"

#define RUN_SUCCESS_TEXT_FORMAT "Job %s was submitted successfully \n" \
                                "Total num jobs in queue: %d \n" \
                                "Expected waiting time: %d seconds \n" \
                                "Schedule Policy: %s \n"

#define ERROR_RUN_FORK_TEXT "Dispatcher: fork error\n"
#define ERROR_RUN_PIPE_TEXT "Dispatcher: externBuffer pipe error\n"
#define ERROR_RUN_WAITPID_TEXT "waitpid: Process Failed\n"
#define ERROR_PROC_CREATION_FAILED_FORMAT "Execv: Process %s failed\n"

/*---------------------------------------------Test Command ------------------------------------------------------------------*/

#define BENCHMARK_HEADER_FORMAT "\nBenchmark Test, Schedule Policy: %s, Arrival Rate: %d \n" \
                                "Number of Jobs:%d, \t Max Priority Level:%d, \t MinCPU:%d, \t MaxCPU:%d \n" \
                                "Name \t\t\t CPU_Burst_Time \t\t Priority \t    Status \n"

#define BENCHMARK_ROW_FORMAT "%-24s %-31d %-13d %12s \n"

#define BENCHMARK_SAVEFILENAME_FORMAT "%s_%s.txt"

#define ERROR_TEST_TEXT "Error: Test Command. \n " \
                        "test <benchmark_save_file> <policy> <numJobs> <priority_levels_from_0> \n" \
                        "\t<min_CPU_Time> <max_CPU_Time> <arrival_rate>\n"

#define ERROR2_TEST_TEXT "Error: Test Command. \n" \
                        "\tThere are currently jobs in queue or running \n" \
                        "\tPlease wait for them to complete\n"

#define ERROR_INVALID_POLICY_TEXT "Test failed: Invalid policy! \n"
#define ERROR_BENCH_FILE_CREATION_FAILED_TEXT "Test failed: Error opening file! \n"

#define TEST_SUBMIT_SUCCESS_TEXT "Test Submitted Successfully!\n"

#define TEST_DONE_TEXT "Benchmark Test Completed! \n" \
                       "Exit or press Enter (no command) for stats \n"

#define STATS_LIST_FORMAT "Total number of job submitted: %13d \n" \
                     "Average turnaround time: %11.2f seconds \n" \
                     "Average CPU time: \t %11.2f seconds \n" \
                     "Average waiting time: \t %11.2f seconds \n" \
                     "Minimum response time: \t %11d seconds \n" \
                     "Average response time: \t %11.2f seconds \n" \
                     "Maximum response time: \t %11d seconds \n" \
                     "StdDev response time: \t %11.2f seconds \n" \
                     "Throughput: \t %16.6f No./second \n"

#endif  // TEXT_H_