#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<direct.h>


void rank();
int manual_core();
int manual_exact();
int manual_top();
int manual_topk();
int script_core();
int script_exact();
int script_top();
int script_topk();
int script_exact_top();
int script_exact_topk();
int manual_exact_top();
int manual_exact_topk();



void rank(int *a, int *b)
{
	int x,y,t,t1;
	for(y=1;y<=510;y++){
		for(x=1;x<=510-y;x++){
			if(a[x]<a[x+1]){
				t = a[x];
				a[x] = a[x+1];
				a[x+1] = t;
				
				t1 = b[x];
				b[x] = b[x+1];
				b[x+1] = t1;
			}
		}
	}
}


int manual_core()
{
	FILE *p;
	bool go_on = true;
	char name[10];	//存放文件名的数组 
	char str[4096];
	char query_temporary[100];
	char query[10][20];		//存放用户检索关键词 
	char delimiters[] = " \".,;:!?()";
	int line = 0;
	int i = 0;  //query term 的数量 
	int j = 0;
	int id = 0;
	
	printf("Enter the key words, separated by blanks:");
	/*读取用户输入*/ 
	gets(query_temporary);

	
	/*得到query中term的个数*/
	char *pword_2 = strtok(query_temporary,delimiters);
	do{
		strcpy(query[i],pword_2);
		pword_2 = strtok(NULL,delimiters);
		i++;
	}while(pword_2);
	

	for(id=1;id<=510;id++){
		go_on = true;
		sprintf(name,"%03d.txt",id);
		p = fopen(name,"r");
		while(!feof(p) && go_on){
			fgets(str,1024,p);
			if(line >= 5){		//跳过content前的部分 
				/*检索*/
				char *pword_1 = strtok(str,delimiters);
				do{
					for(j=0;j<i;j++){
						if(!strcmp(pword_1,query[j])){
							printf("%d  ",id);	
							go_on = false;	//修复重复出现id的bug，如果是top搜索就不要用到布尔变量 
							break;	
						}
					}
					pword_1 = strtok(NULL,delimiters);
				}while(pword_1 && go_on);
	     	}
			line++;
	    }
    fclose(p);
    line = 0;
	}
	return 0;
}


int manual_exact()
{
	FILE *p;
	bool go_on = true;
	char name[10];	//存放文件名的数组 
	char str[4096];
	char query_temporary[100];
	char query[10][20];		//存放用户检索关键词 
	char delimiters[] = " \".,;:!?()";
	int line = 0;
	int i = 0;  //query term 的数量 
	int j = 0;
	int id = 0;
	int c[10] = {0};
	
	printf("Enter the key words, separated by blanks:");
	/*读取用户输入*/ 
	gets(query_temporary);

	
	/*得到query中term的个数*/
	char *pword_2 = strtok(query_temporary,delimiters);
	do{
		strcpy(query[i],pword_2);
		pword_2 = strtok(NULL,delimiters);
		i++;
	}while(pword_2);
	

	
	
	for(id=1;id<=510;id++){
		go_on = true;
		sprintf(name,"%03d.txt",id);
		p = fopen(name,"r");
		while(!feof(p)){
			fgets(str,1024,p);
			if(line >= 5){		//跳过content前的部分 
				/*检索*/
				char *pword_1 = strtok(str,delimiters);
				do{
					for(j=0;j<i;j++){
						if(!strcmp(pword_1,query[j])){
							c[j] = 1;
							break;	
						}
					}
					pword_1 = strtok(NULL,delimiters);
				}while(pword_1);
	     	}
			line++;
	    }
	for(j=0;j<i;j++){
		if(c[j] == 0)	
			break;
	}
	if(j == i)	
		printf("%d  ",id);
    fclose(p);
    line = 0;
    
    /*初始化c*/
	for(j=0;j<i;j++)
		c[j] = 0;
	}
	return 0;
}


