#include <iostream>
#include <string>
#include <vector>

#include "Process.h"
#include "Partition.h"

// Algorithms
void Initialize();
void BestFit();
void FirstFit();
void NextFit();
void WorstFit();

// Display helpers
void DisplayTitle(const std::string&);
void DisplayWaitingProcess(const Process&);
void DisplayRunningProcess(const Process&, int);
void DisplaySummary(int);

void ResetData();

std::vector<int> processInputDataVector;
std::vector<int> partitionInputDataVector;
std::vector<Process> processVector;
std::vector<Partition> partitionVector;

int processCount = 0;
int partitionCount = 0;

int main()
{
    Initialize();
    BestFit();

    ResetData();
    FirstFit();

    ResetData();
    NextFit();

    ResetData();
    WorstFit();

    std::cin.ignore();
    std::cin.get();

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

        processInputDataVector.push_back(size);
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

        partitionInputDataVector.push_back(size);
        partitionVector.emplace_back(size);
    }
}

void BestFit()
{
    DisplayTitle("Best Fit");

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
            DisplayWaitingProcess(currentProcess);

            continue;
        }

        Partition& lowestWastePartition = partitionVector.at(lowestWastePartitionIndex);

        currentProcess.SetAssignedPartitionID(lowestWastePartition.GetID());
        lowestWastePartition.SetAssignedProcessID(currentProcess.GetID());

        totalWaste += lowestWaste;

        DisplayRunningProcess(currentProcess, lowestWaste);

        lowestWaste = 0xFFFFFF;
        lowestWastePartitionIndex = -1;
    }

    DisplaySummary(totalWaste);
}

void FirstFit()
{
    DisplayTitle("First Fit");

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

                int currentWaste = partitionSize - processSize;
                totalWaste += currentWaste;

                DisplayRunningProcess(currentProcess, currentWaste);

                break;
            }
        }

        if (currentProcess.IsWaiting())
        {
            DisplayWaitingProcess(currentProcess);
        }
    }

    DisplaySummary(totalWaste);
}

void NextFit()
{
    DisplayTitle("Next Fit");

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
                int currentWaste = partitionSize - processSize;
                totalWaste += currentWaste;

                DisplayRunningProcess(currentProcess, currentWaste);

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

        if (currentProcess.IsWaiting())
        {
            DisplayWaitingProcess(currentProcess);
        }
    }

    DisplaySummary(totalWaste);
}

void WorstFit()
{
    DisplayTitle("Worst Fit");

    int totalWaste = 0;
    int highestWaste = -1;
    int highestWastePartitionIndex = -1;

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

                if (highestWaste < currentWaste)
                {
                    highestWaste = currentWaste;
                    highestWastePartitionIndex = j;
                }
            }
        }

        if (highestWastePartitionIndex == -1)
        {
            DisplayWaitingProcess(currentProcess);

            continue;
        }

        Partition& highestWastePartition = partitionVector.at(highestWastePartitionIndex);

        currentProcess.SetAssignedPartitionID(highestWastePartition.GetID());
        highestWastePartition.SetAssignedProcessID(currentProcess.GetID());

        // Create sub partition from the highest waste partition
        partitionVector.emplace_back(highestWaste, &partitionVector.at(highestWastePartitionIndex));
        partitionCount++;

        totalWaste += currentProcess.GetSize() - partitionVector.at(highestWastePartitionIndex).GetSize();

        DisplayRunningProcess(currentProcess, highestWaste);

        highestWaste = -1;
        highestWastePartitionIndex = -1;
    }

    DisplaySummary(totalWaste);
}

void DisplayTitle(const std::string& titleName)
{
    std::cout << "\n----------------------------------------------------------------\n ";
    std::cout << "\t\t\t" << titleName << "\n\n";
    std::cout << "Process ID\tPartition ID\tWaste\t\tStatus\n";
}

void DisplayWaitingProcess(const Process& process)
{
    std::cout << process.GetID() << "\t\t" << "-" << "\t\t-\t\t" << "Waiting\n";
}

void DisplayRunningProcess(const Process& process, int waste)
{
    Partition& processesPartition = partitionVector.at(process.GetAssignedPartitionID() - 1);

    if (!processesPartition.IsSubPartition())
    {
        std::cout << process.GetID() << "\t\t" << process.GetAssignedPartitionID() << "\t\t" << waste << "\t\t" << "Running\n";
    }
    else
    {
        std::cout << process.GetID() << "\t\t" << processesPartition.GetSubPartition()->GetID() << "-" << processesPartition.GetSubID() << "\t\t" << waste << "\t\t" << "Running\n";
    }
}

void DisplaySummary(int totalWaste)
{
    std::cout << "\nTotal Waste: " << totalWaste << "\n";
    std::cout << "----------------------------------------------------------------\n\n";
}

void ResetData()
{
    processVector.clear();
    partitionVector.clear();
    Process::ResetIDs();
    Partition::ResetIDs();

    for (int i = 0; i < processCount; i++)
    {
        processVector.emplace_back(processInputDataVector.at(i));
    }

    for (int i = 0; i < partitionCount; i++)
    {
        partitionVector.emplace_back(partitionInputDataVector.at(i));
    }
}
