#include<stdio.h>

#define MAX 10
int main()
{
    int cost[MAX][MAX], via[MAX][MAX], dist[MAX][MAX];

    printf("Enter the number of routes:");
    int n,i,j,k;
    scanf("%d",&n);

    printf("Enter the cost matrix\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
            via[i][j]  = j; 
        }
    }

    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(dist[i][k]+dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    via[i][j]  = via[i][k];
                }
            }
        }
    }

    for(i=0;i<n;i++)
    {
        printf("The distance for the vector %d\n", i);
        printf("Distance\tNext_Hop\tCost\n");
        for(j=0;j<n;j++)
        {
            if(i!=j)
            printf("%d\t\t%d\t\t%d\n", j,via[i][j],dist[i][j]);
        }
    }
}