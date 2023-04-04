#include<stdio.h>


struct elector {
    char *name;
    long cin_num;
    int choice;
    struct elector *next;
};

typedef struct elector *T_Elector;


int main()
{

}

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


//test github
