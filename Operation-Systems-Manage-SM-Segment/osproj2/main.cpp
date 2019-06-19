#include <iostream>
#include <string>
#include <cstdlib>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "sm_standard.h"

void PrintHelp(std::string s){
    std::cout<<"Usage: " << std::endl;
    std::cout<< s<<" --register\n";
    std::cout<< s<<" --deregister <Optional:PID>\n";
    std::cout<< s<<" --readall\n";
}

struct CLIENT_DATA {
    void *shmaddr_ptr;
    pid_t * array;
} client_data;



int Register(__pid_t pid){
    std::cout<<"Registering PID "<<pid<<"\n";
    client_data.shmaddr_ptr=shmat(shm_data.sharedMemoryId, NULL, 0);
    if(client_data.shmaddr_ptr == (void*)-1){
        std::cerr<<"Error calling shmat, errorno: "<<errno<<std::endl;
        return 1;
    }

    int j=-1;
    client_data.array = (pid_t *) client_data.shmaddr_ptr;
    for(int i=0; i<PID_SEGMENT_COUNT; i++)
    {
        if(client_data.array[i]==0&&j==-1){
            j=i;
        }
        else if(client_data.array[i]==pid){
            j=-2;
            break;
        }
    }
    if(j==-1){std::cerr<<"There was no memory left to store PID!"<<std::endl;}
    else if(j==-2){std::cerr<<"PID already stored!"<<std::endl;}
    else {std::cout<<"Storing "<<pid<<std::endl; client_data.array[j]=pid;}

    if(shmdt(client_data.shmaddr_ptr)==-1){
        std::cerr<<"Error calling shmaddr, errorno: "<<errno<<std::endl;
        return 1;
    }
    return 0;
}

int Deregister(__pid_t pid)
{
    std::cout<<"Deregister PID "<<pid<<"\n";
    client_data.shmaddr_ptr=shmat(shm_data.sharedMemoryId, NULL, 0);
    if(client_data.shmaddr_ptr == (void *) -1){
        std::cerr<<"Error calling shmat, errorno: "<<errno<<std::endl;
        return 1;
    }

    int j=-1;
    client_data.array = (pid_t *) client_data.shmaddr_ptr;
    for(int i=0; i<PID_SEGMENT_COUNT; i++)
    {
        if(client_data.array[i]==pid)
        {
            std::cout<<"Deleted "<<pid<<std::endl;
            for(j=i;j<PID_SEGMENT_COUNT-1;j++)
            {
                client_data.array[j]=client_data.array[j+1];
                if(client_data.array[j+1]==0) break;
            }
            client_data.array[PID_SEGMENT_COUNT-1]=0;
        }
    }
    if(j==-1) std::cout<<"There was no process of PID "<<pid<<" in the memory."<<std::endl;

    if(shmdt(client_data.shmaddr_ptr)==-1){
        std::cerr<<"Error calling shmaddr, errorno: "<<errno<<std::endl;
        return 1;
    }
    return 0;
}
int Readall()
{
    std::cout<<"Print all PID\n";
    client_data.shmaddr_ptr=shmat(shm_data.sharedMemoryId, NULL, SHM_RDONLY);
    if(client_data.shmaddr_ptr == (void *) -1){
        std::cerr<<"Error calling shmat, errorno: "<<errno<<std::endl;
        return 1;
    }

    client_data.array = (pid_t *) client_data.shmaddr_ptr;
    for(int i=0; i<PID_SEGMENT_COUNT; i++)
    {
        std::cout<<i<<") "<<client_data.array[i]<<std::endl;
    }

    if(shmdt(client_data.shmaddr_ptr)==-1){
        std::cerr<<"Error calling shmaddr, errorno: "<<errno<<std::endl;
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    __pid_t myPid = ::getpid();

    if ((argc==2||(argc==3&&argv[1]==std::string("--deregister"))) && SetKeys()==0) { // We expect 2 arguments: the program name and command
        shm_data.sharedMemoryId = shmget(shm_data.sharedMemoryKey, shm_data.sharedMemorySegmentSize, IPC_EXCL);
        if(shm_data.sharedMemoryId==-1){
            SharedMemoryNotValid();
            return 1;
        }
        if (argv[1]==std::string("--register")){
            return Register(myPid);
        }
        else if (argv[1]==std::string("--deregister")){
            if(argc==3)
            {
                myPid = static_cast<pid_t>(strtol(argv[2],NULL,10));
                std::cout<<"MyPid: "<<myPid<<std::endl;
            }
            return Deregister(myPid);
        }
        else if (argv[1]==std::string("--readall")){
            return Readall();
        }
    }
    PrintHelp(argv[0]);
    return 1;
}
