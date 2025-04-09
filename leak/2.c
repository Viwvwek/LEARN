#include<stdio.h>
int main()
{
    printf("enter the bucket size:");
    int bsize;
    scanf("%d", &bsize);

    printf("enter th outflow rate:");
    int rate;
    scanf("%d", &rate);

    printf("Enter the number of incoming packets:");
    int n;
    scanf("%d",&n);

    int i,bucket = 0;
    for(i=0;i<n;i++)
    {
        printf("\nenter the size of packet at %d:",i+1);
        int __in;
        scanf("%d", &__in);

        if(__in <(bsize - bucket))
        {
            bucket = bucket + __in;
            printf("\nAdding packets: %d|%d\n", bucket,bsize);
        }
        else
        {
            printf("\nDropping packets %d\n", __in -(bsize - bucket));
            bucket = bsize;
        }
        if((bucket - rate )> 0)
        {
            bucket = bucket - rate;
        }
        else
        {
            bucket = 0;
        }
        printf("\nBucket filled %d|%d\n", bucket, bsize);
    }



}