#include <iostream>
#include <string>

using namespace std;

// Implementation of Heap Sort algorithm for strings
// Time complexity: O(n*log(n))
// Space complexity: O(1)

// function to compare numbers
bool isGreater(const string& a, const string& b) {
    if (a.length() > b.length() or (a.length() == b.length() and a > b))
        return true;
    else
        return false;
}

// Heapify subtree rooted at index i in arr[]
void heapify(string arr[], int n, int i) {
    int largest = i;  // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2;  // Right child

    // If left child is larger than root
    if (left < n && isGreater(arr[left], arr[largest]))
        largest = left;

    // If right child is larger than largest so far
    if (right < n && isGreater(arr[right], arr[largest]))
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Heap Sort function
void heapSort(string arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    cin >> n;

    auto *arr = new string[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    heapSort(arr, n);

    for (int i = 0; i < n; i++)
        cout << arr[i] << endl;

    delete[] arr;
    return 0;
}