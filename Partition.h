class Partition
{
private:
    static int lastPartitionID;

    Partition* subPartition;
    int ID;
    int subID;
    int lastSubID;
    int size;
    int assignedProcessID;

public:
    Partition(int, Partition* = nullptr);

    static void ResetIDs();

    int GetID() const;
    bool IsInUse() const;
    bool IsSubPartition() const;
    int GetSize() const;
    int GetAssignedProcessID() const;
    void SetAssignedProcessID(int);
    void SetSubID(int);
    Partition* GetSubPartition();
    int GetSubID() const;
    void AddSubPartition(Partition&);
};