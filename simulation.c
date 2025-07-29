// #include "simulation.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <unistd.h> // For sleep()

// // A helper function to simulate traffic density change (simple random variation)
// float simulateTrafficDensity(float currentDensity) {
//     // Randomly increase or decrease density by up to 10%
//     float change = ((rand() % 21) - 10) / 100.0; // -0.10 to +0.10
//     float newDensity = currentDensity + (currentDensity * change);
//     // Ensure density stays within reasonable bounds, e.g., 0 to 100
//     if (newDensity < 0) newDensity = 0;
//     if (newDensity > 100) newDensity = 100;
//     return newDensity;
// }

// // Update traffic on each edge based on simulated conditions
// void updateTraffic(Graph G) {
//     for (int i = 0; i < G->NumVertex; i++) {
//         Node temp = G->VertexList[i]->NextNode;
//         while (temp != NULL) {
//             // Update traffic density using our simulation function.
//             temp->traf_density = simulateTrafficDensity(temp->traf_density);
//             temp = temp->NextNode;
//         }
//     }
// }

// void setTrafficDensity(Graph G, int intersection, float newDensity) {
//     if (newDensity < 0) newDensity = 0;
//     if (newDensity > 100) newDensity = 100;

//     // Update the incoming traffic at the intersection
//     G->VertexList[intersection]->IncTraff = newDensity;
    
//     printf("Updated traffic density at Intersection %d to %.2f\n", intersection, newDensity);
// }


// // Adjust signal timings at each intersection based on incoming traffic
// // void adjustSignals(Graph G) {
// //     const int THRESHOLD = 50;  // Example threshold for incoming traffic
// //     const int BASE_GREEN = 30; // Base green time in seconds
// //     const int EXTRA_GREEN = 20; // Extra green time if heavy traffic

// //     for (int i = 0; i < G->NumVertex; i++) {
// //         int totalIncoming = G->VertexList[i]->IncTraff;
// //         // For simulation, assume totalIncoming is already updated by InsertEdge in real-time,
// //         // or you can calculate by summing traffic densities from incoming edges.
// //         if (totalIncoming > THRESHOLD) {
// //             G->VertexList[i]->currentGreenTime = BASE_GREEN + EXTRA_GREEN;
// //         } else {
// //             G->VertexList[i]->currentGreenTime = BASE_GREEN;
// //         }
// //         // Optionally update cycleLength if needed
// //         // G->VertexList[i]->cycleLength = ...;
// //     }
// // }
// // void adjustSignals(Graph G) {
// //     const int THRESHOLD = 50;  // Example threshold for incoming traffic
// //     const int BASE_GREEN = 30; // Base green time in seconds
// //     const int EXTRA_GREEN = 20; // Extra green time if heavy traffic

// //     for (int i = 0; i < G->NumVertex; i++) {
// //         int totalIncoming = G->VertexList[i]->IncTraff;  // Now uses manually updated value

// //         if (totalIncoming > THRESHOLD) {
// //             G->VertexList[i]->currentGreenTime = BASE_GREEN + EXTRA_GREEN;
// //         } else {
// //             G->VertexList[i]->currentGreenTime = BASE_GREEN;
// //         }
// //     }
// // }

// void adjustSignals(Graph G) {
//     const int THRESHOLD = 50;
//     const int BASE_GREEN = 30;
//     const int EXTRA_GREEN = 20;
//     const int BASE_CYCLE = 60; // Default cycle length
//     const int EXTRA_CYCLE = 10; // Extra cycle time for heavy traffic

//     for (int i = 0; i < G->NumVertex; i++) {
//         int totalIncoming = G->VertexList[i]->IncTraff;

//         if (totalIncoming > THRESHOLD) {
//             G->VertexList[i]->currentGreenTime = BASE_GREEN + EXTRA_GREEN;
//             G->VertexList[i]->cycleLength = BASE_CYCLE + EXTRA_CYCLE; // Adjust cycle length too
//         } else {
//             G->VertexList[i]->currentGreenTime = BASE_GREEN;
//             G->VertexList[i]->cycleLength = BASE_CYCLE;
//         }
//     }
// }



// // A simple simulation loop that runs for a given duration (in simulation steps)
// void simulationLoop(Graph G, int simulationDuration) {
//     int simulationTime = 0;
//     while (simulationTime < simulationDuration) {
//         printf("\n--- Simulation Time: %d ---\n", simulationTime);

//         // Ask user if they want to enter traffic density manually
//         char choice;
//         printf("Do you want to update traffic density manually? (y/n): ");
//         scanf(" %c", &choice);

//         if (choice == 'y' || choice == 'Y') {
//             int intersection;
//             float newDensity;
//             printf("Enter intersection (vertex ID): ");
//             scanf("%d", &intersection);
//             printf("Enter new traffic density (0-100): ");
//             scanf("%f", &newDensity);

//             // Ensure the vertex is valid and set the traffic density
//             if (intersection >= 0 && intersection < G->NumVertex) {
//                 setTrafficDensity(G, intersection, newDensity);
//             } else {
//                 printf("Invalid intersection!\n");
//             }
//         } else {
//             // Otherwise, continue normal simulation (random updates)
//             updateTraffic(G);
//         }

//         // Adjust signals at intersections based on current conditions
//         adjustSignals(G);

//         // Print current state for each vertex (signal timing)
//         for (int i = 0; i < G->NumVertex; i++) {
//             printf("Intersection %d: Green Time = %d sec, Cycle Length = %d sec\n", 
//                     G->VertexList[i]->VertexID, 
//                     G->VertexList[i]->currentGreenTime, 
//                     G->VertexList[i]->cycleLength);
//         }

