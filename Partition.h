class Partition
{
private:
    static int lastPartitionID;

    int ID;
    int size;
    int assignedProcessID;

public:
    Partition(int);

    static void ResetIDs();

    int GetID() const;
    bool IsInUse() const;
    int GetSize() const;
    int GetAssignedProcessID() const;
    void SetAssignedProcessID(int);
};