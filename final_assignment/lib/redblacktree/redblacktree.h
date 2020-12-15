typedef enum __Color {
    RED = 0,
    BLACK = 1,
} Color;

typedef struct __Node {
    Color color;
    int wordId;
    struct __Node* left;
    struct __Node* right;
} Node;

void CreateNilNode();