int manual_top()
{
	FILE *p;
	bool go_on = true;
	char name[10];	//存放文件名的数组 
	char str[4096];
	char query_temporary[100];
	char query[10][20];		//存放用户检索关键词 
	char delimiters[] = " \".,;:!?()";
	int line = 0;
	int i = 0;  //query term 的数量 
	int j = 0;
	int k = 0;
	int id = 0;
	int count = 0;
	int max = 0;
	int a[511];
	
	printf("Enter the key words, separated by blanks:");
	/*读取用户输入*/ 
	gets(query_temporary);

	
	/*得到query中term的个数*/
	char *pword_2 = strtok(query_temporary,delimiters);
	do{
		strcpy(query[i],pword_2);
		pword_2 = strtok(NULL,delimiters);
		i++;
	}while(pword_2);
	

	
	
	for(id=1;id<=510;id++){
		go_on = true;
		sprintf(name,"%03d.txt",id);
		p = fopen(name,"r");
		while(!feof(p)){
			fgets(str,sizeof(str),p);
			if(line >= 5){		//跳过content前的部分 
				/*检索*/
				char *pword_1 = strtok(str,delimiters);
				do{
					for(j=0;j<i;j++){
						if(!strcmp(pword_1,query[j])){	
							count++;
							break;	
						}
					}
					pword_1 = strtok(NULL,delimiters);
				}while(pword_1);
	     	}
			line++;
	    }
    fclose(p);
    line = 0;
    a[id] = count;
    count = 0;
	}
	
	/*找出最大值*/
	for(id=1;id<=510;id++){
		if(a[id] > max){
			max = a[id];
			k = id;
		}
	}
	printf("%d",k);
	
	 
	return 0;
}



int manual_topk()
{
	FILE *p;
	bool go_on = true;
	char name[10];	//存放文件名的数组 
	char str[4096];
	char query_temporary[100];
	char query[10][20];		//存放用户检索关键词 
	char delimiters[] = " \".,;:!?()";
	int line = 0;
	int i = 0;  //query term 的数量 
	int j = 0;
	int k = 0;
	int id = 0;
	int count = 0;
	int max = 0;
	int a[511];
	int b[511];
	
	for(i=1;i<=510;i++)
		b[i] = i; 
	
	printf("Enter the key words, separated by blanks:");
	/*读取用户输入*/ 
	gets(query_temporary);

	
	/*得到query中term的个数*/
	i = 0;
	char *pword_2 = strtok(query_temporary,delimiters);
	do{
		strcpy(query[i],pword_2);
		pword_2 = strtok(NULL,delimiters);
		i++;
	}while(pword_2);
	

	for(id=1;id<=510;id++){
		go_on = true;
		sprintf(name,"%03d.txt",id);
		p = fopen(name,"r");
		while(!feof(p)){
			fgets(str,sizeof(str),p);
			if(line >= 5){		//跳过content前的部分 
				/*检索*/
				char *pword_1 = strtok(str,delimiters);
				do{
					for(j=0;j<i;j++){
						if(!strcmp(pword_1,query[j])){	
							count++;
							break;	
						}
					}
					pword_1 = strtok(NULL,delimiters);
				}while(pword_1);
	     	}
			line++;
	    }
    fclose(p);
    line = 0;
    a[id] = count;
    count = 0;
	}
	
	/*排序*/
	rank(a,b);
	
	for(j=1;j<=3;j++){
		if(a[j] != 0)
			printf("%d ",b[j]);
	}
	
	return 0;
}



