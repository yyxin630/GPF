
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
int main()
{
    int i,count;
    int *nbr_voy=NULL;
    int sum;
    int position,position1,position2;
    int Lmax_index;
    int *tchange=NULL,*mieux=NULL;
    int j,k,index;
	int visited[TACHE];
    info_tache=initial_infor_tache();
    info_site=initial_infor_site();

    if((ordre=(int *)malloc(sizeof(int)*TACHE))==NULL)
        exit(-1);
    if((voyage=(int *)malloc(sizeof(int)*2*TACHE))==NULL)
        exit(-1);
    if((nbr_voy=(int *)malloc(sizeof(int)*TACHE))==NULL)
        exit(-1);

    //initial ordre()
    for(i=0;i<TACHE;i++)
        visited[i]=0;

    i=0;
	while(i<TACHE){
		for(j=0;j<TACHE;j++){
			if(visited[j]==0){
				index=j;
				break;
			}
		}
		for(k=j+1;k<TACHE;k++){
			if((info_tache[1][k]<=info_tache[1][index])&&(visited[k]==0)){
				index=k;
			}
		}
		ordre[i]=index;
		visited[index]=1;
		i++;
	}
	print_ordre(ordre);
    initial_voyage();  //initial int* voyage
    print_voyage(voyage);

    //printf("%d",voyage[0]);
	//printf("%d\n",TACHE);
	//printf("%d\n",info_tache[0][2]);
	//printf("%d",info_site[0][3]);
	Lmax=Calcule_Lmax(voyage);
	printf("Lmax= %d",Lmax);
    printf("\n");

	mieux=voyage;
    count=1;

	do{
	    printf("\n \n");
	    printf("************** Literation %d ***********\n",count);
	    print_ordre(ordre);
	    print_voyage(voyage);
	     sum=0;
         Lmax_index=Lmax;
         mieux=voyage;
         nbr_voy[0]=voyage[0];
	     for(i=1;i<TACHE;i++){
		   sum=sum+nbr_voy[i-1];
		   nbr_voy[i]=voyage[sum+i];
	     }

        //Swap_dans_voyage
        printf("Swap_dans_voyage:\n");
        for(i=0;i<TACHE-1;i++){
            for(position1=1;position1<nbr_voy[i];position1++){
                for(position2=position1+1;position2<=nbr_voy[i];position2++){
                     tchange=swap_dans_voyage(i,position1,position2);
                     if(Lmax>Calcule_Lmax(tchange)){
                        Lmax=Calcule_Lmax(tchange);
                        printf("Lmax=%d : ",Lmax);
                        mieux=tchange;
                        print_voyage(tchange);
                     }else{
                         print_voyage(tchange);
                         free(tchange);
                         tchange=NULL;
                     }
                }
            }
        }

        //Swap_voyage
        printf("Swap_voyage:\n");
        for(i=0;i<TACHE-1;i++){
            for(position1=1;position1<=nbr_voy[i];position1++){
             for(j=i+1;j<TACHE;j++){
                for(position2=1;position2<=nbr_voy[j];position2++){
                    tchange=swap_voyage(i,j,position1,position2);
                    if(Lmax>Calcule_Lmax(tchange)){
                            Lmax=Calcule_Lmax(tchange);
                            printf("Lmax=%d : ",Lmax);
                            mieux=tchange;
                            print_voyage(tchange);
                            print_ordre(ordre);
                         }else{
                             print_voyage(tchange);
                             free(tchange);
                             tchange=NULL;
                             print_ordre(ordre);
                         }
                }
            }
            }
        }

        //Shift_voyage_droite
        printf("Shift_voyage_droite:\n");
       for(i=0;i<TACHE-1;i++){
           if(nbr_voy[i]!=0){
                tchange=shift_voyage_droite(i);
                if(Lmax>Calcule_Lmax(tchange)){
                            Lmax=Calcule_Lmax(tchange);
                            printf("Lmax=%d\ : ",Lmax);
                            mieux=tchange;
                            print_voyage(tchange);
                         }else{
                             print_voyage(tchange);
                             free(tchange);
                             tchange=NULL;
                         }
        }
       }

        //Shift_voyage_left
        printf("Shift_voyage_gauche:\n");
        for(i=1;i<TACHE;i++){
            if(nbr_voy[i]!=0){
                tchange=shift_voyage_gauche(i);
                if(Lmax>Calcule_Lmax(tchange)){
                            Lmax=Calcule_Lmax(tchange);
                            printf("Lmax=%d : ",Lmax);
                            mieux=tchange;
                            print_voyage(tchange);
                         }else{
                             print_voyage(tchange);
                             free(tchange);
                             tchange=NULL;
                         }
        }
        }

        free(voyage);
        voyage=NULL;
        voyage=mieux;
        count++;
	}while(Lmax!=Lmax_index);
    printf("-------------------------------");
	printf("meilleur ");
	//printf("%d",voyage[0]);
	print_voyage(voyage);

    return 0;
}

