#include <stdio.h>
#include <string.h>
#define kernel_size 3

int pixel[360][250]; //width and height are manually taken by taking a glance at the pgm file.
int padded[450][450];

void convert_to_binary()
{
	int i,j;
	for(i=0;i<360;i++)
	{
		for(j=0;j<250;j++)
		{
			padded[i][j]=padded[i][j]>128 ? 255:0;
		}
	}
}

int multiply(int kernel[kernel_size][kernel_size],int x,int y,char c)
{
	int res=0;
	int i,j,k;
	for(i=0;i<kernel_size;i++)
	{
		for(j=0;j<kernel_size;j++)
		{
			if(kernel[i][j])
			{
				if(x+i<450 && y+j<450)
				res+=padded[x+i][y+j];
			}
		}
	}
	
	FILE* f;
	char ext[]=".pgm";
	char filename[100]="D:\\write";
	strncat(filename,&c,1);
	int last=0;
	while(filename[last++]!='\0');
	last--;
	for(j=0;i<ext[j]!='\0';last++,j++)
	{
		filename[last]=ext[j];
	}
	filename[last]='\0';
	//puts(filename);
	f=fopen(filename,"wb");
	fprintf(f,"P2\n");
	fprintf(f,"%d %d\n",kernel_size,kernel_size);
	fprintf(f,"255\n");
	//int resm[kernel_size][kernel_size];
	for(i=0;i<kernel_size;i++)
	{
		for(j=0;j<kernel_size;j++)
		{
		//	printf("%d ",kernel[i][j]);
			if(kernel[i][j] && x+i<450 && y+j<450)
			{
				printf("%d ",padded[x+i][y+j]);
				fprintf(f,"%d ",padded[x+i][y+j]);
			}
			else
			{
				printf("255 ");
				fprintf(f,"%d ",255);
			}
		}
		printf("\n");
		fprintf(f,"\n");
	}
	fclose(f);
	return res;
}

void convoluteandwrite()
{
	int kernel[kernel_size][kernel_size]={{1,0,1},{0,1,0},{1,0,1}};
	int stride=1;
	int x=0,y=0,i,j;
	//memset(padded,255,450*450*sizeof(int));
	for(i=0;i<450;i++)
	{
		for(j=0;j<450;j++)
		{
			padded[i][j]=255;
		}
	}
	for(i=45;i<405;i++)
	{
		for(j=100;j<350;j++)
		{
			padded[i][j]=pixel[(i+360)-405][(j+250)-350];
		}
	}
	char c='a';
	for(i=44;i<450-kernel_size;i+=stride)
	{
		for(j=99;j<450-kernel_size;j+=stride)
		{
			int r=multiply(kernel,i,j,c++);
			printf("Executing...\n");
		}
		printf("\n");
	}
}

main()
{
	FILE* fp;
	fp=fopen("D:\\mona.pgm","rb");
	char d[1000];
	int cntl=1,row=0,i,j,col=0;
	char* token;
	while(fgets(d,1000,fp)!=NULL && row<360)
	{
		
		if(cntl>4)
		{
			//printf("%d\n",strlen(d));
			
			
//			d[last+1]='\0';
		    //if(cntl==5)
		    //   printf("Character:%sgap\n",d);
		//	fputs(d,stdout);
		    //printf("Length: %d\n",strlen(d));
			col=0;
			for(i=1;d[i]!='\0' && col<250;)
			{
				
				while(d[i]!=' ' && d[i]!='\n')
				{
					
					//printf("%d\n",i);
					//printf("%c",d[i]);
					pixel[row][col]=pixel[row][col]*10+(d[i]-48);
					i++;
				}
			
				i+=1;
				col+=1;
			}
			row++;
		}
		cntl++;
	}
	
	for(i=0;i<360;i++)
	{
	//	printf("i:%d\n",i);
		for(j=0;j<250;j++)
		{
		//	printf("%d ",pixel[i][j]);
		}
		//printf("\n");
	}
	convoluteandwrite();
	fclose(fp);
	fp=NULL;
}
