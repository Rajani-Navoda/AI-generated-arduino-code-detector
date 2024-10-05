#include <AceSorting.h>  // Include the AceSorting library

// Function prototypes for the sorting algorithms to be tested
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);

// Helper function to measure sorting time
void measureSort(void (*sortFunc)(int[], int), int arr[], int size) {
    unsigned long startTime = millis();
    sortFunc(arr, size);
    unsigned long elapsedTime = millis() - startTime;
    Serial.print("Sorting took: ");
    Serial.print(elapsedTime);
    Serial.println(" ms");
}

void setup() {
    Serial.begin(9600);
    delay(1000);  // Give time for Serial Monitor to open

    const int sampleSize = 100;  // Number of samples
    const int dataSize = 100;     // Size of data to sort

    // Array for storing sorting times
    unsigned long times[sampleSize];

    // Benchmarking Bubble Sort
    Serial.println("Benchmarking Bubble Sort...");
    for (int i = 0; i < sampleSize; i++) {
        int arr[dataSize];
        randomizeArray(arr, dataSize);
        unsigned long startTime = millis();
        bubbleSort(arr, dataSize);
        unsigned long elapsedTime = millis() - startTime;
        times[i] = elapsedTime;
    }
    printBenchmarkResults("Bubble Sort", times, sampleSize);

    // Benchmarking Insertion Sort
    Serial.println("Benchmarking Insertion Sort...");
    for (int i = 0; i < sampleSize; i++) {
        int arr[dataSize];
        randomizeArray(arr, dataSize);
        unsigned long startTime = millis();
        insertionSort(arr, dataSize);
        unsigned long elapsedTime = millis() - startTime;
        times[i] = elapsedTime;
    }
    printBenchmarkResults("Insertion Sort", times, sampleSize);

    // Benchmarking Selection Sort
    Serial.println("Benchmarking Selection Sort...");
    for (int i = 0; i < sampleSize; i++) {
        int arr[dataSize];
        randomizeArray(arr, dataSize);
        unsigned long startTime = millis();
        selectionSort(arr, dataSize);
        unsigned long elapsedTime = millis() - startTime;
        times[i] = elapsedTime;
    }
    printBenchmarkResults("Selection Sort", times, sampleSize);
}

void loop() {
    // Do nothing
}

void printBenchmarkResults(const char* name, unsigned long* times, int size) {
    unsigned long min = times[0];
    unsigned long max = times[0];
    unsigned long sum = 0;

    for (int i = 0; i < size; i++) {
        if (times[i] < min) min = times[i];
        if (times[i] > max) max = times[i];
        sum += times[i];
    }
    unsigned long avg = sum / size;

    Serial.print(name);
    Serial.print(" ");
    Serial.print(size);
    Serial.print(" ");
    Serial.print(min);
    Serial.print(" ");
    Serial.print(avg);
    Serial.print(" ");
    Serial.print(max);
    Serial.println();
}

void randomizeArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = random(0, 1000);  // Fill the array with random integers
    }
}

// Example sorting algorithms (implement these as needed)
void bubbleSort(int arr[], int n) {
    // Bubble sort implementation
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    // Insertion sort implementation
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    // Selection sort implementation
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap arr[minIndex] and arr[i]
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}
