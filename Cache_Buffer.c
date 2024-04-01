#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 5 // the maximum number of times an address can be used, if it is greater than this threshold, the address is moved to the front of the cache buffer
#define L 4 // cache buffer size that is the maximum number of nodes in the cache buffer
#define N 10 // address string size

typedef struct Node // Node structure for the cache buffer
{
    char *address; // address of the node
    struct Node *next; // next node
    struct Node *previous; // previous node
    int counter; // counter for the node that shows how many times the address is used
} NODE;
NODE *head; // head of the cache buffer

/*
@brief creates a new node, allocates memory for it and returns the address of the new node. It also initializes the counter to 1, next and previous to NULL.

@return returns the address of the new node.
*/
NODE *createNode();

/*
@brief checks if the given address is already in the cache buffer. If it is, it returns the address of the node that contains the address. If it is not, it returns NULL.

@param address the address that is going to be checked if it is in the cache buffer.

@return returns the address of the node that contains the address if it is in the cache buffer. If it is not, it returns NULL.
*/
NODE *checkNodeIfExist(char *address);

/*
@brief prints the addresses in the cache buffer and their counters.

@return 
*/
void printNodes();

/*
@brief inserts a new node at the front of the cache buffer. It also initializes the address of the new node with the given address.

@param p the address of the new node.
@param address the address that is going to be assigned to the new node.

@return
*/
void insertNodeAtFront(NODE *p, char *address);

/*
@brief moves the given node to the front of the cache buffer. It also updates the previous and next pointers of the nodes that are before and after the given node.

@param p the address of the node that is going to be moved to the front of the cache buffer.

@return
*/
void moveNodeToFront(NODE *p);

/*
@brief deletes the node at the end of the cache buffer. It also updates the previous and next pointers of the nodes that are before and after the node that is going to be deleted.

@return
*/
void deleteNodeAtEnd();

/*
@brief deletes all the nodes in the cache buffer.

@return
*/
void deleteAllNodes();

/*
@brief counts the number of nodes in the cache buffer.

@return returns the number of nodes in the cache buffer.
*/
int nodeCounter();

int main()
{
    char *address; // address string
    char key, choice; // key for the menu, choice for the user's choice
    address = (char *)malloc(N * sizeof(char)); // allocate memory for the address string

    FILE *file; // file pointer

    do // menu for the user to choose the address input method
    {
        printf("1- Enter the address\n2- Read the address from the file\nEnter to choose: ");
        scanf(" %c", &key);
    } while (key != '1' && key != '2'); // check if the user entered a valid key

    switch (key) // switch case for the user's choice
    {
    case '1': // if the user chooses to enter the address
        do // do-while loop for the user to enter the choice to continue or exit
        {
            printf("Enter the address: ");
            scanf("%s", address); // get the address from the user

            NODE *temp = checkNodeIfExist(address); // check if the address is in the cache buffer
            if (temp == NULL) // if the address is not in the cache buffer
            {
                NODE *node = createNode(); // create a new node
                insertNodeAtFront(node, address); // insert the new node at the front of the cache buffer
                if (nodeCounter() > L) // if the number of nodes in the cache buffer is greater than the cache buffer size
                    deleteNodeAtEnd(); // delete the node at the end of the cache buffer
            }
            else // if the address is in the cache buffer
            {
                temp->counter++; // increment the counter of the node that contains the address
                if (temp->counter > T) // if the counter of the node that contains the address is greater than the counter threshold
                    moveNodeToFront(temp); // move the node to the front of the cache buffer
            }

            printNodes(); // print the addresses in the cache buffer and their counters

            do // do-while loop for the user to enter the choice to clear the cache buffer, continue or exit
            {
                printf("\nDo you want to clear the cache buffer?\nYes [1]\nNo [2]\nChoice: ");
                scanf(" %c", &choice); // get the choice from the user
            } while (choice != '1' && choice != '2'); // check if the user entered a valid choice

            if (choice == '1') // if the user chooses to clear the cache buffer
            {
                deleteAllNodes(); // delete all the nodes in the cache buffer
                printf("\nAll nodes have been cleared!"); // print a message to inform the user
            }

            do // do-while loop for the user to enter the choice to continue or exit
            {
                printf("\nContinue [1]\nExit [2]\nChoice: ");
                scanf(" %c", &choice); // get the choice from the user
            } while (choice != '1' && choice != '2'); // check if the user entered a valid choice
        } while (choice == '1'); // check if the user wants to continue or exit

        break; // break the switch case

    case '2': // if the user chooses to read the address from the file
        do // do-while loop for the user to enter the choice to continue or exit
        {
            file = fopen("addresses.txt", "r"); // open the file that contains the addresses

            if (file == NULL) // if the file cannot be opened
            {
                printf("Error opening the file.\n");
                exit(1); // exit the program
            }

            while (fscanf(file, "%s", address) != EOF) // read the addresses from the file
            {
                NODE *temp = checkNodeIfExist(address); // check if the address is in the cache buffer
                if (temp == NULL) // if the address is not in the cache buffer
                {
                    NODE *node = createNode(); // create a new node
                    insertNodeAtFront(node, address); // insert the new node at the front of the cache buffer
                    if (nodeCounter() > L) // if the number of nodes in the cache buffer is greater than the cache buffer size
                        deleteNodeAtEnd(); // delete the node at the end of the cache buffer
                }
                else // if the address is in the cache buffer
                {
                    temp->counter++; // increment the counter of the node that contains the address
                    if (temp->counter > T) // if the counter of the node that contains the address is greater than the counter threshold
                        moveNodeToFront(temp); // move the node to the front of the cache buffer
                }
            }
            printNodes(); // print the addresses in the cache buffer and their counters
            fclose(file); // close the file

            do // do-while loop for the user to enter the choice to clear the cache buffer, continue or exit
            {
                printf("\nDo you want to clear the cache buffer?\nYes [1]\nNo [2]\nChoice: ");
                scanf(" %c", &choice); // get the choice from the user
            } while (choice != '1' && choice != '2'); // check if the user entered a valid choice

            if (choice == '1') // if the user chooses to clear the cache buffer
            {
                deleteAllNodes(); // delete all the nodes in the cache buffer
                printf("\nAll nodes have been cleared!"); // print a message to inform the user
            }

            do // do-while loop for the user to enter the choice to continue or exit
            {
                printf("\nContinue [1]\nExit [2]\nChoice: "); 
                scanf(" %c", &choice); // get the choice from the user
            } while (choice != '1' && choice != '2'); // check if the user entered a valid choice
        } while (choice == '1'); // check if the user wants to continue or exit

        break; // break the switch case
    }

    free(address); // free the memory allocated for the address string
    return 0;
}

