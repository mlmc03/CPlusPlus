#include "lpclib.h"
#include "hgraphics.h"
#include "vector.h"
#include <ctime>
using namespace std;

void Swap(int & a, int & b);
void Setup(Vector<int> & v, int N, bool preSort=false);
void SelectionSort(Vector<int> & v);
bool LinearSearch(Vector<int> & v, int target, bool isSorted);
bool BinarySearch(Vector<int> & v, int target);
void Print(Vector<int> & v);

int main()
{
    Vector<int> nums;
    nums.add(3);
    nums.add(5);
    nums.add(2);
    nums.add(7);
    nums.add(1);
    nums.add(6);
    nums.add(9);
    SelectionSort(nums);
    Print(nums);
    while (1)
    {
        cout << "target = ";
        int what = GetInt();
        if (BinarySearch(nums, what))
            cout << "Found it.n";
        else
            cout << "Not found.n";
    }
}

bool BinarySearch(Vector<int> & v, int target)
{
    int begin = 0;
    int end = v.size() - 1;

    while (begin <= end)
    {
        int middle = (begin + end) / 2;
        if (v[middle] == target)
            return true;
        else if (target < v[middle])
        {
            end = middle - 1;
        }
        else if (target > v[middle])
        {
            begin = middle + 1;
        }
    }
    return false;
}

bool LinearSearch(Vector<int> & v, int target, bool isSorted)
{
    foreach (int item in v)
    {
        if (isSorted && item > target)
        {
            cout << "stopped after seeing " << item << endl;
            return false;
        }
        if (item == target)
            return true;
    }
    return false;
}

void Setup(Vector<int> & v, int N, bool preSort)
{
    for (int i = 0; i < N; i++)
        v.add(RandomInt(1, N));
    if (preSort)
    {
        SelectionSort(v);
    }
}

void Swap(int & a, int & b)
{
    int originalA = a;
    a = b; /// I have a copy of the original a, so this is fine.
    b = originalA;
}

void Print(Vector<int> & v)
{
    foreach (int x in v)
    {
        cout << x << " ";
    }
    cout << endl;
}

void SelectionSort(Vector<int> & v)
{
    int numItemsSorted = 0;
    while (numItemsSorted < v.size() - 1) /// N-1 compares
    {
        int minValue = v[numItemsSorted];
        int minIndex = numItemsSorted;
        for (int i = numItemsSorted + 1; i < v.size(); i++) /// (N^2+N)/2 - 1
        {
            if (v[i] < minValue)   /// (N^2+N)/2 - 2
            {
                minValue = v[i];
                minIndex = i;
            }
        }
        Swap(v[minIndex], v[numItemsSorted]); /// N-2
        numItemsSorted++;
    }

}



}