int script_core()
{
	FILE *p;
	FILE *p_1;
	FILE *p_2; 
	bool go_on = true;
	char query_temporary[100];
	char query[10][20];	
	char name[10];
	char delimiters[] = " \".,;:!?()";
	char str_1[1024];	//存储脚本 
	char str[4096];	//存储文本 
	int line = 0; 
	int i = 0,j = 0,qid = 1;  
	int id = 0;

	p_1 = fopen("query.txt","r"); 
	
	i = 0;
	/*进入大循环体*/ 
	while(!feof(p_1)){
	    fgets(str_1,sizeof(str_1),p_1);
		if(str_1[strlen(str_1)-1] == '\n')
			str_1[strlen(str_1)-1] = ' ';
		char *pword_2 = strtok(str_1,delimiters);
		do{
			if(i != 0)
				strcpy(query[i-1],pword_2);
			pword_2 = strtok(NULL,delimiters);
			i++;                       
		}while(pword_2);

		/*检索循环体*/
		for(id=1;id<=510;id++){
			go_on = true;
			sprintf(name,"%03d.txt",id);
			p = fopen(name,"r");
			while(!feof(p) && go_on){
				fgets(str,sizeof(str),p);
				if(line >= 5){		//跳过content前的部分 
					/*检索*/
					char *pword_1 = strtok(str,delimiters);
					do{
						for(j=0;j<i-1;j++){
							if(!strcmp(pword_1,query[j])){
								printf("q%d %03d\n",qid,id);
								go_on = false;
								break;	
							}
						}
						pword_1 = strtok(NULL,delimiters);
					}while(pword_1 && go_on);
		     	}
				line++;
		    }
	    	fclose(p);
	    	line = 0;
		}
		qid++;	
		i = 0; 
	}
	fclose(p_1); 
	return 0;
}


int script_exact()
{
	FILE *p;
	FILE *p_1;
	FILE *p_2;
	bool go_on = true;
	char query_temporary[100];
	char query[10][20];	
	char name[10];
	char delimiters[] = " \".,;:!?()";
	char str_1[1024];	//存储脚本 
	char str[4096];	//存储文本 
	int line = 0; 
	int i = 0,j = 0,qid = 1;  
	int id = 0;
	int c[10]  = {0}; 
	
	p_1 = fopen("query.txt","r"); 
	
	/*进入大循环体*/ 
	while(!feof(p_1)){
		fgets(str_1,sizeof(str_1),p_1);
		if(str_1[strlen(str_1)-1] == '\n')
			str_1[strlen(str_1)-1] = ' ';
		char *pword_2 = strtok(str_1,delimiters);
		do{
			if(i != 0)
				strcpy(query[i-1],pword_2);
			pword_2 = strtok(NULL,delimiters);
			i++;                       
		}while(pword_2);

		/*检索循环体*/
		for(id=1;id<=510;id++){
			go_on = true;
			sprintf(name,"%03d.txt",id);
			p = fopen(name,"r");
			while(!feof(p)){
				fgets(str,sizeof(str),p);
				
				if(line >= 5){		//跳过content前的部分 
					/*检索*/
					char *pword_1 = strtok(str,delimiters);
					do{
						for(j=0;j<i-1;j++){
							if(!strcmp(pword_1,query[j])){	
								c[j] = 1;
								break;	
							}
						}
						pword_1 = strtok(NULL,delimiters);
					}while(pword_1);
		     	}
				line++;
		    }
	    	for(j=0;j<i-1;j++){
				if(c[j] == 0)	
					break;
			}
			if(j == i-1){
				printf("q%d %03d\n",qid,id);
			}
								
			fclose(p);
	    	line = 0;
	    	
			/*初始化c*/
			for(j=0;j<i-1;j++)
				c[j] = 0;
		}
		qid++;	
		i = 0; 
	} 
	
	fclose(p_1); 
	return 0;
}


