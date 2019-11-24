#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main () {
	int c=0,i=0,a=0;
	string name1,name2;
	string *s,*p,word1,word2;
	cin>>name1;
	ifstream inf(name1.c_str());
	while (!inf.eof()){
        inf>>word1;
		c++;
	}
	cout << c <<endl;
	inf.close();
	s=new string [c];
	int z=0;
	ifstream in2(name1.c_str());
	while (!in2.eof()){
		in2>>s[z];
		z++;
	}
	inf.close();
	cin >> name2;
	ifstream in(name2.c_str());
	while (!in.eof()){
		in>>word2;
		i++;
	}
	in.close();
	cout << i << endl;
	p=new string [i];
	int q=0;
	ifstream in3(name2.c_str());
	while (!in3.eof()){
		in3>>p[q];
		q++;
	}
	int count=0,b;
	for (int a=0;a<c;a++){   
	    b=0;
		while(b<i){
			 if (s[a]==p[b]){
				count++;
			    break;
			 }
		b++;
		}
	}
	float percentage;
	cout << count <<' '<< i <<endl;
	cout << "number of same words are "<<count<<endl;
	percentage=(count*1.0)/(i*1.0)*100;
	cout << percentage<<"% percent words of files are same";
}
