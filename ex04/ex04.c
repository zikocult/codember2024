#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 201

typedef struct {
    int nodes[MAX_NODES];
    int size;
} Component;

void add_edge(int graph[MAX_NODES][MAX_NODES], int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void dfs(int node, int visited[MAX_NODES], int graph[MAX_NODES][MAX_NODES], Component *component) {
    visited[node] = 1;
    component->nodes[component->size++] = node;
    for (int i = 0; i < MAX_NODES; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i, visited, graph, component);
        }
    }
}

void find_components(int graph[MAX_NODES][MAX_NODES], Component components[MAX_NODES], int *component_count, int nodes[], int node_count) {
    int visited[MAX_NODES] = {0};
    for (int i = 0; i < node_count; i++) {
        int node = nodes[i];
        if (!visited[node]) {
            components[*component_count].size = 0;
            dfs(node, visited, graph, &components[*component_count]);
            if (components[*component_count].size > 0) {
                (*component_count)++;
            }
        }
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    FILE *file = fopen("network.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int graph[MAX_NODES][MAX_NODES] = {0};
    int nodes[MAX_NODES] = {0};
    int node_count = 0;
    int u, v;
    char buffer[256];

    // Read the file content
    while (fgets(buffer, sizeof(buffer), file)) {
        char *ptr = buffer;
        while (*ptr) {
            if (*ptr == '[') {
                ptr++;
                if (sscanf(ptr, "%d,%d", &u, &v) == 2) {
                    add_edge(graph, u, v);
                    if (!nodes[u]) {
                        nodes[u] = 1;
                        node_count++;
                    }
                    if (!nodes[v]) {
                        nodes[v] = 1;
                        node_count++;
                    }
                }
            }
            ptr++;
        }
    }
    fclose(file);

    int unique_nodes[node_count];
    int index = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodes[i]) {
            unique_nodes[index++] = i;
        }
    }

    Component components[MAX_NODES];
    int component_count = 0;
    find_components(graph, components, &component_count, unique_nodes, node_count);

    int safe_nodes[MAX_NODES];
    int safe_count = 0;

    for (int i = 0; i < component_count; i++) {
        if (components[i].size < 3) {
            for (int j = 0; j < components[i].size; j++) {
                safe_nodes[safe_count++] = components[i].nodes[j];
            }
        }
    }

    qsort(safe_nodes, safe_count, sizeof(int), compare);

    printf("submit ");
    for (int i = 0; i < safe_count; i++) {
        if (i > 0) {
            printf(",");
        }
        printf("%d", safe_nodes[i]);
    }
    printf("\n");

    return 0;
}

