#include <stdio.h>

#define INFINITY 999
#define MAX 10

int main() {
    int cost[MAX][MAX], dist[MAX][MAX], via[MAX][MAX];
    int n;

    printf("Enter number of routers: ");
    scanf("%d", &n);

    printf("Enter cost matrix (999 for infinity):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
            via[i][j] = j;
        }

    // Distance vector algorithm
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    via[i][j] = via[i][k];
                }

    // Print routing table
    for (int i = 0; i < n; i++) {
        printf("\nRouting table for router %d:\n", i);
        printf("Destination\tNext Hop\tCost\n");
        for (int j = 0; j < n; j++)
            if (i != j)
                printf("%d\t\t%d\t\t%d\n", j, via[i][j], dist[i][j]);
    }

    return 0;
}
