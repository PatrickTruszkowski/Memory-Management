#include "Partition.h"

int Partition::lastPartitionID = 1;

Partition::Partition(int size, Partition* subPartition) : ID(lastPartitionID), subID(0), lastSubID(1), subPartition(subPartition), size(size), assignedProcessID(0)
{
    if (subPartition)
    {
        subPartition->AddSubPartition(*this);
    }
    lastPartitionID++;
}

void Partition::ResetIDs()
{
    lastPartitionID = 1;
}

int Partition::GetID() const
{
    return ID;
}

bool Partition::IsInUse() const
{
    return assignedProcessID != 0;
}

bool Partition::IsSubPartition() const
{
    return subID != 0;
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

void Partition::SetSubID(int ID)
{
    subID = ID;
}

Partition* Partition::GetSubPartition()
{
    return subPartition;
}

int Partition::GetSubID() const
{
    return subID;
}

void Partition::AddSubPartition(Partition& partition)
{
    partition.SetSubID(lastSubID);
    this->size -= partition.GetSize();
    lastSubID++;
}
