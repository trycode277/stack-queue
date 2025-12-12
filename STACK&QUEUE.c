#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Merged programs 1.c - 6.c as function blocks.
  - palindrome_using_stack()
  - linked_stack_demo()
  - linked_queue_demo()
  - sum_avg_stack_demo()
  - findmin_stack_demo()
  - dynamic_stack_demo()

  Top-level menu calls each demo. Each demo returns to main menu when done.
*/

void palindrome_using_stack(void) {
	enum { MAX = 100 };
	char str[MAX];
	char stack[MAX];
	int top = -1;

	printf("Enter a string: ");
	if (!fgets(str, sizeof(str), stdin)) return;
	size_t len = strlen(str);
	if (len > 0 && str[len-1] == '\n') str[len-1] = '\0';

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

/* --- Linked list based stack demo (from 2.c) --- */
void linked_stack_demo(void) {
	struct node { int data; struct node *next; };
	struct node *top = NULL;

	void push(int x) {
		struct node *newnode = (struct node*)malloc(sizeof(struct node));
		if (newnode == NULL) { printf("Memory not allocated\n"); return; }
		newnode->data = x;
		newnode->next = top;
		top = newnode;
		printf("%d pushed\n", x);
	}

	void pop(void) {
		if (top == NULL) { printf("Stack Underflow\n"); return; }
		struct node *temp = top;
		printf("Popped: %d\n", top->data);
		top = top->next;
		free(temp);
	}

	void display(void) {
		if (top == NULL) { printf("Stack is Empty\n"); return; }
		struct node *p = top;
		printf("Stack elements: ");
		while (p != NULL) { printf("%d ", p->data); p = p->next; }
		printf("\n");
	}

	int choice = 0, value;
	while (1) {
		printf("\n--- LINKED STACK MENU ---\n1.Push 2.Pop 3.Display 4.Back\nEnter choice: ");
		if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
		if (choice == 4) { while (top) { struct node *t = top; top = top->next; free(t); } break; }
		switch (choice) {
			case 1:
				printf("Enter value to push: ");
				if (scanf("%d", &value) == 1) push(value);
				while (getchar() != '\n');
				break;
			case 2: pop(); break;
			case 3: display(); break;
			default: printf("Invalid Choice\n"); break;
		}
	}
}

/* --- Linked queue demo (from 3.c) --- */
void linked_queue_demo(void) {
	struct node { int data; struct node *next; };
	struct node *front = NULL, *rear = NULL;
	int MAX_SIZE = 0, count = 0;
	printf("Enter the size of Linked Queue: ");
	if (scanf("%d", &MAX_SIZE) != 1 || MAX_SIZE <= 0) { while (getchar() != '\n'); printf("Invalid size\n"); return; }
	while (getchar() != '\n');

	void insert(int element) {
		if (count == MAX_SIZE) { printf("Linked Queue Overflow! \n"); return; }
		struct node *newnode = (struct node*) malloc(sizeof(struct node));
		if (!newnode) { printf("Memory allocation failed\n"); return; }
		newnode->data = element; newnode->next = NULL;
		if (front == NULL) front = rear = newnode; else { rear->next = newnode; rear = newnode; }
		count++; printf("Inserted element:%d\n", element);
	}

	void delete(void) {
		if (front == NULL) { printf("Queue Underflow! Queue is empty.\n"); return; }
		struct node *temp = front; printf("Deleted element:%d\n", temp->data);
		front = front->next; if (front == NULL) rear = NULL; free(temp); count--; }

	void peek(void) { if (front == NULL) printf("Queue is empty.\n"); else printf("Front element = %d\n", front->data); }

	void display(void) { if (front == NULL) { printf("Queue is empty.\n"); return; } struct node *temp = front; printf("Front: "); while (temp) { printf("[%d]", temp->data); if (temp->next) printf(" -> "); temp = temp->next; } printf(" :Rear\n"); }

	void cleanup(void) { while (front) { struct node *t = front; front = front->next; free(t); } rear = NULL; count = 0; }

	int choice, element;
	while (1) {
		printf("\n--- LINKED QUEUE MENU ---\n1.Insert 2.Delete 3.Peek 4.Display 5.Node count 6.Back\nEnter your choice: ");
		if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
		switch (choice) {
			case 1: printf("Enter element to insert: "); if (scanf("%d", &element) == 1) insert(element); while (getchar() != '\n'); break;
			case 2: delete(); break;
			case 3: peek(); break;
			case 4: display(); break;
			case 5: printf("Number of nodes = %d\n", count); break;
			case 6: cleanup(); return;
			default: printf("Invalid choice!\n"); break;
		}
	}
}

/* --- Sum and average demo (from 4.c) --- */
void sum_avg_stack_demo(void) {
	enum { MAX = 100 };
	int stack[MAX]; int top = -1;
	void push_fn(int val) { if (top < MAX - 1) stack[++top] = val; }

	push_fn(10); push_fn(20); push_fn(30);
	if (top == -1) { printf("Stack empty\n"); return; }
	int sum = 0;
	for (int i = 0; i <= top; i++) sum += stack[i];
	printf("Sum = %d\n", sum);
	printf("Average = %.2f\n", (float)sum / (top + 1));
}

/* --- Find minimum in stack demo (from 5.c) --- */
void findmin_stack_demo(void) {
	enum { MAX = 100 };
	int stack[MAX]; int top = -1;
	void push(int val) { if (top < MAX - 1) stack[++top] = val; }
	void findMin(void) {
		if (top == -1) { printf("Stack is empty\n"); return; }
		int min = stack[0];
		for (int i = 1; i <= top; i++) if (stack[i] < min) min = stack[i];
		printf("Minimum element = %d\n", min);
	}

	int choice; int val;
	while (1) {
		printf("\n1.push 2.findmin 3.back\nEnter the choice: ");
		if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
		switch (choice) {
			case 1: printf("enter the element to be pushed: "); if (scanf("%d", &val) == 1) push(val); while (getchar() != '\n'); break;
			case 2: findMin(); break;
			case 3: return;
			default: printf("Invalid choice\n"); break;
		}
	}
}

/* --- Dynamic array stack demo (fixed from 6.c) --- */
void dynamic_stack_demo(void) {
	int *stack = NULL;
	int top = -1;
	int maxsize = 0;
	printf("enter the size of array: ");
	if (scanf("%d", &maxsize) != 1 || maxsize <= 0) { while (getchar() != '\n'); printf("Invalid size\n"); return; }
	while (getchar() != '\n');
	stack = (int *)malloc(maxsize * sizeof(int));
	if (!stack) { printf("Memory allocation failed\n"); return; }

	void push(void) {
		if (top == maxsize - 1) { printf("stack is full\n"); return; }
		int item;
		printf("enter the item: ");
		if (scanf("%d", &item) != 1) { while (getchar() != '\n'); printf("Invalid input\n"); return; }
		stack[++top] = item;
		while (getchar() != '\n');
	}

	int pop(void) {
		if (top == -1) { printf("stack is underflow\n"); return -1; }
		return stack[top--];
	}

	void display(void) {
		if (top == -1) { printf("stack is underflow\n"); return; }
		for (int i = top; i >= 0; i--) printf("%d\n", stack[i]);
	}

	int choice;
	while (1) {
		printf("\nDynamic Stack Menu: 1.push 2.pop 3.display 4.back\nEnter choice: ");
		if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); break; }
		switch (choice) {
			case 1: push(); break;
			case 2: { int v = pop(); if (v != -1) printf("Popped: %d\n", v); } break;
			case 3: display(); break;
			case 4: free(stack); return;
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

