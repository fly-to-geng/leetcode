#define N 1001
#define min(a,b) ((a) > (b) ? (b) : (a))

typedef struct {
    int array[N];
    int end;
    int maxSize;
} CustomStack;


CustomStack* customStackCreate(int maxSize) {
    CustomStack *new = (CustomStack*)malloc(sizeof(CustomStack));
    new->end = 0;
    new->maxSize = maxSize;
    return new;
}

void customStackPush(CustomStack* obj, int x) {
    if (obj->end < obj->maxSize) {
        obj->array[obj->end++] = x;
    }
}

int customStackPop(CustomStack* obj) {
    int ans = -1;
    if (obj->end > 0) {
        ans = obj->array[(obj->end)--];
    }
    return ans;
}

void customStackIncrement(CustomStack* obj, int k, int val) {
    for (int i = 0; i < min(k, obj->end); i++) {
        obj->array[i] += val;
    }
}

void customStackFree(CustomStack* obj) {
    free(obj);
}

/**
 * Your CustomStack struct will be instantiated and called as such:
 * CustomStack* obj = customStackCreate(maxSize);
 * customStackPush(obj, x);

 * int param_2 = customStackPop(obj);

 * customStackIncrement(obj, k, val);

 * customStackFree(obj);
*/