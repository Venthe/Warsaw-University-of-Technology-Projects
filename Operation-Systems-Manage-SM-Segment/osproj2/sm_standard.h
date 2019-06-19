#include <errno.h>
#include <libgen.h>

#ifndef SM_STANDARD_H_INCLUDED
#define SM_STANDARD_H_INCLUDED

#define PATH_MAX 0xFF
#define PID_SEGMENT_COUNT 0xF

struct SHM_DATA {
    key_t sharedMemoryKey;
    static const size_t sharedMemorySegmentSize = static_cast<size_t>(sizeof(pid_t)*PID_SEGMENT_COUNT);
    int sharedMemoryId;
}static shm_data;

void SharedMemoryNotValid(){
    std::cerr<<"Unable to reserve a shared memory segment! Error: "<<errno<<std::endl;
}

int SetKeys(){
    std::string path;
    {
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX-1);
        if (count == -1) {
            std::cerr<<"Could not find path to caller executable, unique Key could not be generated! Error: "<<errno<<std::endl;
            return 1;
        }
        path = dirname(result);
    }

    shm_data.sharedMemoryKey = ftok(path.c_str(), 'R');
    return 0;
}

#endif // SM_STANDARD_H_INCLUDED
