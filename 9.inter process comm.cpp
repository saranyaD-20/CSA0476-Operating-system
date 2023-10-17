#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, L"MySharedMemory");

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d)\n", GetLastError());
        return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 256);

    if (pBuf == NULL) {
        printf("Could not map view of file (%d)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Parent process (writer)
    if (fork() > 0) {
        printf("Parent process is writing data to shared memory...\n");
        sprintf((char*)pBuf, "Hello from the parent process!");

        // Wait for the child process to read and finish
        wait(NULL);
        printf("Parent process finished.\n");

        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
    }
    // Child process (reader)
    else {
        Sleep(2000); // Allow some time for the parent to write
        printf("Child process is reading data from shared memory...\n");
        printf("Data read from shared memory: %s\n", pBuf);
        printf("Child process finished.\n");

        UnmapViewOfFile(pBuf);
    }

    return 0;
}
