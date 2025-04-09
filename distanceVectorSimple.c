#include<stdio.h>
int cost[10][10],distance[10][10],nextHop[10][10];
int nodes;
int main(){
    printf("Enter the number of routers: ");
    scanf("%d", &nodes);
    printf("Enter the cost matrix (enter 9999 for no direct link):\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &cost[i][j]);
            if (i == j) {
                cost[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            distance[i][j] = cost[i][j];
            nextHop[i][j] = j;
        }
    }
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                for (int k = 0; k < nodes; k++) {
                    if (distance[i][j] > distance[i][k] + distance[k][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                        nextHop[i][j] = nextHop[i][k];
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
    for (int i = 0; i < nodes; i++) {
        printf("\nRouter %d's Routing Table:\n", i + 1);
        printf("Destination\tCost\tNext Hop\n");
        for (int j = 0; j < nodes; j++) {
            printf("%d\t\t%d\t%d\n", j + 1, distance[i][j], nextHop[i][j] + 1);
        }
    }
}