/*void initial_ordre(){
    int i=0,j,k,index;
	int visited[TACHE];
	for(i=0;i<TACHE;i++)
        visited[i]=0;
	while(i<TACHE){
		for(j=0;j<TACHE;j++){
			if(visited[j]==0){
				index=j;
				break;
			}
		}
		for(k=j+1;k<TACHE;k++){
			if((info_tache[1][k]<=info_tache[1][index])&&(visited[k]==0)){
				index=k;
			}
		}
		printf("%d",index);
		ordre[i]=index;
		visited[index]=1;
		i++;
	}

}*/
void initial_voyage(){
    int i;
	int fin_ordre[TACHE];
	int date_actu,site_actu;
	int index_dernier_voyage,nbr_voyage;
	int date_group,date_non_group;
    memset(voyage,0,sizeof(int)*TACHE*2);

	//initialiser l'ordonnence par EDD
	fin_ordre[0]=info_tache[0][ordre[0]];
    for(i=1;i<TACHE;i++){
        fin_ordre[i]=fin_ordre[i-1]+info_tache[0][ordre[i]];
    }

	//initialiser le voyage
	date_actu=fin_ordre[0]+info_site[ordre[0]][TACHE];
	site_actu=ordre[0];
	index_dernier_voyage=0;
	nbr_voyage=1;
	voyage[index_dernier_voyage]=nbr_voyage;
	voyage[1]=ordre[0];
	for(i=1;i<TACHE;i++){
		date_group=date_actu+info_site[ordre[i]][site_actu];
		if(date_actu+info_site[site_actu][TACHE]>fin_ordre[i]){
			date_non_group=date_actu+info_site[site_actu][TACHE]+info_site[TACHE][ordre[i]];
		}else{
			date_non_group=fin_ordre[i]+info_site[TACHE][ordre[i]];
		}
		if(date_group<date_non_group){
			nbr_voyage++;
			voyage[index_dernier_voyage]=nbr_voyage;
			voyage[index_dernier_voyage+nbr_voyage]=ordre[i];
			date_actu=date_group;
		}else{
			index_dernier_voyage=index_dernier_voyage+nbr_voyage+1;
			nbr_voyage=1;
			voyage[index_dernier_voyage]=nbr_voyage;
			date_actu=date_non_group;
		}
		site_actu=ordre[i];
	}
}


int** initial_infor_tache(){
    int **inforTache;
	FILE *fp;
	unsigned int i,j;
	if((fp=fopen("infor.txt","r"))==NULL){
		printf("infor.txt ne peut pas ouvrir!");
		exit(-1);
	}else{
	fscanf(fp,"%d",&TACHE);   //lire nombre de taches

    inforTache=(int**)malloc(sizeof(int*)*2);
    for(i=0;i<2;i++){ //initiale inforTach
        inforTache[i]=(int*)malloc(sizeof(int)*TACHE);
        if(inforTache[i]==NULL){
            printf("initial_infor inforTache[i] malloc error.");
            exit(-1);
        }
    }

    for(i=0;i<2;i++){
        for(j=0;j<TACHE;j++){
            fscanf(fp,"%d",&inforTache[i][j]);
        }
    }

	return inforTache;
}
}

