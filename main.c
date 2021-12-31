#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    int endpoint;

    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

int printGraph(int graphSize, const struct GRAPH_NODE_ *graph, int inputFlag);

void newGraph(char *choose, int *graphSize, struct GRAPH_NODE_ **graph, int *inputFlag);

void addNewVertex(char *choose, int *graphSize, struct GRAPH_NODE_ **graph, int *inputFlag);

void deleteNode(int *graphSize, struct GRAPH_NODE_ **graph, int *inputFlag);

void shortestPath(int graphSize, const struct GRAPH_NODE_ *graph);

void TSP(int graphSize, const struct GRAPH_NODE_ *graph);

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void printarray(int arr[], int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void permutation(int *arr, int start, int end,int *mat,int graphSize,int *dist,int fact)
{
    if(start==end)
    {
        int dest=0;
        for(int i=0;i< end;i++){
            dest=dest+mat[arr[i]*graphSize+arr[i+1]];
        }


        for(int i=0;i<fact;i++){
            if(dist[i]==INT_MAX){
                dist[i]=dest;
                i=fact;
            }
        }
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //swapping numbers
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(arr, start+1, end,mat,graphSize,dist,fact);
        swap((arr+i), (arr+start));
    }
}

int min(int a,int b){
    return (a>b) ? b:a ;
}

void optimaize(int mat[4]){
    for(int k=0;k<4;k++){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(mat[i*4+j]!=0 && mat[i*4+k]!=0 && mat[k*4+j]!=0){
                    mat[i*4+j]=min(mat[i*4+j],mat[i*4+k]+mat[k*4+j]);
                }
                if(i!=j && mat[i*4+j]==0 && mat[i*4+k]!=0 && mat[k*4+j]!=0){
                    mat[i*4+j]=mat[i*4+k]+mat[k*4+j];
                }

            }
        }
    }

}

///
///QUEUE IMPLEMATION for dijikstra:
void freeGraph(pnode graph,int graphSize){
    for(int i=0;i<graphSize;i++){
        pedge tmp;

        while (graph[i].edges != NULL)
        {
            tmp = graph[i].edges;
            graph[i].edges = graph[i].edges->next;
            free(tmp);
        }

        graph[i].edges=NULL;
    }
    free(graph);
    graph=NULL;
}




int main() {
    char choose;
    int graphSize = 1;
    scanf(" %c",&choose);

    struct GRAPH_NODE_* graph = (pnode) malloc(graphSize * sizeof(node));
    graph[0].edges=(pedge) malloc(sizeof (edge));
    graph[0].edges->next=NULL;
    graph[0].edges->weight=-1;
    graph[0].edges->endpoint=-1;
    graph[0].node_num=0;

    int inputFlag = 1;
    while (getchar() != EOF) {
        if (inputFlag == 0) {
            scanf(" %c", &choose);
        }

        inputFlag = 0;
        ///E is for break the loop and exit the program-for testing purpose only
        if (choose == 'E') {
            break;
        }
        ///P is for printing all the nodes ID-for testing purpose only
        if (choose == 'P') {
            inputFlag = printGraph(graphSize, graph, inputFlag);
        }
        ///A is for making new graph
        ///after 'A' enter the number of nodes you start the graph with
        if (choose == 'A') {
            newGraph(&choose, &graphSize, &graph, &inputFlag);
        }
        ///B is for making new vertex
        if (choose == 'B') {
            addNewVertex(&choose, &graphSize, &graph, &inputFlag);
        }
        ///D is for deleting a vertex
        if (choose == 'D') {
            deleteNode(&graphSize, &graph, &inputFlag);
        }
        ///F is for printing the shortest path from A to B using floyd warshell
        if (choose == 'S') {
            if(inputFlag==1){
                inputFlag=0;
            }
            shortestPath(graphSize, graph);
        }
        /// T is for TSP
        if (choose == 'T') {
            if(inputFlag==1){
                inputFlag=0;
            }
            TSP(graphSize, graph);


        }
    }
    freeGraph(graph,graphSize);
    return 0;
}

