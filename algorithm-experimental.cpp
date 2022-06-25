#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <chrono>
#include <fstream>

#define N 1000000

using namespace std;

double elapsed_time_ns;

//prints array
void cout_sample(long int *a, int n)
{
    cout<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

//populates array with rand integers
void generate_sample(long int *a, int n, int max_unit)
{
    for(int i=0; i<n; i++)
    {
        a[i] = rand()%max_unit;
    }

    //cout_sample(a,n);
}

//populates array with reversed list of consecutive integers
void generate_simple_sample(long int *a, int n)
{
    for(int i=0; i<n; i++)
    {
        a[i] = n-i;
    }

    //cout_sample(a,n);
}

void duplicate_sample(long int *a, long int *b, int n)
{
    for(int i=0; i<n; i++)
    {
        b[i]=a[i];
    }
}

void insertion_sort(long int *a, int n) {

   //start stop watch
   auto start_time = chrono::steady_clock::now();

   int key, j;
   for(int i = 1; i<n; i++) {
      key = a[i];//take value
      j = i;
      while(j > 0 && a[j-1]>key) {
         a[j] = a[j-1];
         j--;
      }
      a[j] = key;   //insert in right place
   }

   //end stop watch
   auto end_time = chrono::steady_clock::now();

   elapsed_time_ns = double(chrono::duration_cast <chrono::nanoseconds> (end_time - start_time).count());

   cout<< "Insertion sort: "<<elapsed_time_ns/1e9<<" seconds; Sample size: "<<n<<endl;

   //cout_sample(a,n);
}


// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(long int *arr, int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = arr[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(long int *arr, int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

void mergeMain(long int *arr, int n, int const begin, int const end)
{
    //start stop watch
    auto start_time = chrono::steady_clock::now();

    mergeSort(arr, begin, end);

    //end stop watch
    auto end_time = chrono::steady_clock::now();

    elapsed_time_ns = double(chrono::duration_cast <chrono::nanoseconds> (end_time - start_time).count());

    cout<< "Merge sort: "<<elapsed_time_ns/1e9<<" seconds; Sample size: "<<n<<endl;
}


// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(long int *arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(long int *arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void heapMain(long int *arr, int n)
{
    //start stop watch
    auto start_time = chrono::steady_clock::now();

    heapSort(arr, n);

    //end stop watch
    auto end_time = chrono::steady_clock::now();

    elapsed_time_ns = double(chrono::duration_cast <chrono::nanoseconds> (end_time - start_time).count());

    cout<< "Heap sort: "<<elapsed_time_ns/1e9<<" seconds; Sample size: "<<n<<endl;
}


// A utility function to swap two elements
void swap(long int* a, long int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* function that consider last element as pivot,
place the pivot at its exact position, and place
smaller elements to left of pivot and greater
elements to right of pivot.  */
int partition (long int *a, int start, int end)
{
    int pivot = a[end]; // pivot element
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
        // If current element is smaller than the pivot
        if (a[j] < pivot)
        {
            i++; // increment index of smaller element
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    int t = a[i+1];
    a[i+1] = a[end];
    a[end] = t;
    return (i + 1);
}

/* function to implement quick sort */
void quick(long int *a, int start, int end) /* a[] = array to be sorted, start = Starting index, end = Ending index */
{
    if (start < end)
    {
        int p = partition(a, start, end);  //p is the partitioning index
        quick(a, start, p - 1);
        quick(a, p + 1, end);
    }
}

void quickMain(long int *arr, int n, int low, int high)
{

    //start stop watch
    auto start_time = chrono::steady_clock::now();

    quick(arr, low, high);

    //end stop watch
    auto end_time = chrono::steady_clock::now();

    elapsed_time_ns = double(chrono::duration_cast <chrono::nanoseconds> (end_time - start_time).count());

    cout<< "Quick sort: "<<elapsed_time_ns/1e9<<" seconds; Sample size: "<<n<<endl;

}



// A utility function to get maximum value in arr[]
int getMax(long int *arr, int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(long int *arr, int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(long int *arr, int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}


void radixMain(long int *arr, int n)
{
    //start stop watch
    auto start_time = chrono::steady_clock::now();

    radixsort(arr, n);

    //end stop watch
    auto end_time = chrono::steady_clock::now();

    elapsed_time_ns = double(chrono::duration_cast <chrono::nanoseconds> (end_time - start_time).count());

    cout<< "Radix sort: "<<elapsed_time_ns/1e9<<" seconds; Sample size: "<<n<<endl;
}



// A function to implement bubble sort
void bubbleSort(long int *arr, int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

void bubbleMain(long int *arr, int n)
{
    //start stop watch
    auto start_time = chrono::steady_clock::now();

    bubbleSort(arr, n);

    //end stop watch
    auto end_time = chrono::steady_clock::now();

    elapsed_time_ns = double(chrono::duration_cast <chrono::nanoseconds> (end_time - start_time).count());

    cout<< "Bubble sort: "<<elapsed_time_ns/1e9<<" seconds; Sample size: "<<n<<endl;
}

void one_sample()
{
    //size of sample, user-input
    int n;
    cout<<"How many numbers you want to have in a sample: ";
    cin>>n;

    //size of sample unit, user-input
    int max_unit;
    cout<<"Sample numbers from 0 to ";
    cin>>max_unit;
    //max_unit=pow(10,max_unit);

    //dynamic allocation of array
    long int *a;
    a = (long int*) malloc(N*sizeof(long int));

    //duplicate array for local manipulation of array
    long int *arr;
    arr = (long int*) malloc(N*sizeof(long int));

    double total_time=0;

    //generate sample
    // make sure the same sample is used on all algorithms, foolish to compare results of 2 algorithms each using its own sample

    int q1;
    cout<<"Type 1 to generate a sample of reversed list of consecutive integers or 0 to generate random sample: ";
    cin>>q1;
    if(q1==0) {
        generate_sample(a,n,max_unit);
    }
    if(q1==1) {
        generate_simple_sample(a,n);
    }

    int q2;
    cout<<"Type 1 to print the sample or 0 to skip: ";
    cin>>q2;
    if(q2==1) {
        cout_sample(a,n);
    }

    cout<<endl<<"Testing sorting algorithms..."<<endl;

    //Radix

    duplicate_sample(a,arr,n);

    radixMain(arr, n);

    total_time+=elapsed_time_ns;

    //cout_sample(arr,n);

    //Quick sort

    duplicate_sample(a,arr,n);

    quickMain(arr, n, 0, n - 1);

    total_time+=elapsed_time_ns;

    //cout_sample(arr,n);

    //Heap sort

    duplicate_sample(a,arr,n);

    heapMain(arr, n);

    total_time+=elapsed_time_ns;

    //cout_sample(arr,n);

    //Merge sort

    duplicate_sample(a,arr,n);

    mergeMain(arr, n, 0, n-1);

    total_time+=elapsed_time_ns;

    //cout_sample(arr,n);

    //Insertion sort

    duplicate_sample(a,arr,n);

    insertion_sort(arr,n);

    total_time+=elapsed_time_ns;

    //cout_sample(arr,n);

    //Bubble sort

    duplicate_sample(a,arr,n);

    bubbleMain(arr,n);

    total_time+=elapsed_time_ns;

    cout<<"Total time: "<<total_time/1e9<<" seconds";

    //cout result: time elapsed, memory used, size of bits for variables in array, size of array

    //cout_sample(arr,n);
}

void matrix_sample()
{
    //int n_arr[] = {1000,2500,5000,7500,
    //               10000,25000,50000,75000,
    //               100000,250000,500000,750000,
    //               1000000};

    long long int n_arr[] = {1000,2500,5000,7500,
                   10000,25000,50000,75000,
                   100000,250000};

    int n_arr_size = 10;

    for(int i = 0; i<n_arr_size; i++)
        cout<<n_arr[i];

    long long int max_unit_arr[] = {1,10,100,1000,10000,100000};
    //int max_unit_arr[] = {10,100,1000,10000};

    int max_unit_arr_size = 6;
    cout<<"hey"<<max_unit_arr<<endl;

    int time_matrix[n_arr_size][6];
    for(int i = 0; i<n_arr_size; i++)
        for(int j = 0; j<6; j++)
            time_matrix[i][j]=0;



    //dynamic allocation of array
    long int *a;
    a = (long int*) malloc(N*sizeof(long int));

    //duplicate array for local manipulation of array
    long int *arr;
    arr = (long int*) malloc(N*sizeof(long int));


    int n,max_unit;
    for(int i = 0; i<n_arr_size; i++)
    {
        for(int j = 0; j<max_unit_arr_size; j++)
        {
            n = n_arr[i];
            max_unit = max_unit_arr[j];

            generate_sample(a,n,max_unit);

            //Bubble
            duplicate_sample(a,arr,n);

            bubbleMain(arr,n);

            time_matrix[i][0]+=elapsed_time_ns;

            //cout_sample(arr,n);

            //Insertion
            duplicate_sample(a,arr,n);

            insertion_sort(arr,n);

            time_matrix[i][1]+=elapsed_time_ns;

            //cout_sample(arr,n);

            //Merge
            duplicate_sample(a,arr,n);

            mergeMain(arr, n, 0, n-1);

            time_matrix[i][2]+=elapsed_time_ns;

            //cout_sample(arr,n);

            //Heap
            duplicate_sample(a,arr,n);

            heapMain(arr, n);

            time_matrix[i][3]+=elapsed_time_ns;

            //cout_sample(arr,n);

            //Quick
            duplicate_sample(a,arr,n);

            quickMain(arr, n, 0, n - 1);

            time_matrix[i][4]+=elapsed_time_ns;

            //cout_sample(arr,n);

            //Radix
            duplicate_sample(a,arr,n);

            radixMain(arr, n);

            time_matrix[i][5]+=elapsed_time_ns;
        }
    }

    for(int i = 0; i<n_arr_size; i++)
        for(int j = 0; j<6; j++)
        {
            //time_matrix[i][j]/=max_unit_arr_size;
        }


    ofstream TimeMatrix("TimeMatrix.txt");
    for(int i = 0; i<n_arr_size; i++)
    {
        for(int j = 0; j<6; j++)
            TimeMatrix<<time_matrix[i][j]<<"    ";
        TimeMatrix<<endl;
    }
    TimeMatrix.close();

    return;
}

int main(){

    //used to delay time of exec in order to get dif random numbers for sample
    srand (time (NULL));

    int q;
    cout<<"Type 0 for one sample or 1 for multiple sampling: ";
    cin>>q;
    switch(q)
    {
        case 0: { one_sample(); break; }
        case 1: matrix_sample();
    }

    return 0;
}
