#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph_vertex vertex;

typedef struct Graph_edge { // 边
    struct Graph_vertex *v; // 该边链接的顶点
    struct Graph_edge *next; // 用链表管理的链接同一顶点的下一条边
}edge;

typedef struct Graph_vertex { // 顶点
    int data;   // 顶点的值
    edge *e; // 顶点的边 链表管理的相连接的边
}vertex;

#define MAX_GRAPH (1 << 8)
typedef struct Graph{
    vertex *vxs[MAX_GRAPH];
}graph;

void init_graph(graph *g){
    int i = 0;
    for (;i < MAX_GRAPH; i++) {
        g->vxs[i] = NULL;
    }
}

/* 创建顶点 */
vertex *create_vertex(int data) {
    if(data < 0) {
        return NULL;
    }

    vertex * v = NULL;
    v = (vertex *)malloc(sizeof(vertex));
    if(v == NULL) {
        return NULL;
    }

    v->data = data+1;
    v->e = NULL;

    return v;
}

/* 创建边 */
edge *create_edge(vertex *v){
    if(v == NULL) {
        return NULL;
    }

    edge *e;
    e = (edge *)malloc(sizeof(edge));
    if(e == NULL) {
        return NULL;
    }

    e->v = v;
    e->next = NULL;

    return e; 
}

/* 为顶点v1 插入边 */
void insert_edge(vertex *v1, vertex *v2) {
    if (v1 == NULL || v2 == NULL) {
        return;
    }

    edge **e;
    e = &v1->e;

    while(*e) {
        e = &(*e)->next;
    }
    *e = create_edge(v2);
}

/* 打印邻接表 */
void dump_graph(graph *g) {
    int i;

    for(i = 0;i < MAX_GRAPH; ++i) {
        vertex *v = g->vxs[i];
        edge *e;

        if(v == NULL) {
           continue; 
        }
        printf("Vertex[%d]:%2d->",i+1, v->data);

        e = v->e;
        while(e) {
           if(e->next != NULL) {
               printf("%2d->", e->v->data);
           }else {
               printf("%2d", e->v->data);
           }
           e = e->next; 
        }
        printf("\n");
    }
}

/* 
  1 ----- 2 ----- 3
  |     / |     /
  |    /  |    / 
  |   /   |   /  
  |  /    |  /   
  | /     | /    
  4 ----- 5
*/
void create_graph(graph *g) {
    int i = 0;
    init_graph(g);

    for (;i < 5; ++i) {
        g->vxs[i] = create_vertex(i);
    }

    // 链接1--2, 1--4
    insert_edge(g->vxs[0],g->vxs[1]);
    insert_edge(g->vxs[0],g->vxs[3]);

    // 链接2--1,2--3,2--4,2--5
    insert_edge(g->vxs[1],g->vxs[0]);
    insert_edge(g->vxs[1],g->vxs[2]);
    insert_edge(g->vxs[1],g->vxs[3]);
    insert_edge(g->vxs[1],g->vxs[4]);

    // 链接3--2,3--5
    insert_edge(g->vxs[2],g->vxs[2]);
    insert_edge(g->vxs[2],g->vxs[4]);

    // 链接4--1,4--2,4--5
    insert_edge(g->vxs[3],g->vxs[0]);
    insert_edge(g->vxs[3],g->vxs[1]);
    insert_edge(g->vxs[3],g->vxs[5]);

    // 链接5--2,5--3,5--4
    insert_edge(g->vxs[4],g->vxs[1]);
    insert_edge(g->vxs[4],g->vxs[2]);
    insert_edge(g->vxs[4],g->vxs[3]);
}

int main() {
    graph g;

    create_graph(&g);
    dump_graph(&g);

    return 0;
}