void TSP(int graphSize, const struct GRAPH_NODE_ *graph) {///floyd warshel
    int *intMatrix;

    intMatrix = (int *)malloc(graphSize * graphSize * sizeof(int));


    for(int i=0;i<graphSize*graphSize;i++){
        intMatrix[i]=0;
    }

    for(int i=0;i<graphSize;i++){
        pedge e=graph[i].edges;
        while (e!=NULL){
            for(int k=0;k<graphSize;k++){
                if(graph[k].node_num==e->endpoint && e->weight!=-1){
                    intMatrix[i*graphSize+k]=e->weight;
                }
            }
            e=e->next;
        }
    }


    for(int k=0;k<graphSize;k++){
        for(int i=0;i<graphSize;i++){
            for(int j=0;j<graphSize;j++){
                if(intMatrix[i*graphSize+j]!=0 && intMatrix[i*graphSize+k]!=0 && intMatrix[k*graphSize+j]!=0){
                    intMatrix[i*graphSize+j]=min(intMatrix[i*graphSize+j],intMatrix[i*graphSize+k]+intMatrix[k*graphSize+j]);
                }
                if(i!=j && intMatrix[i*graphSize+j]==0 && intMatrix[i*graphSize+k]!=0 && intMatrix[k*graphSize+j]!=0){
                    intMatrix[i*graphSize+j]=intMatrix[i*graphSize+k]+intMatrix[k*graphSize+j];
                }
            }
        }
    }

    for(int k=0;k<graphSize;k++){
        for(int i=0;i<graphSize;i++){
            //printf(" %d",intMatrix[k*graphSize+i]);
            if(intMatrix[k*graphSize+i]==0){
                intMatrix[k*graphSize+i]=99999;
            }
        }
        //printf(" \n");
    }

    ///TSP

    ///k is the number of stops
    int k;
    scanf(" %d",&k);
    int *stops=(int *) malloc(k* sizeof(int));

    ///this for loop will put into stop array the INDEX of the stop.
///because the matrix of the distances is working with indexes and not ID.
    for(int i=0;i<k;i++){
        int stopValue;
        scanf(" %d", &stopValue);
        for(int t=0;t<graphSize;t++){
            if(stopValue==graph[t].node_num){
                stops[i]=t;
            }
        }
    }
    //printarray(stops,k);

    ///making an array of all the distance from all the permotations of the TSP root.

    ///calculate k factorial
///and setting all of the array to INT_MAX
    int fact=1;
    for (int i = 1; i <= k; ++i) {
        fact *= i;
    }
    int *dist=malloc(fact* sizeof(int));
    for(int i=0;i<fact;i++){
        dist[i]=INT_MAX;
    }

    ///calling the permotation function.
///the function will set dist array all the permotation distance
    permutation(stops,0,k-1,intMatrix,graphSize,dist,fact);
    int minTSP=INT_MAX;
    for(int i=0;i<fact;i++){
        if(dist[i]<minTSP){
            minTSP=dist[i];
        }
    }
    if(minTSP>99997){
        minTSP=-1;
    }
    printf("TSP shortest path: %d ",minTSP);
    printf("\n");
    free(intMatrix);
    free(stops);
    free(dist);
}

