#include "externalExecutor.h"

void externalProgramFlow(char* const* jobArgs, int externBufferPipe[2]) {
    dup2(externBufferPipe[WRITE_PIPE], STDOUT_FILENO);               // Duplicate the write end to child process' stdout
    dup2(externBufferPipe[WRITE_PIPE], STDERR_FILENO);               // Duplicate the write end to child process' stderr
    close(externBufferPipe[READ_PIPE]);                              // The child isn't reading from the buffer
    close(externBufferPipe[WRITE_PIPE]);                             // We're closing the pipe file descriptor, NOT the pipe

    execv(jobArgs[0], jobArgs);     // This replaces the further code
                                    // In child process with the external program

    // So if the child process reaches here, execv failed!
    
    externalProcessFailure(jobArgs[0]);
}

void parentProgramFlow(
    int forkedProcStatus, 
    int externBufferPipe[2], 
    char* tempExternBuffer, int tempExternBufferSize, 
    char* completeExternBuffer, int completeExternBufferSize, 
    pid_t pid
) {
    int nBytesRead = 0;
    pid_t ch_pid;
    close(externBufferPipe[WRITE_PIPE]);                                                    // The parent isn't writing
    do {
        while (
            (nBytesRead = read(externBufferPipe[READ_PIPE], tempExternBuffer, tempExternBufferSize)) != 0
        ) {             // Listen for output from the child process
            appendToBuffer(completeExternBuffer, completeExternBufferSize, tempExternBuffer);   // Append to temp buffer
        }
        
        ch_pid = waitpid(pid, &forkedProcStatus, WUNTRACED | WCONTINUED);                   // Till the child process terminates
        if (checkProcessFailed(ch_pid)) {                                                   // If failed, log it
            appendToOutputBuffer(ERROR_RUN_WAITPID_TEXT);
        }
        appendToOutputBuffer(completeExternBuffer);
    } while (!WIFEXITED(forkedProcStatus) && !WIFSIGNALED(forkedProcStatus));               // Do that till child process exits or signals
    appendToOutputBuffer(DISPATCHER_COLOR);
}

void execute(JobPtr job, int status) {
    pid_t pid;
    int externBufferPipe[2];
    int tempExternBufferSize = TEMP_EXTERN_BUFFER_SIZE;
    char* completeExternBuffer;
    int completeExternBufferSize = COMP_EXTERN_BUFFER_SIZE;
    char* tempExternBuffer;
    int forkedProcStatus = 0;

    char* const* jobArgs = job->jobArgs;

    // Create the buffers, and reset them
    tempExternBuffer = (char*)malloc((tempExternBufferSize + 1) * sizeof(char));            // +1 for NULL
    completeExternBuffer = (char*)malloc((completeExternBufferSize + 1) * sizeof(char));
    clearBuffer(tempExternBuffer, tempExternBufferSize + 1);
    clearBuffer(completeExternBuffer, completeExternBufferSize + 1);

    appendToBuffer(completeExternBuffer, completeExternBufferSize, EXTERNAL_P_COLOR);       // This is the color for the external program

    if(pipeCreationFailed(externBufferPipe)){
        appendToOutputBuffer(ERROR_RUN_PIPE_TEXT);
        free(tempExternBuffer);
        free(completeExternBuffer);
        return;
    }

    // Here, forking instead of another thread because
    // Processes are protected by hardware
    // Thus the job gets a seperate execution area
    // Why fork? execv replaces the current process --> external process
    // And We don't want execv replacing the dispatcher thread!
    pid = fork();

    if (errorForking(pid)) 
        appendToOutputBuffer(ERROR_RUN_FORK_TEXT);

    else if (inChildProcess(pid))  // Execute and run the program!
        externalProgramFlow(jobArgs, externBufferPipe);

    else  // In the parent, dispatcher's process thread
        parentProgramFlow(
            forkedProcStatus, 
            externBufferPipe, 
            tempExternBuffer, tempExternBufferSize, 
            completeExternBuffer, completeExternBufferSize,
            pid
        );

    free(tempExternBuffer);
    free(completeExternBuffer);
}