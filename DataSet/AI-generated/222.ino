#include <AceSorting.h>  // Include the AceSorting library

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        Serial.print(arr[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void setup() {
    Serial.begin(9600);
    delay(1000);  // Give time for Serial Monitor to open

    // Unsorted array
    int arr[] = {234, 19, 95, 219, 255, 132, 27, 194, 83, 96, 245, 161, 228, 205, 193, 215, 101, 216, 120, 95};
    const int size = sizeof(arr) / sizeof(arr[0]);

    // Print unsorted array
    Serial.print("Unsorted: ");
    printArray(arr, size);

    // Sort using implicit ascending
    shellSortKnuth(arr, size);
    Serial.print("Sorted using implicit ascending: ");
    printArray(arr, size);

    // Sort using function pointer for ascending order
    shellSortKnuth(arr, size, [](const int &a, const int &b) {
        return a < b;
    });
    Serial.print("Sorted using function pointer: ");
    printArray(arr, size);

    // Sort using lambda expression for ascending order
    shellSortKnuth(arr, size, [](const int &a, const int &b) {
        return a < b;
    });
    Serial.print("Sorted using lambda expression: ");
    printArray(arr, size);

    // Sort using lambda expression for descending order
    shellSortKnuth(arr, size, [](const int &a, const int &b) {
        return a > b;
    });
    Serial.print("Reverse sorted using lambda expression: ");
    printArray(arr, size);
}

void loop() {
    // Do nothing
}
