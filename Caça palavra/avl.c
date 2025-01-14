#include "avl.h"

// Funções auxiliares para cálculo de altura e balanceamento
int AvlNodeHeight(AvlNode* p) {
    int hl = (p && p->lchild) ? p->lchild->height : 0;
    int hr = (p && p->rchild) ? p->rchild->height : 0;
    return hl > hr ? hl + 1 : hr + 1;
}

int BalanceFactor(AvlNode* p) {
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

    p->height = AvlNodeHeight(p);
    pl->height = AvlNodeHeight(pl);

    return pl;
}

AvlNode* RRRotation(AvlNode* p) {
    AvlNode* pr = p->rchild;
    AvlNode* prl = pr->lchild;

    pr->lchild = p;
    p->rchild = prl;

    p->height = AvlNodeHeight(p);
    pr->height = AvlNodeHeight(pr);

    return pr;
}

AvlNode* LRRotation(AvlNode* p) {
    AvlNode* pl = p->lchild;
    AvlNode* plr = pl->rchild;

    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;

    plr->lchild = pl;
    plr->rchild = p;

    pl->height = AvlNodeHeight(pl);
    p->height = AvlNodeHeight(p);
    plr->height = AvlNodeHeight(plr);

    return plr;
}

AvlNode* RLRotation(AvlNode* p) {
    AvlNode* pr = p->rchild;
    AvlNode* prl = pr->lchild;

    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;

    prl->rchild = pr;
    prl->lchild = p;

    pr->height = AvlNodeHeight(pr);
    p->height = AvlNodeHeight(p);
    prl->height = AvlNodeHeight(prl);

    return prl;
}

// Função para encontrar o predecessor em ordem
AvlNode* InPre(AvlNode* p) {
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

    p->height = AvlNodeHeight(p);

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
AvlNode* Delete(AvlNode* p, char* key) {
    if (p == NULL) {
        return NULL;
    }

    if (p->lchild == NULL && p->rchild == NULL) {
        free(p);
        return NULL;
    }

    if (strcmp(key, p->palavra) < 0) {
        p->lchild = Delete(p->lchild, key);
    } else if (strcmp(key, p->palavra) > 0) {
        p->rchild = Delete(p->rchild, key);
    } else {
        AvlNode* q;
        if (AvlNodeHeight(p->lchild) > AvlNodeHeight(p->rchild)) {
            q = InPre(p->lchild);
            p->palavra = q->palavra;
            p->lchild = Delete(p->lchild, q->palavra);
        } else {
            q = InSucc(p->rchild);
            p->palavra = q->palavra;
            p->rchild = Delete(p->rchild, q->palavra);
        }
    }

    p->height = AvlNodeHeight(p);

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
void Inorder(AvlNode* p) {
    if (p == NULL) {
        return;
    }
    Inorder(p->lchild);
    printf("Palavra: %s, Início: (%d, %d), Fim: (%d, %d)\n", 
       p->palavra, 
       p->start[0], p->start[1], 
       p->end[0], p->end[1]);
    Inorder(p->rchild);

}
//Libreração da árvore
void FreeTree(AvlNode* p) {
    if (p != NULL) {
        FreeTree(p->lchild); 
        FreeTree(p->rchild);
        free(p->palavra);
        free(p);             
    }
}
