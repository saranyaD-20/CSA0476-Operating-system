#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Define the message structure
struct message {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;

    // Create a key for the message queue
    key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or get the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process (Receiver)
        struct message received_message;

        // Receive a message from the queue
        if (msgrcv(msgid, &received_message, sizeof(received_message.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Received message: %s\n", received_message.mtext);
    } else {
        // Parent process (Sender)
        struct message to_send;
        to_send.mtype = 1;

        // Prepare a message
        strcpy(to_send.mtext, "Hello from the sender!");

        // Send the message to the queue
        if (msgsnd(msgid, &to_send, sizeof(to_send.mtext), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Sent message: %s\n", to_send.mtext);

        // Wait for the child process to finish
        wait(NULL);

        // Remove the message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
