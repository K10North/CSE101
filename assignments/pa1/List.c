
/***
* Kristen North 
* krnorth 
* 2026 Winter CSE101 PA1 
* List.c 
* Implementation for List.h 
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj {

    int data;
    struct NodeObj* next;   
    struct NodeObj* prev;

} NodeObj;

typedef struct ListObj {

    int length;
    int index;
    struct NodeObj* cursor;
    struct NodeObj* front;
    struct NodeObj* back;

} ListObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode(int a){//constructor node
    Node n = malloc(sizeof(NodeObj));
    if(!n){//mem check
        perror( "ListADT Error : newNode() : Memory Allocation\n");
        return NULL;
    }
    n->data=a;//set all fields
    n->next=NULL;
    n->prev=NULL;
    return n;
}

void freeNode(Node* pN){//destructor node
    if(pN || *pN){//node is valid
        free(*pN);//free data
        *pN = NULL;//update node data
        return;
    }
}

List newList(void){ // Creates and returns a new empty List.
    List l = malloc(sizeof(ListObj));//allocate mem
    assert(l!=NULL);//null check

    l->back= NULL; //set all fields
    l->cursor= NULL;
    l->front= NULL;
    l->index= -1;
    l->length= 0;
    return l;
} 

void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        List L = *pL;
        clear(L); //free all nodes 
        free(L);//free list
        *pL = NULL;
    }
} // Frees all heap memory associated with *pL, and sets
// *pL to NULL.

// Access functions -----------------------------------------------------------
int length(List L){
    assert(L !=NULL); //null check
    return L->length;
} // Returns the number of elements in L.

int front(List L){
    assert(L !=NULL); //null check
    if(L->length <= 0){//empty check
        perror("ListADT Error : front() : List Empty\n");
        exit(1);
    }
    return L->front->data;
} // Returns front element of L. Pre: length()>0

int back(List L){
    assert(L !=NULL); //null check
    if(L->length <= 0){ //empty check
         perror("ListADT Error : back() : List Empty\n");
        exit(1);
    }
    return L->back->data;
} // Returns back element of L. Pre: length()>0

int get(List L){
    assert(L !=NULL); //null check
    if(L->length<=0){ //empty check
         perror("ListADT Error : get() : List Empty\n");
        exit(1);
    }
    if(L->index < 0){ 
        perror("ListADT Error : get() : Undefined Index");
        exit(1);
    }
    return L->cursor->data;
} // Returns cursor element of L. Pre: length()>0, index()>=0

bool equals(List A, List B){
    if (A == NULL && B == NULL) return true;//both null

    if (A->length == 0 && B->length == 0) return true;//both empty

    if (A == NULL || B == NULL) return false; //1 is null

    if (A->length != B->length) return false;//dif length

    Node a = A->front;//temp nodes as current nodes
    Node b = B->front;

    while (a != NULL) {//a is valid
        if (a->data != b->data) return false;//dif data
        a = a->next;//incr nodes
        b = b->next;
    }
        return true;
} // Returns 1 iff Lists A and B contain the same
// sequence of elements, returns 0 otherwise.


// Manipulation procedures ----------------------------------------------------

void clear(List L){
    assert(L != NULL);
    
    while (L->length > 0) {//delete front until empty
        deleteFront(L);
    }
    
    L->cursor = NULL;//reset fields
    L->index = -1;
} // Resets L to its original empty state.

int position(List L){
    assert(L != NULL);//empty check
    
    if (L->cursor == NULL) {//invalid cursor
        return -1;
    }
    return L->index;  
}

void set(List L, int x){
    assert(L !=NULL); //null check

    if(L->length<=0){ //empty check
         perror("ListADT Error : set() : List Empty\n");
        exit(1);
    }
    if(L->index < 0){
        perror("ListADT Error : set() : Undefined Index");
        exit(1);
    }

    if(!L->cursor){
        perror("ListADT Error : set() : Undefined cursor");
        exit(1);
    }

    L->cursor->data=x;//update data
} // Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0

void moveFront(List L){
    assert(L !=NULL); //null check
    if(L->length <=0){ //length check
        return;
    }
    L->cursor = L->front;//set cursor
    L->index = 0;//reset index to start
} // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.

void moveBack(List L){
    assert(L !=NULL); //null check
    if(L->length <=0){ //null length check
        perror("Empty list");
        exit(1);
    }
    L->cursor = L->back;//set cursor
    L->index = L->length - 1;//reset index to end
    // If L is non-empty, sets cursor under the back element,
}// otherwise does nothing.

void movePrev(List L){
    assert(L !=NULL); //null check
    assert(L->cursor !=NULL); //curs null check

    if(L->cursor == L->front){//curs at front
        L->cursor = NULL;//undefined curs and index
        L->index = -1;
        return;
    }
    
        L->cursor=L->cursor->prev;//move prev
        L->index--;//move index back

}
 // If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing

void moveNext(List L){
    assert(L !=NULL); //null check
    assert(L->cursor !=NULL); //curs null check

    if(L->cursor == L->back){//curs at back
        L->cursor = NULL; //undefined curs and index
        L->index = -1;
        return;
    }
    
        L->cursor=L->cursor->next;//move next
        L->index++;//inc index
    
} // If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing

void prepend(List L, int x){
    assert(L !=NULL);//null check

     Node n = newNode(x);

    assert(n !=NULL);//mem check

    if(L->length == 0){//empty list
        L->front=n;//set front back as node
        L->back=n;

    }
    else{//set node as front update next prevs
        n->next=L->front;
        L->front->prev=n;
        L->front=n;
    }
    
    if(L->cursor){
        L->index++;//inc index insert node before elems
    }
    L->length++;//inc size

} // Insert new element into L. If L is non-empty,
// insertion takes place before front element.

void append(List L, int x){
    assert(L != NULL);//null check
    
    Node n = newNode(x);
    assert(n != NULL);//mem check
    
    if(L->length == 0){//empty list
        L->back = n;//set front back as node
        L->front = n;
    } else {//set node as back update next prevs
        n->prev = L->back;
        L->back->next = n;
        L->back = n;
    }
    
    //no change in curs no change in index

    L->length++;//inc size
}// Insert new element into L. If L is non-empty,
// insertion takes place after back element.

void insertBefore(List L, int x){
        assert(L !=NULL); //null check
    if(L->cursor == NULL){//curs check
        perror("ListADT Error : insertBefore() : Cursor undefined");
        exit(1);
    }

    Node n = newNode(x);

    assert(n !=NULL); //mem check

    if(L->length <=0){//empty list
        L->back=n;//set all to node
        L->front=n;
        L->cursor=n;
        L->index=0;//reset index
    }
    if(L->index == 0|| L->cursor==L->front){//cursor at front
        n->next=L->cursor;//update next prevs
        L->cursor->prev=n;
        L->front=n;//new node as new front
    }

    else{//cursor not at front
    
        Node t = L->cursor->prev;//save prev
        n->prev=t;//update next prevs
        L->cursor->prev=n;
        n->next=L->cursor;
        t->next=n;
    }

    if(L->cursor){
        L->index++;//newnode placed b4 cursor inc index
    }
    L->length++;

} // Insert new element before cursor.
// Pre: length()>0, index()>=0

void insertAfter(List L, int x){
    assert(L !=NULL); //null check

    Node n = newNode(x);

    assert(n !=NULL);//mem check
   if(L->length <=0){//empty list
        L->back=n;//set all to node
        L->front=n;
        L->cursor=n;
        L->index=0;//reset index
    }

    if(L->index == L->length-1 || L->cursor==L->back){//cursor at back
        L->cursor->next=n;//update next prevs
        n->prev=L->cursor;
        L->back=n;//new node is back
    }
    else{//cursor not at back

        Node t = L->cursor->next;//save next node
        n->next=t;//update next prevs
        L->cursor->next=n;
        n->prev=L->cursor;
        t->prev=n;

    }
    //inserted after cursor dont update index
    L->length++;

} // Insert new element after cursor.
// Pre: length()>0, index()>=0

void deleteFront(List L){
    assert(L !=NULL); //null check


    if(length(L)<=0){
        perror("ListADT Error : deleteFront() : Empty List");
        exit(1);
    }

    if(L->front==NULL){
        perror("ListADT Error : deleteFront() : Front null");
        exit(1);
    }

    if(L->length==1){//1 node in list
        Node toDe = L->front;//save node

        if(L->cursor==toDe){//curs at front
            L->cursor=NULL;//reset curs index
            L->index=-1;
        }

        free(toDe);//delete node
        L->back=NULL;//reset all nodes
        L->front=NULL;
        L->length=0;//update size
        return;
    }
    Node toDe = L->front;
    Node nenex = toDe->next;//save next node

   if(L->cursor==toDe){//curs at front
            L->cursor=NULL;//reset curs index
            L->index=-1;
        }
    else if(L->index > 0){//if index defined
            L->index--;//dec since deleting cursor
        }
        if(nenex !=NULL){//next defined
            nenex->prev=NULL;//reset prev
        }
        L->front=nenex;//update new front
   
    free(toDe);//delete update length
    L->length--;
    
    if(L->length==0){//if list now empty
        L->back=NULL;//reset back
    }
} // Delete the front element. Pre: length()>0


void deleteBack(List L){
    assert(L !=NULL); //null check

     if(length(L)<=0){
        perror("ListADT Error : deleteBack() : Empty List");
        exit(1);
    }

    if(L->back==NULL){
        perror("ListADT Error : deleteBack() : Back null");
        exit(1);
    }
    if(L->length==1){
        if(L->cursor==L->back){//cursor = delete
            L->cursor=NULL; 
            L->index = -1;
        }
        free(L->back);//delete and reset nodes
        L->back=NULL;
        L->front=NULL;
        L->length = 0;
        return;
    }

    Node pr = L->back->prev;//save back prev

    if(L->cursor==L->back){//curs at back
            L->cursor=NULL;//reset curs index
            L->index = -1;
        }

    free(L->back);//delete back
    pr->next = NULL;//update next
    L->back = pr;//update new back
    L->length--;//update size

} // Delete the back element. Pre: length()>0

void delete(List L){
     assert(L !=NULL); //null check

    if(length(L)<=0){
        perror("ListADT Error : delete() : Empty List");
        exit(1);
    }

    if(L->cursor==NULL){
        perror("ListADT Error : deleteBack() : Cursor null");
        exit(1);
    }

    if(L->cursor==L->back){//back
        deleteBack(L);
        return;
    }
    else if(L->cursor==L->front){//front
        deleteFront(L);
        return;
    }

    else{//middle
        Node ne = L->cursor->next;//save next and prev
        Node pre = L->cursor->prev;
        ne->prev = pre;//update prev and nexts
        pre->next=ne;
        free(L->cursor);//delete node
        L->length--;//dec size

    }
    L->cursor = NULL;//undef cursor and index
    L->index  = -1;
    // Delete cursor element, making cursor undefined.
}// Pre: length()>0, index()>=0


// Other operations -----------------------------------------------------------

void printList(FILE* out, List L){
    if(out==NULL){//file null
        perror("ListADT Error : printList() : File Null");
        exit(1);
    }

    if(L==NULL){//list null
        perror("ListADT Error : printList() : List Null");
        exit(1);
    }

    if(length(L)<=0){//empty list
        return;
    }


    fprintf(out, "(");//start print

    Node n = L->front;
    assert(n !=NULL); //null check
    while(n){
        fprintf(out, "%d ", n->data);//print data
        n=n->next;//next node
    }
    fprintf(out, ")");
    
    
} // Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.

List copyList(List L){
    assert(L != NULL);//null check

    List d = newList();
    assert(d != NULL);//mem check
    
    if (L->length == 0) {//empty list
        return d;
    }
    
    Node n = L->front;//save front

    while(n){
        append(d, n->data);//add node to new list
        n = n->next;//next node
    }
    return d;
} // Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.

List join(List A, List B){
    assert(A !=NULL);//null check
    assert(B !=NULL);

    List c = newList();

    assert(c !=NULL);//mem check

    if(A->length <=0 && B->length<=0) return c;//both empty

    Node n = A->front;
    while(n){
        append(c, n->data);//copy A nodes if any
        n=n->next;
    }

    n=B->front;
    while(n){
        append(c, n->data);//copy B nodes if any
        n=n->next;
    }

    return c;

} // Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.

// split()
// Removes all elements before (in front of but not equal to) the cursor element
// in L. The cursor element in L is unchanged. Returns a new List consisting of
// all the removed elements. The cursor in the returned list is undefined.
// Pre: length(L)>0, position(L)>=0
List split(List L){
    assert(L !=NULL);

    if(length(L)<=0){//empty list
        perror("ListADT Error : printList() : Empty List");
        exit(1);
    }

    if(L->cursor==NULL){//list null
        perror("ListADT Error : printList() : Cursor Null");
        exit(1);
    }

    List a = newList();
    assert(a !=NULL);

    Node s = L->front;//get front
    while(s && s != L->cursor){//append until cursor is met
        append(a, s->data);  
        s = s->next;
    }
    while(L->front != L->cursor){//delete the nodes copied in og list
        deleteFront(L);
    }

    return a;
}