int script_top()
{
	FILE *p;
	FILE *p_1;
	FILE *p_2;
	bool go_on = true;
	char query_temporary[100];
	char query[10][20];	
	char name[10];
	char delimiters[] = " \".,;:!?()";
	char str_1[1024];	//存储脚本 
	char str[4096];	//存储文本 
	int line = 0; 
	int i = 0, j = 0, k = 0, qid = 1;  
	int id = 0;
	int id_1 = 0;
	int count = 0;
	int max = 0;
	int a[511];
	
	p_1 = fopen("query.txt","r"); 
	
	i = 0;
	/*进入大循环体*/ 
	while(!feof(p_1)){
		fgets(str_1,sizeof(str_1),p_1);
		if(str_1[strlen(str_1)-1] == '\n')
			str_1[strlen(str_1)-1] = ' ';
		char *pword_2 = strtok(str_1,delimiters);
		do{
			if(i != 0)
				strcpy(query[i-1],pword_2);
			pword_2 = strtok(NULL,delimiters);
			i++;                       
		}while(pword_2);

		/*检索循环体*/
		for(id=1;id<=510;id++){
			go_on = true;
			sprintf(name,"%03d.txt",id);
			p = fopen(name,"r");
			while(!feof(p)){
				fgets(str,sizeof(str),p);
				if(line >= 5){		//跳过content前的部分 
					/*检索*/
					char *pword_1 = strtok(str,delimiters);
					do{
						for(j=0;j<i-1;j++){
							if(!strcmp(pword_1,query[j])){
								count++;
								break;	
							}
						}
						pword_1 = strtok(NULL,delimiters);
					}while(pword_1);
		     	}
				line++;
		    }
	    	fclose(p);
	    	line = 0;
	    	a[id] = count;
			count = 0; 
		}
			/*找出最大值*/
		for(id_1=1;id_1<=510;id_1++){
			if(a[id_1] > max){
				max = a[id_1];
				k = id_1;
			}
		}
		printf("q%d %03d\n",qid,k);
		max = 0;
		qid++;	
		i = 0; 
	}
	
	
	fclose(p_1); 
	return 0;
}


int script_topk()
{
	FILE *p;
	FILE *p_1;
	FILE *p_2;
	bool go_on = true;
	char query_temporary[100];
	char query[10][20];	
	char name[10];
	char delimiters[] = " \".,;:!?()";
	char str_1[1024];	//存储脚本 
	char str[4096];	//存储文本 
	int line = 0; 
	int i = 0, j = 0, k = 0, qid = 1;  
	int id = 0;
	int id_1 = 0;
	int count = 0;
	int max = 0;
	int a[511];		//存放出现次数 
	int b[511];		//存放1到510文件ID 
	
	for(i=1;i<=510;i++)
		b[i] = i; 
	
	p_1 = fopen("query.txt","r"); 
	
	i = 0;
	/*进入大循环体*/ 
	while(!feof(p_1)){
		fgets(str_1,sizeof(str_1),p_1);
	    if(str_1[strlen(str_1)-1] == '\n')
			str_1[strlen(str_1)-1] = ' ';
		char *pword_2 = strtok(str_1,delimiters);
		do{
			if(i != 0)
				strcpy(query[i-1],pword_2);
			pword_2 = strtok(NULL,delimiters);
			i++;                       
		}while(pword_2);

		/*检索循环体*/
		for(id=1;id<=510;id++){
			go_on = true;
			sprintf(name,"%03d.txt",id);
			p = fopen(name,"r");
			while(!feof(p)){
				fgets(str,sizeof(str),p);
				if(line >= 5){		//跳过content前的部分 
					/*检索*/
					char *pword_1 = strtok(str,delimiters);
					do{
						for(j=0;j<i-1;j++){
							if(!strcmp(pword_1,query[j])){
								count++;
								break;	
							}
						}
						pword_1 = strtok(NULL,delimiters);
					}while(pword_1);
		     	}
				line++;
		    }
	    	fclose(p);
	    	line = 0;
	    	a[id] = count;
			count = 0; 
		}
			/*排序*/
		rank(a,b);
		printf("q%d %03d\n",qid,b[1]);
		printf("q%d %03d\n",qid,b[2]);
		printf("q%d %03d\n",qid,b[3]);

		/*初始化数组b*/
		for(id_1=1;id_1<=510;id_1++)
			b[id_1] = id_1;
		
		qid++;	
		i = 0; 
	}
	
	fclose(p_1); 
	return 0;
}

