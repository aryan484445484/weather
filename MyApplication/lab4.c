#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resources;

bool is_safe_state() {
    bool finished[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    int safe_sequence[MAX_PROCESSES];
    int count = 0;

    // Initialize finished array
    for (int i = 0; i < num_processes; ++i)
        finished[i] = false;

    // Initialize work array
    for (int i = 0; i < num_resources; ++i)
        work[i] = available[i];

    // Find a process that can be executed safely
    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; ++i) {
            if (!finished[i]) {
                int j;
                for (j = 0; j < num_resources; ++j)
                    if (need[i][j] > work[j])
                        break;
                if (j == num_resources) {
                    // Process can be executed safely
                    for (int k = 0; k < num_resources; ++k)
                        work[k] += allocation[i][k];
                    safe_sequence[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false; // No process found, not in a safe state
    }

    // Print safe sequence
    printf("Safe Sequence: ");
    for (int i = 0; i < num_processes; ++i)
        printf("%d ", safe_sequence[i]);
    printf("\n");

    return true; // All processes executed safely, in a safe state
}

bool request_resources(int process_id, int request[]) {
    // Check if the request exceeds the need
    for (int i = 0; i < num_resources; ++i) {
        if (request[i] > need[process_id][i])
            return false;
    }

    // Check if the request exceeds the available resources
    for (int i = 0; i < num_resources; ++i) {
        if (request[i] > available[i])
            return false;
    }

    // Attempt to allocate the resources
    for (int i = 0; i < num_resources; ++i) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    // Check if the system is still in a safe state
    if (!is_safe_state()) {
        // Rollback the allocation if the system is not in a safe state
        for (int i = 0; i < num_resources; ++i) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        return false;
    }

    return true; // Resources allocated successfully
}

int main() {
    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    // Input available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < num_resources; ++i)
        scanf("%d", &available[i]);

    // Input maximum resources needed for each process
    printf("Enter maximum resources needed for each process:\n");
    for (int i = 0; i < num_processes; ++i) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; ++j)
            scanf("%d", &max[i][j]);
    }

    // Input resources allocated to each process
    printf("Enter resources allocated to each process:\n");
    for (int i = 0; i < num_processes; ++i) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; ++j)
            scanf("%d", &allocation[i][j]);
    }

    // Calculate need matrix
    for (int i = 0; i < num_processes; ++i) {
        for (int j = 0; j < num_resources; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Check if the initial state is safe
    if (is_safe_state())
        printf("Initial state is safe.\n");
    else {
        printf("Initial state is not safe.\n");
        return 1;
    }

    // Process resource requests
    int process_id;
    int request[MAX_RESOURCES];
    while (true) {
        printf("Enter process id (or -1 to exit): ");
        scanf("%d", &process_id);
        if (process_id == -1)
            break;

        printf("Enter resource request for process %d: ", process_id);
        for (int i = 0; i < num_resources; ++i)
            scanf("%d", &request[i]);

        if (request_resources(process_id, request))
            printf("Resources allocated successfully.\n");
        else
            printf("Resources allocation failed. Request cannot be granted.\n");
    }

    return 0;
}
