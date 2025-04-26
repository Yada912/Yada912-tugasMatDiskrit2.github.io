#include <stdio.h>

#define MAX_VERTICES 100

// Function to input an integer with validation
int inputInteger() {
    int a;
    scanf("%i", &a);
    while (a < 1) {
        printf("/!\\ INPUT TIDAK DIPERBOLEHKAN, KETIK ULANG NILAI : ");
        scanf("%i", &a);
    }
    return a;
}

// Function to input a boolean-like value (0 or 1) with validation
int inputBoolean() {
    int a;
    scanf("%i", &a);
    while (a > 1 || a < 0) {
        printf("/!\\ INPUT TIDAK DIPERBOLEHKAN, KETIK ULANG NILAI : ");
        scanf("%i", &a);
    }
    return a;
}

// Function to perform Depth First Search (DFS)
void DFS(int v, int visited[], int adj[MAX_VERTICES][MAX_VERTICES], int vertices) {
    visited[v] = 1;
    for (int i = 0; i < vertices; i++) {
        if (adj[v][i] && !visited[i]) {
            DFS(i, visited, adj, vertices);
        }
    }
}

// Function to check if the graph is connected
int isConnected(int adj[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int visited[MAX_VERTICES] = { 0 };
    int start = -1;

    // Find a valid starting vertex (a vertex with at least one edge)
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (adj[i][j] == 1) {
                start = i;
                break;
            }
        }
        if (start != -1) break;
    }
    if (start == -1) return 0; // No edges in the graph

    DFS(start, visited, adj, vertices);

    // Check if all vertices are visited
    for (int i = 0; i < vertices; i++) {
        if (visited[i] == 0) {
            return 0; // Graph is not connected
        }
    }
    return 1; // Graph is connected
}

// Function to check if a color assignment is valid
int isSafe(int vertex, int adj[MAX_VERTICES][MAX_VERTICES], int colors[], int color, int vertices) {
    for (int i = 0; i < vertices; i++) {
        if (adj[vertex][i] == 1 && colors[i] == color) {
            return 0; // Conflict: adjacent vertex has the same color
        }
    }
    return 1; // Safe to assign this color
}

// Backtracking function to solve the graph coloring problem
int graphColoringBacktracking(int adj[MAX_VERTICES][MAX_VERTICES], int colors[], int vertex, int maxColors, int vertices, int* maxColorUsed) {
    if (vertex == vertices) {
        return 1; // All vertices are successfully colored
    }

    // coba pasang warna
    for (int color = 0; color < maxColors; color++) {
        if (isSafe(vertex, adj, colors, color, vertices)) {
            colors[vertex] = color; // assign warna vertek

            // Update the max color
            if (color > *maxColorUsed) {
                *maxColorUsed = color;
            }

            // Recur to assign colors to the next vertex
            if (graphColoringBacktracking(adj, colors, vertex + 1, maxColors, vertices, maxColorUsed)) {
                return 1;
            }

            // Backtrack: remove the color assignment
            colors[vertex] = -1;
        }
    }

    return 0; // No valid color assignment found
}

// Wrapper function for graph coloring using backtracking
int graphColoring(int adj[MAX_VERTICES][MAX_VERTICES], int vertices, int colors[]) {
    int maxColors = vertices; // Maximum possible colors (one color per vertex)
    int maxColorUsed = -1;    // Track the maximum color used

    for (int i = 0; i < vertices; i++) {
        colors[i] = -1; // Initialize all vertices as uncolored
    }

    // Start the backtracking algorithm
    if (graphColoringBacktracking(adj, colors, 0, maxColors, vertices, &maxColorUsed)) {
        return maxColorUsed + 1; // Return the total number of colors used (0-based index + 1)
    }
    else {
        printf("Tidak ada solusi pewarnaan graf yang valid.\n");
        return -1; // Gada solusi
    }
}

void berjalan() {
    int vertices, i, j;

    printf("============== Program Pewarnaan Graph ==============\n");

    // Input jumlah vertex
    printf("\nMasukkan jumlah vertek: ");
    vertices = inputInteger();
    int adj[MAX_VERTICES][MAX_VERTICES] = { 0 };

    // Input adjacency matrix
    printf("\n= Masukkan hubungan antar-vertek =\nApakah hubungan antar vertek bersifat dua arah? (Y/N)\n");
    char arah;
    scanf(" %c", &arah);
    printf("== Ketik 1 jika terdapat edge yang menghubungkan, 0 jika tidak ==\n\n");
    if (arah == 'Y' || arah == 'y') {
        for (i = 0; i < vertices; i++) {
            for (j = i; j < vertices; j++) {
                if (i != j) {
                    printf("Hubungan vertek %c <=> %c: ", 'A' + i, 'A' + j);
                    adj[i][j] = inputBoolean();
                    adj[j][i] = adj[i][j];
                }
            }
        }
    }
    else {
        for (i = 0; i < vertices; i++) {
            for (j = 0; j < vertices; j++) {
                if (i != j) {
                    printf("Hubungan vertek %c -> %c: ", 'A' + i, 'A' + j);
                    adj[i][j] = inputBoolean();
                }
            }
        }
    }

    // Display adjacency matrix
    printf("\n=== Adjacency Matrix ===\n");
    printf("     ");
    for (i = 0; i < vertices; i++) {
        printf("%-4c ", 'A' + i);
    }
    printf("\n");

    for (i = 0; i < vertices; i++) {
        printf("%-4c ", 'A' + i);
        for (j = 0; j < vertices; j++) {
            printf("%-4d ", adj[i][j]);
        }
        printf("\n");
    }

    // Check if the graph is connected
    printf("\n=== Kesimpulan Graph ===\n");
    if (isConnected(adj, vertices)) {
        printf("Graph yang diberikan TERHUBUNG.\n");
    }
    else {
        printf("Graph yang diberikan TIDAK TERHUBUNG.\n");
    }

    // graph coloring
    int colors[MAX_VERTICES];
    int colorCount = graphColoring(adj, vertices, colors);

    // Display coloring result
    printf("\n=== Hasil Pewarnaan Graph ===\n");
    for (i = 0; i < vertices; i++) {
        printf("Vertek %c = %d\n", 'A' + i, colors[i]);
    }
    printf("Total warna yang digunakan: %d\n", colorCount);

    // Menentukan derajat in dan out
    printf("\n=== Derajat In dan Out ===\n");
    int inDegree[vertices], outDegree[vertices];
    for (i = 0; i < vertices; i++) {
        inDegree[i] = 0;
        outDegree[i] = 0;
    }
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            if (adj[i][j] == 1) {
                outDegree[i]++;
                inDegree[j]++;
            }
        }
    }
    for (i = 0; i < vertices; i++) {
        printf("Derajat Vertek %c: In= %d, Out= %d\n", 'A' + i, inDegree[i], outDegree[i]);
    }

    // Menampilkan adjacency list
    printf("\n=== Representasi Adjacency List ===\n");
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            if (adj[i][j] == 1) {
                if (adj[j][i] == 1) {
                    printf("%c <=> %c\n", 'A' + i, 'A' + j);
                    adj[j][i] = 0;
                }
                else {
                    printf("%c -> %c\n", 'A' + i, 'A' + j);
                }
            }
        }
    }
}

int main() {
    char jalan;
    do {
        berjalan();
        printf("\n======================================================================\n");
        printf("Jalankan ulang program? (Y/N): ");
        getchar(); // Clear newline character from the buffer
        scanf("%c", &jalan);
        printf("\n======================================================================\n\n");
    } while (jalan == 'y' || jalan == 'Y');

    return 0;
}