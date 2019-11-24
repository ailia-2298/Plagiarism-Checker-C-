/*Plagiarism Check:
In this problem user will enter name of 2 files.
First file will be considered as source means it is to be checked with second file.
System will open both files in text mode and compare their similarity ignoring upper and lower case.
After check give summary no of total words in first file. No of words found in file B.
Similarity based on percentage of words found.
Save result of each usage in some binary file.
Give option to see previous results.*/
#include<iostream>
#include<fstream>
#include<string>
#define asciivalue 32
using namespace std;
int Fileexist(string filename){
	ifstream in(filename.c_str());
	if (FILE*file=fopen(filename.c_str(),"r")){		//check whether the file is in the same folder or not
        fclose(file);
        return true;
    } 
	else
        return false;
}
int countfile(string filename){
	
	int count=0;
	string word;
	ifstream in(filename.c_str());
	while (!in.eof()){
    	    in>>word;
		    count++;								//counting the total words in a file
	}
	in.close();
	return count;
}
void storewords(ifstream &in,string *array){
	
	string word;
	int c=0;						//create dynamic array for file
	while (!in.eof()){
			in>>word;
			for (int i=0;i<word.length();i++)
			{
       			if ('A'<=word[i] && word[i]<='Z')		//converting any capital words to small words
       				word[i]=word[i]+asciivalue;
       		
	            	array[c]=word;
			}								//store data of file in array
		c++;
	}
}
int similarity(string array1[],string array2[],int size1, int size2){
	int x,y;
	int sim=0;
	for (x=0;x<size1;x++){
		y=0;
		while(y<size2){
			if (array1[x]==array2[y]){
				sim++;
				break;
			}
			y++;
		}
	}
	return sim;
}
int main(){

	char w;
	do{
		cout<<"\nDo you want to use plagiarism checker?(y or n)";
		cin>>w;
	if (w=='n')
		break;
		
	float percentage,*data;
	int count1,count2,count,similar;
	bool file1_exists,file2_exists;
	string file1,file2,*first,*second,word1,word2,prv_result;
	
	//system("cls"); 
	cout<<"Enter the name of first file:";
	cin>>file1;
	
	cout<<"Enter the name of the second file:";
	cin>>file2;
	
	file1_exists=Fileexist(file1);
    file2_exists=Fileexist(file2);
    
    if(file1_exists && file2_exists){
	
		count1=countfile(file1);
		count2=countfile(file2);
		first=new string [count1];
		second=new string [count2];
		
		ifstream inf1(file1.c_str());
		storewords(inf1,first);
		inf1.close();
		
		ifstream inf2(file2.c_str());
		storewords(inf2,second);
		inf2.close();
		
		similar=similarity(first,second,count1,count2);
		
		cout<<"\nno of total words in first file:"<<count1;
		cout<<"\nNo of words found in second file:"<<count2;
		percentage=(similar*100)/count1;
		cout<<"\nsimilarity percentage:"<<percentage;
	
		ofstream out("data.bin",ios::binary|ios::app);
		out.write((char*)&percentage,sizeof(float));
		out.close();
	}
	
	else{
		if(file1_exists==false && file2_exists==false)
			cout<<"Both of your files are missing\n";
		else if(file1_exists==false)
			cout<<file1<<" does not exists\n";
		else if(file2_exists==false)
			cout<<file2<<" does not exists\n";
	}
	
	cout<<"\n\nwant to see previous result?(yes or no)";
	cin>>prv_result;
	
	if (prv_result=="yes"){
		
		int beg,end,size,var;
		ifstream in("data.bin",ios::binary);
		
		in.seekg(0,ios::beg);
		beg=in.tellg();
		in.seekg(0,ios::end);
		end=in.tellg();
		size=end-beg;
		var=size/sizeof(float);
		
		data=new float[var];
		in.seekg(0,ios::beg);
		in.read((char*)data,sizeof(float)*var);
		
		for (int x=0;x<var;x++)
			cout<<x+1<<':'<<"previous files had "<<data[x]<<"% similarity.\n";
		
		delete []data;
		in.close();
	}
	
	else if (prv_result=="no")
		cout<<"Ok, Thanks.";                     
}
	while (w!='n');
	return 0;
}

