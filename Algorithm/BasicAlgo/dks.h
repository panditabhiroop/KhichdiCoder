#include <iostream>
#include <cstring>
using namespace std;
#define m_node 5

struct bin {
    int val;
    int degree;
    struct bin* next;
    struct bin* prev;
    struct bin* childs[m_node];
};

typedef struct bin node;

class bin_heap {
    node* root;

   public: bin_heap() {
       // cout<<"this function called\n";
        this->root = NULL;
    }

    int deletenode(node* temp) {

        if(temp == NULL) {
            cout<<"Can't delete empty node\n";
            return 0;
        }

        if(temp->prev == NULL) {
            root = temp->next;
            if(root != NULL) {
                root->prev = NULL;
            }
        //    delete(temp);
            return 1;
        }

        if(temp->next == NULL) {
            temp->prev->next = NULL;
        //    delete(temp);
            return 1;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
       // delete(temp);

        return 1;
    }

    int merge_opr() {

        if(root == NULL) {
            cout<<"Can't merge empty heap\n";
            return 0;
        }
        node* temp = root;
        while(temp->next != NULL && temp->degree == temp->next->degree) {
           // cout<<"degree, val: "<<temp->degree<<" "<<temp->val<<"\n";
            if(temp->val <= temp->next->val) {
                temp->childs[temp->degree] = temp->next;
                /*temp->next->prev = temp->degree > 0 ? temp->childs[temp->degree-1] : NULL;
                if(temp->degree > 0) {
                    temp->childs[temp->degree-1]->next = temp->childs[temp->degree];
                }*/
                temp->degree++;
                deletenode(temp->next);
                //temp = temp->next;
            } else {
                temp->next->childs[temp->degree] = temp;
                temp->next->degree++;
                temp = temp->next;
                deletenode(temp->prev);
            }

          //  cout<<"temp val is: "<<temp->val<<"\n";
        }
        return 1;
    }

    int insert(int val) {

        if(root == NULL) {
            root = new node;
            memset(root, NULL, sizeof(root));
            root->val = val;
            root->degree = 0;
            return 1;
        } else {
            node* temp = new node();
            temp->val = val;
            temp->degree = 0;
            temp->next = root;
            root->prev = temp;
            root = temp;
            merge_opr();
        }
        return 1;
    }

    int insert_node(node* nd, int degree) {

        //cout<<"Inserting the node with value: "<<nd->val<<"\n";

        if(root == NULL) {
            root = nd;
            return 1;
        }

        node* temp = root;
        while(temp->next != NULL && temp->degree < degree) {
            temp = temp->next;
        }

        if(temp->degree == degree) {
           // cout<<"one\n";
            if(temp->val <= nd->val) {
             //   cout<<"two\n";
                temp->childs[degree] = nd;
                temp->degree++;
                merge_opr();
            } else {
                nd->prev = temp->prev;
                nd->next = temp->next;
                if(temp->prev != NULL) {
                    temp->prev->next = nd;
                } else {
                    root = nd;
                }

                if(temp->next != NULL) {
                    temp->next->prev = nd;
                }
                temp->next = NULL;
                temp->prev = NULL;
                nd->childs[degree] = temp;
                nd->degree++;
                merge_opr();
                print_heap();
            }
        }
        else if(temp->degree > degree) {
           // cout<<"3\n";

            nd->next = temp;
            nd->prev = temp->prev;
            temp->prev = nd;
            if(nd->prev != NULL) {
                nd->prev->next = nd;
            }
            else {
                root = nd;
            }
            print_heap();
        }
        else {
            //cout<<"4\n";
            nd->next = temp->next;
            nd->prev = temp;
            temp->next = nd;
            if(nd->next != NULL) {
                nd->next->prev = nd;
            }
            merge_opr();
            print_heap();
        }
    }

    int extract_min() {

        //cout<<"Going to extract min\n";

        if(root == NULL) {
            cout<<"Can't extract min from empty forest\n";
            return -1;
        }

        node* temp = root;
        node* temp1 = root;
        int minv = root->val;

        while(temp != NULL) {
            if(temp->val < minv) {
                temp1 = temp;
                minv = temp->val;
            }
            temp = temp->next;
        }
       // cout<<"After while loop\n";
        //####################################InsertPointer#######################################
        deletenode(temp1);
        for(int i = 0; i<temp1->degree; i++) {
            //################Insert node with degree i################
            insert_node(temp1->childs[i], i);
        }

        return minv;
    }

    int print_node(node* nd) {

        if(nd == NULL) {
            return 0;
        }

        cout<<"val: "<<nd->val<<"\n";
        for(int i = 0; i<nd->degree; i++) {
            print_node(nd->childs[i]);
        }
        return 1;
    }

    int print_heap() {

        if(root == NULL) {
            cout<<"Can't print empty heap\n";
            return 0;
        }

        node* temp = root;
        while(temp != NULL) {
            cout<<"degree: "<<temp->degree<<"\n";
            //cout<<"val: "<<val<<"\n";
            print_node(temp);
            temp = temp->next;
        }
    }
};

class fib_heap {

