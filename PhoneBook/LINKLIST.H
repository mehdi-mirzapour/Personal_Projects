int add_to_link_list(void)
{
new=(struct member *)malloc(sizeof(struct member));
if (new==NULL) return(0);
new->next=NIL;
PAGE_NUMBER++;


if(first==NIL)
   first=this=new;
       else
           {
            this->next=new;
            this=new;
           }



strcpy(this->sfm_name,FM_NAME);
strcpy(this->sft_name,FT_NAME);
strcpy(this->sname,NAME);
strcpy(this->scertify,CERTIFY);
strcpy(this->sage,AGE);
strcpy(this->ssex,SEX);
strcpy(this->sdegree,DEGREE);




FM_NAME[0]='\0';
FT_NAME[0]='\0';
NAME[0]='\0';
CERTIFY[0]='\0';
AGE[0]='\0';
SEX[0]='\0';
DEGREE[0]='\0';
return(1);
}