int** initial_infor_site(){
    int **inforSite;
    FILE *fp;
    unsigned int i,j;
    if((fp=fopen("infor.txt","r"))==NULL){
        printf("infor.txt ne peut pas ouvrir!");
		exit(-1);
    }
    for(i=0;i<3;i++)fscanf(fp,"%*[^\n]%*c");
    if((inforSite=(int**)malloc((TACHE+1)*sizeof(int*)))==NULL){  //initiale inforSite
        printf("initial_infor inforSite malloc error.");
        exit(-1);
    }

    i=0;
    while(!feof(fp)){
        if((inforSite[i]=(int*)malloc((TACHE+1)*sizeof(int)))==NULL){
            printf("initial_infor inforSite[i] malloc error.");
            exit(-1);
        }else{
            for(j=0;j<TACHE+1;j++)
                fscanf(fp,"%d",&inforSite[i][j]);
            i++;
        }
    }

    fclose(fp);
    return inforSite;
}


int Calcule_Lmax(int *voy){
	int nbr_voy[TACHE];
	int sum=0;
	int i;
	int site_actu=TACHE;
	int date_actu=0;
	int fin_site[TACHE],fin_ordre[TACHE],date_return=0;
	int tache_actu,Lmax;

	nbr_voy[0]=voy[0];
	for(i=1;i<TACHE;i++){
		sum=sum+nbr_voy[i-1];
		nbr_voy[i]=voy[sum+i];
	}

	fin_ordre[0]=info_tache[0][ordre[0]];
	for(i=1;i<TACHE;i++){
		fin_ordre[i]=fin_ordre[i-1]+info_tache[0][ordre[i]];
	}

	sum=0;
	for(i=0;i<TACHE;i++){
		sum=sum+nbr_voy[i];
		if(date_return<fin_ordre[sum-1])
			date_actu=fin_ordre[sum-1];
		else
			date_actu=date_return;
		while(nbr_voy[i]>0){
            tache_actu=voy[sum+i+1-nbr_voy[i]];
            fin_site[tache_actu]=date_actu+info_site[site_actu][tache_actu];
            site_actu=tache_actu;
            date_actu=fin_site[tache_actu];
            nbr_voy[i]--;
        }
		date_return=date_actu+info_site[TACHE][site_actu];

	}


	Lmax=fin_site[0]-info_tache[1][0];
	for(i=1;i<TACHE;i++){
		if(Lmax<(fin_site[i]-info_tache[1][i]))
			Lmax=fin_site[i]-info_tache[1][i];
	}

	return Lmax;

}

int * swap_dans_voyage(int val_voyage,int position1,int position2){
	int i,sum=0;
	int t;
	int *temp;
	if((temp=(int *)malloc(2*TACHE*sizeof(int)))==NULL){
        printf("shift_voyage_droite temp malloc error.");
        exit(-1);
    }

	for(i=0;i<2*TACHE;i++)
		temp[i]=voyage[i];
	for(i=0;i<val_voyage;i++)
		sum=sum+voyage[sum]+1;
	if((position1>voyage[sum])||(position2>voyage[sum])||(position1==position2))
		return voyage;
	else{
		t=temp[sum+position1];
		temp[sum+position1]=temp[sum+position2];
		temp[sum+position2]=t;
		return temp;
	}
}


