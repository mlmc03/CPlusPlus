#include "lpclib.h"
using namespace std;

#define USE_ARRAY

#ifndef USE_ARRAY
template <typename T>
struct QueueNode
{
    T data;
    QueueNode<T> * next;
};
#else
#define CAPACITY 5
#endif

template <typename T>
class CS20Queue
{
    private:
#ifdef USE_ARRAY
        T array[CAPACITY];
        int head;
        int tail;
#else
        QueueNode<T> * top;
#endif

    public:
        CS20Queue();
        T Dequeue();
        void Enqueue(T item);
};

template <typename T>
CS20Queue<T>::CS20Queue()
{
#ifdef USE_ARRAY
    head = 0;
    tail = 0;
#else
    top = NULL;
#endif
}


template <typename T>
T CS20Queue<T>::Dequeue()
{
    T result;
#ifdef USE_ARRAY
    if (head == tail)
        Error("Dequeue attempt on an empty queue!");
    result = array[head];
    head = (head + 1) % CAPACITY;
#else

#endif
    return result;
}

template <typename T>
void CS20Queue<T>::Enqueue(T item)
{
#ifdef USE_ARRAY
    if ( (tail + 1)%CAPACITY == head)
        Error("Enqueue attempted on full queue!");
    array[tail] = item;
    tail = (tail + 1) % CAPACITY;
#else

#endif
}

int main()
{
    CS20Queue<string> line;
    line.Enqueue("A");
    line.Enqueue("B");
    line.Enqueue("C");
    line.Enqueue("D");
    cout << line.Dequeue() << " gets the first Hobbit ticket.n";
    cout << line.Dequeue() << " gets the next Hobbit ticket.n";
    line.Enqueue("E");
    line.Enqueue("F");
    //line.Enqueue("G");
    line.Dequeue();
    line.Dequeue();
    line.Dequeue();
    cout << "Last one is " << line.Dequeue() << endl;
    // line.Dequeue();

}



}
