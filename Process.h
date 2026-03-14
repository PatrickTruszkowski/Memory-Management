class Process
{
private:
    static int lastProcessID;

    int ID;
    int size;
    int assignedPartitionID;

public:
    Process(int);

    int GetID() const;
    bool IsWaiting() const;
    int GetSize() const;
    int GetAssignedPartitionID() const;
    void SetAssignedPartitionID(int);
};