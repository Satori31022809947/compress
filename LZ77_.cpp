#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define A first
#define B second 
const int input_lim=50000;
const int window_lim=50000;
class node{
    public:
        int v[8];
};
char val[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 
int a[input_lim+5000];
int w[window_lim+5000];
pair<int,int> chk(int len){
	pair<int,int>res=mp(-1,0);
	for (int st=1;st+res.B<=window_lim;st++)if (a[1]==w[st]){
		for (int i=1;i<=len&&st+i-1<=window_lim&&w[st+i-1]==a[i];i++){
			if (i>res.B){
				res=mp(window_lim-st+1,i);
			}
		}
	}
	return res;
}
void del_window(int len){
	for (int i=1;i+len-1<=window_lim;i++){
		w[i]=w[i+len-1];
	}
}
void add_window(int len){
	for (int i=1;i<=len;i++){
		w[window_lim-len+i]=a[i];
	}
}
void del_input(int len,int tot){
	for (int i=1;i+len-1<=tot;i++){
		a[i]=a[i+len-1];
	}
}


int main(){
	node s,lst;       
    ifstream inFile("DataFrameM256R11.bin",ios::in|ios::binary); //二进制读方式打开
    std::ofstream fout("DataFrameM256R11.out", std::ios::binary);
    
    if(!inFile) {
        cout << "error" <<endl;
        return 0;
    }
    int tot=0;
    int num=0;
    while(inFile.read((char *)&s, sizeof(s))) { //一直读到文件结束
		if (num){
			for (int i=0;i<8;i++){
				s.v[i]^=lst.v[i];
			}
		}
		lst=s;
		for (int i=0;i<8;i++){
    		for (int k=0;k<32;k+=4){
    			a[++tot]=(s.v[i]>>(k))&15;
    		}
		}
		num++;
		if(num%1000000==0)cerr<<num<<endl;
		for (;tot>=input_lim;){
			pair<int,int> tmp=chk(tot);
			short d,l,c;
			if (tmp.A!=-1){
	    		d=tmp.A;
	    		l=tmp.B;
	    		c=a[l+1];
			}
			else{
				d=0;
				l=0;
				c=a[1];	
			}
			fout.write((char*)&d, sizeof(short));
			fout.write((char*)&l, sizeof(short));
			fout.write((char*)&c, sizeof(short));
		    del_window(l+1);
		    add_window(l+1);
			del_input(l+1,tot);
			tot-=l+1;
		}
	}
	for (;tot>=0;){
		pair<int,int> tmp=chk(tot);
		short d,l,c;
		if (tmp.A!=-1){
	   		d=tmp.A;
	   		l=min(tmp.B,tot-1);
	   		c=a[l+1];
		}
		else{
			d=0;
			l=0;
			c=a[1];	
		}
		fout.write((char*)&d, sizeof(short));
		fout.write((char*)&l, sizeof(short));
		fout.write((char*)&c, sizeof(short));
	    del_window(l+1);
	    add_window(l+1);
		del_input(l+1,tot);
		tot-=l+1;
	}
    inFile.close();
    return 0;
}
