#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define s 9
#define max 2000
int mindist(int dis[s],bool sp[s]){
    int min=max,index;
    for(int i=0;i<s-1;i++){
        if(sp[i]==false && dis[i]<min){
            min=dis[i];
            index=i;
        }
    }
    return index;
}
void print(int dist[s],int src){
    printf("distance from source is %d \n",src);
    printf("vertices\tdistance\n");
    for(int i=0;i<s-1;i++){
        printf("%d\t%d\n",i,dist[i]);
    }
}

void dijik(int graph[s][s],int src){
    int dist[s];
    bool spt[s];
    for(int k=0;k<s-1;k++){
        dist[k]=max;
        spt[k]=false;
    }

    dist[src]=0;
    spt[src]=true;
    int u;
    for(int c=0;c<s-1;c++){
        u=mindist(dist,spt);
        spt[c]=true;
        for(int j=0;j<s-1;j++){
            if(spt[j]==false && graph[c][j]!=0 && dist[c]!=max &&
                dist[c]+graph[c][j]<dist[j]){
                    dist[j]=dist[c]+graph[c][j];
                }
        }
    }
    print(dist,src);
}

void main(){
     int graph[s][s] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    dijik(graph,0);
                    
}