int script_exact_top()
{
	FILE *p;
	FILE *p_1;
	bool go_on = true;
	char query_temporary[100];
	char query[10][20];	
	char name[10];
	char delimiters[] = " \".,;:!?()";
	char str_1[1024];	//存储脚本 
	char str[2048];	//存储文本 
	int line = 0; 
	int i = 0,j = 0,qid = 1, k = 0; 
	int id = 0;
	int id_1 = 0;
	int count = 0;
	int max = 0;
	int c[10]  = {0}; 
	int a[511];
	int b[511];
	
	for(id_1=1;id_1<=510;id_1++)
		b[id_1] = id_1; 


	

	p_1 = fopen("query.txt","r"); 
	
	/*进入大循环体*/ 
	while(!feof(p_1)){
		fgets(str_1,sizeof(str_1),p_1);
		if(str_1[strlen(str_1)-1] == '\n')
			str_1[strlen(str_1)-1] = ' ';
		char *pword_2 = strtok(str_1,delimiters);
		do{
			if(i != 0)
				strcpy(query[i-1],pword_2);
			pword_2 = strtok(NULL,delimiters);
			i++;                       
		}while(pword_2);

		/*检索循环体*/
		for(id=1;id<=510;id++){
			go_on = true;
			sprintf(name,"%03d.txt",id);
			p = fopen(name,"r");
			while(!feof(p)){
				fgets(str,sizeof(str),p);
				
				if(line >= 5){		//跳过content前的部分 
					/*检索*/
					char *pword_1 = strtok(str,delimiters);
					do{
						for(j=0;j<i-1;j++){
							if(!strcmp(pword_1,query[j])){	
								c[j] = 1;
								count++;
								break;	
							}
						}
						pword_1 = strtok(NULL,delimiters);
					}while(pword_1);
		     	}
				line++;
		    }
	    	for(j=0;j<i-1;j++){
				if(c[j] == 0)	
					break;
			}
			if(j == i-1)	
				a[id] = count;
			else
				a[id] = 0;
				
				
			fclose(p);
	    	line = 0;
	    	count = 0;
	    
			/*初始化c*/
			for(j=0;j<i-1;j++)
				c[j] = 0;
		}
		
		for(id_1=1;id_1<=510;id_1++){
			if(a[id_1] > max){
				max = a[id_1];
				k = id_1;
			}
		}	
		printf("q%d %03d\n",qid,k);
		max = 0;
		qid++;	
		i = 0; 
	} 
	
	
	fclose(p_1); 
	return 0;
}



