#include "Process.h"

int Process::lastProcessID = 0;

Process::Process(int size) : ID(lastProcessID), size(size), assignedPartitionID(-1)
{
    lastProcessID++;
}

int Process::GetID() const
{
    return ID;
}

bool Process::IsWaiting() const
{
    return assignedPartitionID == -1;
}

int Process::GetSize() const
{
    return size;
}

int Process::GetAssignedPartitionID() const
{
    return assignedPartitionID;
}

void Process::SetAssignedPartitionID(int partitionID)
{
    assignedPartitionID = partitionID;
}
