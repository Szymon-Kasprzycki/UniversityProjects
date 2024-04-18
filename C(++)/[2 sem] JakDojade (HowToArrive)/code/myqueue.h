#ifndef TEST_MYQUEUE_H
#define TEST_MYQUEUE_H

class MyQueue {
private:
    struct Node {
        int val;
        Node *next;
    };
    Node *front;
    Node *rear;
public:
    explicit MyQueue();

    ~MyQueue();

    void enqueue(int data);

    int dequeue();

    bool isEmpty() const;

    void clear();
};


#endif //TEST_MYQUEUE_H
