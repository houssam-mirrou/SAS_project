#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define TAILLE 50
#include <string.h>
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RESET "\033[0m"
#include <ctype.h>
#define TOTAL_WIDTH (col_width * 9 + 40)

//la decoration du code 

int col_width = 14;

//print header **

void print_semi_head(){
    int i;
    printf("*");
	for(i=0;i<col_width+3;i++){
		printf("*");
	}
}

void print_header_footer(){
    for (int i = 0; i < TOTAL_WIDTH; i++) printf("*");
    printf("\n");
}

//structure de date

typedef struct date {
    int j,m,a;
} date;

//structure joueur

typedef struct joueur {
    int id_joueur;
    char nom[TAILLE];
    char prenom[TAILLE];
    int numeroMaillot;
    char poste[TAILLE];
    int age;
    int buts;
    date dateInscription;
    char statut[TAILLE];
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
    if(age<15 && age>60){
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


// For one row (like joueur values, menu, choix)
void print_row(char titre[]) {
    printf("** %-*s **\n", TOTAL_WIDTH - 6, titre); // keeps margin
}

void print_row_menu(char titre[]) {
    printf("* %-*s *\n", TOTAL_WIDTH - 4, titre); // keeps margin
}

//fonction pour ecrire les valeurs du joueur

void print_value(joueur jou){
    char buffer[300];
    char date[12];
    sprintf(date, "%02d/%02d/%04d", 
            jou.dateInscription.j, 
            jou.dateInscription.m, 
            jou.dateInscription.a);
    
    sprintf(buffer,"%-*d ** %-*s ** %-*s ** %-*d ** %-*s ** %-*d ** %-*d ** %-*s ** %-*s", 
        col_width, jou.id_joueur,
        col_width, jou.nom,
        col_width, jou.prenom,
        col_width, jou.numeroMaillot,
        col_width, jou.poste,
        col_width, jou.age,
        col_width, jou.buts,
        col_width, date,
        col_width, jou.statut);
    print_row(buffer);
}


//fontion pour ecrire entétte du tableaux

void print_entete_du_tableaux(){
    char temp [9][19] = {"Id","Nom","Prenom","NumeroMaillot","Poste","Age","Buts","Date Insrip","Statut"};
    char buffer[300];
    print_header_footer();
    sprintf(buffer,"%-*s ** %-*s ** %-*s ** %-*s ** %-*s ** %-*s ** %-*s ** %-*s ** %-*s", 
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
    print_row(buffer);
    print_header_footer();
}

//fonction pour ecrire les element du menu

void print_elem_menu (char titre[],char color[]) {
    printf("%s",color);
    print_row_menu(titre);
}

//deux fonction d'affichage d'un elemnt du menu conciderons le type d'elemnt

void print_elem_menu_avec_extra_par_int (char titre[],char color[],int elem) {
    char buffer[200];
    sprintf(buffer, "%s %d", titre, elem); 
    print_row_menu(buffer);
}
void print_elem_menu_avec_extra_par_float (char titre[],char color[],float elem) {
    char buffer[200];
    sprintf(buffer, "%s %.2f", titre, elem); 
    print_row_menu(buffer);
}

//fonction pour ecriver le star de l'equipe

void print_elem_menu_star_dequipe (char titre[],char color[],joueur temp) {
    char buffer[200];
    sprintf(buffer, "%s %s %s avec %d buts !!", titre, temp.prenom,temp.nom,temp.buts); 
    print_row_menu(buffer);
}

//fonction pour ecriver le jeune et l'agé de l'equipe

void print_elem_menu_jeune_age (char titre[],char color[],joueur temp) {
    char buffer[200];
    sprintf(buffer, "%s %s %s avec l'age %d", titre, temp.nom,temp.prenom,temp.age); 
    print_row_menu(buffer);
}

//fonction pour ecrire un element centrer

void print_centered(char titre[]) {
    int len = strlen(titre);
    int pad = TOTAL_WIDTH - len - 4; // -4 for "**  **"
    int left = pad / 2;
    int right = pad - left;
    printf("**%*s%s%*s**\n", left, "", titre, right, "");
}

//fonction pour printer un chaine de carrctere comme un message ou erreur

void print_error_ou_titre(char titre[] ){
    print_header_footer();
    print_centered(titre);
    print_header_footer();
}

void print_error_ou_titre_avec_index(char titre[] ,int idx){
    char buffer[200];
    sprintf(buffer, "%s (id = %d)", titre, idx);
    print_header_footer();
    print_centered(buffer);
    print_header_footer();
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

//fonction pour transformer la chaine en minuscule

char* transformer_miniscule(char temp[]){
    int i=0;
    while(temp[i]!='\0'){
        temp[i]=tolower(temp[i]);
        i++;
    }
    return temp;
}

char* supprimer_espace(char tab[]){
    int i;
    int cpt;
    while(tab[i]!='\0'){
        if(tab[i] == ' '){
            int j=i;
            while(est_car(tab[j]) ==0){
                j++;
            }
            tab[i]=tab[j];
        }
        i++;
    }
}

char* suprrim2(char tab[]){
    int
}

//compter combien joueur est titulaire

int compter_titul(joueur equipe[] , int n){
    int i=0;
    int cpt=0;
    for(i=0;i<n;i++){
        if(strcmp(equipe[i].statut,"titulaire") == 0){
            cpt++;
        }
    }
    return cpt;
}

//ajouter un joueur

int ajouter_un_joueuer(joueur equipe[],int n){
    char nm[TAILLE],pren[TAILLE];

    //ajouter le nom avec verification

    printf("Donner le nom de joueur : ");
    scanf("%s",nm);
    if(verif_nom(nm) == 0){
        do{
            printf("Donner un nom propre pour le joueur : ");
            scanf("%s",nm);
        } while (verif_nom(nm) == 0);
    }
    strcpy(nm,transformer_miniscule(nm));
    //ajouter le prenom avec verification

    printf("Donner le prenom de joueur : ");
    scanf("%s",pren);
    if(verif_nom(pren) == 0){
        do{
            printf("Donner un prenom propre pour le joueur : ");
            scanf("%s",pren);
        } while (verif_nom(pren) == 0);
    }
    strcpy(pren,transformer_miniscule(pren));
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

    char poste[TAILLE];
    printf("Donner le poste du joueur : ");
    scanf("%s",poste);
    strcpy(poste,transformer_miniscule(poste));
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
    if(age<15 || age >100){
        do{
            printf("Donner un age supperieur a 15 ans : ");
            scanf("%d",&age);
        } while(age<15 || age>100);
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

    char stat[TAILLE];
    printf("Donner le statut de joueur : ");
    scanf("%s",stat);
    int cpt = compter_titul(equipe,n);
    if(verifier_statut(stat) == 0){
        do {
            printf("Le statut doit etre si titulaire si remplacant : ");
            scanf("%s",stat);
        } while(verifier_statut(stat) == 0);
    }
    else{
        if(cpt==11){
            do {
                printf("Il y a deja 11 titulaire dans l'equipe tu doit le saisie en remplacant puis modifier un statut d'un joueur : ");
                scanf("%s",stat);
            } while(verifier_statut(stat) == 0 || strcmp(stat,"titulaire")==0);
        }
    }
    strcpy(stat,transformer_miniscule(stat));
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
    printf(BLU);
    print_error_ou_titre("Fenetre d'ajout des joueurs");
    printf(RESET);
    print_elem_menu("1. Ajouter un seul joueur :",CYN);
    print_elem_menu("2. Ajouter multiple joueur :",CYN);
    print_elem_menu("0. Quitter :",RED);
    print_header_footer();
    int choix = 0;
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<0 || choix>2){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <0 && choix >2);
    }
    switch (choix){
        case 0 :
            return n;
        case 1:
            n=ajouter_un_joueuer(equipe,n);
            break;
        case 2 :
            n=ajout_multiple_joueur(equipe,n);
            break;
    }       
    printf(GRN);
    print_error_ou_titre("Le joueur a ete ajouter avec succee .");
    printf(RESET);
    return n;
}

//tri par ordre alphabetique

int section_tri_ordre_alph(joueur equipe[],int debut,int fin){
    int i=debut-1;
    joueur pivot = equipe[fin];
    int j;
    for(j=debut;j<fin;j++){
        if(strcmp(equipe[j].nom,pivot.nom) <0){
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

//tri par ordre alphabetique

int section_tri_ordre_statut(joueur equipe[],int debut,int fin){
    int i=debut-1;
    joueur pivot = equipe[fin];
    int j;
    for(j=debut;j<fin;j++){
        if(strcmp(equipe[j].statut,pivot.statut) <0){
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
        if(equipe[j].age<pivot.age){
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

//section par id

int section_tri_id(joueur equipe[],int debut,int fin){
    int i=debut-1;
    joueur pivot = equipe[fin];
    int j;
    for(j=debut;j<fin;j++){
        if(equipe[j].id_joueur<pivot.id_joueur){
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
        if(strcmp(equipe[j].poste,pivot.poste)<0){
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
        if(choix == 4){
            int pi = section_tri_id(equipe,debut,fin);
            tri_equipe(equipe,debut,pi-1,choix);
            tri_equipe(equipe,pi+1,fin,choix);
        }
        if(choix == 5){
            int pi = section_tri_ordre_statut(equipe,debut,fin);
            tri_equipe(equipe,debut,pi-1,choix);
            tri_equipe(equipe,pi+1,fin,choix);
        }
    }
}

//afficher une equipe

void afficher_equipe(joueur equipe[],int n){
    printf(CYN);
    print_entete_du_tableaux();
    printf(WHT);
    for(int i=0;i<n;i++){
        print_value(equipe[i]);
    }
    printf(RESET);
    printf(CYN);
    print_header_footer();
    printf(RESET);
}

//fenetre d'affichage baser sur le choix

void fenetre_affichage(joueur equipe[] ,int n){
    system("cls");
    if(n==0){
        printf(RED);
        print_error_ou_titre("L'equipe n'a aucun joueur !! ");
        printf(RESET);
        return;
    }
    printf(BLU);
    print_error_ou_titre("Fenettre d'affichage (Tri de l'equipe)");
    printf(RESET);
    print_elem_menu("1. Afficher les joueurs trier le nom par ordre alphabetique.",CYN);
    print_elem_menu("2. Afficher les joueurs trier par age.",CYN);
    print_elem_menu("3. Afficher les joueurs trier par poste.",CYN);
    print_elem_menu("4. Afficher les joueur trier par id",CYN);
    print_elem_menu("5. Afficher les joueur trier par le statut",CYN);
    print_elem_menu("0. Quitter",RED);
    print_header_footer();
    int choix = -1;
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<0 || choix>5){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <0 && choix >5);
    }
    switch (choix){
        case 0 :
            return;
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
            break;
        case 4 :
            tri_equipe(equipe,0,n-1,choix);
            afficher_equipe(equipe,n);
            break;
        case 5 :
            tri_equipe(equipe,0,n-1,choix);
            afficher_equipe(equipe,n);
            break;
    } 
}

//modifier la poste

void modifier_poste(joueur equipe[],int idx){
    char poste[TAILLE];
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
    if(age<15 || age >100){
        do{
            printf("Donner un age supperieur a 15 ans : ");
            scanf("%d",&age);
        } while(age<15 && age > 100);
    }
    
    equipe[idx].age=age;
}

//modifier les buts

void modifier_but(joueur equipe[],int idx){
    int but ;
    printf("Donner les but du joueur : ");
    scanf("%d",&but);
    if(but<0){
        do{
            printf("les buts doit etre supperieur a 0 ! : ");
            scanf("%d",&but);
        } while(but<0);
    }
    equipe[idx].buts=but;
}



//modifier le statu d un joueur

void modifier_statut(joueur equipe[],int idx,int n){
    char stat[TAILLE];
    printf("Donner le nouvelle statut de joueur : ");
    scanf("%s",stat);
    int cpt = compter_titul(equipe,n);
    if(cpt>=11){
        do {
            printf(RED);
            printf("Il y a deja 11 titulaire dans l'equipe tu doit le saisie en remplacant puis modifier un statut d'un joueur : ");
            scanf("%s",stat);
            printf(RESET);
        } while(verifier_statut(stat) == 0 || strcmp(stat,"titulaire")==0);
    }
    if(verifier_statut(stat) == 0){
        do {
            printf("Le statut doit etre si titulaire si remplacant : ");
            scanf("%s",stat);
        } while(verifier_statut(stat) == 0);
    }
    strcpy(equipe[idx].statut,stat);
}

//fenetre de choix de modification

void fenetre_choix_modification(joueur equipe[],int idx,int n){
    system("cls");
    print_header_footer();
    print_elem_menu("1. Modifier un poste joueur.",CYN);
    print_elem_menu("2. Modifier l'age du joueur.",CYN);
    print_elem_menu("3. Modifier les buts marque par le joueur.",CYN);
    print_elem_menu("4. Modifier le status d un joueur.",CYN);
    print_elem_menu("0. Quitter.",RED);
    print_header_footer();
    int choix = -1;
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<0 || choix>4){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <0 && choix >4);
    }
    switch(choix){
        case 0 :
            return;
        case 1:
            modifier_poste(equipe,idx);
            break;
        case 2:
            modifier_age(equipe,idx);
            break;
        case 3:
            modifier_but(equipe,idx);
            break;
        case 4:
            modifier_statut(equipe,idx,n);
            break;
    }
    printf(GRN);
    print_error_ou_titre("Le joueur apres la modification.");
    printf(RESET);
    printf(CYN);
    print_entete_du_tableaux();
    print_value(equipe[idx]);
    print_header_footer();
    printf(RESET);
}

//fenetre de choix de modification par le nom ou identite

void fenetre_choix_modification_par_nom_ou_ident(joueur equipe[],int n){
    system("cls");
    if(n==0){
        printf(RED);
        print_error_ou_titre("L'equipe est vide !!");
        printf(RESET);
        return;
    }
    printf(BLU);
    print_error_ou_titre("Fenetre de choix des modification");
    printf(RESET);
    print_elem_menu("1. Modifier par nom et prenom.",CYN);
    print_elem_menu("2. Modifier par identiter de joueur.",CYN);
    print_elem_menu("0. Quitter.",RED);
    print_header_footer();
    int choix = -1;
    printf(CYN);
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<0 || choix>2){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <0 && choix >2);
    }
    int idx=-1;
    int id=-1;
    char nm[TAILLE],pren[TAILLE];
    switch (choix){
        case 0 :
            return;
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
            fenetre_choix_modification(equipe,idx,n);
            break;
        case 2 :
            printf("Donner l'id du joueur : ");
            scanf("%d",&id);
            if(id<1){
                do {
                    printf("L'id des joueur commence par 1, donner une nouveaux id : ");
                    scanf("%d",&id);
                } while(id<1);
            }
            idx=recherche_par_id_joueur(equipe,n,id);
            if(idx == -1){
                print_error_ou_titre("Le joueur n'existe pas dans l'equipe !!");
                break;
            }
            fenetre_choix_modification(equipe,idx,n);
            break; 
    } 
}

//fonction_pour_supprimer_un_joueur_par_identifiant

int supprimer_un_joueur(joueur equipe[] ,int n ,int idx){
    int i=0;
    for(i=idx;i<n-1;i++){
        equipe[i]=equipe[i+1];
    }
    n--;
    return n;
}

//fonction pour supprimer un joueur

int fenetre_supprimer(joueur equipe[],int n){
    system("cls");
    if(n==0){
        printf(RED);
        print_error_ou_titre("L'equipe est vide !!");
        printf(RESET);
        return n;
    }
    printf(BLU);
    print_error_ou_titre("Fenetre de choix des suppressions");
    printf(RESET);
    print_elem_menu("1. Supprimer par nom et prenom.",CYN);
    print_elem_menu("2. Supprimer par identiter de joueur.",CYN);
    print_elem_menu("0. Quitter.",RED);
    print_header_footer();
    int choix = -1;
    int idx=-1;
    char nm[TAILLE],pren[TAILLE];
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<0 || choix>2){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <0 && choix >2);
    }
    switch (choix){
        case 0 :
            return n;
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
        n=supprimer_un_joueur(equipe,n,idx);
        break;
    case 2 :
        int id=0;
        printf("Donner l'id du joueur : ");
        scanf("%d",&id);
        if(id<0){
            do {
                printf("L'id des joueur commence par 1, donner une nouvelle id : ");
                scanf("%d",&id);
            } while(id<1);
        }
        idx = recherche_par_id_joueur(equipe,n,id);
        if(idx == -1){
            print_error_ou_titre("Le joueur n'existe pas !!");
            return n;
        }
        n=supprimer_un_joueur(equipe,n,idx);
        break;
    }
    printf(GRN);
    print_error_ou_titre("L'equipe apres la suppresion : ");
    afficher_equipe(equipe,n);
    print_header_footer();
    printf(RESET);
    return n;
}

//rechercher par post

void rechercher_par_post(joueur equipe[],int n,char post[]){
    print_header_footer();
    print_entete_du_tableaux();
    int i;
    for(i=0;i<n;i++){
        if(strcmp(equipe[i].poste,post) == 0){
            print_value(equipe[i]);
        }
    }
    print_header_footer();
}

//rechercher un joueur

void fenetre_recherche_joueur(joueur equipe[],int n){
    system("cls");
    if(n==0){
        printf(RED);
        print_error_ou_titre("L'equipe est vide !!!");
        printf(RESET);
        return;
    }
    print_error_ou_titre("Fenettre de recherche");
    print_elem_menu("1. Rechercher par le nom.",CYN);
    print_elem_menu("2. Rechercher par l'identiter de joueur.",MAG);
    print_elem_menu("3. Rechercher par post.",CYN);
    print_elem_menu("0. Quitter.",RED);
    print_header_footer();
    int choix = -1;
    int idx=-1;
    char nm[TAILLE],pren[TAILLE];
    printf("Donner votre choix : ");
    scanf("%d",&choix);
    if(choix<0 || choix>3){
        do {
            printf("Donner un choix convenable : ");
            scanf("%d",&choix);
        } while(choix <0 && choix >3);
    }
    switch (choix){
    case 0 :
        return;
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
        strcpy(nm,transformer_miniscule(nm));
        idx=rechercher_par_nom(equipe,n,nm);
        if(idx == -1){
            print_error_ou_titre("Le joueur n'existe pas dans l'equipe !!");
            return;
        }
        print_entete_du_tableaux();
        print_value(equipe[idx]);
        print_header_footer();
        break;
    case 2:
        int id=0;
        printf("Donner l'id du joueur : ");
        scanf("%d",&id);
        if(id<1){
            do {
                printf("L'id des joueur commence par 1, donner une nouvelle id : ");
                scanf("%d",&id);
            } while(id<1);
        }
        idx = recherche_par_id_joueur(equipe,n,id);
        if(idx == -1){
            print_error_ou_titre("Le joueur n'existe pas !!");
            return;
        }
        print_entete_du_tableaux();
        print_value(equipe[idx]);
        print_header_footer();
        break;
    case 3:
        char temp[TAILLE];
        printf("Donner le post que vous vouler le rechercher : ");
        scanf("%s",temp);
        if(verifier_poste(temp)==0){
            do {
                printf("Donner un poste depuis ces example (gardien, defenseur, milieu, attaquant) :");
                scanf("%s",temp);
            } while(verifier_poste(temp) == 0);
        }
        rechercher_par_post(equipe,n,temp);
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
    return moy;
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
    int idx=0;
    if(n==1){
        return equipe[0];
    }
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
    joueur best = max_but_joueur(equipe,n);
    char buffer[200];
    sprintf(buffer, "le butteur de l'equipe est %s %s avec %d buts.", best.prenom,best.nom,best.buts); 
    print_row_menu(buffer);
}

//fonction afficher le jeune et plut age
void afficher_jeune_age(joueur equipe[],int n){
    if(n==0){
        return;
    }
    int i=0;
    int min,max;
    joueur jeune,age;
    min=max=equipe[0].age;
    jeune=age=equipe[0];
    if(n==1){
        print_elem_menu("Il y'a un seul joueur dans l'equipe :",WHT);
        print_entete_du_tableaux();
        print_value(equipe[0]);
        print_header_footer();
    }
    if(n>1){
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
        print_elem_menu_jeune_age("Le joueur le plus jeune de l'equipe est ",WHT,jeune);
        print_elem_menu_jeune_age("Le joueur le plus age de l'equipe est ",WHT,age);
    }
}

//fenetre de statistique

void fenetre_statistique(joueur equipe[],int n){
    system("cls");
    
    if(n==0){
        printf(RED);
        print_error_ou_titre("L'equipe est vide !!");
        printf(RESET);
        return;
    }
    printf(BLU);
    print_error_ou_titre("Fenetre des Statistiques");
    printf(RESET);
    printf("\n");

    int but ;
    printf("Donner le nombre de but pour les statistique : ");
    scanf("%d",&but);
    if(but<0){
        do{
            printf("les buts doit etre supperieur a 0 ! : ");
            scanf("%d",&but);
        } while(but<0);
    }
    printf("\n");

    float moy=moyen_des_age(equipe,n);
    print_header_footer();
    print_elem_menu_avec_extra_par_int("Le nombre totale des joueur est : ",CYN,n);
    print_elem_menu_avec_extra_par_float("Le moyenne des age est: ",CYN,moy);
    afficher_les_joueur_avec_x_but(equipe,n,but);
    afficher_butteur(equipe,n);
    afficher_jeune_age(equipe,n);
    print_header_footer();
}

//enregister les informations du joueur dans un fichier

void enregistrer_fichier(joueur equipe[],int n){
    system("cls");
    FILE *f;
    if(n==0){
        printf(RED);
        print_error_ou_titre("L'equipe est vide !!");
        printf(RESET);
        return;
    }
    f=fopen("sauvegarde.txt","w+");
    if(n==0){
        print_error_ou_titre("L equipe est vide !!");
        return;
    }
    fprintf(f,"Id\tNom\tPrenom\tNumero du Maillot\tPost\tAge\tBut\tDate Inscription\tStatus\n");
    for(int i=0;i<n;i++){
        fprintf(f,"%d\t%s\t%s\t%d\t%s\t%d\t%d\t%d/%d/%d\t%s\n",
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
    fflush(f);
    fclose(f);
    printf(GRN);
    print_error_ou_titre("L'enregistrement dans le fichier sauvegarde.txt a fait en succes");
    printf(RESET);
}

//lire depuis un fichier

int lire_depui_fichier(joueur equipe[], int n){
    FILE *f;
    system("cls");
    f=fopen("equipe.txt","r");
    if(f==NULL){
        printf(RED);
        print_error_ou_titre("Il y a un erreur lorsque ouverir le fichier !! ");
        printf(RESET);
    }
    joueur temp;
    char c[256];
    fgets(c,sizeof(c),f);
    int ret=0;
    while ((ret = fscanf(f, "%d\t%s\t%s\t%d\t%s\t%d\t%d\t%d/%d/%d\t%s\n",
            &temp.id_joueur,
            temp.nom,
            temp.prenom,
            &temp.numeroMaillot,
            temp.poste,
            &temp.age,
            &temp.buts,
            &temp.dateInscription.j, &temp.dateInscription.m, &temp.dateInscription.a,
            temp.statut)) == 11) {
        
        if (recherche_par_nom_prenom(equipe, n, temp.nom, temp.prenom) == -1) {
            equipe[n].id_joueur = id_global;
            strcpy(equipe[n].nom, transformer_miniscule(temp.nom));
            strcpy(equipe[n].prenom, transformer_miniscule(temp.prenom));
            equipe[n].numeroMaillot = temp.numeroMaillot;
            strcpy(equipe[n].poste, transformer_miniscule(temp.poste));
            equipe[n].age = temp.age;
            equipe[n].buts = temp.buts;
            equipe[n].dateInscription = temp.dateInscription;
            strcpy(equipe[n].statut, transformer_miniscule(temp.statut));
            n++;
            id_global++;
        }
    }
    fclose(f);
    printf(GRN);
    print_error_ou_titre("La lecture depuis un fichier a faites en succee.");
    printf(RESET);
    return n;
}

//stocker les joueur titulaire dans un tableaux

joueur* stocker_tab_tit(joueur equipe[],int n){
    int i,j=0;
    joueur *temp = (joueur*) malloc(sizeof(joueur) *11);
    for(i=0;i<n;i++){
        if(strcmp(equipe[i].statut,"titulaire") == 0){
            temp[j]=equipe[i];
            j++;
        }
    }
    return temp;
}

//fonction qui stock les joueur titulaire et par post dans un destination

void return_joueur_par_post_etape1(joueur equipe[],int n,char post[],int taille,joueur dest[]){
    int i,j;
    j=0;
    for(i=0;i<n;i++){
        if(strcmp(equipe[i].poste,post) == 0 && strcmp(equipe[i].statut,"titulaire") == 0){
            dest[j]=equipe[i];
            j++;
        }
    }
}

//printer la plan des joueur

void print_header_plan(){
    int i;
    printf("+");
    for(i=0;i<60;i++){
        printf("-");
    }
    printf("+\n");
}

void print_empty_plan(){
    int i;
    printf("|");
    for(i=0;i<60;i++){
        printf(" ");
    }
    printf("|\n");
}

int len_int(int temp){
    int cpt=0;
    while(temp>0){
        temp/=10;
        cpt++;
    }
    return cpt;
}

//ecerire un joueur dans le plan

void print_un_joueur(joueur temp) {
    int total_width = 60;
    char buffer[50];
    sprintf(buffer, "%d %s", temp.numeroMaillot, temp.nom);
    int content_len = strlen(buffer);

    int pad_width = total_width - content_len;
    int left_padding = pad_width / 2;
    int right_padding = pad_width - left_padding;

    printf("|%*s%s%*s|\n", left_padding, "", buffer, right_padding, "");
}

void print_deux_joueur(joueur temp1, joueur temp2) {
    int total_width = 60;
    int middlepad = 10;

    char buffer1[30], buffer2[30];
    sprintf(buffer1, "%d %s", temp1.numeroMaillot, temp1.nom);
    sprintf(buffer2, "%d %s", temp2.numeroMaillot, temp2.nom);

    int content_len = strlen(buffer1) + strlen(buffer2) + middlepad;
    int pad_width = total_width - content_len;
    int left_padding = pad_width / 2;
    int right_padding = pad_width - left_padding;

    printf("|%*s%s%*s%s%*s|\n",
           left_padding, "", buffer1, middlepad, "", buffer2, right_padding, "");
}

void print_trois_joueur(joueur temp1, joueur temp2, joueur temp3) {
    int total_width = 60;
    int middlepad = 4;

    char b1[30], b2[30], b3[30];
    sprintf(b1, "%d %s", temp1.numeroMaillot, temp1.nom);
    sprintf(b2, "%d %s", temp2.numeroMaillot, temp2.nom);
    sprintf(b3, "%d %s", temp3.numeroMaillot, temp3.nom);

    int content_len = strlen(b1) + strlen(b2) + strlen(b3) + 2 * middlepad;
    int pad_width = total_width - content_len;
    int left_padding = pad_width / 2;
    int right_padding = pad_width - left_padding;

    printf("|%*s%s%*s%s%*s%s%*s|\n",
           left_padding, "", b1, middlepad, "", b2, middlepad, "", b3, right_padding, "");
}

void print_quatre_joueur(joueur temp1, joueur temp2, joueur temp3,joueur temp4){
    int total_width = 60;
    int middlepad = 4;

    char b1[30], b2[30], b3[30],b4[30];
    sprintf(b1, "%d %s", temp1.numeroMaillot, temp1.nom);
    sprintf(b2, "%d %s", temp2.numeroMaillot, temp2.nom);
    sprintf(b3, "%d %s", temp3.numeroMaillot, temp3.nom);
    sprintf(b4, "%d %s", temp4.numeroMaillot, temp4.nom);

    int content_len = strlen(b1) + strlen(b2) + strlen(b3) + strlen(b4) + 3 * middlepad;
    int pad_width = total_width - content_len;
    int left_padding = pad_width / 2;
    int right_padding = pad_width - left_padding;

    printf("|%*s%s%*s%s%*s%s%*s%s%*s|\n",
           left_padding, "", b1, middlepad, "", b2, middlepad, "", b3, middlepad, "", b4, right_padding, "");
}


//fonction qui calcule le nombre des titulaire

int nbr_titul(joueur equipe[],int n){
    int i;
    int cpt=0;
    for(i=0;i<n;i++){
        if(strcmp(equipe[i].statut,"titulaire") == 0){
            cpt++;
        }
    }
    return cpt;
}

//fonction qui afficher le plan d'equipe


void afficher_le_plan(joueur equipe[], int n) {
    system("cls");
    if(nbr_titul(equipe,n)<11){
        printf(RED);
        print_error_ou_titre("l'equipe a moins de 11 titulaire !!");
        printf(RESET);
        return;
    }
    if(n==0){
        printf(RED);
        print_error_ou_titre("l'equipe est vide !!");
        printf(RESET);
        return;
    }
    joueur attaquant[3],milieu[3],defenseur[4],gardien[1];
    return_joueur_par_post_etape1(equipe, n, "attaquant", 3,attaquant);
    return_joueur_par_post_etape1(equipe, n, "milieu", 3,milieu);
    return_joueur_par_post_etape1(equipe, n, "defenseur", 4,defenseur);
    return_joueur_par_post_etape1(equipe, n, "gardien", 1,gardien);
                        
    print_header_plan();
    print_empty_plan();
    print_un_joueur(attaquant[0]);
    print_deux_joueur(attaquant[1],attaquant[2]);
    print_empty_plan();
    print_trois_joueur(milieu[0],milieu[1],milieu[2]);
    print_empty_plan();
    print_quatre_joueur(defenseur[0],defenseur[1],defenseur[2],defenseur[3]);
    print_empty_plan();
    print_un_joueur(gardien[0]);
    print_header_plan();
}


void main_2(){
    joueur equipe[MAX];
    int n=0;
    int x=0;
    int choix =0;
    while(x==0){
        int i = 0;
        printf(BLU);
        print_header_footer();
        print_elem_menu(" 1. Ajouter un ou plusieur joueur ." ,GRN);
        print_elem_menu(" 2. Afficher les joueur d'equipe." ,GRN);
        print_elem_menu(" 3. Modifier un joueur." ,CYN);
        print_elem_menu(" 4. Supprimer un joueur." ,RED);
        print_elem_menu(" 5. Rechercher un joueur." ,CYN);
        print_elem_menu(" 6. Statistiques du l'equipe." ,GRN);
        print_elem_menu(" 7. Enregistrer l equipe dans le fichier.",CYN);
        print_elem_menu(" 8. Liser les donner depuis un fichier.",CYN);
        print_elem_menu(" 9. Afficher le plan du l'equipe." ,GRN);
        print_elem_menu(" 10. Quiter le program." ,RED);
        
        if(n!=0){
            joueur temp = max_but_joueur(equipe,n);
            if(temp.buts>10){
                print_elem_menu_star_dequipe(" Le star de l'equipe est ",MAG,temp);
            }
        }
        print_header_footer();
        printf("\n"RESET);
        printf("Donner votre choix : ");
        scanf("%d",&choix);
        if(choix <1 || choix > 10){
            do {
                printf("Donner un choix convenable : ");
                scanf("%d",&choix);
            } while(choix <1 && choix >10);
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
                n=fenetre_supprimer(equipe,n);
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
                enregistrer_fichier(equipe,n);
                break;
            case 8 :
                n=lire_depui_fichier(equipe,n);
                break;
            case 9 :
                afficher_le_plan(equipe,n);
                break;
            case 10 :
                x=1;
                return;
                break;
        }
        printf("Appuyer sur entrer ! "RESET);
		getchar();
		getchar();
		system("cls");
    }
}



