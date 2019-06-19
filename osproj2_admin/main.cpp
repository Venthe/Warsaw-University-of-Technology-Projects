#include <iostream>
#include <string>

#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "sm_standard.h"

void PrintHelp(std::string s){
    std::cout<<"Usage: " << std::endl;
    std::cout<< s<<" --create"<<std::endl;
    std::cout<< s<<" --destroy"<<std::endl;
}

int Create()
{
    shm_data.sharedMemoryId = shmget(shm_data.sharedMemoryKey, shm_data.sharedMemorySegmentSize, IPC_CREAT);

    if(shm_data.sharedMemoryId==-1){
        SharedMemoryNotValid();
        return 1;
    }

    std::cout<<"Shared memory segment created with ID: "<<shm_data.sharedMemoryId<<std::endl;
    return 0;
}
int Destroy(){
    shm_data.sharedMemoryId = shmget(shm_data.sharedMemoryKey, shm_data.sharedMemorySegmentSize, IPC_EXCL);

    if(shm_data.sharedMemoryId==-1){
        SharedMemoryNotValid();
        return 1;
    }

    if ((shmctl(shm_data.sharedMemoryId,IPC_RMID,0)) == -1){
        std::cerr<<"Could not shmctl(IPC_RMID) of ID "<< shm_data.sharedMemoryId <<" Error: "<<errno<<std::endl;
        return 1;
    }
    std::cout<<"Shared memory segment "<<shm_data.sharedMemoryId<<" destroyed successfully!"<<std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc==2 && SetKeys()==0) { // We expect 2 arguments: the program name and command
        if (argv[1]==std::string("--create")){
            return Create();
        }
        else if (argv[1]==std::string("--destroy")){
            return Destroy();
        }
    }
    PrintHelp(argv[0]);
    return 1;
}
