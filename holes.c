/*	Saatvik Bhayana
*	0939774
*	3110 A3
*	
*	CODE FOUND ONLINE WAS USED AS REFERNCE
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mem {
	char id;
	int size;
	int num;
	struct mem *next;
} mem;

static int total = 0, count = 0, cumuMem = 0, proNum = 0, holeNum = 0, tCMem = 0, pos = 0;

void aBack(mem *data,char *read) {
	mem *temp = malloc(sizeof(mem));
	temp->id = *strtok(read," ");
	temp->size = atoi(strtok(NULL,""));
	temp->num=0;
	temp->next=NULL;
	mem *end=data;

	while(end->next) {
		end=end->next;
	}
	end->next=temp;
}
void memBack(mem *data, mem *temp, int lSize) {
	mem *end = &(*data);
	mem *temp2 = malloc(sizeof(mem));

	temp2->id=temp->id;
	temp2->size=temp->size;
	temp2->num=temp->num;
	temp2->next=NULL;

	while(end->next) {
 		end=end->next;
 	}
	end->next=temp2;
}

mem rFront(mem *data) {
	mem temp;
	temp=*data;
	(*data)=*data->next;
	temp.next=NULL;
	return temp;
}

char getCLoc(mem *data,int loc) {
	mem *temp = data;
	for(int i=0 ;i < loc-1; i++) {
		temp = temp->next;
	}
	return temp->id;
}
char oChar(mem *data,int mNum) {
	int total = 0, loc = 0;
	mem *temp = data;
	total += temp->num;
	while(temp->next != NULL) {
		temp = temp->next;
		total += temp->num;
	}
	if(total >= mNum) {
		total %= mNum;
	}
	loc = total+1;
	return getCLoc(data,loc);
}

int iLoc(mem *data,int loc) {
	mem *temp=data;
	for(int i = 0; i < loc-1; i++) {
		temp = temp->next;
	}
	return temp->size;
}
int oSize(mem *data,int mNum) {
	int total = 0;
	mem *temp = data;
	while(temp->next) {
		total += temp->num;
		temp = temp->next;
	}
	while(total > mNum) {
		total -= mNum;
	}
	int loc = mNum - total;
	return iLoc(data,loc);
}
int swapped(mem *data, char memory[], int mNum) {
	int ret=1;
	for(int i = 0; i < 128; i++) {
		if(memory[i]=='q')
			for(int j = 0; j < data->size; j++) {
				if(memory[i+j] != 'q') {
					ret = 0;
				}
				if((i+j) > 128) {
					ret = 0;
				}
			}
	}
	return ret;
}

char *swap(mem *data,char memory[],int mNum) {
	int swapped = 0;
	int count = 0;
	char oldId = oChar(data,mNum);
	int oldSize = oSize(data,mNum);
	for(int i=0; i<128; i++) {
		if(memory[i] == oldId) {
			memory[i] = 'q';
			count++;
			if(count == oldSize) {
				swapped = 1;
			}
		}
	}
	if(!swapped) {
		memory = swap(data->next,memory,--mNum);
	}
	
	return memory;
}

char *load(mem *data,char memory[],int mNum) {
	int free = 0;
	int full = 0;
	for(int i = 0; i<128; i++) {
		if(memory[i]=='q') {
			free = 1;
			for(int j = 0; j < data->size; j++) {
				if(memory[i+j] != 'q') {
					free = 0;
				}
				if(i+j > 128) {
					full = 1;
				}
			}
		}
		if(free) {
			int j;
			for(j = 0; j < data->size; j++) {
				memory[i+j] = data->id;
			}
			data->num++;
			return memory;
		}
		else if(!free && full) {
			memory = swap(data,memory,mNum);
			memory = load(data,memory,mNum);
			return memory;
		}
	}
	return memory;
}
int cProcNum(char memory[],mem data,int mNum) {
	char *ids;
	int sizes[mNum];
	int index=0;
	int num=0;
	ids=malloc(sizeof(char)*mNum);
	while(data.next) {
		ids[index]=data.id;
		sizes[index]=data.size;
		data=*data.next;
		index++;
	}
	ids[index]=data.id;
	sizes[index]=data.size;
	for(int i=0;i<128;i++) {
		for(int j=0;j<mNum;j++) {
			if(memory[i]==ids[j]) {
				num++;
				i+=sizes[j]-1;
			}
		}
	}
	
	return num;
}
int cHoles(char memory[]) {
 	int num=0;
	for(int i=0;i<128;i++) {
		if(memory[i]=='q') {
			while(memory[i]=='q') {
				i++;
			}
			num++;
		} else {
			while(memory[i]!='q') {
				i++;
			}
		}
	}
	return num;
}
int cMemU(char memory[]) {
	int num=0;
	double ans;
	for(int i=0;i<128;i++) {
		if(memory[i]!='q') {
			num++;
		}
	}
	ans=(num/128.0)*100;
	return ans;
}
int cMemC(mem data,char memory[],int mNum,int numAdds) {
	int total=0;
	double ans;
	for(int i=0;i<numAdds;i++) {
		
	}
	ans=(double)total/numAdds;
	return ans;
}

void output(mem data,char memory[],int mNum,int numAdds) {
	int numProcesses, numHoles, memUsage;
	numProcesses=cProcNum(memory,data,mNum);
	proNum+=numProcesses;
	numHoles=cHoles(memory);
	holeNum+=numHoles-1;
	memUsage=cMemU(memory);
	total+=memUsage;
	count++;
	cumuMem=total/count;
	tCMem+=cumuMem;
	printf("pid %c loaded, ",data.id);
	printf("process num = %d, ",numProcesses);
	printf("#holes = %d, ",numHoles-1);
	printf("mem usage %% = %d, ",memUsage);
	printf("cumulative mem %% = %d",cumuMem);
	printf("\n");	
}

void print(int numAdds) {
	double avgPros = (double) proNum / (double)numAdds;
	double avgHoles = (double) holeNum / (double)numAdds;
	int avgMem = tCMem/numAdds;
	printf("Total loads = %d, ",numAdds);
	printf("average process num= %3.2f, ",avgPros);
	printf("average hole num= %3.2f, ",avgHoles);
	printf("cumulative mem %% = %d\n",avgMem);
}

void first(mem data, int mNum) {
	char *memory = malloc(sizeof(char)*128);
	mem temp;

	for(int i=0;i<128;i++) {
		memory[i]='q';
	}

	printf("\n");
	int i;

	for(i=0; i < mNum*3; i++) {
		if(data.num<3) {

			memory=load(&data,memory,mNum);
			output(data,memory,mNum,i);
			temp=rFront(&data);
			temp.next=NULL;
 			memBack(&data,&temp,mNum);

 		} else {
 			temp=rFront(&data);
 		}
	}
	print(i);
	total=0;
	count=0;
	cumuMem=0;
	tCMem=0;
}
char *loadBest(mem *data,char memory[], int mNum) {
	int free=0;
	int full=0;
	int index=0;
	int *possible;
	possible=malloc(sizeof(int)*64);
	for(int i=0;i<128;i++) {
		if(memory[i]=='q') {
			free=1;
			for(int j=0;j<data->size;j++) {
				if(memory[i+j]!='q') {
					free=0;
				}
				if(i+j>128) {
					full=1;
					free=0;
				}
			}
			if(free) {
				possible[index]=i;
				index++;
			}
		}
		if(free) {
			int *cCheck;
			cCheck = malloc(sizeof(int)*index);
			
			for(int j=0; j < index; j++) {
				cCheck[j]=possible[j];
				while(cCheck[j]>data->size) {
					cCheck[j]-=data->size;
				}
			}
			int shortestPos=possible[0];
			for(int j=0; j < index; j++) {
				if(cCheck[j] < shortestPos)
					shortestPos=possible[j];
			}
			for(int j=0;j<data->size;j++) {
				memory[shortestPos+j]=data->id;
			}
			data->num++;
			return memory;
		}
		else if(!free&&full) {
			memory = swap(data,memory,mNum);
			memory = load(data,memory,mNum);
			return memory;
		}
	}
	return memory;
}
void best(mem data,int mNum) {
	char *memory;
	mem temp;
	memory=malloc(sizeof(char)*128);
	for(int i=0;i<128;i++) {
		memory[i]='q';
	}
	int i;
	for(i=0;i<mNum*3;i++) {
		if(data.num<3) {
			memory=loadBest(&data,memory,mNum);
			output(data,memory,mNum,i);
			temp=rFront(&data);
			temp.next=NULL;
			memBack(&data,&temp,mNum);
		} else {
			temp=rFront(&data);
		}
	}
	print(i);
	total=0; count=0; cumuMem=0; tCMem=0;
}
char *loadNext(mem *data,char memory[], int mNum) {
	int free=0;
	int full=0;
	for(int i=pos;i<128;i++) {
		if(memory[i]=='q') {
			free=1;
			for(int j=0;j<data->size;j++) {
				if(memory[i+j]!='q') {
					free=0;
				}
				if(i+j>128) {
					full=1;
					free=0;
					pos=0;
				}
			}
		}
		if(free) {
			int j;
			for(j=0;j<data->size;j++) {
				memory[i+j]=data->id;
			}
			pos=i+j;
			data->num++;
			return memory;
		}
		else if(!free&&full) {
			memory=swap(data,memory,mNum);
			memory=load(data,memory,mNum);
			return memory;
		}
	}
	return memory;
}
void next(mem data,int mNum) {
	char *memory;
	mem temp;
	memory=malloc(sizeof(char)*128);
	for(int i=0;i<128;i++) {
		memory[i]='q';
	}
	int i;
	for(i=0;i<mNum*3;i++) {
		if(data.num<3) {
			memory=loadNext(&data,memory,mNum);
			output(data,memory,mNum,i);
			temp=rFront(&data);
			temp.next=NULL;
			memBack(&data,&temp,mNum);
		} else {
			temp=rFront(&data);
		}
	}
	print(i);
	total=0; count=0; cumuMem=0; tCMem=0;
}
char *loadWorst(mem *data, char memory[],int mNum) {
	int free=0;
	int full=0;
	int index=0;
	int *possible;
	possible = malloc(sizeof(int)*64);
	for(int i = 0; i < 128; i++) {
		if(memory[i] == 'q') {
			free = 1;
			for(int j=0; j < data->size; j++) {
				if(memory[i+j] != 'q') {
					free=0;
				}
				if(i + j > 128) {
					full=1;
					free=0;
				}
			}
			if(free) {
				possible[index]=i;
				index++;
			}
		}
		if(free) {
			int *cCheck;
			cCheck=malloc(sizeof(int)*index);
			
			for(int j=0;j<index;j++) {
				cCheck[j] = possible[j];
				while(cCheck[j] > data->size) {
					cCheck[j] -= data->size;
				}
			}
			int largestPos=possible[0];
			for(int j=0;j<index;j++) {
				if(cCheck[j]>largestPos)
					largestPos=possible[j];
			}
			for(int j=0;j<data->size;j++) {
				memory[largestPos+j]=data->id;
			}
			data->num++;
			return memory;
		}
		else if(!free&&full) {
			memory=swap(data,memory,mNum);
			memory=load(data,memory,mNum);
			return memory;
		}
	}
	return memory;
}
void worst(mem data,int mNum) {
	char *memory;
	mem temp;
	memory=malloc(sizeof(char)*128);
	for(int i = 0; i < 128; i++) {
		memory[i]='q';
	}
	int i;
	for(i=0;i<mNum*3;i++) {
		if(data.num<3) {
			memory = loadWorst(&data,memory,mNum);
			output(data,memory,mNum,i);
			temp = rFront(&data);
			temp.next=NULL;
			memBack(&data,&temp,mNum);
		} else {
			temp=rFront(&data);
		}
	}
	print(i);
	total=0; count=0; cumuMem=0; tCMem=0;
}

void clearData(mem* data){
	data->id='\0';
	data->size=0;
	data->next=NULL;
}

int main(int argc, char **argv) {
	FILE *fp;
	mem data;
	char *read[128], *bRead[128], *nRead[128], *wRead[128];
	int i = 0;
	if(argc != 2) {
		printf("Incorrect amount of arguments\n");
		exit(0);
	}
	fp = fopen(argv[1],"r");
	if(fp == NULL) {
		printf("Error opening file\n");
		exit(0);
	}
	read[0] = malloc(sizeof(char)*7);

	while(fgets(read[i],7,fp)) {
		strtok(read[i],"\n");
		read[++i]=malloc(sizeof(char)*7);
	}
	for(int j = 0; j < i;j++) {
		bRead[j] = malloc(sizeof(char)*7);
		strcpy(bRead[j],read[j]);
	}
	for(int j = 0; j < i; j++) {
		nRead[j]=malloc(sizeof(char)*7);
		strcpy(nRead[j],read[j]);
	}
	for(int j=0; j < i; j++) {
		wRead[j]=malloc(sizeof(char)*7);
		strcpy(wRead[j],read[j]);
	}
	data.id = *strtok(read[0]," ");
 	data.size = atoi(strtok(NULL,""));
 	data.num = 0;
 	data.next = NULL;
 	for(int j = 1; j < i; j++) {
 		aBack(&data,read[j]); 
 	}
	printf("first fit\n\n");
	first(data,i);
	printf("\n");

	clearData(&data);

 	for(int j = 0; j < i; j++) {
 		aBack(&data,bRead[j]); 
 	}
 	rFront(&data);
 	printf("best fit\n\n");
	best(data,i);
	printf("\n");
	
	clearData(&data);

 	for(int j=0; j < i; j++) {
 		aBack(&data , nRead[j]);
 	}

	rFront(&data);

	printf("next fit\n\n");
	next(data,i);
	printf("\n");

	clearData(&data);

 	for(int j = 0; j < i; j++) {
 		aBack(&data,wRead[j]);
 	} 
	rFront(&data);
	printf("worst fit\n\n");
	worst(data,i);
	
	printf("\n");
	
	return 0;
}