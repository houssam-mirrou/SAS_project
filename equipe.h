#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define N 50
#include <string.h>
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define reset "\e[0m"
#include <ctype.h>

//la decoration du code 

int col_width = 12;

//print header **

void print_semi_head(){
    int i;
    printf("*");
	for(i=0;i<col_width+3;i++){
		printf("*");
	}
}

void print_header_footer(){
    int i=0;
    printf("*");
	for(i=0;i<col_width+4;i++){
		printf("*");
	}
    for(i=0;i<9;i++){
        print_semi_head();
    }
	printf("*\n");
}

//structure de date

typedef struct date {
    int j,m,a;
} date;

//structure joueur

typedef struct joueur {
    int id_joueur;
    char nom[N];
    char prenom[N];
    int numeroMaillot;
    char poste[N];
    int age;
    int buts;
    date dateInscription;
    char statut[N];
} joueur ;

int id_global=1;

//fonction pour verifier si un caracter et a jusqua z

int est_car(char c){
    if(c<='z' && c>='a' || c>='A' && c<='Z'){
        return 1;
    }
    return 0;
}

//fonction pour verifier le nom ou prenom 
int verif_nom(char nom[]){
    if(strlen(nom) < 3){
        return 0;
    }
    int i=0;
    while (nom[i]!='\0') {
        if(est_car(nom[i])!=1){
            return 0;
        }
        i++;
    }
    return 1;
}

//fonction pour verifier le numero du maillo
int recherche_num_maillo(joueur equipe[],int n,int num){
    int i;
    for(i=0;i<n;i++){
        if(equipe[i].numeroMaillot == num){
            return i;
        }
    }
    return -1;
}

//fonction pour verifier si aux moin un joueur marquer les buts ciblé

int recherche_but(joueur equipe[],int n,int but){
    int i=0;
    for(i=0;i<n;i++){
        if(equipe[i].buts>=but){
            return 1;
        }
    }
    return 0;
}

//fonction pour verifier la poste
int verifier_poste(char post[]){
    char temp[4][10] = {"gardien", "defenseur","milieu","attaquant"};
    int i=0;
    while(post[i]!='\0'){
        post[i] = tolower(post[i]);
        i++;
    }
    for(i=0;i<4;i++){
        if(strcmp(post,temp[i]) == 0){
            return 1;
        }
    }
    return 0;
}

//fonction pour verifier l'age
int verifier_age(int age){
    if(age<15){
        return 0;
    }
    return 1;
}

//fonction pour verifier les but
int verifier_but(int b){
    if(b<0) return 0;
    return 1;
}