void shortestPath(int graphSize, const struct GRAPH_NODE_ *graph) {
    int srcID;
    int destID;
    int srcIndex;
    int destIndex;
    scanf(" %d",&srcID);
    scanf(" %d",&destID);

    for(int i=0;i<graphSize;i++){
        if(graph[i].node_num==srcID){
            srcIndex=i;
        }
        if(graph[i].node_num==destID){
            destIndex=i;
        }
    }

    int *intMatrix;

    intMatrix = (int *)malloc(graphSize * graphSize * sizeof(int));


    for(int i=0;i<graphSize*graphSize;i++){
        intMatrix[i]=0;
    }

    for(int i=0;i<graphSize;i++){
        pedge e=graph[i].edges;
        while (e!=NULL){
            for(int k=0;k<graphSize;k++){
                if(graph[k].node_num==e->endpoint && e->weight!=-1){
                    intMatrix[i*graphSize+k]=e->weight;
                }
            }
            e=e->next;
        }
    }


    for(int k=0;k<graphSize;k++){
        for(int i=0;i<graphSize;i++){
            for(int j=0;j<graphSize;j++){
                if(intMatrix[i*graphSize+j]!=0 && intMatrix[i*graphSize+k]!=0 && intMatrix[k*graphSize+j]!=0){
                    intMatrix[i*graphSize+j]=min(intMatrix[i*graphSize+j],intMatrix[i*graphSize+k]+intMatrix[k*graphSize+j]);
                }
                if(i!=j && intMatrix[i*graphSize+j]==0 && intMatrix[i*graphSize+k]!=0 && intMatrix[k*graphSize+j]!=0){
                    intMatrix[i*graphSize+j]=intMatrix[i*graphSize+k]+intMatrix[k*graphSize+j];
                }
            }
        }
    }



    if(intMatrix[srcIndex*graphSize+destIndex]!=0){
        printf("Dijsktra shortest path: %d ",intMatrix[srcIndex*graphSize+destIndex]);
    }
    else{
        printf("Dijsktra shortest path: -1 ");

    }
    printf("\n");
    free(intMatrix);
}

void deleteNode(int *graphSize, struct GRAPH_NODE_ **graph, int *inputFlag) {
    if((*inputFlag) == 1){
        (*inputFlag) =0;
    }
    int deletingNodeID;
    scanf(" %d",&deletingNodeID);
    ///checking if the node exist
    int isNodeExist=0;
    int deletingNodeIndex;
    for(int i=0; i < (*graphSize); i++){
        if((*graph)[i].node_num == deletingNodeID){
            isNodeExist=1;
            deletingNodeIndex=i;
        }
    }
    if(isNodeExist==1){
        ///deleting edges to the node
        for(int i=0; i < (*graphSize); i++){
            pedge temp= (*graph)[i].edges;
            pedge prev;
            while (temp != NULL && temp->endpoint != deletingNodeID) {
                prev = temp;
                temp = temp->next;
            }
            if(temp!=NULL){
                prev->next=temp->next;

            }
            free(temp);
        }
        ///deleting the node

        pedge tmp;
        while ((*graph)[deletingNodeIndex].edges != NULL)
        {
            tmp = (*graph)[deletingNodeIndex].edges;
            (*graph)[deletingNodeIndex].edges = (*graph)[deletingNodeIndex].edges->next;
            free(tmp);
        }

        (*graph)[deletingNodeIndex].edges=NULL;
        //free((*graph)[deletingNodeIndex].edges);
        for(int i = deletingNodeIndex; i < (*graphSize) - 1; i++) {
            (*graph)[i] = (*graph)[i + 1];
        }

        (*graphSize) = (*graphSize) - 1;

        (*graph) =(pnode) realloc((*graph), (*graphSize) * sizeof(node));

    }
}

