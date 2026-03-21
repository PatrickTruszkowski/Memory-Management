#include "Process.h"

int Process::lastProcessID = 1;

Process::Process(int size) : ID(lastProcessID), size(size), assignedPartitionID(0)
{
    lastProcessID++;
}

void Process::ResetIDs()
{
    lastProcessID = 1;
}

int Process::GetID() const
{
    return ID;
}

bool Process::IsWaiting() const
{
    return assignedPartitionID == 0;
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