//fonction pour verifier la date
int verifier_date(date dt){
    if(dt.a > 2025 || dt.a<1986){
        return 0;
    }
    if(dt.m <0 || dt.m>12){
        return 0;
    }
    if(dt.a%4 == 0 && dt.m == 2){
        if(dt.j>29 || dt.j<0){
            return 0;
        }
    }
    int jours[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(dt.j > jours[dt.m-1] || dt.j<0){
        return 0;
    }
    return 1;
}

// fonction pour verifier statut
int verifier_statut(char stat[]){
    char temp[2][12] = {"titulaire", "remplacant"};
    int i=0;
    while(stat[i]!='\0'){
        stat[i] = tolower(stat[i]);
        i++;
    }
    for(i=0;i<2;i++){
        if(strcmp(stat,temp[i]) == 0){
            return 1;
        }
    }
    return 0;
}

//fonction pour ecrire les valeurs du joueur

void print_value(joueur jou){
    printf("** %-*d ** %-*s ** %-*s ** %-*d ** %-*s ** %-*d ** %-*d ** %-*d/%d/%d ** %-*s **\n", 
        col_width, jou.id_joueur,
        col_width, jou.nom,
        col_width, jou.prenom,
        col_width, jou.numeroMaillot,
        col_width, jou.poste,
        col_width, jou.age,
        col_width, jou.buts,
        col_width, jou.dateInscription.j,jou.dateInscription.m,jou.dateInscription.a,
        col_width, jou.statut);
}

//fontion pour ecrire entétte du tableaux

void print_entete_du_tableaux(){
    char temp [9][19] = {"Id","Nom","Prenom","NumeroMaillot","Poste","Age","Buts","Date d'inscription","statut"};
    print_header_footer();
    printf("** %-*s ** %-*s ** %-*s ** %-*s ** %-*s ** %-*s ** %-*s ** %-*s ** %-*s **\n", 
        col_width, temp[0],
        col_width, temp[1],
        col_width, temp[2],
        col_width, temp[3],
        col_width, temp[4],
        col_width, temp[5],
        col_width, temp[6],
        col_width, temp[7],
        col_width, temp[8]
    );
    print_header_footer();
}

//fonction pour ecrire les element du menu

void print_elem_menu (char title[],char color[]) {
    int menu_width = (col_width * 9);
    printf(color);
    printf("*");
    printf("\t");
    printf("%-*s", menu_width-2-1, title); 
    
    printf("\t");
    printf(" *\n");
}

//deux fonction d'affichage d'un elemnt du menu conciderons le type d'elemnt

void print_elem_menu_avec_extra_par_int (char title[],char color[],int elem) {
    int menu_width = (col_width * 9);
    printf(color);
    printf("*");
    printf("\t");
    printf("%-*s %d", menu_width-2-1, title,elem); 
    
    printf("\t");
    printf(" *\n");
}
void print_elem_menu_avec_extra_par_float (char title[],char color[],float elem) {
    int menu_width = (col_width * 9);
    printf(color);
    printf("*");
    printf("\t");
    printf("%-*s %d", menu_width-2-1, title,elem); 
    
    printf("\t");
    printf(" *\n");
}

//fonction pour printer un chaine de carrctere comme un message ou erreur

void print_error_ou_titre(char title[] ){
    int total_width = (col_width * 9)+10;
    int title_len = strlen(title);

    if (title_len >= total_width) {
        printf("%s\n", title);
        return;
    }

    int pad_width = total_width - title_len;
    int left_padding = pad_width / 2;
    int right_padding = pad_width - left_padding;

    print_header_footer();
    printf("**%*s%s%*s**\n", left_padding, "", title, right_padding, "");

    print_header_footer();
}

void print_error_ou_titre_avec_index(char title[] ,int idx){
    int total_width = (col_width * 9)+10;
    int title_len = strlen(title);

    if (title_len >= total_width) {
        printf("%s\n", title);
        return;
    }

    int pad_width = total_width - title_len;
    int left_padding = pad_width / 2;
    int right_padding = pad_width - left_padding;

    print_header_footer();
    printf("**%*s%s (id = %d)%*s**\n", left_padding, "", title,idx, right_padding, "");

    print_header_footer();
}

//printer un choix

void print_choix (char title[],char color[]) {
    int menu_width = (col_width * 3);
    printf(color);
    printf("*");
    printf("\t");
    printf("%-*s", menu_width-2-1, title); 
    
    printf("\t");
    printf(" *\n");
}

//rechercher par nom et prenom

int recherche_par_nom_prenom(joueur equipe[],int n,char nm[],char pren[]){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(equipe[i].nom,nm) == 0 && strcmp(equipe[i].prenom,pren) == 0){
            return i;
        }
    }
    return -1;
}

int rechercher_par_nom(joueur equipe[],int n,char nm[]){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(equipe[i].nom,nm) == 0){
            return i;
        }
    }
    return -1;
}

//recherche par id de joueur

int recherche_par_id_joueur(joueur equipe[],int n,int id){
    int i;
    for(i=0;i<n;i++){
        if(equipe[i].id_joueur == id){
            return i;
        }
    }
    return -1;
}

//ajouter un joueur

