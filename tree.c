#include <stdio.h>
#include <stdlib.h>

// Definição do nó da AVL
typedef struct Node {
    struct Node* lchild;
    int data;
    struct Node* rchild;
    int height;
} Node;

// Funções auxiliares para cálculo de altura e balanceamento
int NodeHeight(Node* p) {
    int hl = (p && p->lchild) ? p->lchild->height : 0;
    int hr = (p && p->rchild) ? p->rchild->height : 0;
    return hl > hr ? hl + 1 : hr + 1;
}

int BalanceFactor(Node* p) {
    int hl = (p && p->lchild) ? p->lchild->height : 0;
    int hr = (p && p->rchild) ? p->rchild->height : 0;
    return hl - hr;
}

// Rotações
Node* LLRotation(Node* p) {
    Node* pl = p->lchild;
    Node* plr = pl->rchild;

    pl->rchild = p;
    p->lchild = plr;

    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);

    return pl;
}

Node* RRRotation(Node* p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;

    pr->lchild = p;
    p->rchild = prl;

    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);

    return pr;
}

Node* LRRotation(Node* p) {
    Node* pl = p->lchild;
    Node* plr = pl->rchild;

    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;

    plr->lchild = pl;
    plr->rchild = p;

    pl->height = NodeHeight(pl);
    p->height = NodeHeight(p);
    plr->height = NodeHeight(plr);

    return plr;
}

Node* RLRotation(Node* p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;

    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;

    prl->rchild = pr;
    prl->lchild = p;

    pr->height = NodeHeight(pr);
    p->height = NodeHeight(p);
    prl->height = NodeHeight(prl);

    return prl;
}

// Função para encontrar o predecessor em ordem
Node* InPre(Node* p) {
    while (p && p->rchild != NULL) {
        p = p->rchild;
    }
    return p;
}

// Função para encontrar o sucessor em ordem
Node* InSucc(Node* p) {
    while (p && p->lchild != NULL) {
        p = p->lchild;
    }
    return p;
}

// Inserção balanceada
Node* rInsert(Node* p, int key) {
    if (p == NULL) {
        Node* t = (Node*)malloc(sizeof(Node));
        t->data = key;
        t->lchild = NULL;
        t->rchild = NULL;
        t->height = 1;
        return t;
    }

    if (key < p->data) {
        p->lchild = rInsert(p->lchild, key);
    } else if (key > p->data) {
        p->rchild = rInsert(p->rchild, key);
    }

    p->height = NodeHeight(p);

    // Balanceamento
    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1) {
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1) {
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1) {
        return RLRotation(p);
    }

    return p;
}

// Remoção balanceada
Node* Delete(Node* p, int key) {
    if (p == NULL) {
        return NULL;
    }

    if (p->lchild == NULL && p->rchild == NULL) {
        free(p);
        return NULL;
    }

    if (key < p->data) {
        p->lchild = Delete(p->lchild, key);
    } else if (key > p->data) {
        p->rchild = Delete(p->rchild, key);
    } else {
        Node* q;
        if (NodeHeight(p->lchild) > NodeHeight(p->rchild)) {
            q = InPre(p->lchild);
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        } else {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
    }

    p->height = NodeHeight(p);

    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1) {
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1) {
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1) {
        return RLRotation(p);
    }

    return p;
}

// Travessia em ordem
void Inorder(Node* p) {
    if (p) {
        Inorder(p->lchild);
        printf("%d ", p->data);
        Inorder(p->rchild);
    }
}

// Função principal
int main() {
    Node* root = NULL;

    int A[] = {10, 20, 30, 25, 28, 27, 5};
    int n = sizeof(A) / sizeof(A[0]);

    for (int i = 0; i < n; i++) {
        root = rInsert(root, A[i]);
    }

    printf("Inorder traversal before deletion: ");
    Inorder(root);
    printf("\n");

    root = Delete(root, 28);

    printf("Inorder traversal after deletion: ");
    Inorder(root);
    printf("\n");

    return 0;
}