int script_exact_topk()
{
	FILE *p;
	FILE *p_1;
	bool go_on = true;
	char query_temporary[100];
	char query[10][20];	
	char name[10];
	char delimiters[] = " \".,;:!?()";
	char str_1[1024];	//存储脚本 
	char str[2048];	//存储文本 
	int line = 0; 
	int i = 0,j = 0,qid = 1;
	int id = 0;
	int id_1 = 0;
	int count = 0;
	int c[10]  = {0}; 
	int a[511];
	int b[511];
	
	for(id_1=1;id_1<=510;id_1++)
		b[id_1] = id_1; 


	p_1 = fopen("query.txt","r"); 
	
	/*进入大循环体*/ 
	while(!feof(p_1)){
		fgets(str_1,sizeof(str_1),p_1);
		if(str_1[strlen(str_1)-1] == '\n')
			str_1[strlen(str_1)-1] = ' ';
		char *pword_2 = strtok(str_1,delimiters);
		do{
			if(i != 0)
				strcpy(query[i-1],pword_2);
			pword_2 = strtok(NULL,delimiters);
			i++;                       
		}while(pword_2);

		/*检索循环体*/
		for(id=1;id<=510;id++){
			go_on = true;
			sprintf(name,"%03d.txt",id);
			p = fopen(name,"r");
			while(!feof(p)){
				fgets(str,sizeof(str),p);
				
				if(line >= 5){		//跳过content前的部分 
					/*检索*/
					char *pword_1 = strtok(str,delimiters);
					do{
						for(j=0;j<i-1;j++){
							if(!strcmp(pword_1,query[j])){	
								c[j] = 1;
								count++;
								break;	
							}
						}
						pword_1 = strtok(NULL,delimiters);
					}while(pword_1);
		     	}
				line++;
		    }
	    	for(j=0;j<i-1;j++){
				if(c[j] == 0)	
					break;
			}
			if(j == i-1)	
				a[id] = count;
			else
				a[id] = 0;
				
				
			fclose(p);
	    	line = 0;
	    	count = 0;
	    
			/*初始化c*/
			for(j=0;j<i-1;j++)
				c[j] = 0;
		}
		
		rank(a,b);
		for(j=1;j<=3;j++){
			if(a[j] != 0)
				printf("q%d %03d\n",qid,b[j]);
		}
		
		/*初始化数组b*/
		for(id_1=1;id_1<=510;id_1++)
			b[id_1] = id_1;
		
		qid++;	
		i = 0; 
	} 
	
	
	fclose(p_1); 
	return 0;
}


int manual_exact_top()
{
	FILE *p;
	bool go_on = true;
	char name[10];	//存放文件名的数组 
	char str[4096];
	char query_temporary[100];
	char query[10][20];		//存放用户检索关键词 
	char delimiters[] = " \".,;:!?()";
	int line = 0;
	int i = 0;  //query term 的数量 
	int j = 0;
	int k = 0;
	int id = 0;
	int count = 0;
	int max = 0;
	int a[511];
	int c[10]  = {0}; 
	
	
	printf("Enter the key words, separated by blanks:");
	/*读取用户输入*/ 
	gets(query_temporary);

	
	/*得到query中term的个数*/
	char *pword_2 = strtok(query_temporary,delimiters);
	do{
		strcpy(query[i],pword_2);
		pword_2 = strtok(NULL,delimiters);
		i++;
	}while(pword_2);
	

	
	
	for(id=1;id<=510;id++){
		go_on = true;
		sprintf(name,"%03d.txt",id);
		p = fopen(name,"r");
		while(!feof(p)){
			fgets(str,sizeof(str),p);
			if(line >= 5){		//跳过content前的部分 
				/*检索*/
				char *pword_1 = strtok(str,delimiters);
				do{
					for(j=0;j<i;j++){
						if(!strcmp(pword_1,query[j])){	
							count++;
							c[j] = 1;
							break;	
						}
					}
					pword_1 = strtok(NULL,delimiters);
				}while(pword_1);
	     	}
			line++;
	    }
   		for(j=0;j<i;j++){
			if(c[j] == 0)	
				break;
		}
		if(j == i)	
			a[id] = count;
		else
			a[id] = 0;
	
		fclose(p);
   		line = 0;
    	count = 0;
    	/*初始化c*/
		for(j=0;j<i;j++)
			c[j] = 0;
	}
	
	/*找出最大值*/
	for(id=1;id<=510;id++){
		if(a[id] > max){
			max = a[id];
			k = id;
		}
	}
	printf("%d",k);
	
	 
	return 0;
}