int ajouter_un_joueuer(joueur equipe[],int n){
    char nm[N],pren[N];

    //ajouter le nom avec verification

    printf("Donner le nom de joueur : ");
    scanf("%s",nm);
    if(verif_nom(nm) == 0){
        do{
            printf("Donner un nom propre pour le joueur : ");
            scanf("%s",nm);
        } while (verif_nom(nm) == 0);
    }

    //ajouter le prenom avec verification

    printf("Donner le prenom de joueur : ");
    scanf("%s",pren);
    if(verif_nom(pren) == 0){
        do{
            printf("Donner un prenom propre pour le joueur : ");
            scanf("%s",pren);
        } while (verif_nom(pren) == 0);
    }

    //recherche si l'equipe deja le joueur saisie

    int idx = recherche_par_nom_prenom(equipe,n,nm,pren);
    if(idx!=-1){
        print_error_ou_titre_avec_index("Le joueur est deja dans l'equipe essayer de le modifier dans l'index ",idx);
        return n;
    }

    //ajout du nom et prenom
    
    strcpy(equipe[n].nom,nm);
    strcpy(equipe[n].prenom,pren);

    //verifier si le numero du mailot et deja appris par un joueur 

    int num=0;
    printf("Donner le numero du maillo du joueur : ");
    scanf("%d",&num);
    if(recherche_num_maillo(equipe,n,num) != -1){
        do {
            printf("Donner un numero de maillo qui n'existe pas : ");
            scanf("%d",&num);
        } while (recherche_num_maillo(equipe,n,num)!= -1);
    }
    equipe[n].numeroMaillot=num;

    //verifier le post

    char poste[N];
    printf("Donner le poste du joueur : ");
    scanf("%s",poste);
    if(verifier_poste(poste) == 0){
        do {
            printf("Donner un poste depuis ces example (gardien, defenseur, milieu, attaquant) :");
            scanf("%s",poste);
        } while(verifier_poste(poste) == 0);
    }
    strcpy(equipe[n].poste,poste);

    //verifier age 

    int age ;
    printf("Donner l'age du joueur : ");
    scanf("%d",&age);
    if(age<15){
        do{
            printf("Donner un age supperieur a 15 ans : ");
            scanf("%d",&age);
        } while(age<15);
    }
    equipe[n].age=age;

    //verifier but

    int but ;
    printf("Donner les but du joueur : ");
    scanf("%d",&but);
    if(but<0){
        do{
            printf("les buts doit etre supperieur a 0 ! : ");
            scanf("%d",&but);
        } while(but<0);
    }
    equipe[n].buts=but;

    //verifier date

    date d;
    printf("Donner la date JJ/MM/AAAA : " );
    scanf("%d/%d/%d",&d.j,&d.m,&d.a);
    if(verifier_date(d) == 0){
        do {
            printf("Donner une date convenable : ");
            scanf("%d/%d/%d",&d.j,&d.m,&d.a);
        } while(verifier_date(d) == 0);
    }
    equipe[n].dateInscription=d;

    // verif statut

    char stat[N];
    printf("Donner le statut de joueur : ");
    scanf("%s",stat);
    if(verifier_statut(stat) == 0){
        do {
            printf("Le statut doit etre si titulaire si remplacant : ");
            scanf("%s",stat);
        } while(verifier_statut(stat) == 0);
    }
    strcpy(equipe[n].statut,stat);
    equipe[n].id_joueur=id_global;
    id_global++;
    n++;
    return n;
}

//ajouter multiple joueur

int ajout_multiple_joueur(joueur equipe[] ,int n){
    int nbr;
    printf("Donner le nombre de joueur a ajouter : ");
    scanf("%d",&nbr);
    int temp;
    while(nbr>0){
        temp=n;
        n=ajouter_un_joueuer(equipe,n);
        if(temp!=n){
            nbr--;
        }
    }
    return n;
}

//fenetre ajout des joueur

int fentre_ajout(joueur equipe[],int n){
    system("cls");
    print_header_footer();
    print_choix("1. Ajouter un seul joueur :",GRN);
    print_choix("2. Ajouter multiple joueur :",MAG);
    print_header_footer();
    int choix = 0;
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<1 || choix>2){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <1 && choix >2);
    }
    switch (choix){
        case 1:
            n=ajouter_un_joueuer(equipe,n);
            break;
        case 2 :
            n=ajout_multiple_joueur(equipe,n);
            break;
    }       
    return n;
}

