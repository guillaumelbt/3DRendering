#include "utils.h"

void QuickSortTriangles(triangle* triangles, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(triangles, low, high);
        QuickSortTriangles(triangles, low, pivotIndex - 1);
        QuickSortTriangles(triangles, pivotIndex + 1, high);
    }
}

int Partition(triangle* triangles, int low, int high) {
    float pivot = triangles[high].avgDepth;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (triangles[j].avgDepth > pivot) {  // Tri décroissant (plus profond en premier)
            i++;
            triangle temp = triangles[i];
            triangles[i] = triangles[j];
            triangles[j] = temp;
        }
    }

    triangle temp = triangles[i + 1];
    triangles[i + 1] = triangles[high];
    triangles[high] = temp;

    return i + 1;
}