#include <AceSorting.h>  // Include the AceSorting library

void setup() {
    Serial.begin(9600);
    delay(1000);  // Give time for Serial Monitor to open

    // Measure the size of different sorting functions
    Serial.println("Size of sorting algorithms in AceSorting library:");

    Serial.print("Size of shellSortKnuth: ");
    Serial.println(sizeof(&shellSortKnuth)); // Size of the function pointer

    Serial.print("Size of bubbleSort: ");
    Serial.println(sizeof(&bubbleSort)); // Size of the function pointer

    Serial.print("Size of insertionSort: ");
    Serial.println(sizeof(&insertionSort)); // Size of the function pointer

    Serial.print("Size of selectionSort: ");
    Serial.println(sizeof(&selectionSort)); // Size of the function pointer

    Serial.print("Size of quickSort: ");
    Serial.println(sizeof(&quickSort)); // Size of the function pointer

    Serial.print("Size of mergeSort: ");
    Serial.println(sizeof(&mergeSort)); // Size of the function pointer

    Serial.print("Size of heapSort: ");
    Serial.println(sizeof(&heapSort)); // Size of the function pointer

    // Add more sorting functions as needed
}

void loop() {
    // Do nothing
}
