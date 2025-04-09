#include<stdio.h>
int main(){
    int bucketCapacity, leakRate, noOfPackets, leaked, bucket = 0;

    printf("Enter bucket capacity : ");
    scanf("%d",&bucketCapacity);

    printf("Enter leak rate : ");
    scanf("%d",&leakRate);

    printf("Enter no. of packets : ");
    scanf("%d",&noOfPackets);

    int packets[noOfPackets];
    printf("Enter size of the packets : ");
    for(int i=0;i<noOfPackets;i++){
        scanf("%d",&packets[i]);
    }

    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");
    for(int i=0;i<noOfPackets;i++){
        printf("%d\t%d\t",i+1,packets[i]);

        bucket = bucket + packets[i];
        if(bucket > bucketCapacity){
            printf("Overflow, Dropped %d",bucket-bucketCapacity);
            bucket = bucketCapacity;
        }
        else{
            printf("%d\t",bucket);
        }
        
        if(bucket >= leakRate){
            leaked = leakRate;
        }
        else{
            leaked = bucket;
        }
        bucket = bucket - leaked;
        printf("%d\t%d\n",leaked,bucket);
    }
    int time = noOfPackets + 1;
    while(bucket > 0){
        if(bucket >= leakRate){
            leaked = leakRate;
        }
        else{
            leaked = bucket;
        }
        printf("%d\t%d\t%d\t%d\t%d\n",time,0,bucket,leaked,bucket-leaked);
        bucket = bucket - leaked;
        time = time + 1;
    }
}