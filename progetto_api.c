#include <stdio.h>
#include <stdlib.h>
#define N 19  //lunghezza massima prima parola del comando
#define M 515 //numero massimo di auto in una stazione

typedef struct node
{
    int stazione[M];
    struct node *prev;
    struct node *next;
} node_t;
typedef node_t *ptr_nodo;


int main()
{
    int dim,n,m,t,i,j,max,r_value,l;
    int *fermate;
    ptr_nodo list,head,tail,tmp,start;
    char parola[N];
    FILE *fin=stdin;
    list=NULL;
    start=NULL;
    head=NULL;
    tmp=NULL;
    tail=NULL;
    FILE *fout=stdout;
    l=0;
    while(!feof(fin))
    {
     t=0;
     n=0;
     max=1;
     i=0;
     j=0;
     r_value=fscanf(fin,"%s", parola);

     //inizio algoritmo aggiungi-stazione (aggiunge le stazione in ordine dalla distanza minore alla maggiore)
     if(parola[0]=='a' && parola[9]=='s')
        {
	 list=malloc(sizeof(node_t));
	 list -> next=NULL;
         list -> prev=NULL;
         //creazione array stazione con al 3 posto la macchina con autonomia maggiore
         r_value=fscanf(fin,"%d", &list->stazione[0]);
         r_value=fscanf(fin,"%d", &list->stazione[1]);
         i=2;
	 while(i<=list->stazione[1]+1)
            {
	     n=fscanf(fin,"%d", &list->stazione[i]);
             if(list->stazione[i]>=max && i>=2)
               {
		max=list->stazione[i];
		j=i;
	       }
	     i++;
	    }
         list->stazione[i]=-1;
         if (list->stazione[1]!=0)
            {
             list->stazione[j]=list->stazione[2];
	     list->stazione[2]=max;
	    }
	 if (l>=3)
            {
             if(list->stazione[0]>tail->stazione[0])
                 tmp=tail;
             else if(list->stazione[0]<head->stazione[0])
                 tmp=head;
             else if(tmp->stazione[0]>list->stazione[0])
		{
		 if(list->stazione[0]-head->stazione[0]>tail->stazione[0]-list->stazione[0] && tmp->stazione[0]-list->stazione[0]>=tail->stazione[0]-list->stazione[0])
		     tmp=tail;
		 else if(list->stazione[0]-head->stazione[0]<=tail->stazione[0]-list->stazione[0] && tmp->stazione[0]-list->stazione[0]>=list->stazione[0]-head->stazione[0])
		     tmp=head;
		}
	     else if(tmp->stazione[0]<list->stazione[0])
                {
                 if(list->stazione[0]-head->stazione[0]>tail->stazione[0]-list->stazione[0] && list->stazione[0]-tmp->stazione[0]>=tail->stazione[0]-list->stazione[0])
                     tmp=tail;
                 else if(list->stazione[0]-head->stazione[0]<=tail->stazione[0]-list->stazione[0] && list->stazione[0]-tmp->stazione[0]>=list->stazione[0]-head->stazione[0])
                     tmp=head;
                }
            }
	 if(head==NULL)
            {
             r_value=fprintf(fout,"aggiunta\n");
             head=list;
             tmp=list;
             tail=list;
             l=1;
            }
	 else
	    {
	     if(tmp->stazione[0]>list->stazione[0])
	       {
	        while (tmp->stazione[0]>list->stazione[0] && tmp->prev!=NULL)
	   	    tmp=tmp->prev;
                if (tmp->stazione[0]==list->stazione[0])
                  {
                   free(list);
                   r_value=fprintf(fout,"non aggiunta\n");
                   l--;
		  }
	        else if (tmp->prev==NULL && tmp->stazione[0]>list->stazione[0])
                  {
		   list->next = tmp;
                   list->prev = NULL;
                   tmp->prev = list;
                   head=list;
		   r_value=fprintf(fout,"aggiunta\n");
		   tmp=list;
	          }
                else
	          {
		   list->prev = tmp;
                   list->next = tmp->next;
                   tmp->next->prev = list;
                   tmp->next = list;
		   r_value=fprintf(fout,"aggiunta\n");
		   tmp=list;
	          }
	       }
             else
	       {
	        while (tmp->stazione[0]<list->stazione[0] && tmp->next!=NULL)
	  	    tmp=tmp->next;
                if (tmp->stazione[0]==list->stazione[0])
                  {
		   free(list);
                   r_value=fprintf(fout,"non aggiunta\n");
		   l--;
	          }
	        else if (tmp->next==NULL && tmp->stazione[0]<list->stazione[0])
                  {
                   list->next = NULL;
                   list->prev = tmp;
                   tmp->next = list;
		   r_value=fprintf(fout,"aggiunta\n");
		   tmp=list;
                   tail=list;
                  }
                else
                  {
                   list->next = tmp;
                   list->prev = tmp->prev;
		   tmp->prev->next = list;
                   tmp->prev = list;
		   r_value=fprintf(fout,"aggiunta\n");
		   tmp=list;
                  }
	       }
             l++;
	    }
        }


     //inizio algoritmo demolisci-stazione
     else if(parola[0]=='d')
       {
	r_value=fscanf(fin,"%d", &n);
        r_value=0;
	if (head==NULL)
           r_value=fprintf(fout, "non demolita\n");
        else
           {
	    if (l>=3)
              {
               if(n>tail->stazione[0])
                   i=2;
               else if(n<head->stazione[0])
                   i=2;
               else if(tmp->stazione[0]>n)
                  {
                   if(n-head->stazione[0]>tail->stazione[0]-n && tmp->stazione[0]-n>=tail->stazione[0]-n)
                       {
		        list=tail;
                        r_value=2;
                       }
                   else if(n-head->stazione[0]<=tail->stazione[0]-n && tmp->stazione[0]-n>=n-head->stazione[0])
                       list=head;
                  else
		       {
			list=tmp;
                        r_value=2;
                       }
		  }
               else if(tmp->stazione[0]<n)
                  {
                   if(n-head->stazione[0]>tail->stazione[0]-n && n-tmp->stazione[0]>=tail->stazione[0]-n)
                       {
			list=tail;
			r_value=2;
		       }
                   else if(n-head->stazione[0]<=tail->stazione[0]-n && n-tmp->stazione[0]>=n-head->stazione[0])
                       list=head;
                   else
		       list=tmp;
                  }
               else
		  list=tmp;
              }
            else
	      list=head;
	    while (i==0)
	       {
		if (list->stazione[0]==n)
		  {
                   i=1;
		   if(list->prev==NULL && list->next==NULL)
                      {
		       start=NULL;
                       head=NULL;
                       tmp=NULL;
		       tail=NULL;
		      }
                   else if(list->prev==NULL)
                      {
		       list->next->prev=NULL;
		       head=list->next;
		      }
                   else if(list->next==NULL)
                      {
		       list->prev->next=NULL;
		       tail=list->prev;
		      }
                   else
		      {
		       list->prev->next=list->next;
                       list->next->prev=list->prev;
		      }
		  }
                else
                  {
		   if (r_value==0)
		      {
		       if (list->next==NULL || list->next->stazione[0]>n)
                         break;
		       list=list->next;
		      }
                   else if (r_value==2)
		      {
                       if (list->prev==NULL || list->prev->stazione[0]<n)
                         break;
                       list=list->prev;
                      }
		  }
	       }
            if (i==1)
               {
                if(tmp==list && tmp->prev!=NULL)
		   tmp=tmp->prev;
	        else if(tmp==list && tmp->next!=NULL)
                   tmp=tmp->next;
		free(list);
		l--;
                r_value=fprintf(fout, "demolita\n");
	       }
            else
                r_value=fprintf(fout, "non demolita\n");
	   }
       }

     //inizio algoritmo aggiungi-auto
     else if(parola[0]=='a' && parola[9]=='a')
       {
	r_value=fscanf(fin,"%d", &n); //distanza stazione di interesse
	r_value=fscanf(fin,"%d", &j); //autonomia auto da aggiungere
        r_value=0;
        if (head==NULL)
           r_value=fprintf(fout, "non aggiunta\n");
        else
           {
	    if (n==tmp->stazione[0])
		list=tmp;
            else if (l>=3)
              {
               if(n>tail->stazione[0])
                   i=2;
               else if(n<head->stazione[0])
                   i=2;
               else if(tmp->stazione[0]>n)
                  {
                   if(n-head->stazione[0]>tail->stazione[0]-n && tmp->stazione[0]-n>=tail->stazione[0]-n)
                       {
                        list=tail;
                        r_value=2;
                       }
                   else if(n-head->stazione[0]<=tail->stazione[0]-n && tmp->stazione[0]-n>=n-head->stazione[0])
                       list=head;
                  else
                       {
                        list=tmp;
                        r_value=2;
                       }
                  }
               else if(tmp->stazione[0]<n)
                  {
                   if(n-head->stazione[0]>tail->stazione[0]-n && n-tmp->stazione[0]>=tail->stazione[0]-n)
                       {
                        list=tail;
                        r_value=2;
                       }
                   else if(n-head->stazione[0]<=tail->stazione[0]-n && n-tmp->stazione[0]>=n-head->stazione[0])
                       list=head;
                   else
                       list=tmp;
                  }
              }
            else
              list=head;
	    while (i==0)
              {
	       if (list->stazione[0]==n)
		 {
		  i=1;
		  if (j>list->stazione[2])
                    {
		     max=list->stazione[2];
	 	     list->stazione[2]=j;
                     if (list->stazione[1]==0)
                        list->stazione[3]=-1;
                     else
			{
		         list->stazione[list->stazione[1]+2]=max;
		         list->stazione[list->stazione[1]+3]=-1;
			}
		     list->stazione[1]=list->stazione[1]+1;
		    }
		  else
		    {
		     list->stazione[list->stazione[1]+2]=j;
                     list->stazione[list->stazione[1]+3]=-1;
                     list->stazione[1]=list->stazione[1]+1;
		    }
		 }
	       else
		 {
		  if (r_value==0)
                      {
                       if (list->next==NULL || list->next->stazione[0]>n)
                         break;
                       list=list->next;
                      }
                   else if (r_value==2)
                      {
                       if (list->prev==NULL || list->prev->stazione[0]<n)
                         break;
                       list=list->prev;
                      }
		 }
	      }
	    if (i==1)
	       {
                r_value=fprintf(fout, "aggiunta\n");
	        tmp=list;
	       }
            else
                r_value=fprintf(fout, "non aggiunta\n");
           }
       }

     //inizio algoritmo rottama-auto
     else if(parola[0]=='r')
       {
	r_value=fscanf(fin,"%d", &n); //distanza stazione di interesse
        r_value=fscanf(fin,"%d", &j); //autonomia auto da rottamare
	r_value=0;
        if (head==NULL)
           r_value=fprintf(fout, "non rottamata\n");
        else
           {
            max=0;
	    if (n==tmp->stazione[0])
                list=tmp;
            else if (l>=3)
              {
               if(n>tail->stazione[0])
                   i=2;
               else if(n<head->stazione[0])
                   i=2;
               else if(tmp->stazione[0]>n)
                  {
                   if(n-head->stazione[0]>tail->stazione[0]-n && tmp->stazione[0]-n>=tail->stazione[0]-n)
                       {
                        list=tail;
                        r_value=2;
                       }
                   else if(n-head->stazione[0]<=tail->stazione[0]-n && tmp->stazione[0]-n>=n-head->stazione[0])
                       list=head;
                  else
                       {
                        list=tmp;
                        r_value=2;
                       }
                  }
               else if(tmp->stazione[0]<n)
                  {
                   if(n-head->stazione[0]>tail->stazione[0]-n && n-tmp->stazione[0]>=tail->stazione[0]-n)
                       {
                        list=tail;
                        r_value=2;
                       }
                   else if(n-head->stazione[0]<=tail->stazione[0]-n && n-tmp->stazione[0]>=n-head->stazione[0])
                       list=head;
                   else
                       list=tmp;
                  }
              }
            else
              list=head;
            while (max==0)
              {
               if (list->stazione[0]==n)
                 {
                  max=1;
                  for(i=2;list->stazione[i]>0;i++)
                    {
		     if (list->stazione[i]==j)
		       {
                        max=2;
			if (i==2)
			  {
			   list->stazione[i]=list->stazione[list->stazione[1]+1];
                           list->stazione[list->stazione[1]+1]=-1;
                           while (list->stazione[i]>0)
			     {
			      if(list->stazione[2]<list->stazione[i])
			        {
				 t=list->stazione[2];
				 list->stazione[2]=list->stazione[i];
				 list->stazione[i]=t;
				}
			      i++;
			     }
			   i=2;
			   list->stazione[1]=list->stazione[1]-1;
			  }
			else
			  {
			   list->stazione[i]=list->stazione[list->stazione[1]+1];
                           list->stazione[list->stazione[1]+1]=-1;
			   list->stazione[1]=list->stazione[1]-1;
			  }
		       }
                    }
		 }
               else
		 {
                  if (r_value==0)
                      {
                       if (list->next==NULL || list->next->stazione[0]>n)
                         break;
                       list=list->next;
                      }
                   else if (r_value==2)
                      {
                       if (list->prev==NULL || list->prev->stazione[0]<n)
                         break;
                       list=list->prev;
                      }
		 }
	      }
	    if (max==2)
              r_value=fprintf(fout, "rottamata\n");
            else
              r_value=fprintf(fout, "non rottamata\n");
	   }
       }

     //inizio codice pianifica-percorso (il real deal)
     else if(parola[0]=='p')
       {
        r_value=fscanf(fin,"%d", &n); //distanza da inizio autostrada stazione di partenza
        r_value=fscanf(fin,"%d", &j); //distanza da inizio autostrada stazione d'arrivo
	list=head;
        if (n>j)
	  {
           while (list->stazione[0]!=n)
             list=list->next;
	  }
	if (n==j)
	   r_value=fprintf(fout,"%d\n",n);
	else
	  {
	   while(t==0)
             {
	      if(list->stazione[0]==n)
                {
                 start=list;
                 dim=1;
	         t=1;
	         m=0;
                 if(n<j) //percorso in avanti
                  {
                   while (list->stazione[0]+list->stazione[2]<j && dim>0)
		     {
                      dim++;
		      i=list->stazione[0]+list->stazione[2];
                      list=list->next;
		      max=0;
		      while (list->stazione[0]<=i)
		        {
			 if (list->stazione[0]==j)
			   {
			    max=1;
                            break;
			   }
		         if (list->stazione[0]+list->stazione[2]>max)
			   {
			    max=list->stazione[0]+list->stazione[2];
			    tmp=list;
			   }
                         list=list->next;
		        }
                      if (max==0)
		       {
			dim=0;
                        m=1;
                        r_value=fprintf(fout,"nessun percorso");
                       }
		      list=tmp;
		     }
                   if (dim>0)
                     {
		      fermate=(int*)malloc((dim+1)*sizeof(int));
                      for(m=0;m<=dim;m++)
                         fermate[m]=0;
                      m=1;
                      list=start;
                      fermate[0]=list->stazione[0];
                      while (list->stazione[0]+list->stazione[2]<j)
                        {
                         i=list->stazione[0]+list->stazione[2];
                         list=list->next;
                         max=0;
                         while (list->stazione[0]<=i)
                           {
			    if (list->stazione[0]==j)
                               break;
                            if (list->stazione[0]+list->stazione[2]>max)
                              {
                               max=list->stazione[0]+list->stazione[2];
                               tmp=list;
                              }
                            list=list->next;
                           }
                         list=tmp;
                         fermate[m]=list->stazione[0];
		         m++;
		        }
                      fermate[dim]=j;
		      m=dim-1;
                      while (m>0)
			{
                         while (list->stazione[0]>fermate[m-1])
			   {
			    if (list->stazione[0]+list->stazione[2]>=fermate[m+1])
                               fermate[m]=list->stazione[0];
                            list=list->prev;
			   }
			 m--;
			}
		     }
                  }
                else //percorso all'indietro
                  {
		   while (list->stazione[0]-list->stazione[2]>j && dim>0)
                     {
                      dim++;
                      i=list->stazione[0]-list->stazione[2];
                      list=list->prev;
                      max=n;
                      while (list->stazione[0]>=i)
                        {
                         if (list->stazione[0]==j)
                           {
                            max=1;
                            break;
                           }
                         if (list->stazione[0]-list->stazione[2]<max)
                           {
                            max=list->stazione[0]-list->stazione[2];
                            tmp=list;
                           }
                         list=list->prev;
                        }
                      if (max==n)
                       {
                        dim=0;
                        m=1;
                        r_value=fprintf(fout,"nessun percorso");
                       }
                      list=tmp;
                     }
                   if (dim>0)
                     {
                      fermate=(int*)malloc((dim+1)*sizeof(int));
                      for(m=0;m<=dim;m++)
                         fermate[m]=0;
                      m=1;
                      list=start;
                      fermate[0]=list->stazione[0];
                      while (list->stazione[0]-list->stazione[2]>j)
                        {
                         i=list->stazione[0]-list->stazione[2];
                         list=list->prev;
                         max=n;
                         while (list->stazione[0]>=i)
                           {
                            if (list->stazione[0]==j)
                               break;
                            if (list->stazione[0]-list->stazione[2]<max)
                              {
                               max=list->stazione[0]-list->stazione[2];
                               tmp=list;
                              }
                            list=list->prev;
                           }
                         list=tmp;
                         fermate[m]=list->stazione[0];
			 m++;
                        }
                      fermate[dim]=j;
		      m=dim-1;
                      while (m>0)
                        {
			 list=tmp;
                         while (tmp->stazione[0]!=fermate[m-1])
                            tmp=tmp->next;
                         while (list->stazione[0]>fermate[m+1] && list->stazione[0]>=tmp->stazione[0]-tmp->stazione[2])
                           {
                            if (list->stazione[0]-list->stazione[2]<=fermate[m+1])
                               fermate[m]=list->stazione[0];
                            list=list->prev;
                           }
                         m--;
                        }
		     }
		  }
		}
              else
                {
                 if(n<j)
                   list=list->next;
                 else
                   list=list->prev;
                }
	     }
           if(dim>0)
             {
	      for(m=0;m<=dim-1;m++)
	         r_value=fprintf(fout,"%d ",fermate[m]);
              r_value=fprintf(fout,"%d",fermate[dim]);
             }
           r_value=fprintf(fout,"\n");
	  }
       }
     parola[0]='z';
    }

							/*
							//per vedere il funzionamento
							if (head==NULL)
							 fprintf(fout,"lista vuota");
							else
							{
							list=head;
							while (list->next!=NULL)
							{
							for (i=0;list->stazione[i]!=-1;i++)
							 fprintf(fout,"%d ",list->stazione[i]);
							fprintf(fout,"\n");
							list=list->next;
							}
							for (i=0;list->stazione[i]!=-1;i++)
							 fprintf(fout,"%d ",list->stazione[i]);
							fprintf(fout,"\n");
							}
							*/

   return 0;
}

