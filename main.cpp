#include <iostream>
#include <vector>

#include "Process.h"
#include "Partition.h"

void Initialize();
void BestFit();
int FirstFit();
void NextFit();
void WorstFit();

std::vector<Process> processVector;
std::vector<Partition> partitionVector;

int processCount = 0;
int partitionCount = 0;

int main()
{
    Initialize();

    std::cout << "\nFirst Fit Waste: " << FirstFit() << "\n\n";

    for (const Partition& partition : partitionVector)
    {
        std::cout << "Partition " << partition.GetID() << ": Assigned Process ID: " << partition.GetAssignedProcessID() << "\n";
    }
    for (const Process& process : processVector)
    {
        std::cout << "Process " << process.GetID() << ": Assigned Partition ID: " << process.GetAssignedPartitionID() << "\n";
    }

    return 0;
}

void Initialize()
{
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

void BestFit()
{
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

            if (processSize <= partitionSize)
            {
                if (currentPartition.IsInUse())
                {
                    continue;
                }

                currentProcess.SetAssignedPartitionID(currentPartition.GetID());
                currentPartition.SetAssignedProcessID(currentProcess.GetID());

                totalWaste += partitionSize - processSize;

                break;
            }
        }
    }

    return totalWaste;
}

void NextFit()
{
}

void WorstFit()
{
}
