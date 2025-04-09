#include <stdio.h>


int main()
{
    printf("enter the size of the bucket: ");
    int bsize;
    scanf("%d", &bsize);
    printf("enter the outflow rate: ");
    int out_rate;
    scanf("%d", &out_rate);
    printf("enter the number of packets: ");
    int n;
    scanf("%d", &n);
    int bucket = 0;

    int i;
    for(i=0;i<n;i++)
    {
        printf("Enter the size of the incoming packet at %d: ", i+1);
        int in;
        scanf("%d", &in);

        if(in<(bsize-bucket))
        {
            bucket = bucket + in;
            printf("Adding the packets %d|%d", bucket, bsize);
        }
        else
        {
            printf("Discarding the packets %d", in-(bsize-bsize));
            bucket = bsize;
        }
        if((bucket - out_rate)>0)
        {
            bucket = bucket - out_rate;
        }
        else
        {
            bucket = 0;
        }
        printf("STATUS %d|%d", bucket, bsize);
    }
}