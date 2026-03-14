#include "Partition.h"

int Partition::lastPartitionID = 0;

Partition::Partition(int size) : ID(lastPartitionID), size(size), assignedProcessID(-1)
{
    lastPartitionID++;
}

int Partition::GetID() const
{
    return ID;
}

bool Partition::IsInUse() const
{
    return assignedProcessID != -1;
}

int Partition::GetSize() const
{
    return size;
}

int Partition::GetAssignedProcessID() const
{
    return assignedProcessID;
}

void Partition::SetAssignedProcessID(int processID)
{
    assignedProcessID = processID;
}
