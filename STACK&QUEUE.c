#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Palindrome using stack (array) ---------- */
void palindrome_using_stack(void) {
    enum { MAX = 100 };
    char str[MAX];
    char stack[MAX];
    int top = -1;

    printf("Enter a string: ");
    if (!fgets(str, sizeof(str), stdin)) return;
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (top < MAX - 1) stack[++top] = str[i];
    }

    char rev[MAX];
    int j = 0;
    while (top >= 0) rev[j++] = stack[top--];
    rev[j] = '\0';

    if (strcmp(str, rev) == 0)
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");
}

/* ---------- Linked stack demo (no nested functions) ---------- */
struct LNode {
    int data;
    struct LNode *next;
};

static void linked_stack_push(struct LNode **top_ref, int x) {
    struct LNode *newnode = (struct LNode*)malloc(sizeof(struct LNode));
    if (newnode == NULL) { printf("Memory not allocated\n"); return; }
    newnode->data = x;
    newnode->next = *top_ref;
    *top_ref = newnode;
    printf("%d Pushed\n", x);
}

static void linked_stack_pop(struct LNode **top_ref) {
    if (*top_ref == NULL) { printf("Stack Underflow\n"); return; }
    struct LNode *temp = *top_ref;
    printf("Popped: %d\n", temp->data);
    *top_ref = temp->next;
    free(temp);
}

static void linked_stack_display(struct LNode *top) {
    if (top == NULL) { printf("Stack is Empty\n"); return; }
    struct LNode *p = top;
    printf("Stack elements: ");
    while (p != NULL) { printf("%d ", p->data); p = p->next; }
    printf("\n");
}

void linked_stack_demo(void) {
    struct LNode *top = NULL;
    int choice = 0, value;
    while (1) {
        printf("\n--- LINKED STACK MENU ---\n1.Push 2.Pop 3.Display 4.Back\nEnter choice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
        if (choice == 4) {
            /* cleanup */
            while (top) { struct LNode *t = top; top = top->next; free(t); }
            break;
        }
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                if (scanf("%d", &value) == 1) linked_stack_push(&top, value);
                while (getchar() != '\n');
                break;
            case 2: linked_stack_pop(&top); break;
            case 3: linked_stack_display(top); break;
            default: printf("Invalid Choice\n"); break;
        }
    }
}

/* ---------- Linked queue demo (no nested functions) ---------- */
struct QNode {
    int data;
    struct QNode *next;
};

static int linked_queue_insert(struct QNode **front_ref, struct QNode **rear_ref, int element, int *count, int max_size) {
    if (*count == max_size) { printf("Linked Queue Overflow!\n"); return 0; }
    struct QNode *newnode = (struct QNode*)malloc(sizeof(struct QNode));
    if (!newnode) { printf("Memory allocation failed\n"); return 0; }
    newnode->data = element;
    newnode->next = NULL;
    if (*front_ref == NULL) *front_ref = *rear_ref = newnode;
    else { (*rear_ref)->next = newnode; *rear_ref = newnode; }
    (*count)++;
    printf("Inserted element: %d\n", element);
    return 1;
}

static void linked_queue_delete(struct QNode **front_ref, struct QNode **rear_ref, int *count) {
    if (*front_ref == NULL) { printf("Queue Underflow! Queue is empty.\n"); return; }
    struct QNode *temp = *front_ref;
    printf("Deleted element: %d\n", temp->data);
    *front_ref = (*front_ref)->next;
    if (*front_ref == NULL) *rear_ref = NULL;
    free(temp);
    (*count)--;
}

static void linked_queue_peek(struct QNode *front) {
    if (front == NULL) printf("Queue is empty.\n");
    else printf("Front element = %d\n", front->data);
}

static void linked_queue_display(struct QNode *front) {
    if (front == NULL) { printf("Queue is empty.\n"); return; }
    struct QNode *temp = front;
    printf("Front: ");
    while (temp) {
        printf("[%d]", temp->data);
        if (temp->next) printf(" -> ");
        temp = temp->next;
    }
    printf(" :Rear\n");
}

void linked_queue_demo(void) {
    struct QNode *front = NULL, *rear = NULL;
    int MAX_SIZE = 0, count = 0;
    printf("Enter the size of Linked Queue: ");
    if (scanf("%d", &MAX_SIZE) != 1 || MAX_SIZE <= 0) { while (getchar() != '\n'); printf("Invalid size\n"); return; }
    while (getchar() != '\n');

    int choice, element;
    while (1) {
        printf("\n--- LINKED QUEUE MENU ---\n1.Insert\n 2.Delete\n 3.Peek\n 4.Display\n 5.Node count\n 6.Back\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                if (scanf("%d", &element) == 1) linked_queue_insert(&front, &rear, element, &count, MAX_SIZE);
                while (getchar() != '\n');
                break;
            case 2: linked_queue_delete(&front, &rear, &count); break;
            case 3: linked_queue_peek(front); break;
            case 4: linked_queue_display(front); break;
            case 5: printf("Number of nodes = %d\n", count); break;
            case 6:
                /* cleanup */
                while (front) { struct QNode *t = front; front = front->next; free(t); }
                rear = NULL; count = 0;
                return;
            default: printf("Invalid choice!\n"); break;
        }
    }
}

