#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "monitor.h"
using namespace std;


Monitor M;

void* reader(void* id)
{
    int c = 0;
    int i = *(int*)id;

    // each reader attempts to read 5 times
    while (c < 3) {
        sleep(0.1);
        cout << i << " try start reading...\n";
        M.beginread();
        cout << i << " start reading\n";
        sleep(2);
        cout << i << " end reading\n";
        M.endread();
        cout << i << " finished reading...\n";
        c++;
    }
}

void* writer(void* id)
{
    int c = 0;
    int i = *(int*)id;

    // each writer attempts to write 5 times
    while (c < 3) {
        sleep(0.1);
        cout << i << " try start writing...\n";
        M.beginwrite();
        cout << i << " start writing\n";
        sleep(2);
        cout << i << " end writing\n";
        M.endwrite();
        cout << i << " finished writing...\n";
        c++;
    }
}

int main(int argc, char *argv[])
{
    pthread_t r[5], w[5];
    int id[5];
    for (int i = 0; i < 5; i++) {
        id[i] = i;

    //     // creating threads which execute reader function
        pthread_create(&r[i], NULL, &reader, &id[i]);

        // creating threads which execute writer function
        pthread_create(&w[i], NULL, &writer, &id[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(w[i], NULL);
    }
    cout << "working!\n";
}