#include<bits/stdc++.h>
using namespace std;

class Minheap{
    public:
    int *harr;
    int capacity;
    int heap_size;

    Minheap(int cap){
        heap_size = 0;
        capacity = cap;
        harr = new int[cap];

    }

    int parent( int i ){
        return (i-1)/2;
    }

    int left(int i){
        return 2*i + 1;
    }
 
    int right(int i){
        return 2*i + 2;
    }

    void insert(int k){
        if (heap_size == capacity)
        {
            cout<<"Heap Overflow";
        }
        heap_size++;
        int i = heap_size-1;
        harr[i] = k;       
        while (i != 0 && harr[parent(i)]>harr[i])
        {
            swap(harr[i],harr[parent(i)]);
            i = parent(i);
        }
         
    }

    void insertArray(int arr[], int n){
        for (int i = 0; i < n; i++)
        {
            insert(arr[i]);
        }
   }

    void heapify(int i){
        int smallest = i;
        int l = left(i);
        int r = right(i);
 
        if (l < heap_size && harr[l] < harr[smallest])
            smallest = l;
        if (r < heap_size && harr[r] < harr[smallest])
            smallest = r;
 
        if (smallest != i)
        {
            swap(harr[i], harr[smallest]);
            heapify(smallest);
        }
    }

    int extractMin(){
        if (heap_size <= 0)
        {
            cout<<"Heap Underflow\n";
            return -1;
        }
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }
 
        int root = harr[0];
        harr[0] = harr[heap_size-1];
        heap_size--;
        heapify(0);
        return root;
    }

    void display(){
        if (heap_size == 0)
        {
            cout<<"Heap is empty\n";
            return;
        }
        cout<<"Heap elements: ";
        for (int i = 0; i < heap_size; i++)
        {
            cout<<harr[i]<<" ";
        }
        cout<<endl;
    }

    int kthSmallest(int k){
    if (k <= 0 || k > heap_size)
    {
        cout<<"Invalid k\n";
        return -1;
    }

    int result = -1;
    for (int i = 0; i < k; i++)
    {
        result = extractMin();   
    }
    return result;
}

};

int main(){
    int arr1[] = {12, 2, 30, 8, 5};
    int arr2[] = {20, 1, 25, 9, 4, 15};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    int n2 = sizeof(arr2)/sizeof(arr2[0]);

     Minheap obj(n1 + n2);   
    obj.insertArray(arr1, n1);
    obj.insertArray(arr2, n2);

    cout<<"Heap created from both arrays\n";
    obj.display();

    int k;
    cout<<"Enter k: ";
    cin>>k;
    cout<<"K-th smallest: "<<obj.kthSmallest(k)<<endl;

    return 0;
}

   