NODE *createNode()
{
    NODE *p; // create a new node
 
    p = (NODE *)malloc(sizeof(NODE)); // allocate memory for the new node
    p->address = (char *)malloc(N * sizeof(char)); // allocate memory for the address of the new node
    p->counter = 1; // initialize the counter of the new node to 1

    if (p == NULL) // if the new node cannot be created
    {
        printf("Node cannot be created!");
        exit(0); // exit the program
    }
    p->next = NULL; // initialize the next pointer of the new node to NULL
    p->previous = NULL; // initialize the previous pointer of the new node to NULL

    return p; // return the address of the new node
}

NODE *checkNodeIfExist(char *address)
{
    NODE *current = head; // set the current node to the head of the cache buffer

    while (current != NULL) // while the current node is not NULL
    {
        if (strcmp(current->address, address) == 0) // if the address of the current node is equal to the given address
        {
            return current; // return the address of the current node
        }
        current = current->next; // set the current node to the next node
    }
    return NULL; // return NULL
}

void printNodes()
{
    NODE *tmp = head; // set the temporary node to the head of the cache buffer

    printf("\n");
    while (tmp != NULL) // while the temporary node is not NULL
    {
        if (tmp->next == NULL) // if the next node of the temporary node is NULL
            printf("%s (%d)\n", tmp->address, tmp->counter); // print the addresses in the cache buffer and their counters
        else
            printf("%s (%d) -> ", tmp->address, tmp->counter);

        tmp = tmp->next; // set the temporary node to the next node
    }
}

void insertNodeAtFront(NODE *p, char *address)
{
    strcpy(p->address, address); // copy the given address to the address of the new node
    if (head == NULL) // if the head of the cache buffer is NULL
        head = p; // set the head of the cache buffer to the new node
    else
    {
        head->previous = p; // set the previous pointer of the head of the cache buffer to the new node
        p->next = head; // set the next pointer of the new node to the head of the cache buffer
        head = p; // set the head of the cache buffer to the new node
    }
}

void moveNodeToFront(NODE *p)
{
    if (p == NULL || p->previous == NULL) // if the given node is NULL or the previous pointer of the given node is NULL
        return; // return
    else 
    {
        if (p->previous != NULL) // if the previous pointer of the given node is not NULL
        {
            p->previous->next = p->next; // set the next pointer of the previous node of the given node to the next node of the given node
        }
        if (p->next != NULL) // if the next pointer of the given node is not NULL
        {
            p->next->previous = p->previous; // set the previous pointer of the next node of the given node to the previous node of the given node
        }
        head->previous = p; // set the previous pointer of the head of the cache buffer to the given node
        p->next = head; // set the next pointer of the given node to the head of the cache buffer
        p->previous = NULL; // set the previous pointer of the given node to NULL
        head = p; // set the head of the cache buffer to the given node
    }
}

void deleteNodeAtEnd()
{
    if (head == NULL) // if the head of the cache buffer is NULL
    {
        return; // return
    } 

    NODE *last = head; // set the last node to the head of the cache buffer
    while (last->next != NULL) // while the next node of the last node is not NULL
    {
        last = last->next; // set the last node to the next node
    }
    if (last->previous != NULL) // if the previous pointer of the last node is not NULL
    {
        last->previous->next = NULL; // set the next pointer of the previous node of the last node to NULL
    }
    else // if the previous pointer of the last node is NULL
    {
        head = NULL; // set the head of the cache buffer to NULL
    }

    free(last->address); // free the memory allocated for the address of the last node
    free(last); // free the memory allocated for the last node
}

void deleteAllNodes()
{
    NODE *tmp = head; // set the temporary node to the head of the cache buffer
    while (tmp != NULL) // while the temporary node is not NULL
    {
        NODE *next = tmp->next; // set the next node to the next node of the temporary node
        free(tmp->address); // free the memory allocated for the address of the temporary node
        free(tmp); // free the memory allocated for the temporary node
        tmp = next; // set the temporary node to the next node
    }
    head = NULL; // set the head of the cache buffer to NULL
}

int nodeCounter()
{
    int count = 0; // counter for the number of nodes in the cache buffer
    NODE *current = head; // set the current node to the head of the cache buffer

    while (current != NULL) // while the current node is not NULL
    {
        count++; // increment the counter
        current = current->next; // set the current node to the next node
    }

    return count; // return the counter
}