    node* root;
    node* lastNode;
    node* minNode;
    node* arr[m_node];

    public : fib_heap() {
        this->root = NULL;
        this->lastNode = NULL;
        this->minNode = NULL;
        memset(this->arr, NULL, sizeof(this->arr));
    }

    int insert(int val) {
        node* temp = new node;
        temp->val = val;
        temp->degree = 0;

        if(root == NULL) {
            root = temp;
            root->prev = NULL;
            root->next = NULL;
            arr[0] = root;
            lastNode = root;
            minNode = root;
            return 1;
        }
        minNode = minNode->val > temp->val ? temp : minNode;
        temp->next = root;
        root->prev = temp;
        temp->prev = NULL;
        root = temp;
        arr[0] = root;
        return 1;
    }

    int insert_node(node* nd) {

        if(nd == NULL) {
            cout<<"Can't insert NULL node into this heap\n";
            return 0;
        }
        if(root == NULL) {
            root = nd;
            minNode = nd;
            return 1;
        }

        minNode = minNode->val > nd->val ? nd : minNode;
        int temp = nd->degree;

        while(temp < m_node && arr[temp] == NULL) {
            temp++;
        }

        if(temp == m_node) {
            lastNode->next = nd;
            nd->prev = lastNode;
            nd->next = NULL;
            lastNode = nd;
            arr[nd->degree] = nd;
            return 1;

        } else {
            nd->next = arr[temp];
            nd->prev = arr[temp]->prev;
            arr[temp]->prev = nd;

             if(nd->prev != NULL) {
                nd->prev->next = nd;
            } else {
                root = nd;
                arr[0] = root;
            }

            arr[nd->degree] = nd;
            return 1;
        }
    }

    int merge_nodes() {

        /*for(int i = 1; i<m_node; i++) {
            if(arr[i] == NULL) {
                continue;
            }

        }*/
        int opr = 1;
        while(opr) {
            opr = 0;
            node* temp = lastNode;
            while(temp != NULL && temp->prev != NULL) {
                if(temp->prev->degree == temp->degree) {
                opr = 1;
                if(temp->prev->val <= temp->val) {
                    temp->prev->childs[temp->degree] = temp;
                    temp = temp->prev;
                    deleteNode(temp->next);
                } else {
                    temp->childs[temp->degree] = temp->prev;
                    deleteNode(temp->prev);
                }
                temp->degree++;
                arr[temp->degree] = temp;
                minNode = minNode->val > temp->val ? temp : minNode;
                temp = temp->prev;
                } else {
                    temp = temp->prev;
                }
            }
        }
    }

    int deleteNode(node* nd) {

        if(nd == NULL) {
            cout<<"Can't delete NULL node\n";
            return 0;
        }

        //Checking if the node is the first node of it's degree then change the arr value respectively
        if(arr[nd->degree] == nd) {
            if(nd->next != NULL && nd->next->degree == nd->degree) {
                arr[nd->degree] = nd->next;
            } else {
                arr[nd->degree] = NULL;
            }
        }

        if(nd->prev != NULL) {
            nd->prev->next = nd->next;
        }else {
            root = nd->next;
            arr[0] = root;
        }

        if(nd->next != NULL) {
            nd->next->prev = nd->prev;
        } else {
            lastNode = nd->prev;
        }
        return 1;
    }

    int extract_min() {

        int mval = minNode->val;

        deleteNode(minNode);
        minNode = root;

        for(int i = 0; i<minNode->degree; i++) {
            insert_node(minNode->childs[i]);
        }
        merge_nodes();
        return mval;
    }

    int print_node(node* nd) {

        if(nd == NULL) {
            return 0;
        }

        cout<<"val: "<<nd->val<<"\n";
        for(int i = 0; i<nd->degree; i++) {
            print_node(nd->childs[i]);
        }
        return 1;
    }

    int print_heap() {

        if(root == NULL) {
            cout<<"Can't print empty heap\n";
            return 0;
        }

        node* temp = root;
        while(temp != NULL) {
            cout<<"degree: "<<temp->degree<<"\n";
            //cout<<"val: "<<val<<"\n";
            print_node(temp);
            temp = temp->next;
        }
    }
};