//tri par ordre alphabetique

int section_tri_ordre_alph(joueur equipe[],int debut,int fin){
    int i=debut-1;
    joueur pivot = equipe[fin];
    int j;
    for(j=debut;j<fin;j++){
        if(strcmp(equipe[j].nom,pivot.nom) == -1){
            i++;
            joueur temp =equipe[i];
            equipe[i]=equipe[j];
            equipe[j]=temp;
        }
    }
    i++;
    joueur temp =equipe[i];
    equipe[i]=equipe[fin];
    equipe[fin]=temp;
    return i;
}

//section par age

int section_tri_ordre_age(joueur equipe[],int debut,int fin){
    int i=debut-1;
    joueur pivot = equipe[fin];
    int j;
    for(j=debut;j<fin;j++){
        if(equipe[j].age>pivot.age){
            i++;
            joueur temp =equipe[i];
            equipe[i]=equipe[j];
            equipe[j]=temp;
        }
    }
    i++;
    joueur temp =equipe[i];
    equipe[i]=equipe[fin];
    equipe[fin]=temp;
    return i;
}

//section par poste

int section_tri_ordre_poste(joueur equipe[],int debut,int fin){
    int i=debut-1;
    joueur pivot = equipe[fin];
    int j;
    for(j=debut;j<fin;j++){
        if(strcmp(equipe[j].poste,pivot.poste)==-1){
            i++;
            joueur temp =equipe[i];
            equipe[i]=equipe[j];
            equipe[j]=temp;
        }
    }
    i++;
    joueur temp =equipe[i];
    equipe[i]=equipe[fin];
    equipe[fin]=temp;
    return i;
}

void tri_equipe(joueur equipe[],int debut,int fin,int choix){
    if(debut<fin){
        if(choix == 1){
            int pi = section_tri_ordre_alph(equipe,debut,fin);
            tri_equipe(equipe,debut,pi-1,choix);
            tri_equipe(equipe,pi+1,fin,choix);
        }
        if(choix == 2){
            int pi = section_tri_ordre_age(equipe,debut,fin);
            tri_equipe(equipe,debut,pi-1,choix);
            tri_equipe(equipe,pi+1,fin,choix);
        }
        if(choix == 3){
            int pi = section_tri_ordre_poste(equipe,debut,fin);
            tri_equipe(equipe,debut,pi-1,choix);
            tri_equipe(equipe,pi+1,fin,choix);
        }
    }
}

void afficher_equipe(joueur equipe[],int n){
    print_entete_du_tableaux();
    for(int i=0;i<n;i++){
        print_value(equipe[i]);
    }
    print_header_footer();
}

void fenetre_affichage(joueur equipe[] ,int n){
    if(n==0){
        print_error_ou_titre("L'equipe n'a aucun joueur !! ");
        return;
    }
    system("cls");
    print_header_footer();
    print_choix("1. Afficher les joueurs trier par ordre alphabétique.",GRN);
    print_choix("2. Afficher les joueurs trier par âge.",MAG);
    print_choix("3. Afficher les joueurs trier par poste.",CYN);
    print_header_footer();
    int choix = 0;
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<1 || choix>3){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <1 && choix >3);
    }
    switch (choix){
        case 1:
            tri_equipe(equipe,0,n-1,choix);
            afficher_equipe(equipe,n);
            break;
        case 2 :
            tri_equipe(equipe,0,n-1,choix);
            afficher_equipe(equipe,n);
            break;
        case 3 :
            tri_equipe(equipe,0,n-1,choix);
            afficher_equipe(equipe,n);
    } 
}

//modifier la poste

void modifier_poste(joueur equipe[],int idx){
    char poste[N];
    printf("Donner le poste du joueur : ");
    scanf("%s",poste);
    if(verifier_poste(poste) == 0){
        do {
            printf("Donner un poste depuis ces example (gardien, defenseur, milieu, attaquant) :");
            scanf("%s",poste);
        } while(verifier_poste(poste) == 0);
    }
    strcpy(equipe[idx].poste,poste);
}

