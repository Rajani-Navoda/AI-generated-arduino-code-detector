#include <AceSorting.h>  // Include the AceSorting library

void printResults(const char* name, int dataSize, long randomTime, long alreadySortedTime, long reverseSortedTime) {
    Serial.print(name);
    Serial.print(" ");
    Serial.print(dataSize);
    Serial.print(" ");
    Serial.print(randomTime);
    Serial.print(" ");
    Serial.print(alreadySortedTime);
    Serial.print(" ");
    Serial.println(reverseSortedTime);
}

void measureSortingTime(void (*sortFunction)(int*, int), int* data, int size) {
    unsigned long startTime = millis();
    sortFunction(data, size);
    return millis() - startTime;
}

void setup() {
    Serial.begin(9600);
    delay(1000);  // Give time for Serial Monitor to open

    const int dataSize = 20;  // Adjust size as needed
    int randomData[dataSize];
    int sortedData[dataSize];
    int reverseSortedData[dataSize];

    // Fill randomData with random values
    for (int i = 0; i < dataSize; i++) {
        randomData[i] = random(100);
    }

    // Create already sorted and reverse sorted data
    for (int i = 0; i < dataSize; i++) {
        sortedData[i] = i;
        reverseSortedData[i] = dataSize - i - 1;
    }

    // Measure sorting times for bubbleSort as an example
    Serial.println("Sorting algorithm benchmark results (ms):");
    Serial.println("Algorithm DataSize Random AlreadySorted ReverseSorted");

    // Measure bubbleSort
    Serial.println("bubbleSort");
    printResults("bubbleSort", dataSize,
                 measureSortingTime(bubbleSort, randomData, dataSize),
                 measureSortingTime(bubbleSort, sortedData, dataSize),
                 measureSortingTime(bubbleSort, reverseSortedData, dataSize));

    // Repeat for other sorting algorithms as needed...
}

void loop() {
    // Do nothing
}