void sum_avg_stack_demo(void) {
    enum { MAX = 100 };
    int stack[MAX];
    int top = -1;
    int choice, val;

    while (1) {
        printf("\n--- SUM & AVERAGE STACK MENU ---\n");
        printf("1. Push element\n");
        printf("2. Calculate sum & average\n");
        printf("3. Back\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:  // PUSH
                if (top == MAX - 1) {
                    printf("Stack Overflow! Cannot insert more.\n");
                } else {
                    printf("Enter value to push: ");
                    if (scanf("%d", &val) == 1) {
                        stack[++top] = val;
                        printf("%d Pushed.\n", val);
                    }
                    while (getchar() != '\n');
                }
                break;

            case 2:  // CALCULATE SUM & AVERAGE
                if (top == -1) {
                    printf("Stack is empty.\n");
                } else {
                    int sum = 0;
                    for (int i = 0; i <= top; i++) {
                        sum += stack[i];
                    }
                    printf("Sum = %d\n", sum);
                    printf("Average = %.2f\n", (float)sum / (top + 1));
                }
                break;

            case 3:  // BACK
                return;

            default:
                printf("Invalid choice!\n");
        }
    }
}



/* ---------- Find minimum in stack demo ---------- */
void findmin_stack_demo(void) {
    enum { MAX = 100 };
    int stack[MAX]; int top = -1;
    int choice; int val;

    while (1) {
        printf("\n1.Push\n 2.Findminimum\n 3.Back\nEnter the choice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
        switch (choice) {
            case 1:
                printf("Enter the element to be pushed: ");
                if (scanf("%d", &val) == 1) {
                    if (top < MAX - 1) stack[++top] = val;
                    else printf("Stack overflow (max %d)\n", MAX);
                }
                while (getchar() != '\n');
                break;
            case 2:
                if (top == -1) { printf("Stack is empty\n"); }
                else {
                    int min = stack[0];
                    for (int i = 1; i <= top; i++) if (stack[i] < min) min = stack[i];
                    printf("Minimum element = %d\n", min);
                }
                break;
            case 3: return;
            default: printf("Invalid choice\n"); break;
        }
    }
}

/* ---------- Dynamic array stack demo (no nested functions) ---------- */
void dynamic_stack_demo(void) {
    int *stack = NULL;
    int top = -1;
    int maxsize = 0;
    printf("Enter the size of array: ");
    if (scanf("%d", &maxsize) != 1 || maxsize <= 0) { while (getchar() != '\n'); printf("Invalid size\n"); return; }
    while (getchar() != '\n');
    stack = (int *)malloc(maxsize * sizeof(int));
    if (!stack) { printf("Memory allocation failed\n"); return; }

    int choice;
    while (1) {
        printf("\nDynamic Stack Menu:\n 1.Push\n 2.Pop\n 3.Display\n 4.back\nEnter choice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
        switch (choice) {
            case 1: {
                if (top == maxsize - 1) { printf("Stack is full\n"); }
                else {
                    int item;
                    printf("Enter the item: ");
                    if (scanf("%d", &item) == 1) {
                        stack[++top] = item;
                    } else {
                        while (getchar() != '\n');
                        printf("Invalid input\n");
                    }
                }
                while (getchar() != '\n');
                break;
            }
            case 2: {
                if (top == -1) { printf("Stack is underflow\n"); }
                else {
                    int v = stack[top--];
                    printf("Popped: %d\n", v);
                }
                break;
            }
            case 3:
                if (top == -1) { printf("Stack is underflow\n"); }
                else {
                    for (int i = top; i >= 0; i--) printf("%d\n", stack[i]);
                }
                break;
            case 4:
                free(stack);
                return;
            default: printf("Invalid choice\n"); break;
        }
    }
}

int main(void) {
    int choice = 0;
    while (1) {
        printf("\n=== MERGED STACK & QUEUE DEMOS ===\n");
        printf("1. Palindrome (stack)\n2. Linked Stack Demo\n3. Linked Queue Demo\n4. Sum & Avg (stack)\n5. Find Min (stack)\n6. Dynamic Stack Demo\n7. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
        while (getchar() != '\n');
        switch (choice) {
            case 1: palindrome_using_stack(); break;
            case 2: linked_stack_demo(); break;
            case 3: linked_queue_demo(); break;
            case 4: sum_avg_stack_demo(); break;
            case 5: findmin_stack_demo(); break;
            case 6: dynamic_stack_demo(); break;
            case 7: printf("Exiting.\n"); return 0;
            default: printf("Invalid choice\n"); break;
        }
    }
    return 0;
}