void addNewVertex(char *choose, int *graphSize, struct GRAPH_NODE_ **graph, int *inputFlag) {
    if((*inputFlag) == 1){
        (*inputFlag) =0;
    }
    ///input the node id
    int workingNode;
    scanf(" %d",&workingNode);
    ///first we need to check if the node exist in the graph
    int existFlag=0;
    int workingNodeIndex;
    for(int i=0; i < (*graphSize); i++){
        if((*graph)[i].node_num == workingNode){
            existFlag=1;
            workingNodeIndex=i;
        }
    }
    ///case 1: node exist
    if(existFlag==1){
        free((*graph)[workingNodeIndex].edges);

        (*graph)[workingNodeIndex].edges=(pedge) malloc(sizeof(edge));
        (*graph)[workingNodeIndex].edges->next=NULL;
        (*graph)[workingNodeIndex].edges->weight=-1;
        (*graph)[workingNodeIndex].edges->endpoint=-1;

    } else{
        ///case 2: node does not exist
        workingNodeIndex= (*graphSize);
        (*graphSize) = (*graphSize) + 1;
        (*graph) =(node*)realloc((*graph), (*graphSize) * sizeof(node));
        (*graph)[workingNodeIndex].node_num=workingNode;
        (*graph)[workingNodeIndex].edges=(pedge) malloc(sizeof (edge));
        (*graph)[workingNodeIndex].edges->weight=-1;
        (*graph)[workingNodeIndex].edges->endpoint=-1;
        (*graph)[workingNodeIndex].edges->next=NULL;
    }
    ///adding edges to the new node
    int dest;
    int weight;
    char c;
    while (1==1){
        ///check if input to dest is number.
        ///if not then input is char and exist B
        if(scanf(" %d",&dest) != 1) {
            c = getchar();
            (*choose) =c;
            (*inputFlag) =1;
            break;
        }
        ///if dest is number then next input will be weight
        scanf(" %d",&weight);
        ///adding new edge to node
        pedge current= (*graph)[workingNodeIndex].edges;
        while (current->next!=NULL){
            current=current->next;
        }
        current->next=(pedge) malloc(sizeof(edge));
        current->next->endpoint=dest;
        current->next->weight=weight;
        current->next->next=NULL;
    }
}

void newGraph(char *choose, int *graphSize, struct GRAPH_NODE_ **graph, int *inputFlag) {
    if ((*inputFlag) == 1) {
        (*inputFlag) = 0;
    }

    freeGraph(*graph,*graphSize);

    scanf(" %d", graphSize);
    (*graph) = (struct GRAPH_NODE_ *) malloc((*graphSize) * sizeof(struct GRAPH_NODE_));
    ///setting the nodes Id to each node
///setting the edges linkList to each node
///the head edge will have -1 weight. WE WILL NOT USE THIS EDGE.
    for (int i = 0; i < (*graphSize); ++i) {
        (*graph)[i].node_num = i;
        (*graph)[i].edges=(pedge) malloc(sizeof(edge));
        (*graph)[i].edges[0].weight=-1;
        (*graph)[i].edges[0].endpoint=-1;
        (*graph)[i].edges[0].next=NULL;
    }
    ///if ch=='n' then we want to work with node and add edges to this node.
    char ch;
    scanf(" %c", &ch);
    if (ch == 'n')
    {
        int workingNode;
        scanf(" %d",&workingNode);
        int loopBreak=1;
        int dest;
        int weight;
        char c;
        while (loopBreak==1){
            ///entered char
            ///check if input is number.
            ///if not then input is char and exist A
            if(scanf(" %d",&dest) != 1){
                c=getchar();
                if(c=='n'){
                    scanf("%d",&workingNode);
                } else{
                    (*choose) =c;
                    (*inputFlag) =1;
                    break;
                }
            }///entered number
            else{
                scanf(" %d",&weight);
                ///edding new edge
                ///first we will find the working node Index
                int workingNodeIndex=0;
                for(int i=0; i < (*graphSize); i++){
                    if((*graph)[i].node_num == workingNode){
                        workingNodeIndex=i;
                    }
                }
                ///adding new edge to working Node
                pedge current= (*graph)[workingNodeIndex].edges;
                while (current->next!=NULL){
                    current=current->next;
                }
                current->next=(pedge) malloc(sizeof(edge));
                current->next->endpoint=dest;
                current->next->weight=weight;
                current->next->next=NULL;


            }
        }
    } else{
        (*inputFlag) =1;
        (*choose) =ch;
    }
}

int printGraph(int graphSize, const struct GRAPH_NODE_ *graph, int inputFlag) {
    if (inputFlag == 1) {
        inputFlag = 0;
    }
    for (int i = 0; i < graphSize; i++) {
        printf("node number: %d \n", graph[i].node_num);
        pedge current=graph[i].edges;
        while (current != NULL) {
            if(current->weight!=-2){
                printf("src: %d dest: %d weight: %d \n", graph[i].node_num,current->endpoint,current->weight);
            }
            current = current->next;
        }
    }
    return inputFlag;
}



