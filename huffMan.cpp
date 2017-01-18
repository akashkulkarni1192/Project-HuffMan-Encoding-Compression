#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

using namespace std;
struct node{
	char alpha[5];
	float prob;
	node *left;
	node *right;
};
typedef struct node NODE;
NODE* arrayNode[20];
float uniqueCharProb[20]={0.0};
char uniqueChar[20];
char inputString[20];
char code[20][10];

template<class T>
T* sort(T *variable,int length){
	int i,j,k;
	T temp;
	for(i=0;i<length;i++)
		for(j=0;j<length-1-i;j++)
			if(*(variable+j)<*(variable+j+1)){
				temp=*(variable+j);
				*(variable+j)=*(variable+j+1);
				*(variable+j+1)=temp;
			}
	strcpy(inputString,variable);
}
void sortNode(int n){
	int i,j;
	NODE *tempNode = new NODE();
	for(i=1;i<n;i++){
		tempNode = arrayNode[i];
		j=i-1;
		while(j>=0 && tempNode->prob>=arrayNode[j]->prob){
			arrayNode[j+1]=arrayNode[j];
			j--;
		}
		arrayNode[j+1]=tempNode;
	}
}

int getIndex(char ch,char input[]){
	int i;
	for(i=0;i<strlen(input);i++)
		if(ch==input[i])		
			return i;
	return -1;
}

void findProb(char *input){
	int i;
	for(i=0;*(input+i)!='\0';i++)
		uniqueCharProb[getIndex(*(input+i),uniqueChar)]++;
	for(i=0;uniqueCharProb[i];i++)
		uniqueCharProb[i]/=strlen(input);
}
void fillUniqueChar(char input[]){
	int i,j=0,k=0;
	uniqueChar[k++]=input[0];
	for(i=1;i<strlen(input);i++){
		if(input[i]<input[j]){
			uniqueChar[k++]=input[i];
			j=i;
		}
	}
	uniqueChar[k]='\0';
	
}
void startHuffmaning(){
	int i,till,j;
	char tempChar[5];
	till=strlen(uniqueChar);
	cout<<"\n\nSteps in HUFFMANING :";
	cout<<endl;
	for(j=0;j<strlen(uniqueChar);j++){
		cout<<arrayNode[j]->alpha<<"\t";
	}
	cout<<endl;
	for(j=0;j<strlen(uniqueChar);j++){
		cout<<arrayNode[j]->prob<<"\t";
	}
	for(i=till-1;i>0;i--){
		NODE *newParent = new NODE();
		NODE *leftNode = new NODE();
		NODE *rightNode = new NODE();
		leftNode = arrayNode[i-1];
		rightNode = arrayNode[i];
		strcpy(tempChar,leftNode->alpha);
		strcpy(newParent->alpha,strcat(tempChar,"'"));
		newParent->prob = leftNode->prob+rightNode->prob;
		
		newParent->left=leftNode;
		newParent->right=rightNode;
		arrayNode[i-1]=newParent;

		sortNode(i);
		cout<<endl;
		for(j=0;j<i;j++){
			cout<<arrayNode[j]->alpha<<"\t";
		}
		cout<<endl;
		for(j=0;j<i;j++){
			cout<<arrayNode[j]->prob<<"\t";
		}
	}
}
void formHuffmanTree(){
	int i;
	char tempChar[2];
	for(i=0;i<strlen(uniqueChar);i++){
		NODE *newNode = new NODE();
		tempChar[0]=uniqueChar[i];
		tempChar[1]='\0';
		strcpy(newNode->alpha,tempChar);
		newNode->prob = uniqueCharProb[i];
		newNode->left=NULL;
		newNode->right=NULL;
		arrayNode[i]=newNode;
	}
	sortNode(i);

	startHuffmaning();
}
void inOrderTraversal(NODE *root){
	if(root==NULL)
		return;
	inOrderTraversal(root->left);
	cout<<"\t"<<root->alpha<<":"<<root->prob;
	inOrderTraversal(root->right);
}
void findPath(NODE *root,char c,char path[],int i){
	char tempPath[10];
	if(root==NULL)
		return;
	if((c==root->alpha[0]) && ((strlen(root->alpha)==1)))
		strcpy(code[i],path);
	strcpy(tempPath,path);
	strcat(tempPath,"0");
	findPath(root->left,c,tempPath,i);
	tempPath[strlen(tempPath)-1]='1';
	findPath(root->right,c,tempPath,i);
}
void getCode(){
	int i;
	for(int i=0;i<strlen(uniqueChar);i++){
		findPath(arrayNode[0],uniqueChar[i],"",i);
	}
}
int main()
{
	int inputLength,i;
	cout<<"\nEnter InputString :";
	cin>>inputString;
	
	for(i=0;*(inputString+i);i++);

	sort(inputString,i);
	fillUniqueChar(inputString);
	findProb(inputString);
	

	
	cout<<"\n\tProbabilities :"<<endl;
	for(i=0;i<strlen(uniqueChar);i++)
		cout<<uniqueChar[i]<<"\t";
	cout<<endl;
	for(i=0;i<strlen(uniqueChar);i++)
		cout<<uniqueCharProb[i]<<"\t";	
	cout<<"\n\nSorted String: "<<inputString;
	
	formHuffmanTree();
	cout<<"\nTesting using inOrderTraversal :";
	
	inOrderTraversal(arrayNode[0]);
	getCode();

	cout<<endl<<"Codes  :\n";
	for(int i=0;i<uniqueChar[i];i++){
		cout<<uniqueChar[i]<<" : "<<code[i]<<endl;
	}
	return 0;
}
	
	
