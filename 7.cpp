#include <cstdio>

bool debug = false;
int inf = 10000000;

struct Gnode {
    int m_v;
    int m_weight;
    Gnode *next;
};

struct Edge {
    int begin;
    int end;
    int weight;
};

struct Gragh {
    int vCnt;
    // int eCnt;   // 在本题中，没有必要储存边数
    Gnode *adj;
};

void init(Gragh *gragh, int v) {   // 复制一个图与原图相连
    gragh->adj = new Gnode[v * 2];
    gragh->vCnt = v;             
    for (int i = 0; i < gragh->vCnt; i++) {   // 各点与其复制点相连
        gragh->adj[i].next = nullptr;
        gragh->adj[i].m_v = i;
        gragh->adj[i].m_weight = 0;
    }
    for (int i = 0; i < v; i++) {  // 原图到新图权重设为0
        Gnode *newNode = new Gnode;
        newNode->m_v = v + i;
        newNode->m_weight = 0;
        newNode->next = gragh->adj[i].next;
        gragh->adj[i].next = newNode;
    }
}

// 同时在新图中插入复制反向边
void insert(Gragh *gragh, int v, int w, int weight) {
    Gnode *newNode = new Gnode;
    newNode->m_v = w;
    newNode->m_weight = weight;
    newNode->next = gragh->adj[v].next;
    gragh->adj[v].next = newNode;
    // gragh->eCnt++;

    Gnode *newNodeCopy = new Gnode;
    newNodeCopy->m_v = v + gragh->vCnt;
    newNodeCopy->m_weight = weight;
    newNodeCopy->next = gragh->adj[w + gragh->vCnt].next;
    gragh->adj[w + gragh->vCnt].next = newNodeCopy;
    // gragh->eCnt++;
}

int weightOfAdjVex(Gragh *gragh, int v, int w) {
    if (gragh == nullptr) return -1;
    Gnode *t = gragh->adj[v].next;
    while (t) {
        if (t->m_v == w) return t->m_weight;
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
    Edge *path = new Edge[gragh->vCnt * 2];
    for (int i = 0; i < gragh->vCnt * 2; i++) {  // 初始化源点到各点距离
        path[i].begin = v;
        path[i].end = i;
        path[i].weight = weightOfAdjVex(gragh, v, i);

        // if (debug) { printf("%d-%d: %d  ", v, i, path[i].weight); }
    }
    path[v].weight = -1; // spt内顶点距离设为-1吧
    int edgeCount = 0;
    for (int i = 1; i < gragh->vCnt * 2; i++) {
        int pathNum = minEdge(path, gragh->vCnt * 2); 

        // if (debug) printf("\n最短边：%d-%d: %d\n", path[pathNum].begin, path[pathNum].end, path[pathNum].weight);

        spt[edgeCount] = path[pathNum];
        edgeCount++;
        int curV = path[pathNum].end;  // 当前加入spt的顶点

        Gnode* p = gragh->adj[curV].next;  // 利用curV的邻接点更新path
        while (p != nullptr) {
            int w = path[curV].weight + p->m_weight;
            if (w < path[p->m_v].weight) {
                path[p->m_v].begin = curV;
                path[p->m_v].weight = w;
                // if (debug) {
                //     printf("成功加入一条边: %d-%d: %d\n", path[p->m_v].begin, path[p->m_v].end, path[p->m_v].weight);
                // }
            }
            p = p->next;
        }
        path[curV].weight = -1;  // spt内不再参与比较        
    }

    delete[] path;
    return edgeCount;
}

int main() {

    if (debug) { freopen("./data.in", "r", stdin); }

    int vCnt, eCnt;
    scanf("%d%d", &vCnt, &eCnt);

    // if (debug) { printf("%d %d", vCnt, eCnt); }
    
    Gragh *gragh = new Gragh;
    init(gragh, vCnt);
    for (int i = 0; i < eCnt; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        insert(gragh, u - 1, v - 1, w);
    }

    Edge *spt0 = new Edge[vCnt * 2];           
    int edgeCount0 = dijkstra(gragh, 0, spt0);

    if (debug) {
        for (int i = 0; i < vCnt * 2; i++)
            printf("%d-%d shortest: %d   ", spt0[i].begin, spt0[i].end, spt0[i].weight);
    }

    int *res = new int[vCnt * 2];
    for (int i = 0; i < vCnt * 2; i++) {
        res[spt0[i].end] = spt0[i].weight;
    }
    for (int i = vCnt + 1; i < vCnt * 2; i++) {
        if (res[i] < inf) 
            printf("%d ", res[i]);
        else
            printf("-1 ");
    }

    delete[] gragh;
    delete[] spt0;
    delete[] res;
    return 0;
}