#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_LOCATIONS 10
int numLocations;
int numVehicles;
int capacity[MAX_LOCATIONS];
int graph[MAX_LOCATIONS][MAX_LOCATIONS];
char locationNames[MAX_LOCATIONS][50];
int vehicleCapacities[MAX_LOCATIONS];
int optimalRoute[MAX_LOCATIONS];
int minCost = INT_MAX;
bool visited[MAX_LOCATIONS];
void initialize() {
 for (int i = 0; i < MAX_LOCATIONS; i++) {
 visited[i] = false;
 optimalRoute[i] = -1;
 capacity[i] = 0;
 vehicleCapacities[i] = 0;
 for (int j = 0; j < MAX_LOCATIONS; j++) {
 graph[i][j] = 0;
 }
 locationNames[i][0] = '\0';
 }
}
void inputLocations() {
 printf("Enter the number of delivery locations (max %d): ", MAX_LOCATIONS);
 scanf("%d", &numLocations);
 if (numLocations > MAX_LOCATIONS || numLocations <= 0) {
printf("Invalid number of delivery locations. Please enter a number between 1 and %d.\n", MAX_LOCATIONS);
exit(1);
 }
 printf("Enter the number of vehicles: ");
 scanf("%d", &numVehicles);
 printf("Enter vehicle capacities:\n");
 for (int i = 0; i < numVehicles; i++) {
     printf("Vehicle %d capacity: ", i + 1);
 scanf("%d", &vehicleCapacities[i]);
 }
 printf("Enter location names:\n");
 for (int i = 0; i < numLocations; i++) {
 printf("Location %d: ", i + 1);
 scanf("%s", locationNames[i]);
 }
 //printf("Enter location capacities:\n");
 //for (int i = 0; i < numLocations; i++) {
 // printf("Capacity of location %s: ", locationNames[i]);
 //scanf("%d", &capacity[i]);
 //}
 printf("Enter the distance matrix (0 for no connection):\n");
 for (int i = 0; i < numLocations; i++) {
 for (int j = 0; j < numLocations; j++) {
 scanf("%d", &graph[i][j]);
 }
 }
}
int min(int a, int b) {
 return (a < b) ? a : b;
}
void tsp(int current, int count, int cost) {
 visited[current] = true;
 optimalRoute[count - 1] = current;
 if (count == numLocations) {
 if (graph[current][0] != 0) {
 cost += graph[current][0];
 if (cost < minCost) {
 minCost = cost;
 }
 }
 } else {
 for (int i = 0; i < numLocations; i++) {
 if (!visited[i] && graph[current][i] != 0) {
 tsp(i, count + 1, cost + graph[current][i]);
 }
 }
 }
 visited[current] = false;
}
void printOptimalRoute() {
 printf("Optimal Route for Multiple Vehicles:\n");
 int totalMinCost = 0; // Initialize the total minimum cost
 for (int v = 0; v < numVehicles; v++) {
 printf("Vehicle %d Route: %s", v + 1, locationNames[optimalRoute[0]]);
 int totalCapacity = capacity[optimalRoute[0]];
 int totalCost = 0;
 for (int i = 1; i < numLocations; i++) {
 int location = optimalRoute[i];
 if (totalCapacity + capacity[location] > vehicleCapacities[v]) {
 // Switch to the next vehicle if capacity is exceeded
 printf(" -> %s", locationNames[optimalRoute[i - 1]]);
 totalCost += graph[optimalRoute[i - 1]][optimalRoute[i - 2]];
 totalCapacity = capacity[location];
 }
 totalCapacity += capacity[location];
 printf(" -> %s", locationNames[location]);
 totalCost += graph[optimalRoute[i - 1]][optimalRoute[i]];
 }
 // Print the total distance for the current vehicle
 printf(" -> %s (Total distance: %d)\n", locationNames[optimalRoute[0]], totalCost);
 // Add the total cost of the current vehicle route to the total minimum cost
 totalMinCost += totalCost;
 }
 // Print the minimum distance traveled when all vehicles are used
 printf("Minimum distance when all vehicles are used: %d\n", totalMinCost);
}
int main() {
 initialize();
 inputLocations();
 tsp(0, 1, 0);
 if (minCost == INT_MAX) {
 printf("No Hamiltonian cycle exists.\n");
 } else {
 printOptimalRoute();
 }
 return 0;
}