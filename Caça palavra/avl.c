#include "avl.h"

// Funções auxiliares para cálculo de altura e balanceamento
int avlNodeHeight(AvlNode* p) {
    int hl = (p && p->lchild) ? p->lchild->height : 0;
    int hr = (p && p->rchild) ? p->rchild->height : 0;
    return hl > hr ? hl + 1 : hr + 1;
}

int balanceFactor(AvlNode* p) {
    int hl = (p && p->lchild) ? p->lchild->height : 0;
    int hr = (p && p->rchild) ? p->rchild->height : 0;
    return hl - hr;
}

// Rotações
AvlNode* LLRotation(AvlNode* p) {
    AvlNode* pl = p->lchild;
    AvlNode* plr = pl->rchild;

    pl->rchild = p;
    p->lchild = plr;

    p->height = avlNodeHeight(p);
    pl->height = avlNodeHeight(pl);

    return pl;
}

AvlNode* RRRotation(AvlNode* p) {
    AvlNode* pr = p->rchild;
    AvlNode* prl = pr->lchild;

    pr->lchild = p;
    p->rchild = prl;

    p->height = avlNodeHeight(p);
    pr->height = avlNodeHeight(pr);

    return pr;
}

AvlNode* LRRotation(AvlNode* p) {
    AvlNode* pl = p->lchild;
    AvlNode* plr = pl->rchild;

    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;

    plr->lchild = pl;
    plr->rchild = p;

    pl->height = avlNodeHeight(pl);
    p->height = avlNodeHeight(p);
    plr->height = avlNodeHeight(plr);

    return plr;
}

AvlNode* RLRotation(AvlNode* p) {
    AvlNode* pr = p->rchild;
    AvlNode* prl = pr->lchild;

    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;

    prl->rchild = pr;
    prl->lchild = p;

    pr->height = avlNodeHeight(pr);
    p->height = avlNodeHeight(p);
    prl->height = avlNodeHeight(prl);

    return prl;
}

// Função para encontrar o predecessor em ordem
AvlNode* inPre(AvlNode* p) {
    while (p && p->rchild != NULL) {
        p = p->rchild;
    }
    return p;
}

// Função para encontrar o sucessor em ordem
AvlNode* InSucc(AvlNode* p) {
    while (p && p->lchild != NULL) {
        p = p->lchild;
    }
    return p;
}

// Inserção balanceada
AvlNode* rInsert(AvlNode* p, char* key, int start[], int end[]){
    if (p == NULL) {
        AvlNode* t = (AvlNode*)malloc(sizeof(AvlNode));
        t->palavra = strdup(key);
        t->start[0] = start[0];
        t->start[1] = start[1];
        t->end[0] = end[0];
        t->end[1] = end[1];
        t->lchild = NULL;
        t->rchild = NULL;
        t->height = 1;
        return t;
    }

   if (strcmp(key, p->palavra) < 0) {
        p->lchild = rInsert(p->lchild, key, start, end);
    } else if (strcmp(key, p->palavra) > 0) {
        p->rchild = rInsert(p->rchild, key, start, end);
    }

    p->height = avlNodeHeight(p);

    // Balanceamento
    if (balanceFactor(p) == 2 && balanceFactor(p->lchild) == 1) {
        return LLRotation(p);
    } else if (balanceFactor(p) == 2 && balanceFactor(p->lchild) == -1) {
        return LRRotation(p);
    } else if (balanceFactor(p) == -2 && balanceFactor(p->rchild) == -1) {
        return RRRotation(p);
    } else if (balanceFactor(p) == -2 && balanceFactor(p->rchild) == 1) {
        return RLRotation(p);
    }

    return p;
}

// Remoção balanceada
AvlNode* delete(AvlNode* p, char* key) {
    if (p == NULL) {
        return NULL;
    }

    if (p->lchild == NULL && p->rchild == NULL) {
        free(p);
        return NULL;
    }

    if (strcmp(key, p->palavra) < 0) {
        p->lchild = delete(p->lchild, key);
    } else if (strcmp(key, p->palavra) > 0) {
        p->rchild = delete(p->rchild, key);
    } else {
        AvlNode* q;
        if (avlNodeHeight(p->lchild) > avlNodeHeight(p->rchild)) {
            q = inPre(p->lchild);
            p->palavra = q->palavra;
            p->lchild = delete(p->lchild, q->palavra);
        } else {
            q = InSucc(p->rchild);
            p->palavra = q->palavra;
            p->rchild = delete(p->rchild, q->palavra);
        }
    }

    p->height = avlNodeHeight(p);

    if (balanceFactor(p) == 2 && balanceFactor(p->lchild) == 1) {
        return LLRotation(p);
    } else if (balanceFactor(p) == 2 && balanceFactor(p->lchild) == -1) {
        return LRRotation(p);
    } else if (balanceFactor(p) == -2 && balanceFactor(p->rchild) == -1) {
        return RRRotation(p);
    } else if (balanceFactor(p) == -2 && balanceFactor(p->rchild) == 1) {
        return RLRotation(p);
    }

    return p;
}

// Travessia em ordem
void printInOrder(AvlNode* p) {
    if (p == NULL) {
        return;
    }
    printInOrder(p->lchild);
    printf("Palavra: %s, Início: (%d, %d), Fim: (%d, %d)\n", 
       p->palavra, 
       p->start[0], p->start[1], 
       p->end[0], p->end[1]);
    printInOrder(p->rchild);

}
//Libreração da árvore
void freeTree(AvlNode* p) {
    if (p != NULL) {
        freeTree(p->lchild); 
        freeTree(p->rchild);
        free(p->palavra);
        free(p);             
    }
}
