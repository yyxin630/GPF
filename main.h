#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED



#endif // MAIN_H_INCLUDED
int TACHE;
int Lmax;
int **info_tache;

int **info_site;

int *ordre;
int *voyage;

int** initial_infor_tache();
int** initial_infor_site();
void initial_ordre();
void initial_voyage();
int Calcule_Lmax(int *voy);
int *shift_voyage_droite(int val_voyage,int position);
int *shift_voyage_left(int val_voyage,int position);
int *swap_voyage(int val1_voyage,int val2_voyage,int position1,int position2);
int *swap_dans_voyage(int val_voyage,int position1,int position2);
void print_ordre(int *ordre);
void print_voyage(int *voyage);
void free_info_tache(int **info_tache);
void free_info_site(int **info_site);
void free_ordre(int *ordre);
void free_voyage(int *voyage);