//modifier l'age

void modifier_age(joueur equipe[],int idx){
    int age ;
    printf("Donner l'age du joueur : ");
    scanf("%d",&age);
    do{
        printf("Donner un age supperieur a 15 ans : ");
        scanf("%d",&age);
    } while(age<15);
    equipe[idx].age=age;
}

//modifier les buts

void modifier_but(joueur equipe[],int idx){
    int but ;
    printf("Donner les but du joueur : ");
    scanf("%d",&but);
    do{
        printf("les buts doit etre supperieur a 0 ! : ");
        scanf("%d",&but);
    } while(but<0);
    equipe[idx].buts=but;
}

//fenetre de choix de modification

void fenetre_choix_modification(joueur equipe[],int idx){
    system("cls");
    print_header_footer();
    print_choix("1. Modifier un poste joueur.",CYN);
    print_choix("2. Modifier l'age du joueur.",MAG);
    print_choix("3. Modifier les buts marque par le joueur.",GRN);
    print_header_footer();
    int choix = 0;
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<1 || choix>3){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <1 && choix >3);
    }
    switch(choix){
        case 1:
            modifier_poste(equipe,idx);
            break;
        case 2:
            modifier_age(equipe,idx);
            break;
        case 3:
            modifier_poste(equipe,idx);
            break;
    }
}

//fenetre de choix de modification par le nom ou identite

void fenetre_choix_modification_par_nom_ou_ident(joueur equipe[],int n){
    system("cls");
    print_header_footer();
    print_choix("1. Modifier par nom et prenom.",CYN);
    print_choix("2. Modifier par identiter de joueur.",MAG);
    print_header_footer();
    int choix = 0;
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<1 || choix>2){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <1 && choix >2);
    }
    int idx=-1;
    int id=-1;
    char nm[N],pren[N];
    switch (choix){
        case 1:
            printf("Donner le nom de joueur : ");
            scanf("%s",nm);
            if(verif_nom(nm) == 0){
                do{
                    printf("Donner un nom propre pour le joueur : ");
                    scanf("%s",nm);
                } while (verif_nom(nm) == 0);
            }

            printf("Donner le prenom de joueur : ");
            scanf("%s",pren);
            if(verif_nom(pren) == 0){
                do{
                    printf("Donner un prenom propre pour le joueur : ");
                    scanf("%s",pren);
                } while (verif_nom(pren) == 0);
            }
            idx=recherche_par_nom_prenom(equipe,n,nm,pren);
            if(idx == -1){
                print_error_ou_titre("Le joueur n'existe pas dans l'equipe !!");
                return;
            }
            fenetre_choix_modification(equipe,idx);
            break;
        case 2 :
            printf("Donner l'id du joueur : ");
            scanf("%d",&id);
            do {
                printf("L'id des joueur commence par 1, donner une nouveaux id : ");
                scanf("%d",&id);
            } while(id<1);
            idx=recherche_par_id_joueur(equipe,n,id);
            if(idx == -1){
                print_error_ou_titre("Le joueur n'existe pas dans l'equipe !!");
            }
            fenetre_choix_modification(equipe,idx);
            break; 
    } 
}

//fonction_pour_supprimer_un_joueur_par_identifiant

int supprimer_un_joueur(joueur equipe[] ,int n ,int idx){
    int i=0;
    for(i=idx;i<n;i++){
        equipe[i]=equipe[i+1];
    }
    n--;
    return n;
}

//fonction pour supprimer un joueur