int manual_exact_topk()
{
	FILE *p;
	bool go_on = true;
	char name[10];	//存放文件名的数组 
	char str[4096];
	char query_temporary[100];
	char query[10][20];		//存放用户检索关键词 
	char delimiters[] = " \".,;:!?()";
	int line = 0;
	int i = 0;  //query term 的数量 
	int j = 0;
	int k = 0;
	int id = 0;
	int count = 0;
	int max = 0;
	int a[511];
	int b[511];
	int c[10]  = {0}; 
	
	
	for(j=1;j<=510;j++)
		b[j] = j; 
		
		
	printf("Enter the key words, separated by blanks:");
	/*读取用户输入*/ 
	gets(query_temporary);

	
	/*得到query中term的个数*/
	char *pword_2 = strtok(query_temporary,delimiters);
	do{
		strcpy(query[i],pword_2);
		pword_2 = strtok(NULL,delimiters);
		i++;
	}while(pword_2);
	
	
	for(id=1;id<=510;id++){
		go_on = true;
		sprintf(name,"%03d.txt",id);
		p = fopen(name,"r");
		while(!feof(p)){
			fgets(str,sizeof(str),p);
			if(line >= 5){		//跳过content前的部分 
				/*检索*/
				char *pword_1 = strtok(str,delimiters);
				do{
					for(j=0;j<i;j++){
						if(!strcmp(pword_1,query[j])){	
							count++;
							c[j] = 1;
							break;	
						}
					}
					pword_1 = strtok(NULL,delimiters);
				}while(pword_1);
	     	}
			line++;
	    }
   		for(j=0;j<i;j++){
			if(c[j] == 0)	
				break;
		}
		if(j == i)	
			a[id] = count;
		else
			a[id] = 0;
	
		fclose(p);
   		line = 0;
    	count = 0;
    	/*初始化c*/
		for(j=0;j<i;j++)
			c[j] = 0;
	}
	
	/*排序*/
	rank(a,b);
	for(j=1;j<=3;j++){
		if(a[j] != 0)
			printf("%d ",b[j]);
	}
	
	return 0;
}



int main(int argc, char *argv[])

{	
	if(argc == 2){
		if(!strcmp(argv[1], "manual"))
			manual_core();
		if(!strcmp(argv[1], "script"))
			script_core();
	}
	
	else if(argc == 3){
		if(!strcmp(argv[1], "manual")){
			if(!strcmp(argv[2], "exactSearch"))
				manual_exact();
			if(!strcmp(argv[2], "topSearch"))
				manual_top();
			if(!strcmp(argv[2], "topKSearch"))
				manual_topk();
		}
		else if(!strcmp(argv[1], "script")){
			if(!strcmp(argv[2], "exactSearch"))
				script_exact();
			if(!strcmp(argv[2], "topSearch"))
				script_top();
			if(!strcmp(argv[2], "topKSearch"))
				script_topk();
		}
	}
	
	
	else if(argc == 4){
		if(!strcmp(argv[1], "manual")){		//compatible
			if(strcmp(argv[2], "exactSearch")==0 && strcmp(argv[3], "topSearch")==0 )
				manual_exact_top();
			if(strcmp(argv[3], "exactSearch")==0 && strcmp(argv[2], "topSearch")==0 )
				manual_exact_top();
			if(strcmp(argv[2], "exactSearch")==0 && strcmp(argv[3], "topKSearch")==0 )
				manual_exact_topk();
			if(strcmp(argv[3], "exactSearch")==0 && strcmp(argv[2], "topKSearch")==0 )
				manual_exact_topk();
			}
		else if(!strcmp(argv[1], "script")){		//compatible
			if(strcmp(argv[2], "exactSearch")==0 && strcmp(argv[3], "topSearch")==0 )
				script_exact_top();
			if(strcmp(argv[3], "exactSearch")==0 && strcmp(argv[2], "topSearch")==0 )
				script_exact_top();
			if(strcmp(argv[2], "exactSearch")==0 && strcmp(argv[3], "topKSearch")==0 )
				script_exact_topk();
			if(strcmp(argv[3], "exactSearch")==0 && strcmp(argv[2], "topKSearch")==0 )
				script_exact_topk();
			
		}
	}
	
	else{
		printf("error");
	}
	
	return 0;
}
