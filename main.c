#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a stack object
struct tagStackObj {
    int height;
    int width;
};

// Function to calculate the largest rectangle area in a histogram
int largestRectangleArea(int* heights, int heightsSize) {
    int maxSize = 0; // Variable to store the maximum area
    int squareSize = 0; // Variable to store the area of the current rectangle
    int i;
    int index = 0; // Index for the stack
    int stride = 0; // Width of the rectangle
    struct tagStackObj* pStack = NULL; // Stack to store heights and widths

    if (heightsSize == 0) {
        return 0; // If the histogram is empty, return 0
    }

    // Allocate memory for the stack
    pStack = malloc(heightsSize * sizeof(struct tagStackObj));
    if (!pStack) {
        perror("Failed to allocate memory for the stack");
        exit(EXIT_FAILURE);
    }

    // Initialize the stack with the first bar
    pStack[index].width = 1;
    pStack[index].height = heights[0];

    // Traverse the histogram
    for (i = 1; i < heightsSize; i++) {
        if (heights[i] >= pStack[index].height) {
            // Push the current bar onto the stack
            index++;
            pStack[index].height = heights[i];
            pStack[index].width = 1;
        } else {
            // Calculate areas for bars taller than the current bar
            stride = 0;
            while (index >= 0 && pStack[index].height > heights[i]) {
                stride += pStack[index].width;
                squareSize = stride * pStack[index].height;
                if (squareSize > maxSize) {
                    maxSize = squareSize;
                }
                index--;
            }

            // Push the current bar onto the stack with updated width
            index++;
            pStack[index].height = heights[i];
            pStack[index].width = stride + 1;
        }
    }

    // Calculate areas for remaining bars in the stack
    stride = 0;
    while (index >= 0) {
        stride += pStack[index].width;
        squareSize = stride * pStack[index].height;
        if (squareSize > maxSize) {
            maxSize = squareSize;
        }
        index--;
    }

    // Free the allocated memory for the stack
    free(pStack);

    return maxSize;
}

// Main function to test the largestRectangleArea function
int main() {
    // Example 1
    int heights1[] = {2, 1, 5, 6, 2, 3};
    int heightsSize1 = sizeof(heights1) / sizeof(heights1[0]);
    printf("Input: heights = [2,1,5,6,2,3]\n");
    printf("Output: %d\n", largestRectangleArea(heights1, heightsSize1));

    // Example 2
    int heights2[] = {2, 4};
    int heightsSize2 = sizeof(heights2) / sizeof(heights2[0]);
    printf("Input: heights = [2,4]\n");
    printf("Output: %d\n", largestRectangleArea(heights2, heightsSize2));

    return 0;
}
