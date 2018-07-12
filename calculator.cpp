#include<bits/stdc++.h>
using namespace std;
#define pi acos(-1)
///***Function Prototypes***///
bool isOperand(char ch);
bool isArithematic(string s);
bool isTriagonomatric(string s);
string doubletoString(double x);
string convert(string s);
int prec(char ch);
string evaluate(string a,string b,string c);
int powerint(int n,int x);
double powerdoub(double n,int x);
///*************************///
int powerint(int n,int x){
    int res=1,i;
    for(i=0;i<x;i++)res*=n;
    return res;
}
double powerdoub(double n,int x){
    double res=1;
    int i;
    for(i=0;i<x;i++)res*=n;
    return res;
}
bool isOperand(char ch){
    return ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch=='.');
}
bool isArithematic(string s){
    return ((s[0]=='-'&&(s[1]>='0'&&s[0]<='9'))||(s[0]>='0'&&s[0]<='9')||s[0]=='.');
}
bool isTriagonomatric(string s){
    string s1;
    for(int i=0;s[i]>='a'&&s[i]<='z';i++)s1+=s[i];
    return ((s1=="cos")||(s1=="sin")||(s1=="tan")||(s1=="cosec")||(s1=="sec")||(s1=="cot")||(s1=="log"));
}
string convert(string s){
    string s1;
    char c[10];
    int i,b=0,a=0;
    double d,chk;
    for(i=0;s[i]>='a'&&s[i]<='z';i++,b++)s1+=s[i];
    for(int i=b;i<s.length();i++)c[a++]=s[i];
    d=atof(c);
    if(s1=="sin")d=sin(d*pi/180);
    else if(s1=="cosec"){
        chk=sin(d*pi/180);
        if(chk<1e-9){
            printf("Undetermined\n");
            return "r";
        }
        else d=1/chk;
    }
    else if(s1=="cos")d=cos(d*pi/180);
    else if(s1=="sec"){
        chk=cos(d*pi/180);
        if(chk<1e-9){
            printf("Undetermined\n");
            return "r";
        }
        else d=1/chk;
    }
    else if(s1=="tan"){
        chk=cos(d*pi/180);
        if(chk<1e-9){
            printf("Undetermined\n");
            return "r";
        }
        else if(d==45)d=1;
        else d=sin(d*pi/180)/chk;
    }
    else if(s1=="cot"){
        chk=sin(d*pi/180);
        if(chk<1e-9){
            printf("Undetermined\n");
            return "r";
        }
        else if(d==45)d=1;
        else d=cos(d*pi/180)/chk;
    }
    else if(s1=="log"){
        d=log10(d);
    }
    bool flag=true;
    if(d<0){
        d=-1*d;
        flag=false;
    }
    s1=doubletoString(d);
    if(!flag)s1="-"+s1;
    return s1;
}
string doubletoString(double x){
    int intpart;
    float decpart;
    intpart=x;
    decpart=x-(double)intpart;
    string s1,s2;
    if(intpart==0)s1+='0';
    else{
        while(intpart!=0){
            s1+=((intpart%10)+'0');
            intpart/=10;
        }
        reverse(s1.begin(),s1.end());
    }
    for(int i=0;i<9;i++){
        decpart*=10;
    }
    intpart=decpart;
    if(intpart!=0){
        while(intpart!=0){
            s2+=((intpart%10)+'0');
            intpart/=10;
        }
        int j;
        for(j=0;s2[j]=='0';j++);
        s2.erase(0,j);
        reverse(s2.begin(),s2.end());
        s1+='.';
        s1+=s2;
    }
    return s1;
}
int prec(char ch){
    switch(ch){
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}
string evaluate(string a,string b,string c){
    string l;
    char m[a.length()+1],n[b.length()+1];
    int len,j,intpart;
    for(int i=0;i<a.length();i++)m[i]=a[i];
    for(int i=0;i<b.length();i++)n[i]=b[i];
    if(strstr(m,".")||strstr(n,".")){
        st:
        double doubx=atof(m),douby=atof(n);
        if(c =="+")doubx+=douby;
        else if(c =="-")doubx-=douby;
        else if(c =="*")doubx*=douby;
        else if(c =="/"){
            if(douby==0){
                printf("Can not be divided by zero!!!\n");
                return "r";
            }
            else doubx=doubx/douby;
        }
        else if(c=="^")doubx=powerdoub(doubx,douby);
        bool flag=false;
        if(doubx<0){
            doubx*=(-1.0);
            flag=true;
        }
        string s1=doubletoString(doubx);
        if(flag)s1="-"+s1;
        return s1;
    }
    else{
        int intx=atoi(m),inty=atoi(n);
        if(c =="+")intx+=inty;
        else if(c =="-")intx-=inty;
        else if(c =="*")intx*=inty;
        else if(c =="/"){
            if(inty==0){
                printf("Can not be divided by zero!!!\n");
                return "r";
            }
            else if(intx<inty)intx=0;
            else if(intx%inty==0)intx=intx/inty;
            else goto st;
        }
        else if(c=="^")intx=powerint(intx,inty);
        bool flag=false;
        if(intx<0){
            flag=true;
            intx*=(-1);
        }
        if(intx==0)l+='0';
        else{
            while(intx!=0){
                l+=((intx%10)+'0');
                intx/=10;
            }
        }
        reverse(l.begin(),l.end());
        if(flag)l="-"+l;
        return l;
    }
}
int main(){
    //freopen("calculator.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int i,j;
    string t;
    string s,n;
    while(1){
        start:
        beg:
        stack<char>c;
        vector<string>p;
        printf("Enter the expression (Press q for quit) :\n");;
        cin>>s;
        if(s!="q")cout<<"The expression : "<<s<<endl;
        else if(s=="q"){
            printf("Good Bye!!!\n");
            break;
        }
        if(s[0]=='-'||s[0]=='+')s="0"+s;
        for(i=0;i<s.length();i++){
            if(s[i]=='('){
                if(s[i+1]=='-')s.insert(i+1,"0");
            }
        }
        c.push('(');
        s+=')';
        int count=0;
        for(i=0;i<s.length();i++){
            if(isOperand(s[i])){
                n.clear();
                n+=s[i];
                for(int j=i+1;j<s.length();j++){
                    if(isOperand(s[j]))n+=s[j];
                    else{
                        i=j-1;
                        break;
                    }
                }
                if(n=="log0"){
                    printf("Undetermined\n");
                    n="r";
                }
                else if(isTriagonomatric(n))n=convert(n);
                if(n=="r"){
                    goto beg;
                }
                else if(!isArithematic(n)){
                    printf("Invalid\n");
                    goto start;
                }
                p.push_back(n);
                count++;
            }
            else if(s[i]=='(')c.push(s[i]);
            else if(s[i]==')'){
                while(!c.empty()&&c.top()!='('){
                    t=c.top();
                    c.pop();
                    p.push_back(t);
                    count++;
                }
                if(c.top()=='(')c.pop();
            }
            else{
                while(!c.empty()&&prec(s[i])<=prec(c.top())){
                    t=c.top();
                    c.pop();
                    p.push_back(t);
                    count++;
                }
                c.push(s[i]);
            }
        }
        /*printf("Postfix expression is: ");
        for(int i=0;i<p.size();i++)cout<<p[i]<<" ";
        cout<<endl;*/
        while(!c.empty()){
            t=c.top();
            p.push_back(t);
            count++;
            c.pop();
        }
        stack<string>value;
        for(i=0;i<count;i++){
            if(isArithematic(p[i])){
                value.push(p[i]);
            }
            else{
                string op3,op4,res;
                op3=value.top();
                value.pop();
                op4=value.top();
                value.pop();
                swap(op3,op4);
                res=evaluate(op3,op4,p[i]);
                if(res=="r"){
                    goto start;
                }
                value.push(res);
            }
        }
        printf("The answer is : ");
        cout<<value.top()<<endl;
        value.pop();
    }
    return 0;
}
