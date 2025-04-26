#include <stdio.h>
#define MAX_Integer 100

// Function to input an integer (greater than 0) with validation
int inputInteger() {
    int a;
    scanf("%i", &a);
    while (a < 1) {
        printf("/!\\ INPUT TIDAK DIPERBOLEHKAN, KETIK ULANG NILAI : ");
        scanf("%i", &a);
    }
    return a;
}

// Function to input a boolean (0 or 1) with validation
int inputBoolean() {
    int a;
    scanf("%i", &a);
    while (a > 1 || a < 0) {
        printf("/!\\ INPUT TIDAK DIPERBOLEHKAN, KETIK ULANG NILAI : ");
        scanf("%i", &a);
    }
    return a;
}

// Function to create an adjacency matrix
void createAdjacencyMatrix(int adj[MAX_Integer][MAX_Integer], int *vertices) {
    printf("\nMasukkan jumlah vertek: ");
    *vertices = inputInteger();

    printf("\n= Masukkan hubungan antar-vertek =\nApakah hubungan antar vertek bersifat dua arah? (Y/N)\n");
    char arah;
    scanf(" %c", &arah);
    printf("== Ketik 1 jika terdapat edge yang menghubungkan, 0 jika tidak ==\n\n");

    if (arah == 'Y' || arah == 'y') {
        for (int i = 0; i < *vertices; i++) {
            for (int j = i; j < *vertices; j++) {
                if (i != j) {
                    printf("Hubungan vertek %c <=> %c: ", 'A' + i, 'A' + j);
                    adj[i][j] = inputBoolean();
                    adj[j][i] = adj[i][j];
                }
            }
        }
    } else {
        for (int i = 0; i < *vertices; i++) {
            for (int j = 0; j < *vertices; j++) {
                if (i != j) {
                    printf("Hubungan vertek %c -> %c: ", 'A' + i, 'A' + j);
                    adj[i][j] = inputBoolean();
                }
            }
        }
    }
}

// Function to encode a Prufer code from an adjacency matrix
void encodePrufer(int adj[MAX_Integer][MAX_Integer], int vertices) {
    int degree[MAX_Integer] = {0};
    int pruferCode[MAX_Integer] = {0};
    int i, j, k = 0;

    // Calculate the degree of each vertex
printf("\n[ENCODING] Calculating degrees of vertices...\n");
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            if (adj[i][j] == 1) {
                degree[i]++;
            }
        }
printf("Vertex %c has degree %d\n", 'A' + i, degree[i]);
    }

    // Generate Prufer code
printf("\n[ENCODING] Generating Prufer code...\n");
    for (i = 0; i < vertices - 2; i++) {
        for (j = 0; j < vertices; j++) {
            if (degree[j] == 1) {
printf("Removing leaf vertex %c\n", 'A' + j);
                degree[j]--; // Remove the leaf
                for (k = 0; k < vertices; k++) {
                    if (adj[j][k] == 1) {
                        pruferCode[i] = k;
                        adj[j][k] = adj[k][j] = 0; // Remove the edge
                        degree[k]--;
printf("Edge between %c and %c removed\n", 'A' + j, 'A' + k);
                        break;
                    }
                }
                break;
            }
        }
    }

    // Print the Prufer code
    printf("\nPrufer Code: ");
    for (i = 0; i < vertices - 2; i++) {
        printf("%c ", 'A' + pruferCode[i]);
    }
    printf("\n");
}

// Function to decode a Prufer code into an adjacency matrix
void decodePrufer(int pruferCode[], int length) {
    int vertices = length + 2;
    int degree[MAX_Integer] = {0};
    int adj[MAX_Integer][MAX_Integer] = {0};
    int i, j;

    // Initialize degree array
printf("\n[DECODING] Initializing degrees from Prufer code...\n");
    for (i = 0; i < length; i++) {
        degree[pruferCode[i]]++;
    }
    for (i = 0; i < vertices; i++) {
        degree[i]++;
printf("Vertex %c has degree %d\n", 'A' + i, degree[i]);
    }

    // Build the adjacency matrix
printf("\n[DECODING] Building adjacency matrix...\n");
    for (i = 0; i < length; i++) {
        for (j = 0; j < vertices; j++) {
            if (degree[j] == 1) {
                adj[j][pruferCode[i]] = 1;
                adj[pruferCode[i]][j] = 1;
                degree[j]--;
                degree[pruferCode[i]]--;
printf("Connecting vertex %c with %c\n", 'A' + j, 'A' + pruferCode[i]);
                break;
            }
        }
    }

    // Connect the last two vertices
    int u = -1, v = -1;
    for (i = 0; i < vertices; i++) {
        if (degree[i] == 1) {
            if (u == -1) {
                u = i;
            } else {
                v = i;
                break;
            }
        }
    }
    adj[u][v] = adj[v][u] = 1;
printf("Connecting last two vertices %c and %c\n", 'A' + u, 'A' + v);

    // Print the adjacency matrix
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
}

// Main running code
void berjalan() {
    int vertices;
    int adj[MAX_Integer][MAX_Integer] = {0};

    printf("============== Program Pewarnaan Graph ==============\n");
    printf("Menggunakan predata? [Y/N]: ");
    char metaData;
    scanf(" %c", &metaData);

    if (metaData == 'Y' || metaData == 'y') {
        vertices = 6;
        int predefinedAdj[6][6] = {
        {0, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 1},
        {0, 1, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0}};
                for (int i = 0; i < vertices; i++) {
                for (int j = 0 ; j < vertices; j++) {
                    adj[i][j] = predefinedAdj[i][j];
                    }
                }
            } else {
    createAdjacencyMatrix(adj, &vertices);
}

    // Prufer code operations
    printf("\nApakah ingin encode atau decode Prufer code? (E/D): ");
    char choice;
    scanf(" %c", &choice);

    if (choice == 'E' || choice == 'e') {
        encodePrufer(adj, vertices);
    } else if (choice == 'D' || choice == 'd') {
        printf("\nMasukkan panjang Prufer code: ");
        int length = inputInteger();
        int pruferCode[MAX_Integer];
        printf("\nMasukkan Prufer code (sebagai indeks 0-based):\n");
        for (int i = 0; i < length; i++) {
            printf("Elemen ke-%d: ", i + 1);
            pruferCode[i] = inputInteger() - 1; // Convert to 0-based index
        }
        decodePrufer(pruferCode, length);
} else {
        printf("\nPilihan tidak valid.\n");
    }
}

// Wrapper looping seluruh program
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