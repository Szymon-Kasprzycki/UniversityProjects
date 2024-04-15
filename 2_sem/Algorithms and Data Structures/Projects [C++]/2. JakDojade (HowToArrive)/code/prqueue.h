#ifndef TEST_PRQUEUE_H
#define TEST_PRQUEUE_H


class PrQNode {
public:
    int value;
    int priority;
    PrQNode *next;
};

class PrQueue {
private:
    PrQNode *head;
public:
    PrQueue();

    ~PrQueue();

    void insert(int value, int priority);

    int pop();

    bool isEmpty() const;
};


#endif //TEST_PRQUEUE_H
