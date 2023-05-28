#include <stdio.h>
#include <stdlib.h>

// Structure de file
typedef struct {
    char message;
    struct node* next;
} node;

typedef struct {
    node* somm;
    node* que;
} file;

// Initialiser la file
void initQueue(file* queue) {
    queue->somm = NULL;
    queue->que = NULL;
}

// Verifier si la file est vide
int isEmpty(file* queue) {
    return (queue->somm == NULL);
}

// Ajouter un element dans la file
void enqueue(file* queue, char message) {
    node* nouveauNode = (node*)malloc(sizeof(node));
    nouveauNode->message = message;
    nouveauNode->next = NULL;
    
    if (isEmpty(queue)) {
        queue->somm = nouveauNode;
        queue->que = nouveauNode;
    } else {
        queue->que->next = nouveauNode;
        queue->que = nouveauNode;
    }
}

// Supprimer un element de la file
char dequeue(file* queue) {
    if (isEmpty(queue)) {
        printf("Erreur : la file est vide.\n");
        exit(1);
    }
    
    node* temp = queue->somm;
    char message = temp->message;
    queue->somm = queue->somm->next;
    
    if (queue->somm == NULL) {
        queue->que = NULL;
    }
    
    free(temp);
    return message;
}

// Chiffrement de Cesar
void chiffrement(file* message, int nb) {
    file messagechiffre;
    initQueue(&messagechiffre);
    
    while (!isEmpty(message)) {
        char ch = dequeue(message);
        
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base + nb) % 26 + base;
        }
        
        enqueue(&messagechiffre, ch);
    }
    
    printf("Message chiffre : ");
    while (!isEmpty(&messagechiffre)) {
        printf("%c", dequeue(&messagechiffre));
    }
    printf("\n");
}

// Dechiffrement de Cesar
void decrypt(file* message, int nb) {
    file messagedechifree;
    initQueue(&messagedechifree);
    
    while (!isEmpty(message)) {
        char ch = dequeue(message);
        
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base - nb + 26) % 26 + base;
        }
        
        enqueue(&messagedechifree, ch);
    }
    
    printf("Message dechiffre : ");
    while (!isEmpty(&messagedechifree)) {
        printf("%c", dequeue(&messagedechifree));
    }
    printf("\n");
}

int main() {
    file message;
    initQueue(&message);
    
    int choix;
    printf("*********************Menu :*********************\n");
    printf("1. Chiffrer un message\n");
    printf("2. Dechiffrer un message\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    
    
    while (getchar() != '\n');
    
    if (choix == 1) {
        char ch;
        printf("Entrez le message a chiffrer : ");
        
        while ((ch = getchar()) != '\n') {
            enqueue(&message, ch);
        }
        
        int nb;
        printf("Entrez le decalage : ");
        scanf("%d", &nb);
        
        chiffrement(&message, nb);
    } else if (choix == 2) {
        char ch;
        printf("Entrez le message chiffre : ");
        
        while ((ch = getchar()) != '\n') {
            enqueue(&message, ch);
        }
        
        int nb;
        printf("Entrez le decalage utilise : ");
        scanf("%d", &nb);
        
        decrypt(&message, nb);
    } else {
        printf("Choix invalide.\n");
        return 1;
    }
    
    return 0;
}