int *swap_voyage(int val1_voyage,int val2_voyage,int position1,int position2){
	int i,sum1=0,sum2=0;
	int t,t_ordre;
	int *temp;
    if((temp=(int *)malloc(2*TACHE*sizeof(int)))==NULL){
        printf("shift_voyage_droite temp malloc error.");
        exit(-1);
    }
	for(i=0;i<2*TACHE;i++)
		temp[i]=voyage[i];

	for(i=0;i<val1_voyage;i++)
			sum1=sum1+voyage[sum1]+1;

	for(i=0;i<val2_voyage;i++)
			sum2=sum2+voyage[sum2]+1;

    t=temp[sum1+position1];
    temp[sum1+position1]=temp[sum2+position2];
    temp[sum2+position2]=t;
    t_ordre=ordre[sum1+position1-val1_voyage-1];
    ordre[sum1+position1-val1_voyage-1]=ordre[sum2+position2-val2_voyage-1];
    ordre[sum2+position2-val2_voyage-1]=t_ordre;
    //print_ordre(ordre);
    return temp;
}


int *shift_voyage_gauche(int val_voyage){
	int i,sum=0;
	int t;
	int *temp;
    if((temp=(int *)malloc(2*TACHE*sizeof(int)))==NULL){
        printf("shift_voyage_droite temp malloc error.");
        exit(-1);
    }

	for(i=0;i<2*TACHE;i++)
			temp[i]=voyage[i];

	for(i=0;i<val_voyage-1;i++)
				sum=sum+temp[sum]+1;
	/*t=temp[sum+temp[sum]+1+position];
	for(i=sum+temp[sum]+1+position;i>sum+temp[sum]+1;i--)
		temp[i]=temp[i-1];
	temp[i]=t;
	temp[i+1]--;
	temp[sum]++;*/
    t=temp[sum+temp[sum]+2];
    temp[sum+temp[sum]+1]--;
    temp[sum+temp[sum]+2]=temp[sum+temp[sum]+1];
    temp[sum+temp[sum]+1]=t;
    temp[sum]++;
	return temp;
}

int *shift_voyage_droite(int val_voyage){
	int i,sum=0;
	int t;
	int *temp;
    if((temp=(int *)malloc(2*TACHE*sizeof(int)))==NULL){
        printf("shift_voyage_droite temp malloc error.");
        exit(-1);
    }

	for(i=0;i<2*TACHE;i++)
			temp[i]=voyage[i];

	for(i=0;i<val_voyage;i++)
				sum=sum+temp[sum]+1;

	//for(i=sum-1;i<sum+temp[sum]+1;i++)
		//temp[i]=temp[i+1];

	/*temp[i]=t;
	temp[i-1]++;
	temp[sum]--;*/
        t=temp[sum+temp[sum]];
        temp[sum+temp[sum]]=temp[sum+temp[sum]+1];
        temp[sum+temp[sum]+1]=t;
        temp[sum+temp[sum]]++;
        temp[sum]--;
        return temp;
}

void print_ordre(int *ordre){
    int i;
    printf("ordre : ");//print ordre[TACHE]
    for(i=0;i<TACHE;i++)
       printf("%d ",ordre[i]);
    printf("\n");
}

void print_voyage(int *voyage){
    int i;
    printf("voyage : ");
    for(i=0;i<2*TACHE;i++) //print voyage initial
        printf("%d ",voyage[i]);
    printf("\n");
}
void free_info_tache(int **info_tache){
    int i=0;
    for(;i<2;i++){
        free(info_tache[i]);
        info_tache[i]=NULL;
    }
    free(info_tache);
    info_tache=NULL;
}
void free_info_site(int **info_site){
    int i=0;
    for(;i<TACHE;i++){
        free(info_site[i]);
        info_site[i]=NULL;
    }
    free(info_site);
    info_site=NULL;
}
void free_ordre(int *ordre){
    if(ordre!= NULL){
        free(ordre);
        ordre=NULL;
    }
}
void free_voyage(int *voyage){
    if(voyage!= NULL){
        free(voyage);
        voyage=NULL;
    }
}



