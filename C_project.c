#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure du contact
typedef struct Contact {
    char nom[50];
    char prenom[50];
    char telephone[20];
    char email[100];
    char adresse[200];
    struct Contact* suivant;
} Contact;

Contact* tete = NULL;

// Nettoyer le buffer clavier
void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Supprimer le \n de fgets
void enleverSautLigne(char* str) {
    str[strcspn(str, "\n")] = '\0';
}

// Créer un nouveau contact
Contact* creerContact(const char* nom, const char* prenom, const char* telephone,
                      const char* email, const char* adresse) {
    Contact* nouveau = (Contact*)malloc(sizeof(Contact));
    if (!nouveau) {
        printf("Erreur d'allocation memoire.\n");
        exit(1);
    }

    strcpy(nouveau->nom, nom);
    strcpy(nouveau->prenom, prenom);
    strcpy(nouveau->telephone, telephone);
    strcpy(nouveau->email, email);
    strcpy(nouveau->adresse, adresse);
    nouveau->suivant = NULL;
    return nouveau;
}

// Ajouter un contact en fin de liste (ou insertion triée si souhaitée)
void ajouterContact(Contact* contact) {
    if (tete == NULL || strcmp(contact->nom, tete->nom) < 0) {
        contact->suivant = tete;
        tete = contact;
    } else {
        Contact* temp = tete;
        while (temp->suivant != NULL && strcmp(contact->nom, temp->suivant->nom) > 0) {
            temp = temp->suivant;
        }
        contact->suivant = temp->suivant;
        temp->suivant = contact;
    }
}

// Afficher tous les contacts
void afficherContacts() {
    if (tete == NULL) {
        printf("Carnet vide.\n");
        return;
    }

    Contact* temp = tete;
    while (temp != NULL) {
        printf("\nNom: %s\nPrenom: %s\nTelephone: %s\nEmail: %s\nAdresse: %s\n",
               temp->nom, temp->prenom, temp->telephone, temp->email, temp->adresse);
        temp = temp->suivant;
    }
}

// Rechercher par nom
Contact* rechercherParNom(const char* nom) {
    Contact* temp = tete;
    while (temp != NULL) {
        if (strcmp(temp->nom, nom) == 0)
            return temp;
        temp = temp->suivant;
    }
    return NULL;
}

// Rechercher par téléphone
Contact* rechercherParTelephone(const char* telephone) {
    Contact* temp = tete;
    while (temp != NULL) {
        if (strcmp(temp->telephone, telephone) == 0)
            return temp;
        temp = temp->suivant;
    }
    return NULL;
}

// Supprimer par nom
void supprimerContact(const char* nom) {
    Contact *temp = tete, *precedent = NULL;

    while (temp != NULL && strcmp(temp->nom, nom) != 0) {
        precedent = temp;
        temp = temp->suivant;
    }

    if (temp == NULL) {
        printf("Contact non trouve.\n");
        return;
    }

    if (precedent == NULL) {
        tete = temp->suivant;
    } else {
        precedent->suivant = temp->suivant;
    }

    free(temp);
    printf("Contact supprime avec succes.\n");
}

// Modifier un contact
void modifierContact(const char* nom) {
    Contact* contact = rechercherParNom(nom);
    if (!contact) {
        printf("Contact non trouve.\n");
        return;
    }

    char nouveauNom[50], nouveauPrenom[50], nouveauTelephone[20], nouvelEmail[100], nouvelleAdresse[200];

    viderBuffer();
    printf("Nouveau nom : ");
    fgets(nouveauNom, sizeof(nouveauNom), stdin);
    enleverSautLigne(nouveauNom);
    
    printf("Nouveau prenom : ");
    fgets(nouveauPrenom, sizeof(nouveauPrenom), stdin);
    enleverSautLigne(nouveauPrenom);

    printf("Nouveau telephone : ");
    fgets(nouveauTelephone, sizeof(nouveauTelephone), stdin);
    enleverSautLigne(nouveauTelephone);

    printf("Nouvel email : ");
    fgets(nouvelEmail, sizeof(nouvelEmail), stdin);
    enleverSautLigne(nouvelEmail);

    printf("Nouvelle adresse : ");
    fgets(nouvelleAdresse, sizeof(nouvelleAdresse), stdin);
    enleverSautLigne(nouvelleAdresse);
    
	strcpy(contact->nom, nouveauNom);
    strcpy(contact->prenom, nouveauPrenom);
    strcpy(contact->telephone, nouveauTelephone);
    strcpy(contact->email, nouvelEmail);
    strcpy(contact->adresse, nouvelleAdresse);

    printf("Contact modifie avec succes.\n");
}

// Menu principal
void menu() {
    int choix;
    char nom[50], prenom[50], telephone[20], email[100], adresse[200];
    Contact* contact;

    do {
        printf("\n======= MENU CARNET D'ADRESSES =======\n");
        printf("1. Ajouter un contact\n");
        printf("2. Afficher tous les contacts\n");
        printf("3. Rechercher un contact par nom\n");
        printf("4. Rechercher un contact par telephone\n");
        printf("5. Supprimer un contact par nom\n");
        printf("6. Modifier un contact\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        viderBuffer();

        switch (choix) {
            case 1:
                printf("Nom : ");
                fgets(nom, sizeof(nom), stdin);
                enleverSautLigne(nom);

                printf("Prenom : ");
                fgets(prenom, sizeof(prenom), stdin);
                enleverSautLigne(prenom);

                printf("Telephone : ");
                fgets(telephone, sizeof(telephone), stdin);
                enleverSautLigne(telephone);

                printf("Email : ");
                fgets(email, sizeof(email), stdin);
                enleverSautLigne(email);

                printf("Adresse : ");
                fgets(adresse, sizeof(adresse), stdin);
                enleverSautLigne(adresse);

                contact = creerContact(nom, prenom, telephone, email, adresse);
                ajouterContact(contact);
                printf("Contact ajoute avec succes !\n");
                break;

            case 2:
                afficherContacts();
                break;

            case 3:
                printf("Entrez le nom à rechercher : ");
                fgets(nom, sizeof(nom), stdin);
                enleverSautLigne(nom);
                contact = rechercherParNom(nom);
                if (contact)
                    printf("\nNom: %s\nPrenom: %s\nTelephone: %s\nEmail: %s\nAdresse: %s\n",
                           contact->nom, contact->prenom, contact->telephone, contact->email, contact->adresse);
                else
                    printf("Contact non trouve.\n");
                break;

            case 4:
                printf("Entrez le numéro de telephone : ");
                fgets(telephone, sizeof(telephone), stdin);
                enleverSautLigne(telephone);
                contact = rechercherParTelephone(telephone);
                if (contact)
                    printf("\nNom: %s\nPrenom: %s\nTelephone: %s\nEmail: %s\nAdresse: %s\n",
                           contact->nom, contact->prenom, contact->telephone, contact->email, contact->adresse);
                else
                    printf("Contact non trouve.\n");
                break;

            case 5:
                printf("Entrez le nom du contact à supprimer : ");
                fgets(nom, sizeof(nom), stdin);
                enleverSautLigne(nom);
                supprimerContact(nom);
                break;

            case 6:
                printf("Entrez le nom du contact à modifier : ");
                fgets(nom, sizeof(nom), stdin);
                enleverSautLigne(nom);
                modifierContact(nom);
                break;

            case 0:
                printf("Fermeture du carnet...\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);
}

// Fonction principale
int main() {
    menu();
    return 0;
}