int fenetre_supprimer(joueur equipe[],int n){
    system("cls");
    print_header_footer();
    print_choix("1. Supprimer par nom et prenom.",CYN);
    print_choix("2. Supprimer par identiter de joueur.",MAG);
    print_header_footer();
    int choix = 0;
    int idx=-1;
    char nm[N],pren[N];
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<1 || choix>2){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <1 && choix >2);
    }
    switch (choix){
    case 1:
        //le nom avec verification
        printf("Donner le nom de joueur : ");
        scanf("%s",nm);
        if(verif_nom(nm) == 0){
            do{
                printf("Donner un nom propre pour le joueur : ");
                scanf("%s",nm);
            } while (verif_nom(nm) == 0);
        }
        //le prenom avec modification
        printf("Donner le prenom de joueur : ");
        scanf("%s",pren);
        if(verif_nom(pren) == 0){
            do{
                printf("Donner un prenom propre pour le joueur : ");
                scanf("%s",pren);
            } while (verif_nom(pren) == 0);
        }

        idx=recherche_par_nom_prenom(equipe,n,nm,pren);
        if(idx == -1){
            print_error_ou_titre("Le joueur n'existe pas dans l'equipe !!");
            return n;
        }
        supprimer_un_joueur(equipe,n,idx);
        break;
    case 2 :
        int id=0;
        printf("Donner l'id du joueur : ");
        scanf("%d",&id);
        do {
            printf("L'id des joueur commence par 1, donner une nouvelle id : ");
            scanf("%d",&id);
        } while(id<1);
        idx = recherche_par_id_joueur(equipe,n,id);
        if(idx == 0){
            print_error_ou_titre("Le joueur n'existe pas !!");
            return n;
        }
        supprimer_un_joueur(equipe,n,idx);
        break;
    }
}

//rechercher un joueur

void fenetre_recherche_joueur(joueur equipe[],int n){
    system("cls");
    print_header_footer();
    print_choix("1. Rechercher par le nom et prenom.",CYN);
    print_choix("2. Rechercher par l'identiter de joueur.",MAG);
    print_header_footer();
    int choix = 0;
    int idx=-1;
    char nm[N],pren[N];
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<1 || choix>2){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <1 && choix >2);
    }
    switch (choix){
    case 1:
        //le nom avec verification
        printf("Donner le nom de joueur : ");
        scanf("%s",nm);
        if(verif_nom(nm) == 0){
            do{
                printf("Donner un nom propre pour le joueur : ");
                scanf("%s",nm);
            } while (verif_nom(nm) == 0);
        }

        idx=rechercher_par_nom(equipe,n,nm);
        if(idx == -1){
            print_error_ou_titre("Le joueur n'existe pas dans l'equipe !!");
            return;
        }
        print_entete_du_tableaux();
        print_value(equipe[idx]);
        break;
    case 2:
        int id=0;
        printf("Donner l'id du joueur : ");
        scanf("%d",&id);
        do {
            printf("L'id des joueur commence par 1, donner une nouvelle id : ");
            scanf("%d",&id);
        } while(id<1);
        idx = recherche_par_id_joueur(equipe,n,id);
        if(idx == 0){
            print_error_ou_titre("Le joueur n'existe pas !!");
            return;
        }
        print_entete_du_tableaux();
        print_value(equipe[idx]);
        break;
    }
}

float moyen_des_age(joueur equipe[],int n){
    float moy=0;
    int i=0;
    for(i=0;i<n;i++){
        moy+=equipe[i].age;
    }
    moy/=n;
    return n;
}

//fonction pour afficher les joueur ayant x but

void afficher_les_joueur_avec_x_but(joueur equipe[],int n,int but){
    int i=0;
    int test = recherche_but(equipe,n,but);
    if(test == 0){
        print_elem_menu("Il n'ya pas un joueur dans l'equipe qui a marquer X buts .",WHT);
        return;
    }
    print_elem_menu_avec_extra_par_int("Les joueur qui ont marquer plus de but que",WHT,but);
    print_entete_du_tableaux();
    for(i=0;i<n;i++){
        if(equipe[i].buts >= but){
            print_value(equipe[i]);
        }
    }
    print_header_footer();
}

//fonction qui retournait le joueur avec max des but

joueur max_but_joueur(joueur equipe[],int n){
    int max=equipe[0].buts;
    int i;
    int idx;
    for(i=1;i<n;i++){
        if(max<equipe[i].buts){
            max=equipe[i].buts;
            idx=i;
        }
    }
    return equipe[idx];
}

