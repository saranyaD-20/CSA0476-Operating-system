#include <stdio.h>

#define MEMORY_SIZE 100
#define MAX_BLOCKS 10

int memory[MEMORY_SIZE];
int blockSizes[MAX_BLOCKS];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = -1; // Initialize memory with -1 to represent free space
    }
}

void displayMemory() {
    printf("Memory Status:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == -1) {
            printf("[ ]"); // Free space
        } else {
            printf("[%d]", memory[i]); // Allocated block
        }
    }
    printf("\n");
}

int bestFit(int size) {
    int index = -1;
    int bestFitSize = MEMORY_SIZE + 1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == -1) {
            int blockSize = 0;
            int j = i;
            while (j < MEMORY_SIZE && memory[j] == -1) {
                blockSize++;
                j++;
            }
            if (blockSize >= size && blockSize < bestFitSize) {
                bestFitSize = blockSize;
                index = i;
            }
            i = j; // Skip to the next block
        }
    }

    return index;
}

void allocateBlock(int index, int size, int processId) {
    for (int i = index; i < index + size; i++) {
        memory[i] = processId;
    }
}

int main() {
    initializeMemory();
    displayMemory();

    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of Process %d: ", i + 1);
        scanf("%d", &blockSizes[i]);
    }

    for (int i = 0; i < numProcesses; i++) {
        int index = bestFit(blockSizes[i]);
        if (index != -1) {
            allocateBlock(index, blockSizes[i], i + 1);
            printf("Allocated Process %d of size %d at position %d\n", i + 1, blockSizes[i], index);
        } else {
            printf("Unable to allocate Process %d of size %d\n", i + 1, blockSizes[i]);
        }
        displayMemory();
    }

    return 0;
}
