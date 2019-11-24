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
int countline(string filename){
	
	int count=0;
	string word;
	ifstream in(filename.c_str());
	while (!in.eof()){
    	    getline(in,word);
		    count++;								//counting the total lines in a file
	}
	in.close();
	return count;
}
void storelines(ifstream &in,string *array,int count){
	
	string word;
	while (!in.eof()){
		getline(in,word);
		for (int i=0;i<count;i++)
		   	array[i]=word;
	}
}
int linesSimilarityChecker(string line1,string line2){
string word="";
int similarWords=0;
for(int i=0;i<line1.length();i++){
		word=word+line1[i];
	
	if(line1[i]==' '||i==line1.length()-1){
		if (line2.find(word) != string::npos) {
			//.. found.
			similarWords++;
			line2.replace(line2.find(word), word.length(), "");
		}
		word="";
	}
}
	return similarWords;
}
int main(){

	char w;
	do{
		system("pause");
		system("cls");
		cout<<"\nDo you want to use plagiarism checker?(y or n)";
		cin>>w;
		if (w=='n')
			break;
			
		float percentage,*data;
		int count1,count2,count,similarwords,*similar;
		bool file1_exists,file2_exists;
		string file1,file2,*first,*second,word1,word2,prv_result;
 
		cout<<"Enter the name of first file:";
		cin>>file1;
	
		cout<<"Enter the name of the second file:";
		cin>>file2;
	
		file1_exists=Fileexist(file1);
	    file2_exists=Fileexist(file2);
    
	    if(file1_exists && file2_exists){
	
			count1=countline(file1);
			count2=countline(file2);
    
			first=new string [count1];
			second=new string [count2];
		
			ifstream inf1(file1.c_str());
			storelines(inf1,first,count1);
			inf1.close();
		
			ifstream inf2(file2.c_str());
			storelines(inf2,second,count2);
			inf2.close();
		
			int line,totalwrds=0,maX;
			float highest,per,allpers[count1];
			for (int i=0;i<count1;i++){
				similar=new int[count2];
				
				for (int j=0;j<count2;j++){
					similarwords=linesSimilarityChecker(first[i],second[j]);
					similar[j]=similarwords;
					for (int l=0; l<second[j].length(); l++)
       					if (second[j][l] == ' ')
        	    			totalwrds++;		
				}
				
				maX=similar[0];
				line=1;
				for (int o=1;o<count2;o++)
					if (maX<similar[o]){
						maX=similar[o];
						line=o;
					}
				
				per=(maX*100)/totalwrds;
				cout<<i+1<<" line of first file has maximum similarity percentage "<<per<<" with the "<<line+1<<" line of the second file.\n";
				allpers[i]=per;
			}
		
			highest=allpers[0];
				for (int p=0;p<count1;p++)
					if (highest<=allpers[p])
						highest=allpers[p];
						
			
			cout<<"\nno of total lines in first file:"<<count1;
			cout<<"\nNo of lines found in second file:"<<count2;
			cout<<"\nsimilarity percentage:"<<highest;
		
			ofstream out("data.bin",ios::binary|ios::app);
			out.write((char*)&highest,sizeof(float));
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
	while (w=='y');
		return 0;
}

