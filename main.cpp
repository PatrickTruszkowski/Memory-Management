#include <iostream>
#include <vector>

#include "Process.h"
#include "Partition.h"

void Initialize();
int BestFit();
int FirstFit();
int NextFit();
int WorstFit();

std::vector<Process> processVector;
std::vector<Partition> partitionVector;

int processCount = 0;
int partitionCount = 0;

int main()
{
    Initialize();

    std::cout << "\nBest Fit Waste: " << BestFit() << "\n\n";

    for (const Partition& partition : partitionVector)
    {
        std::cout << "Partition " << partition.GetID() + 1 << ": Assigned Process ID: " << partition.GetAssignedProcessID() + 1 << "\n";
    }

    std::cout << "\n";

    for (const Process& process : processVector)
    {
        std::cout << "Process " << process.GetID() + 1 << ": Assigned Partition ID: " << process.GetAssignedPartitionID() + 1;

        if (process.IsWaiting())
        {
            std::cout << " (Waiting)";
        }

        std::cout << "\n";
    }

    return 0;
}

void Initialize()
{
    // Pre-defined test values.
    processVector.emplace_back(200);
    processVector.emplace_back(100);
    processVector.emplace_back(300);
    processVector.emplace_back(300);
    processVector.emplace_back(200);

    processCount = 5;

    partitionVector.emplace_back(100);
    partitionVector.emplace_back(300);
    partitionVector.emplace_back(200);
    partitionVector.emplace_back(450);

    partitionCount = 4;

    return;

    std::cout << "Enter process count: ";
    std::cin >> processCount;

    std::cout << "\n";

    for (int i = 0; i < processCount; i++)
    {
        int size = 0;

        std::cout << "Enter process " << i + 1 << " size: ";
        std::cin >> size;

        processVector.emplace_back(size);
    }

    std::cout << "\n";

    std::cout << "Enter partition count: ";
    std::cin >> partitionCount;

    std::cout << "\n";

    for (int i = 0; i < partitionCount; i++)
    {
        int size = 0;

        std::cout << "Enter partition " << i + 1 << " size: ";
        std::cin >> size;

        partitionVector.emplace_back(size);
    }
}

int BestFit()
{
    int totalWaste = 0;
    int lowestWaste = 0xFFFFFF;
    int lowestWastePartitionIndex = -1;

    for (int i = 0; i < processCount; i++)
    {
        Process& currentProcess = processVector.at(i);
        int processSize = currentProcess.GetSize();

        for (int j = 0; j < partitionCount; j++)
        {
            Partition& currentPartition = partitionVector.at(j);
            int partitionSize = currentPartition.GetSize();

            if (processSize <= partitionSize && !currentPartition.IsInUse())
            {
                int currentWaste = partitionSize - processSize;

                if (lowestWaste > currentWaste)
                {
                    lowestWaste = currentWaste;
                    lowestWastePartitionIndex = j;
                }
            }
        }

        if (lowestWastePartitionIndex == -1)
        {
            continue;
        }

        Partition& lowestWastePartition = partitionVector.at(lowestWastePartitionIndex);

        currentProcess.SetAssignedPartitionID(lowestWastePartition.GetID());
        lowestWastePartition.SetAssignedProcessID(currentProcess.GetID());

        totalWaste += lowestWaste;

        lowestWaste = 0xFFFFFF;
        lowestWastePartitionIndex = -1;
    }

    return totalWaste;
}

int FirstFit()
{
    int totalWaste = 0;

    for (int i = 0; i < processCount; i++)
    {
        Process& currentProcess = processVector.at(i);
        int processSize = currentProcess.GetSize();

        for (int j = 0; j < partitionCount; j++)
        {
            Partition& currentPartition = partitionVector.at(j);
            int partitionSize = currentPartition.GetSize();

            if (processSize <= partitionSize && !currentPartition.IsInUse())
            {
                currentProcess.SetAssignedPartitionID(currentPartition.GetID());
                currentPartition.SetAssignedProcessID(currentProcess.GetID());

                totalWaste += partitionSize - processSize;

                break;
            }
        }
    }

    return totalWaste;
}

int NextFit()
{
    int totalWaste = 0;
    int checkedPartitionCount = 0;
    int lastIndex = 0;

    for (int i = 0; i < processCount; i++)
    {
        Process& currentProcess = processVector.at(i);
        int processSize = currentProcess.GetSize();

        for (int j = lastIndex; j < partitionCount; j++)
        {
            Partition& currentPartition = partitionVector.at(j);
            int partitionSize = currentPartition.GetSize();

            if (processSize <= partitionSize && !currentPartition.IsInUse())
            {
                currentProcess.SetAssignedPartitionID(currentPartition.GetID());
                currentPartition.SetAssignedProcessID(currentProcess.GetID());

                lastIndex = j;
                totalWaste += partitionSize - processSize;

                break;
            }
            else
            {
                if (checkedPartitionCount == partitionCount)
                {
                    checkedPartitionCount = 0;
                    break;
                }

                if (lastIndex == partitionCount)
                {
                    lastIndex = 0;
                }
            }
        }
    }

    return totalWaste;
}

int WorstFit()
{
}
