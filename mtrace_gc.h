#include<stdio.h>
#include<malloc.h>
#include<mcheck.h>
#include<string.h>
void gc() {
    int pluscount=0;
    int minuscount=0;
    int i=0;
    int j=0;
    int pflag=0;
    int mflag=0;
    void *pptr[100];
    void *mptr[100];
    FILE *fp=popen("echo $MALLOC_TRACE","r");
    char filecontent[100];
    fscanf(fp,"%s",filecontent);
    fclose(fp);

    char *filename=(char*)malloc(sizeof(char)*strlen(filecontent));
    strcpy(filename,filecontent);

    fp=fopen(filename,"r");


    while(!feof(fp)) {
        fscanf(fp,"%s",filecontent);
        if(pflag==1) {
             sscanf(filecontent,"%x",&j);
             pptr[pluscount-1]=j; 
             pflag=0;
        }


        if(mflag==1) {
             sscanf(filecontent,"%x",&j);
             mptr[minuscount-1]=j;
             mflag=0;
        }


             
        if(strcmp(filecontent,"+")==0) {
             pluscount++;
             pflag=1;
        }
        else if(strcmp(filecontent,"-")==0) {
             minuscount++;
             mflag=1;
       }
             
     }

    if(pluscount>minuscount) {
         int diff=pluscount-minuscount;
         int flag=0;
         i=0;j=0;
         while(diff>0) {
             for(j=0;j<minuscount;j++) {
                  if(pptr[i]==mptr[j]) {
                       i++;
                       flag=1;
                       break;
                 }
            }
            if(flag==0) {
                printf("Unchecked memory at %p being freed by garbage collector\n",pptr[i]);
                free(pptr[i]);
                diff--;
                i++;
            }


        }
    }
    free(filename);
    fclose(fp);
}