//fonction affiche le meilleur butteur
void afficher_butteur(joueur equipe[],int n){
    int i=0;
    joueur temp = max_but_joueur(equipe,n);
    print_elem_menu("Le butteur est :\n",WHT);
    print_entete_du_tableaux();
    print_value(temp);
    print_header_footer();
}

//fonction afficher le jeune et plut age
void afficher_jeune_age(joueur equipe[],int n){
    int i=0;
    int min,max;
    joueur jeune,age;
    min=max=equipe[0].age;
    for(i=0;i<n;i++){
        if(min>equipe[i].age){
            min=equipe[i].age;
            jeune=equipe[i];
        }   
        if(max<equipe[i].age){
            max=equipe[i].age;
            age=equipe[i];
        }
    }
    print_entete_du_tableaux();
    print_value(jeune);
    print_value(age);
    print_header_footer();
}

void fenetre_statistique(joueur equipe[],int n){
    system("cls");
    int but ;
    printf("Donner le nombre de but pour les statistique : ");
    scanf("%d",&but);
    do{
        printf("les buts doit etre supperieur a 0 ! : ");
        scanf("%d",&but);
    } while(but<0);
    printf("\n");

    float moy=moyen_des_age(equipe,n);
    print_header_footer();
    print_elem_menu_avec_extra_par_int("Le nombre totale des joueur est : ",WHT,n);
    print_elem_menu_avec_extra_par_float("Le moyenne des age est: ",WHT,moy);
    afficher_les_joueur_avec_x_but(equipe,n,but);
    afficher_butteur(equipe,n);
    afficher_jeune_age(equipe,n);
}

void enregistrer_fichier(joueur equipe[],int n,FILE *f){
    for(int i=0;i<n;i++){
        fprintf(f,"id : %d, nom : %s, prenom : %s, Numero Maillot %d, Post : %s, Age : %d, Buts %d, Date Inscription %d/%d/%d, Status %s **\n",
            equipe[i].id_joueur,
            equipe[i].nom,
            equipe[i].prenom,
            equipe[i].numeroMaillot,
            equipe[i].poste,
            equipe[i].age,
            equipe[i].buts,
            equipe[i].dateInscription.j,equipe[i].dateInscription.m,equipe[i].dateInscription.a,
            equipe[i].statut);
    }
}

void main_2(){
    FILE *f;
    f=fopen("equipe.txt","w+");
    joueur equipe[MAX];
    int n=0;
    int x=0;
    int choix =0;
    while(x==0){
        int i = 0;
        printf(BLU);
        print_header_footer();
        print_elem_menu(" 1. Ajouter un ou plusieur joueur ." ,BLU);
        print_elem_menu(" 2. Afficher les joueur d'equipe." ,GRN);
        print_elem_menu(" 3. Modifier un joueur." ,YEL);
        print_elem_menu(" 4. Supprimer un joueur." ,MAG);
        print_elem_menu(" 5. Rechercher un joueur." ,CYN);
        print_elem_menu(" 6. Statistiques du l'equipe." ,WHT);
        print_elem_menu(" 7. Quiter le program." ,RED);
        print_header_footer();
        printf("\n"reset);
        printf("Donner votre choix : ");
        scanf("%d",&choix);
        if(choix <1 || choix >7){
            do {
                printf("Donner un choix convenable : ");
                scanf("%d",&choix);
            } while(choix <1 && choix >7);
        }
        switch (choix){
            case 1 :
                printf(BLU);
                n=fentre_ajout(equipe,n);
                break;
            case 2 :
                printf(GRN);
                fenetre_affichage(equipe,n);
                break;
            case 3 :
                printf(YEL);
                fenetre_choix_modification_par_nom_ou_ident(equipe,n);
                break;
            case 4 :
                printf(MAG);
                fenetre_supprimer(equipe,n);
                break;
            case 5 :
                printf(CYN);
                fenetre_recherche_joueur(equipe,n);
                break;
            case 6 :
                printf(WHT);
                fenetre_statistique(equipe,n);
                break;
            case 7 :
                x=1;
                return;
        }
        printf("Appuyer sur entrer ! "reset);
		getchar();
		getchar();
		system("cls");
    }
}



