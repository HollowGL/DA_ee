#include <cstdio>
#include <limits>

/*仅实现了单向Dijkstra算法*/

bool debug = false;
int inf = 1000000000;

struct Gnode {
    int v;
    int weight;
    Gnode *next;
};

struct Edge {
    int begin;
    int end;
    int weight;
};

struct Gragh {
    int vCnt;
    int eCnt;
    Gnode *adj;
};

void init(Gragh *gragh, int v) {
    gragh->adj = new Gnode[v];
    gragh->vCnt = v;
    gragh->eCnt = 0;
    for (int i = 0; i < v; i++) {
        gragh->adj[i].next = nullptr;
        gragh->adj[i].v = i;
        gragh->adj[i].weight = 0;
    }
}

void insert(Gragh *gragh, int v, int w, int weight) {
    Gnode *newNode = new Gnode;
    newNode->v = w;
    newNode->weight = weight;
    newNode->next = gragh->adj[v].next;
    gragh->adj[v].next = newNode;
    gragh->eCnt++;
}

int weightOfAdjVex(Gragh *gragh, int v, int w) {
    if (gragh == nullptr) return -1;
    Gnode *t = gragh->adj[v].next;
    while (t) {
        if (t->v == w) return t->weight;
        t = t->next;
    }
    return inf;
}

int minEdge(Edge *pEdge, int num) {
    int min = inf + 1;
    int  minElem = -1;
    for (int i = 0; i < num; i++) {
        if (pEdge[i].weight == -1) continue;
        if (pEdge[i].weight < min) {
            min = pEdge[i].weight;
            minElem = i;
        }
    }
    return minElem;
}

int dijkstra(Gragh *gragh, int v, Edge *spt) {
    Edge *path = new Edge[gragh->vCnt];
    for (int i = 0; i < gragh->vCnt; i++) {  // 初始化源点到各点距离
        path[i].begin = v;
        path[i].end = i;
        path[i].weight = weightOfAdjVex(gragh, v, i);

        if (debug) { printf("%d-%d: %d  ", v, i, path[i].weight); }
    }
    path[v].weight = -1; // spt内顶点距离设为-1吧
    int edgeCount = 0;
    for (int i = 1; i < gragh->vCnt; i++) {
        int pathNum = minEdge(path, gragh->vCnt); 

        if (debug) printf("\n最短边：%d-%d: %d\n", path[pathNum].begin, path[pathNum].end, path[pathNum].weight);

        spt[edgeCount] = path[pathNum];
        edgeCount++;
        int curV = path[pathNum].end;  // 当前加入spt的顶点

        Gnode* p = gragh->adj[curV].next;  // 利用curV的邻接点更新path
        while (p != nullptr) {
            int w = path[curV].weight + p->weight;
            if (w < path[p->v].weight) {
                path[p->v].begin = curV;
                path[p->v].weight = w;
                if (debug) {
                    printf("成功加入一条边: %d-%d: %d\n", path[p->v].begin, path[p->v].end, path[p->v].weight);
                }
            }
            p = p->next;
        }
        path[curV].weight = -1;  // spt内不再参与比较        
    }

    delete[] path;
    return edgeCount;
}

int main() {

    if (debug) { freopen("../data.in", "r", stdin); }

    int vCnt, eCnt;
    scanf("%d%d", &vCnt, &eCnt);

    if (debug) { printf("%d %d", vCnt, eCnt); }
    
    Gragh *gragh = new Gragh;
    init(gragh, vCnt);
    for (int i = 0; i < eCnt; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        insert(gragh, u - 1, v - 1, w);
    }

    Edge *spt0 = new Edge[eCnt];             // 0到其它点的单向最短路径
    int edgeCount0 = dijkstra(gragh, 0, spt0);
    int *res0 = new int[edgeCount0 + 1];
    for (int i = 0; i < edgeCount0; i++) 
        res0[spt0[i].end] = spt0[i].weight;
    res0[0] = 0;

    int *allRes = new int[vCnt];            // 双向最短路径
    for (int i = 0; i < vCnt; i++)
        allRes[i] = inf;

    for (int i = 1; i < vCnt; i++) {        // i到其它点的单向最短路径
        Edge *spti = new Edge[eCnt];
        int edgeCounti = dijkstra(gragh, i, spti);
        int *resi = new int[edgeCounti + 1];
        for (int i = 0; i < edgeCounti; i++) 
            resi[spti[i].end] = spti[i].weight;
        resi[i] = 0;

        if (debug) {
            printf("\n0-j: \n");
            for (int i = 0; i < vCnt; i++) 
                printf("%d ", res0[i]);
            printf("\n%d-j: \n", i);
            for (int i = 0; i < vCnt; i++) 
                printf("%d ", resi[i]);
            printf("\n");
        }

        int shortest = inf;                 // 通过两个单向路径更新双向路径
        for (int j = 0; j < vCnt; j++) {
            if (res0[j] + resi[j] < shortest) {
                allRes[i] = res0[j] + resi[j];
                shortest = allRes[i];
            }
        }
    }    
    // if (debug) {
    //     printf("\n%d", allRes[5]);
    // }

    for (int i = 1; i < vCnt; i++) {
        if (allRes[i] < inf)
            printf("%d ", allRes[i]);
        else 
            printf("-1 ");
    }
    

    delete[] allRes;    
    return 0;
}