#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elector{
  char name[100];
  long cin_num;
  int choice;
  struct elector* next;
} elector;

typedef elector *T_Elector;
/*
Authors: Abid Gurbanov , Ziraddin Ismayilov
*/
void decomposelist(T_Elector head, T_Elector *left, T_Elector *right, T_Elector *white);
void merge_sort(T_Elector *head) ;
void freelist(T_Elector head) ;
int countLR(T_Elector head) ;
T_Elector mergelists(T_Elector, T_Elector);
void merge(T_Elector *head, T_Elector left, T_Elector right) ;

int main()
{



}
//Ziraddin ------------***********************************
T_Elector creationelector(void){
    elector *root = (elector*)malloc(sizeof(elector));
    return root;
}
void displaylist(T_Elector root){
    elector* cursor = root;
    while(cursor->next != NULL){
        printf("%s\n", cursor->name);
    }
}
void addelector(T_Elector root, char name[], long id, int choice){
    elector *new_elector = (elector*)malloc(sizeof(elector));
    strcpy(new_elector->name, name);
    new_elector->cin_num = id;
    new_elector->choice = choice;
    new_elector->next = NULL;
    if (root == NULL) {
        root = new_elector;
    } 
    else {
        T_Elector current = root;
        while (current->next != NULL && strcmp(name, current->next->name) > 0) {
            current = current->next;
        }
        new_elector->next = current->next;
    }
}
int countelector(T_Elector root){
    int count = 0;
    elector* cursor = root;
    while(cursor->next != NULL){
        count++;
    }
    return count;
}
int findelector(T_Elector root, long id){
    elector* cursor = root;
    while(cursor->next != NULL){
        if(cursor->cin_num == id){
            return 1;
        }
    }
    return 0;
}
void deletelector(T_Elector root, long id){
    elector* cursor = root;
    while(cursor->next->next != NULL){
        if(cursor->next->cin_num == id){
            cursor = cursor->next->next;
        }
    }
}




//Abid -------------***************************************
void decomposelist(T_Elector head, T_Elector *left, T_Elector *right, T_Elector *white) {
    *left = NULL;
    *right = NULL;
    *white = NULL;
     
    T_Elector curr = head;
    while (curr != NULL) {
        if (curr->choice == 1 || curr->choice == 3) {
            addelector(left, curr->name, curr->cin_num, curr->choice);
        } else if (curr->choice == 2 || curr->choice == 4) {
            addelector(right, curr->name, curr->cin_num, curr->choice);
        } else {
            addelector(white, curr->name, curr->cin_num, curr->choice);
        }
        curr = curr->next;
    }
}
void merge(T_Elector *head, T_Elector left, T_Elector right) {
    T_Elector curr = *head;
    T_Elector left_curr = left;
    T_Elector right_curr = right;
    while (left_curr != NULL && right_curr != NULL) {
        if (left_curr->cin_num <= right_curr->cin_num) {
            curr->next = left_curr;
            left_curr = left_curr->next;
        } else {
            curr->next = right_curr;
            right_curr = right_curr->next;
        }
        curr = curr->next;
    }
    if (left_curr == NULL) {
        curr->next = right_curr;
    } else {
        curr->next = left_curr;
    }
    *head = (*head)->next;
}

void merge_sort(T_Elector *head) {

    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    T_Elector slow = *head;
    T_Elector fast = (*head)->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    T_Elector left = *head;
    T_Elector right = slow->next;
    slow->next = NULL;
    merge_sort(&left);
    merge_sort(&right);
    merge(head, left, right);
}

void freelist(T_Elector head) {
    T_Elector curr = head;
    while (curr != NULL) {
        T_Elector next = curr->next;
        free(curr);
        curr = next;
    }
}

int countLR(T_Elector head) {
    int count = 0;
    while (head != NULL) {
        if (head->choice == 1 || head->choice == 3) {
            count++;
        }
        head = head->next;
    }
    return count;
}
T_Elector mergelists(T_Elector left, T_Elector right) {
    T_Elector merged_list = NULL;
    T_Elector curr = NULL;

    while (left != NULL && right != NULL) {
        if (left->cin_num <= right->cin_num) {
            if (merged_list == NULL) {
                merged_list = left;
                curr = merged_list;
            } else {
                curr->next = left;
                curr = curr->next;
            }
            left = left->next;
        } else {
            if (merged_list == NULL) {
                merged_list = right;
                curr = merged_list;
            } else {
                curr->next = right;
                curr = curr->next;
            }
            right = right->next;
        }
    }

    if (left == NULL) {
        if (merged_list == NULL) {
            merged_list = right;
        } else {
            curr->next = right;
        }
    } else {
        if (merged_list == NULL) {
            merged_list = left;
        } else {
            curr->next = left;
        }
    }

    return merged_list;
}