//         simulationTime++;
//         sleep(1);  // Sleep for 1 second
//     }
// }


#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For sleep()

// Simulate traffic density changes (random fluctuations)
float simulateTrafficDensity(float currentDensity) {
    float change = ((rand() % 21) - 10) / 100.0; // -10% to +10%
    float newDensity = currentDensity + (currentDensity * change);
    if (newDensity < 0) newDensity = 0;
    if (newDensity > 100) newDensity = 100;
    return newDensity;
}

// float simulateTrafficDensity(float currentDensity) {
//     float change;
    
//     if (currentDensity < 30) {
//         // If density is below 30, increase it with 50% probability
//         change = ((rand() % 11) + 5) / 100.0; // +5% to +15%
//     } else {
//         // If density is above 30, decrease it with 50% probability
//         change = -((rand() % 11) + 5) / 100.0; // -5% to -15%
//     }

//     float newDensity = currentDensity + (currentDensity * change);

//     // Ensure the density remains within 0-100
//     if (newDensity < 0) newDensity = 0;
//     if (newDensity > 100) newDensity = 100;

//     return newDensity;
// }


// Function to update traffic dynamically
void updateTraffic(Graph G) {
    for (int i = 0; i < G->NumVertex; i++) {
        Node temp = G->VertexList[i]->NextNode;
        while (temp != NULL) {
            temp->traf_density = simulateTrafficDensity(temp->traf_density);
            temp = temp->NextNode;
        }
    }
}


// Manually set traffic density for a specific intersection
void setTrafficDensity(Graph G, int intersection, float newDensity) {
    if (newDensity < 0) newDensity = 0;
    if (newDensity > 100) newDensity = 100;
    G->VertexList[intersection]->IncTraff = newDensity;
    printf("Updated traffic density at Intersection %d to %.2f\n", intersection, newDensity);
}

// Function to adjust signals based on traffic density
void adjustSignals(Graph G) {
    const int THRESHOLD = 50;
    const int BASE_GREEN = 30;
    const int EXTRA_GREEN = 20;
    const int BASE_CYCLE = 60;
    const int EXTRA_CYCLE = 10;

    for (int i = 0; i < G->NumVertex; i++) {
        if (G->VertexList[i]->hasEmergency) {
            G->VertexList[i]->currentGreenTime = BASE_CYCLE;
            printf("🚨 Emergency at Intersection %d! Green Light for %d sec\n", i, BASE_CYCLE);
        } else {
            int totalIncoming = G->VertexList[i]->IncTraff;
            if (totalIncoming > THRESHOLD) {
                G->VertexList[i]->currentGreenTime = BASE_GREEN + EXTRA_GREEN;
                G->VertexList[i]->cycleLength = BASE_CYCLE + EXTRA_CYCLE;
            } else {
                G->VertexList[i]->currentGreenTime = BASE_GREEN;
                G->VertexList[i]->cycleLength = BASE_CYCLE;
            }
        }
    }
}

// Set emergency vehicle presence at an intersection
void setEmergencyVehicle(Graph G, int intersection, int status) {
    G->VertexList[intersection]->hasEmergency = status;
    if (status)
        printf("🚑 Emergency vehicle detected at Intersection %d! Prioritizing green signal.\n", intersection);
    else
        printf("🚦 Emergency cleared at Intersection %d. Resuming normal traffic control.\n", intersection);
}

// Simulation loop
void simulationLoop(Graph G, int simulationDuration) {
    int simulationTime = 0;
    srand(time(0));

    while (simulationTime < simulationDuration) {
        printf("\n--- Simulation Time: %d ---\n", simulationTime);

        // User input for traffic density
        char choice;
        printf("Do you want to update traffic density manually? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            int intersection;
            float newDensity;
            printf("Enter intersection (vertex ID): ");
            scanf("%d", &intersection);
            printf("Enter new traffic density (0-100): ");
            scanf("%f", &newDensity);
            if (intersection >= 0 && intersection < G->NumVertex) {
                setTrafficDensity(G, intersection, newDensity);
            } else {
                printf("Invalid intersection!\n");
            }
        } else {
            updateTraffic(G);
        }

        // User input for emergency vehicle
        char emergencyChoice;
        printf("Is there an emergency vehicle at any intersection? (y/n): ");
        scanf(" %c", &emergencyChoice);

        if (emergencyChoice == 'y' || emergencyChoice == 'Y') {
            int intersection;
            printf("Enter intersection (vertex ID) for emergency vehicle: ");
            scanf("%d", &intersection);
            if (intersection >= 0 && intersection < G->NumVertex) {
                setEmergencyVehicle(G, intersection, 1);
            } else {
                printf("Invalid intersection!\n");
            }
        } else {
            for (int i = 0; i < G->NumVertex; i++) {
                setEmergencyVehicle(G, i, 0);
            }
        }

        // Adjust signals based on updated traffic and emergency status
        adjustSignals(G);

        // Display current signal status
        for (int i = 0; i < G->NumVertex; i++) {
            printf("Intersection %d: Green Time = %d sec, Cycle Length = %d sec, Emergency: %s\n", 
                    G->VertexList[i]->VertexID, 
                    G->VertexList[i]->currentGreenTime, 
                    G->VertexList[i]->cycleLength,
                    G->VertexList[i]->hasEmergency ? "YES" : "NO");
        }

        simulationTime++;
        sleep(1);  // Sleep for 1 second before next simulation step
    }
}
