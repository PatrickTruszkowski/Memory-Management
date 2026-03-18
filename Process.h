class Process
{
private:
    static int lastProcessID;

    int ID;
    int size;
    int assignedPartitionID;

public:
    Process(int);

    static void ResetIDs();

    int GetID() const;
    bool IsWaiting() const;
    int GetSize() const;
    int GetAssignedPartitionID() const;
    void SetAssignedPartitionID(int);
};