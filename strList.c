#include "StrList.h"
#include <string.h>


typedef struct _node {
    char *_data;
    struct _node *_next;
} Node;

struct _StrList {
    Node* _head;
    size_t _size;
};


Node* Node_alloc(char* data,
				 Node* next) {
	Node* p= (Node*)malloc(sizeof(Node));
	p->_data= data;
	p->_next= next;
	return p;
}

void Node_free(Node* node) {
	free(node);
}

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc(){

    StrList* p = (StrList*)malloc(sizeof(StrList));

    p->_head = NULL;
    p->_size = 0;

    return p;

}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* StrList){
    
    if(StrList == NULL) return;

    Node* p1 = StrList->_head;
    Node* p2;
    while(p1 != NULL){
        p2=p1;
        p1=p1->_next;
        Node_free(p2);
    }
    free(StrList);
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList){
    return StrList->_size;
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList, const char* data){
    
    Node* p = Node_alloc(data, NULL);
    if(StrList->_head == NULL) {
        StrList->_head = p;
        ++(StrList->_size);
        free(p);
    }
    else{
         Node* current = StrList->_head;
    while(current->_next != NULL){
        current=current->_next;
        }

        current->_next=p;
    }
    ++(StrList->_size);
    free(p);
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* StrList, const char* data,int index) {
    Node* p = Node_alloc(data, NULL);
    if(index == 0){
        p->_next = StrList->_head;
        StrList->_head = p;
        ++(StrList->_size);
        free(p);
    }
    else{
        int i=0;
        Node* current = StrList->_head;
        while(i < index -1 && current->_next != NULL){
            current=current->_next;
            i++;
            }
        if(current != NULL){
            Node* temp = current->_next;
            p->_next = temp;
            current->_next = p;
            ++(StrList->_size);
            }
        else {free(p);}
    }
}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList){
    return StrList->_head->_data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList){
    Node* p = StrList->_head;
    while(p != NULL){
        printf("(%.2f)->" , p->_data);
        p=p->_next;
    }
    printf("|| size:%zu\n", StrList->_size);
    free(p);
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* Strlist,int index){
    if(index==0){StrList_print(Strlist);}
    else{
        int counter = 0;
        Node* p = Strlist->_head;
        while(p != NULL && counter < index - 1){
            p=p->_next;
            counter++;
        }
        if(p != NULL){
            StrList_print(p);
        }
        else{
            free(p);
        }
    }
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* Strlist){
    // check this again
    Node* p = Strlist->_head;
    int ans = 0;
    while(p != NULL){
        ans+=strlen(p->_data);
        p=p->_next;
    }
    free(p);
    return ans;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* StrList, const char* data){
    Node* p = StrList->_head;
    int ans = 0;
    while(p!=NULL){
        if(strcmp(p->_data,data) == 0){
            ans++;
        }
        p=p->_next;
    }
    free(p);
    return ans;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data){
    //check this again
    Node* current = StrList->_head;
    Node* prev = NULL;

    if(strcmp(current->_data,data) == 0){
        StrList->_head = current->_next;
        free(current);
    }
    else{
        while(current != NULL){
            if(strcmp(current->_data,data) != 0){
                prev->_next = current->_next;
            }
            else{
                prev->_next=current;
                current=current->_next;
            }
        }
        free(current);
        free(prev);
    }
}
/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index){
    if(index==0){StrList_remove(StrList, StrList->_head->_data);}
    //check this again
    Node* p = StrList->_head;
    int i=0;
    while(p != NULL && i < index -1){
        p=p->_next;
        i++;
    }
    if(i == index){
        StrList_remove(p,p->_data);
    }
    free(p);
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    const equal =0, not_equal = 1;

    const Node* p1 = StrList1->_head;
    const Node* p2 = StrList2->_head;
    while(p1 != NULL){
        if(p2 == NULL || strcmp(p1->_data,p2->_data) == not_equal){
            return not_equal;
        }
        p1=p1->_next;
        p2=p2->_next;
    }
    if(p2 != NULL){
        free(p1);
        free(p2);
        return not_equal;
        }
    free(p1);
    free(p2);
    return equal;
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* StrList){
    //TODO: check this again
    //StrList* clone = StrList_alloc();
    const Node* p = StrList->_head;
    //Node** copy = &(clone->_head);
    //clone->_size=StrList->_size;
    while(p != NULL){
      //  *copy = Node_alloc(p->_data,NULL);
        p = p->_next;
       // copy = &((*copy)->_next);
    }
    //return clone;
}


/*
 * Reverces the given StrList. 
 */
void StrList_reverse( StrList* StrList){
    Node* prev = NULL;
    Node* current = StrList->head;
    Node* next = NULL;

    
}