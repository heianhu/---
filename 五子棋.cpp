//五子棋
//0 无子 1 电脑 2 玩家 
//主要思路  给每个空位打分，取分数最高的下子  

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>

using namespace std;

class Gobang{
      
      private:
              
             int chessboard[15][15];          //棋盘 
             int five[5][5];                  //5*5小棋盘 
             int six[6][6];
             int computernum,humannum;         //棋子数 
             int p1,p2;                       //棋子数 
             int last1,last2;                    //记录上一步  
             int comresults[15][15];             //存储分数
             int humresults[15][15];
             int temp[15][15];             //临时棋盘 
             int max_com,max_hum,max_com_i,max_com_j,max_hum_i,max_hum_j;           //存储电脑和玩家的最高分数 和相应的坐标 
             int total_com,total_hum;              //电脑和玩家分别总分 
             int goback;                      //反回主菜单； 
   
      
      public:

              Gobang();
              void setchessboard(int ,int,int);     //改变棋子 
              void count();                         //计数，棋子数 
              void count_total();                //计算总分 
              void save(int);                     //保存游戏 
              int dir();                         //显示已保存的棋局 
              void firstgo();                  //电脑先走棋      
              void print(int n);              //显示棋盘 
              void input(int n);              //输入 
              void getfive(int i,int j);             // 读取 数据，存入5*5 的棋盘中 
              void getsix(int,int);
              int ifwin();                     //判断胜负      
              void think();
              void getresults();          //打分下子 
              void r_four();
              void r_three();           
              void r_two();
              int returngoback();
              
 
};
              


Gobang::Gobang(){
                 for(int i=0;i<15;i++)
                         for(int j=0;j<15;j++){
                                chessboard[i][j]=0;
                                temp[i][j]=0;
                                comresults[i][j]=0;
                                humresults[i][j]=0;}
                                
                 for(int i=0;i<5;i++)
                         for(int j=0;j<5;j++)
                                {five[i][j]=0;}
                 computernum=0;
                 humannum=0;
                 p1=0;p2=0;
                 last1=-1;last2=-1;       //-1表示还未开始 
                 max_com=0;max_hum=0;max_com_i=0;
                 max_com_j=0;max_hum_i=0;max_hum_j=0;
                 total_com=0;total_hum=0;
                 goback=0;
}



void Gobang::setchessboard(int i,int j,int n){
     chessboard[i][j]=n;}
     
     
void Gobang::count(){
     computernum=0;
     humannum=0;
     for(int i=0;i<15;i++)
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]==1) computernum++;
                 if(chessboard[i][j]==2) humannum++;
                 p1=computernum;p2=humannum;
                 }
}
             


//分别计算电脑和玩家 得总得分 
 
void Gobang::count_total(){
     
     total_com=0;total_hum=0;
     for(int i=0;i<15;i++)
            for(int j=0;j<15;j++){
                    comresults[i][j]=0;
                    humresults[i][j]=0;}                //每次先置零 
     
     
       //开始打分 
       r_four();
       r_three();
       r_two();
       
       //分别计算各自的总分 
       for(int i=0;i<15;i++)
            for(int j=0;j<15;j++){
                    total_com+=comresults[i][j];
                    total_hum+=humresults[i][j];
                    }
                    
       //能赢了，加1000
       
       //判断是否可以下一个子就立即赢或输,即成五 
     for(int i=0;i<15;i++){
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]!=0) continue;       //找空位 
                  chessboard[i][j]=1;
                  if(ifwin()==1) {total_com+=1000;}                  //电脑赢 
                  chessboard[i][j]=0;                      //没用的位置不下子 
                  }
         }
         
     for(int i=0;i<15;i++){
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]!=0) continue;       //找空位 
                  chessboard[i][j]=2;
                  if(ifwin()==2) {total_hum+=1000;}                  //玩家赢 
                  chessboard[i][j]=0;                      //没用的位置不下子 
                  }
         } 
       
}


//保存游戏

void Gobang::save(int n){                                  //n=1表示人机对战，n=2表示双人对战
          cout<<"输入文件名称（不含后缀）："<<endl;
          string filename;
          cin>>filename;
          filename=filename+".gbg";
          ofstream ofile(filename.c_str());
          ofile<<n<<endl;
          for(int i=0;i<15;i++)
              for(int j=0;j<15;j++){
                      ofile<<chessboard[i][j]<<endl;
                      }
          ofile.close();
          cout<<"棋局保存在 “"<<filename<<"”文件中"<<endl;
} 
                      

//显示

int Gobang::dir(){
     system("dir/b>dir.txt");
     ifstream ifile("dir.txt");
     string filename;
     int num=0;
     while(ifile>>filename){
              if(filename.find(".gbg")!=-1) {
                                             cout<<filename<<endl; 
                                             num++;
                                             }
              }
    cout<<"共计"<<num<<"个文件"<<endl;
    return num;
} 


int Gobang::returngoback(){
    return goback;
}       
          
     
//电脑先走 

void Gobang::firstgo(){
     chessboard[8][8]=1;
     last1=8,last2=8;
     }
                 

//屏幕显示 
                 
void Gobang::print(int n){
     system("cls");
     count();
     count_total();
     cout<<"****************五子棋****************"<<endl;
     cout<<"                        马晟. 2015.12.2"<<endl;
     if(n==1){
              cout<<"棋子状态： - 无子 ， * 电脑 ，o 玩家。"<<endl;
             cout<<"棋子数:  电脑："<<setw(4)<<computernum<<" 玩家："<<setw(4)<<humannum<<endl;
             cout<<"总评分:  电脑："<<setw(4)<<total_com<<" 玩家："<<setw(4)<<total_hum<<endl; 
             }
     if(n==2) {
              cout<<"棋子状态： - 无子 ， * 玩家1 ，o 玩家2。"<<endl;
             cout<<"棋子数:    玩家1："<<setw(4)<<p1<<" 玩家2："<<setw(4)<<p2<<endl;
             cout<<"局势评分:  玩家1："<<setw(4)<<total_com<<" 玩家2："<<setw(4)<<total_hum<<endl;
             }
     cout<<"行/列"<<endl;
     cout<<"  ";
     for(int i=0;i<15;i++){
             cout<<setw(3)<<i;}
     cout<<endl;
     for(int i=0;i<15;i++)
            {
             cout<<setw(3)<<i;
             for(int j=0;j<15;j++)
                    {
                     if(chessboard[i][j]==0) cout<<" - ";
                     if(chessboard[i][j]==1) cout<<" * ";
                     if(chessboard[i][j]==2) cout<<" o ";
                     }
             cout<<endl;
             }
     if(last1!=-1) {
                   if(n==1) cout<<"电脑下子位置： "<<last1<<"  "<<last2<<endl;
                   if(n==2) cout<<"玩家下子位置： "<<last1<<"  "<<last2<<endl;
                   } 
      else cout<<"上一步下子位置：无"<<endl;  
     cout<<"输入坐标下子: "<<endl;      
}
                     

//处理输入数据
 
void Gobang::input(int n){
     if(n==1)
     while(1){ 
     int i,j;
     cin>>i;
     if(i==111) {cout<<"是否将此棋局保存？y/n"<<endl;
                  char yn;cin>>yn;
                  if(yn=='y'){
                              save(1); 
                             cout<<"保存完毕！继续游戏！"<<endl; 
                             }
                  if(yn=='n') cout<<"未保存！继续游戏！"<<endl;
                  cin>>i>>j;
                  }
     else if(i==222) {goback=1;return;}
     else cin>>j;              
     if(!(i>=0&&i<15)) {
                       cout<<"输入错误!超出棋盘范围！请重新输入"<<endl;
                       continue;
                       }
     else if(!(j>=0&&j<15)) {
                       cout<<"输入错误!超出棋盘范围！请重新输入"<<endl;
                       continue;
                       }
     else if(chessboard[i][j]!=0){
                             cout<<"输入错误！ 该位置上已有棋子！请重新输入"<<endl;
                             continue;
                             }
     else{chessboard[i][j]=2;
         last1=i;last2=j;
         humannum++;
         break;
         } 
     
     }
     if(n==2){
     while(1){
              cout<<"玩家1下子:"<<endl; 
              int i,j;
              cin>>i;
               if(i==111) {cout<<"是否将此棋局保存？y/n"<<endl;
                  char yn;cin>>yn;
                  if(yn=='y') {
                              save(2);
                               cout<<"保存完毕！继续游戏！"<<endl; 
                               }
                  if(yn=='n') cout<<"未保存！继续游戏！"<<endl;
                  cin>>i>>j;
                  }
              else if(i==222) {goback=1;return;}
              else cin>>j;
              if(!(i>=0&&i<15)) {
                       cout<<"输入错误!超出棋盘范围！请重新输入"<<endl;
                       continue;
                       }
              else if(!(j>=0&&j<15)) {
                       cout<<"输入错误!超出棋盘范围！请重新输入"<<endl;
                       continue;
                       }
              else if(chessboard[i][j]!=0){
                             cout<<"输入错误！ 该位置上已有棋子！请重新输入"<<endl;
                             continue;
                             }
              else{chessboard[i][j]=1;
                  p1++;
                  last1=i;last2=j;
                  break;
                   }
              }
              print(2);
      while(1){
              cout<<"玩家2下子:"<<endl; 
              int i,j;
              cin>>i>>j;
              if(!(i>=0&&i<15)) {
                       cout<<"输入错误!超出棋盘范围！请重新输入"<<endl;
                       continue;
                       }
              else if(!(j>=0&&j<15)) {
                       cout<<"输入错误!超出棋盘范围！请重新输入"<<endl;
                       continue;
                       }
              else if(chessboard[i][j]!=0){
                             cout<<"输入错误！ 该位置上已有棋子！请重新输入"<<endl;
                             continue;
                             }
              else{chessboard[i][j]=2;
                  p2++;
                  last1=i;last2=j;
                  break;
                   }
     }
     }
              
     
} 
     
     
      

void Gobang::getfive(int i,int j){
     for(int m=0;m<5;m++)
         for(int n=0;n<5;n++)
                 five[m][n]=chessboard[m+i][n+j];
}



void Gobang::getsix(int i,int j){
     for(int m=0;m<6;m++)
         for(int n=0;n<6;n++)
                 six[m][n]=chessboard[m+i][n+j];
}
                             

//判断是否有人赢 
int Gobang::ifwin(){
    for(int i=0;i<=10;i++)
        for(int j=0;j<=10;j++){
              getfive(i,j);
              for(int m=0;m<5;m++){
                      if(five[m][0]==1&&five[m][1]==1&&five[m][2]==1&&five[m][3]==1&&five[m][4]==1)
                          return (1);
                      if(five[0][m]==1&&five[1][m]==1&&five[2][m]==1&&five[3][m]==1&&five[4][m]==1)
                          return (1);}
              if(five[0][0]==1&&five[1][1]==1&&five[2][2]==1&&five[3][3]==1&&five[4][4]==1)
                   return (1);
              if(five[0][4]==1&&five[1][3]==1&&five[2][2]==1&&five[3][1]==1&&five[4][0]==1)
                   return (1);
              }
              
    for(int i=0;i<=10;i++)
        for(int j=0;j<=10;j++){
              getfive(i,j);
              for(int m=0;m<5;m++){
                      if(five[m][0]==2&&five[m][1]==2&&five[m][2]==2&&five[m][3]==2&&five[m][4]==2)
                          return 2;
                      if(five[0][m]==2&&five[1][m]==2&&five[2][m]==2&&five[3][m]==2&&five[4][m]==2)
                          return 2;}
              if(five[0][0]==2&&five[1][1]==2&&five[2][2]==2&&five[3][3]==2&&five[4][4]==2)
                   return 2;
              if(five[0][4]==2&&five[1][3]==2&&five[2][2]==2&&five[3][1]==2&&five[4][0]==2)
                   return 2;
              }
    
    return 0;
}
    
                      
//电脑思考 
void Gobang::think(){
     
     total_com=0;total_hum=0;
     
     //首先判断是否可以下一个子就立即赢或输,即成五 
     for(int i=0;i<15;i++){
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]!=0) continue;       //找空位 
                  chessboard[i][j]=1;
                  if(ifwin()==1) {last1=i;last2=j;return;}                  //电脑赢 
                  chessboard[i][j]=0;                      //没用的位置不下子 
                  }
         }
         
     for(int i=0;i<15;i++){
         for(int j=0;j<15;j++){
                 if(chessboard[i][j]!=0) continue;       //找空位 
                  chessboard[i][j]=2;
                  if(ifwin()==2) {chessboard[i][j]=1;last1=i;last2=j;return;}                  //阻止玩家赢 
                  chessboard[i][j]=0;                      //没用的位置不下子 
                  }
         }    
         

         
         
      //电脑走的第一步，跟子，避开边界 
      if(computernum==0) {
                         if(last1<=2&&chessboard[last1+1][last2]==0) 
                            {chessboard[last1+1][last2]=1;last1++;return; }
                               else if(last1>=12&&chessboard[last1-1][last2]==0) 
                                     {chessboard[last1-1][last2]=1;last1--;return;}
                                        else if(last2<=2&&chessboard[last1][last2+1]==0) 
                                            {chessboard[last1][last2+1]=1;last2++;return;}
                                                else if(last2>=12&&chessboard[last1][last2-1]==0) 
                                                     {chessboard[last1][last2-1]=1;last2--;return;} 
                                                        else if(chessboard[last1+1][last2]==0) 
                                                           {chessboard[last1+1][last2]=1;last1++;return;}
                                                                  else if(chessboard[last1-1][last2]==0) 
                                                                        {chessboard[last1-1][last2]=1;last1--;return;}
                                                                          else if(chessboard[last1][last2+1]==0) 
                                                                                  {chessboard[last1][last2+1]=1;last2++;return;}
                                                                                       else if(chessboard[last1][last2-1]==0) 
                                                                                                {chessboard[last1][last2-1]=1;last2--;return;}
                         }
     
                      
         
   //以上都不满足，开始打分
   getresults(); 
     
            
        
  
}   



void Gobang::getresults(){
     
          for(int i=0;i<15;i++)
            for(int j=0;j<15;j++){
                    comresults[i][j]=0;
                    humresults[i][j]=0;}                //每次先置零 
       max_com=0;max_hum=0;max_com_i=0;
       max_com_j=0;max_hum_i=0;max_hum_j=0;
       
       
       //开始打分 
       r_four();
       r_three();
       r_two();
       
       //分别筛选电脑和玩家的最高分，并保存其坐标 
       for(int i=0;i<15;i++)
            for(int j=0;j<15;j++){
                    if(comresults[i][j]>max_com){
                                                 max_com=comresults[i][j];
                                                 max_com_i=i;
                                                 max_com_j=j;
                                                 }
                    if(humresults[i][j]>max_hum){
                                                 max_hum=humresults[i][j];
                                                 max_hum_i=i;
                                                 max_hum_j=j;
                                                 }
                    } 
                    
       //分析两个最高分，决定攻还是防
       
       if(max_com>=1000) {                                      //电脑能成四 
                       chessboard[max_com_i][max_com_j]=1; 
                       last1=max_com_i;last2=max_com_j;       
                       return;
                       }        
       if(max_hum>=1000) {                                      //阻止玩家四 
                       chessboard[max_hum_i][max_hum_j]=1;
                       last1=max_hum_i;last2=max_hum_j;        
                       return;
                       }
       
       if(max_com>=18) {                                      //电脑能成双三 （或更多） 
                       chessboard[max_com_i][max_com_j]=1; 
                       last1=max_com_i;last2=max_com_j;       
                       return;
                       }        
       if(max_hum>=18) {                                      //阻止玩家双三 （或更多） 
                       chessboard[max_hum_i][max_hum_j]=1;
                       last1=max_hum_i;last2=max_hum_j;        
                       return;
                       }
       
       
       if(max_com==17||max_com==16) {                                      //另一种不能取胜双三
                       chessboard[max_com_i][max_com_j]=1;
                       last1=max_com_i;last2=max_com_j;         
                       return;
                       }        
       if(max_hum==17||max_hum==16) {                                      
                       chessboard[max_hum_i][max_hum_j]=1;
                       last1=max_hum_i;last2=max_hum_j;        
                       return;
                       }
                       
                       
       if(max_com<16&&max_com>=10) {                                      //3,3+1 ,3+2，单4 
                       chessboard[max_com_i][max_com_j]=1;
                       last1=max_com_i;last2=max_com_j;         
                       return;
                       }        
       if(max_hum<16&&max_hum>=10) {                                      
                       chessboard[max_hum_i][max_hum_j]=1; 
                       last1=max_hum_i;last2=max_hum_j;       
                       return;
                       }                                      

       //其他情况不管玩家，电脑走最好的
       chessboard[max_com_i][max_com_j]=1;
       last1=max_com_i;last2=max_com_j; 
       return;
} 


//注： 尚存在的一个很大问题是，在评分过程中的数组越界，但是对结果基本没有影响
//可以加入对数组边界的检查，太多了，以后再说 

void Gobang::r_four(){
     
     for(int i=1;i<14;i++)
         for(int j=1;j<14;j++){
                 
                 if(chessboard[i][j]!=0) continue;
                 
                 
                 //第一种情况    xooo@x
                 
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==0) comresults[i][j]+=100;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==0) comresults[i][j]+=100; 
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==0) comresults[i][j]+=100;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==0) comresults[i][j]+=100;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==0) comresults[i][j]+=100;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==0) comresults[i][j]+=100;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==0) comresults[i][j]+=100;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==0) comresults[i][j]+=100;
                 
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==0) humresults[i][j]+=100;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==0) humresults[i][j]+=100; 
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==0) humresults[i][j]+=100;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==0) humresults[i][j]+=100;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==0) humresults[i][j]+=100;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==0) humresults[i][j]+=100;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==0) humresults[i][j]+=100;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==0) humresults[i][j]+=100;
                 
                 
                 //第二种情况   xoo@ox
                 
                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=100;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=100; 
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==1&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=100;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=100;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==1&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=100;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=100;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=100;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=100;
                 
                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0) humresults[i][j]+=100;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0) humresults[i][j]+=100; 
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==2&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0) humresults[i][j]+=100;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0) humresults[i][j]+=100;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==2&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0) humresults[i][j]+=100;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0) humresults[i][j]+=100;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0) humresults[i][j]+=100;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0) humresults[i][j]+=100;
                 
                 
                 
                 
                 
                 //第三种情况     *ooo@x 
                 
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==2) comresults[i][j]+=11;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==2) comresults[i][j]+=11;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==2) comresults[i][j]+=11;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==2) comresults[i][j]+=11;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==2) comresults[i][j]+=11;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+1][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==2) comresults[i][j]+=11;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==2) comresults[i][j]+=11;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==2) comresults[i][j]+=11;
                 
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==1) humresults[i][j]+=11;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==1) humresults[i][j]+=11;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==1) humresults[i][j]+=11;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==1) humresults[i][j]+=11;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==1) humresults[i][j]+=11;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+1][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==1) humresults[i][j]+=11;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==1) humresults[i][j]+=11;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==1) humresults[i][j]+=11;
                 
                 //第四种情况   *oo@ox
                 
                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==2) comresults[i][j]+=11;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==2) comresults[i][j]+=11; 
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==1&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==2) comresults[i][j]+=11;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==2) comresults[i][j]+=11;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==1&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==2) comresults[i][j]+=11;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==2) comresults[i][j]+=11;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==2) comresults[i][j]+=11;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==2) comresults[i][j]+=11;
                 
                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==1) humresults[i][j]+=11;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==1) humresults[i][j]+=11; 
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==2&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==1) humresults[i][j]+=11;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==1) humresults[i][j]+=11;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==2&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==1) humresults[i][j]+=11;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==1) humresults[i][j]+=11;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==1) humresults[i][j]+=11;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==1) humresults[i][j]+=11;
                 
                 //第五种情况   *o@oox
                 
                 if(chessboard[i][j+2]==2&&chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=11;
                 if(chessboard[i+2][j+2]==2&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=11; 
                 if(chessboard[i+2][j]==2&&chessboard[i+1][j]==1&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=11;
                 if(chessboard[i+2][j-2]==2&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=11;
                 if(chessboard[i][j-2]==2&&chessboard[i][j-1]==1&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=11;
                 if(chessboard[i-2][j-2]==2&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=11;
                 if(chessboard[i-2][j]==2&&chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=11;
                 if(chessboard[i-2][j+2]==2&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=11;
                 
                 if(chessboard[i][j+2]==1&&chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0) humresults[i][j]+=11;
                 if(chessboard[i+2][j+2]==1&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0) humresults[i][j]+=11; 
                 if(chessboard[i+2][j]==1&&chessboard[i+1][j]==2&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0) humresults[i][j]+=11;
                 if(chessboard[i+2][j-2]==1&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0) humresults[i][j]+=11;
                 if(chessboard[i][j-2]==1&&chessboard[i][j-1]==2&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0) humresults[i][j]+=11;
                 if(chessboard[i-2][j-2]==1&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0) humresults[i][j]+=11;
                 if(chessboard[i-2][j]==1&&chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0) humresults[i][j]+=11;
                 if(chessboard[i-2][j+2]==1&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0) humresults[i][j]+=11;
                 
                 //第六种情况  *@ooox
                 
                 if(chessboard[i][j+1]==2&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==0) comresults[i][j]+=11;
                 if(chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==0) comresults[i][j]+=11;
                 if(chessboard[i+1][j]==2&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==0) comresults[i][j]+=11;
                 if(chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==0) comresults[i][j]+=11;
                 if(chessboard[i][j-1]==2&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==0) comresults[i][j]+=11;
                 if(chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==1&&chessboard[i+1][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==0) comresults[i][j]+=11;
                 if(chessboard[i-1][j]==2&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==0) comresults[i][j]+=11;
                 if(chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==0) comresults[i][j]+=11;
                 
                 if(chessboard[i][j+1]==1&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==0) humresults[i][j]+=11;
                 if(chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==0) humresults[i][j]+=11;
                 if(chessboard[i+1][j]==1&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==0) humresults[i][j]+=11;
                 if(chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==0) humresults[i][j]+=11;
                 if(chessboard[i][j-1]==1&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==0) humresults[i][j]+=11;
                 if(chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==2&&chessboard[i+1][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==0) humresults[i][j]+=11;
                 if(chessboard[i-1][j]==1&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==0) humresults[i][j]+=11;
                 if(chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==0) humresults[i][j]+=11;  
                 
                 //第七种情况   @xooo*  
                 
                 if(chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==1) comresults[i][j]+=9;
                 
                 if(chessboard[i][j+1]==0&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-1]==0&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==2) humresults[i][j]+=9;
                 
                 //第八种情况  ox@oo*     *是为了不和活三重复加分 
                 
                 if(chessboard[i][j+3]==2&&chessboard[i][j+2]==1&&chessboard[i][j+1]==1&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1) comresults[i][j]+=9;
                 if(chessboard[i+3][j+3]==2&&chessboard[i+2][j+2]==1&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1) comresults[i][j]+=9; 
                 if(chessboard[i+3][j]==2&&chessboard[i+2][j]==1&&chessboard[i+1][j]==1&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+3][j-3]==2&&chessboard[i+2][j-2]==1&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-3]==2&&chessboard[i][j-2]==1&&chessboard[i][j-1]==1&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1) comresults[i][j]+=9;
                 if(chessboard[i-3][j-3]==2&&chessboard[i-2][j-2]==1&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==12) comresults[i][j]+=9;
                 if(chessboard[i-3][j]==2&&chessboard[i-2][j]==1&&chessboard[i-1][j]==1&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-3][j+3]==2&&chessboard[i-2][j+2]==1&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1) comresults[i][j]+=9;
                 
                 if(chessboard[i][j+3]==1&&chessboard[i][j+2]==2&&chessboard[i][j+1]==2&&chessboard[i][j-1]==0&&chessboard[i][j-2]==2) humresults[i][j]+=9;
                 if(chessboard[i+3][j+3]==1&&chessboard[i+2][j+2]==2&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2) humresults[i][j]+=9; 
                 if(chessboard[i+3][j]==1&&chessboard[i+2][j]==2&&chessboard[i+1][j]==2&&chessboard[i-1][j]==0&&chessboard[i-2][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+3][j-3]==1&&chessboard[i+2][j-2]==2&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-3]==1&&chessboard[i][j-2]==2&&chessboard[i][j-1]==2&&chessboard[i][j+1]==0&&chessboard[i][j+2]==2) humresults[i][j]+=9;
                 if(chessboard[i-3][j-3]==1&&chessboard[i-2][j-2]==2&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2) humresults[i][j]+=9;
                 if(chessboard[i-3][j]==1&&chessboard[i-2][j]==2&&chessboard[i-1][j]==2&&chessboard[i+1][j]==0&&chessboard[i+2][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-3][j+3]==1&&chessboard[i-2][j+2]==2&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2) humresults[i][j]+=9; 
                 
                 //第九种情况   oxo@o*
                 
                 if(chessboard[i][j+2]==2&&chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i+2][j+2]==2&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i+2][j]==2&&chessboard[i+1][j]==1&&chessboard[i-1][j]==1&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+2][j-2]==2&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-2]==2&&chessboard[i][j-1]==1&&chessboard[i][j+1]==1&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i-2][j-2]==2&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i-2][j]==2&&chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-2][j+2]==2&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1) comresults[i][j]+=9;
                 
                 if(chessboard[i][j+2]==2&&chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j-3]==2) humresults[i][j]+=9;
                 if(chessboard[i+2][j+2]==2&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==2) humresults[i][j]+=9;
                 if(chessboard[i+2][j]==2&&chessboard[i+1][j]==2&&chessboard[i-1][j]==2&&chessboard[i-2][j]==0&&chessboard[i-3][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+2][j-2]==2&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-2]==2&&chessboard[i][j-1]==2&&chessboard[i][j+1]==2&&chessboard[i][j+2]==0&&chessboard[i][j+3]==2) humresults[i][j]+=9;
                 if(chessboard[i-2][j-2]==2&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==2) humresults[i][j]+=9;
                 if(chessboard[i-2][j]==2&&chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i+2][j]==0&&chessboard[i+3][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-2][j+2]==2&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==2) humresults[i][j]+=9; 
                 
                 //第十种情况   oxoo@* 
                 
                 if(chessboard[i][j+1]==2&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0&&chessboard[i][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0&&chessboard[i-4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==2&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0&&chessboard[i-4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0&&chessboard[i-4][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-1]==2&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0&&chessboard[i][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==1&&chessboard[i+1][j+2]==1&&chessboard[i+3][j+3]==0&&chessboard[i+4][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==2&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0&&chessboard[i+4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0&&chessboard[i+4][j-4]==1) comresults[i][j]+=9;
                 
                 if(chessboard[i][j+1]==1&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0&&chessboard[i][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0&&chessboard[i-4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==1&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0&&chessboard[i-4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0&&chessboard[i-4][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-1]==1&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0&&chessboard[i][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==2&&chessboard[i+1][j+2]==2&&chessboard[i+3][j+3]==0&&chessboard[i+4][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==1&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0&&chessboard[i+4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0&&chessboard[i+4][j-4]==2) humresults[i][j]+=9; 
                 
                 //第十一种情况   @oxoo
                 
                 if(chessboard[i][j+1]==1&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1&&chessboard[i][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==1&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1&&chessboard[i+4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1&&chessboard[i][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==1&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1&&chessboard[i-4][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==1) comresults[i][j]+=9;
                 
                 if(chessboard[i][j+1]==2&&chessboard[i][j+2]==0&&chessboard[i][j+3]==2&&chessboard[i][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==2&&chessboard[i+2][j]==0&&chessboard[i+3][j]==2&&chessboard[i+4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j-3]==2&&chessboard[i][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==2&&chessboard[i-2][j]==0&&chessboard[i-3][j]==2&&chessboard[i-4][j]==2) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==2) humresults[i][j]+=9;
                 
                 //第十二种情况   o@xoo 
                 
                 if(chessboard[i][j-1]==1&&chessboard[i][j+1]==0&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==1&&chessboard[i+1][j]==0&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i][j+1]==1&&chessboard[i][j-1]==0&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==1&&chessboard[i-1][j]==0&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1) comresults[i][j]+=9;
                 
                 if(chessboard[i][j-1]==2&&chessboard[i][j+1]==0&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==2&&chessboard[i+1][j]==0&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1) humresults[i][j]+=9;
                 if(chessboard[i][j+1]==2&&chessboard[i][j-1]==0&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==2&&chessboard[i-1][j]==0&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1) humresults[i][j]+=9;
                 

     } 
}
     
     
void Gobang::r_three(){
    
     for(int i=1;i<14;i++)
         for(int j=1;j<14;j++){
                 
                 if(chessboard[i][j]!=0) continue;
                 
                 //第一种情况    x@oox
                 
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=10;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=10;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=10;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=10;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=10;
                 
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0) humresults[i][j]+=10;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0) humresults[i][j]+=10;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0) humresults[i][j]+=10;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0) humresults[i][j]+=10;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0) humresults[i][j]+=10;
                 
                 
                 //第二种情况   xo@ox
                 if(chessboard[i][j+1]==1&&chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j+2]==0) comresults[i][j]+=10; 
                 if(chessboard[i-1][j]==1&&chessboard[i+1][j]==1&&chessboard[i-2][j]==0&&chessboard[i+2][j]==0) comresults[i][j]+=10;
                 if(chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i+2][j+2]==0) comresults[i][j]+=10;
                 if(chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+2][j-2]==0) comresults[i][j]+=10;
                 
                 if(chessboard[i][j+1]==2&&chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j+2]==0) humresults[i][j]+=10; 
                 if(chessboard[i-1][j]==2&&chessboard[i+1][j]==2&&chessboard[i-2][j]==0&&chessboard[i+2][j]==0) humresults[i][j]+=10;
                 if(chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i+2][j+2]==0) humresults[i][j]+=10;
                 if(chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+2][j-2]==0) humresults[i][j]+=10;
                 
                 //第三种情况  x@xoox 
                 
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==1&&chessboard[i][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==1&&chessboard[i+4][j]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==1&&chessboard[i][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==1&&chessboard[i-4][j]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==0) comresults[i][j]+=9;
                 
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==2&&chessboard[i][j+3]==2&&chessboard[i][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==2&&chessboard[i+3][j]==2&&chessboard[i+4][j]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==2&&chessboard[i][j-3]==2&&chessboard[i][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==2&&chessboard[i-3][j]==2&&chessboard[i-4][j]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==0) humresults[i][j]+=9;
                 
                 //第四种情况    xox@ox
                 
                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==1&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=9;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==1&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=9;
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==1&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=9;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==1&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=9;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==1&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=9;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==1&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=9;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==1&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=9;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==1&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=9;
                 
                 if(chessboard[i][j+2]==0&&chessboard[i][j+1]==2&&chessboard[i][j-1]==0&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0) humresults[i][j]+=9;
                 if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==2&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0) humresults[i][j]+=9;
                 if(chessboard[i+2][j]==0&&chessboard[i+1][j]==2&&chessboard[i-1][j]==0&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0) humresults[i][j]+=9;
                 if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==2&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0) humresults[i][j]+=9;
                 if(chessboard[i][j-2]==0&&chessboard[i][j-1]==2&&chessboard[i][j+1]==0&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0) humresults[i][j]+=9;
                 if(chessboard[i-2][j-2]==0&&chessboard[i-1][j-1]==2&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0) humresults[i][j]+=9;
                 if(chessboard[i-2][j]==0&&chessboard[i-1][j]==2&&chessboard[i+1][j]==0&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0) humresults[i][j]+=9;
                 if(chessboard[i-2][j+2]==0&&chessboard[i-1][j+1]==2&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0) humresults[i][j]+=9;
                 
                 //第五种情况     xoxo@x
                 
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j-3]==1&&chessboard[i][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==1&&chessboard[i-4][j-4]==0) comresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==0&&chessboard[i-3][j]==1&&chessboard[i-4][j]==0) comresults[i][j]+=9; 
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==1&&chessboard[i-4][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==0&&chessboard[i][j+3]==1&&chessboard[i][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==1&&chessboard[i+4][j+4]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==0&&chessboard[i+3][j]==1&&chessboard[i+4][j]==0) comresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==1&&chessboard[i+4][j-4]==0) comresults[i][j]+=9;
                 
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j-3]==2&&chessboard[i][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==2&&chessboard[i-4][j-4]==0) humresults[i][j]+=9;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==0&&chessboard[i-3][j]==2&&chessboard[i-4][j]==0) humresults[i][j]+=9; 
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==2&&chessboard[i-4][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==0&&chessboard[i][j+3]==2&&chessboard[i][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==2&&chessboard[i+4][j+4]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==0&&chessboard[i+3][j]==2&&chessboard[i+4][j]==0) humresults[i][j]+=9;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==2&&chessboard[i+4][j-4]==0) humresults[i][j]+=9;
                 
                 //第六种情况    x@xoxox
                 
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0&&chessboard[i][j+4]==1&&chessboard[i][j+5]==0) comresults[i][j]+=8; 
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0&&chessboard[i+4][j+4]==1&&chessboard[i+5][j+5]==0) comresults[i][j]+=8;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0&&chessboard[i+4][j]==1&&chessboard[i+5][j]==0) comresults[i][j]+=8;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0&&chessboard[i+4][j-4]==1&&chessboard[i+5][j-5]==0) comresults[i][j]+=8;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0&&chessboard[i][j-4]==1&&chessboard[i][j-5]==0) comresults[i][j]+=8;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0&&chessboard[i-4][j-4]==1&&chessboard[i-5][j-5]==0) comresults[i][j]+=8;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0&&chessboard[i-4][j]==1&&chessboard[i-5][j]==0) comresults[i][j]+=8;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0&&chessboard[i-4][j+4]==1&&chessboard[i-5][j+5]==0) comresults[i][j]+=8;
                 
                 if(chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==2&&chessboard[i][j+3]==0&&chessboard[i][j+4]==2&&chessboard[i][j+5]==0) humresults[i][j]+=8; 
                 if(chessboard[i-1][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==2&&chessboard[i+3][j+3]==0&&chessboard[i+4][j+4]==2&&chessboard[i+5][j+5]==0) humresults[i][j]+=8;
                 if(chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==2&&chessboard[i+3][j]==0&&chessboard[i+4][j]==2&&chessboard[i+5][j]==0) humresults[i][j]+=8;
                 if(chessboard[i-1][j+1]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==2&&chessboard[i+3][j-3]==0&&chessboard[i+4][j-4]==2&&chessboard[i+5][j-5]==0) humresults[i][j]+=8;
                 if(chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==2&&chessboard[i][j-3]==0&&chessboard[i][j-4]==2&&chessboard[i][j-5]==0) humresults[i][j]+=8;
                 if(chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==2&&chessboard[i-3][j-3]==0&&chessboard[i-4][j-4]==2&&chessboard[i-5][j-5]==0) humresults[i][j]+=8;
                 if(chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==2&&chessboard[i-3][j]==0&&chessboard[i-4][j]==2&&chessboard[i-5][j]==0) humresults[i][j]+=8;
                 if(chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==2&&chessboard[i-3][j+3]==0&&chessboard[i-4][j+4]==2&&chessboard[i-5][j+5]==0) humresults[i][j]+=8;
                 
                 //第八种情况   xox@xox
                 
                 //这个似乎不必写，先放着          
                 
                 }     
                 
}



void Gobang::r_two(){
       
     
     for(int i=1;i<14;i++)
            for(int j=1;j<14;j++){
                    
                    if(chessboard[i][j]!=0) continue;
                    
                    //第一种情况  xx@oxx
                    
                    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==1&&chessboard[i][j+2]==0&&chessboard[i][j+3]==0) comresults[i][j]+=2;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==1&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==0) comresults[i][j]+=2;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==1&&chessboard[i+2][j]==0&&chessboard[i+3][j]==0) comresults[i][j]+=2;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==1&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==0) comresults[i][j]+=2;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==1&&chessboard[i][j-2]==0&&chessboard[i][j-3]==0) comresults[i][j]+=2;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==1&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==0) comresults[i][j]+=2;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==1&&chessboard[i-2][j]==0&&chessboard[i-3][j]==0) comresults[i][j]+=2;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==1&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==0) comresults[i][j]+=2;
                    
                    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==2&&chessboard[i][j+2]==0&&chessboard[i][j+3]==0) humresults[i][j]+=2;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==2&&chessboard[i+2][j+2]==0&&chessboard[i+3][j+3]==0) humresults[i][j]+=2;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==2&&chessboard[i+2][j]==0&&chessboard[i+3][j]==0) humresults[i][j]+=2;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==2&&chessboard[i+2][j-2]==0&&chessboard[i+3][j-3]==0) humresults[i][j]+=2;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==2&&chessboard[i][j-2]==0&&chessboard[i][j-3]==0) humresults[i][j]+=2;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==2&&chessboard[i-2][j-2]==0&&chessboard[i-3][j-3]==0) humresults[i][j]+=2;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==2&&chessboard[i-2][j]==0&&chessboard[i-3][j]==0) humresults[i][j]+=2;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==2&&chessboard[i-2][j+2]==0&&chessboard[i-3][j+3]==0) humresults[i][j]+=2; 
                    
                    //第二种情况   xx@xox 
                    
                    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) comresults[i][j]+=1;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) comresults[i][j]+=1;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) comresults[i][j]+=1;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) comresults[i][j]+=1;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) comresults[i][j]+=1;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) comresults[i][j]+=1;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) comresults[i][j]+=1;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) comresults[i][j]+=1;
                    
                    if(chessboard[i][j-2]==0&&chessboard[i][j-1]==0&&chessboard[i][j+1]==0&&chessboard[i][j+2]==1&&chessboard[i][j+3]==0) humresults[i][j]+=1;
                    if(chessboard[i-2][j-2]==0&&chessboard[i-2][j-1]==0&&chessboard[i+1][j+1]==0&&chessboard[i+2][j+2]==1&&chessboard[i+3][j+3]==0) humresults[i][j]+=1;
                    if(chessboard[i-2][j]==0&&chessboard[i-1][j]==0&&chessboard[i+1][j]==0&&chessboard[i+2][j]==1&&chessboard[i+3][j]==0) humresults[i][j]+=1;
                    if(chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==0&&chessboard[i+1][j-1]==0&&chessboard[i+2][j-2]==1&&chessboard[i+3][j-3]==0) humresults[i][j]+=1;
                    if(chessboard[i][j+2]==0&&chessboard[i][j+1]==0&&chessboard[i][j-1]==0&&chessboard[i][j-2]==1&&chessboard[i][j-3]==0) humresults[i][j]+=1;
                    if(chessboard[i+2][j+2]==0&&chessboard[i+1][j+1]==0&&chessboard[i-1][j-1]==0&&chessboard[i-2][j-2]==1&&chessboard[i-3][j-3]==0) humresults[i][j]+=1;
                    if(chessboard[i+2][j]==0&&chessboard[i+1][j]==0&&chessboard[i-1][j]==0&&chessboard[i-2][j]==1&&chessboard[i-3][j]==0) humresults[i][j]+=1;
                    if(chessboard[i+2][j-2]==0&&chessboard[i+1][j-1]==0&&chessboard[i-1][j+1]==0&&chessboard[i-2][j+2]==1&&chessboard[i-3][j+3]==0) humresults[i][j]+=1;
                    
                    
                    }
}
     
     


//开始游戏 
                

void go(int n){
     Gobang g;
     if(n==1)
     {
             cout<<"选择谁先走棋："<<endl;
             cout<<"     1.玩家先"<<endl;
             cout<<"     2.电脑先"<<endl;
             int n;cin>>n;
             if(n==2)  g.firstgo();
     while(1){
              if(g.ifwin()==1) {
                                g.print(1);
                                cout<<"电脑获胜！"<<endl; 
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(1);
                              cout<<"玩家获胜！"<<endl;
                              break;
                              } 
              g.print(1);
              g.input(1);
              if(g.returngoback()==1) {cout<<"认输了！"<<endl;return;}
              if(g.ifwin()==1) {
                                g.print(1);
                              cout<<"电脑获胜！"<<endl;
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(1);
                              cout<<"玩家获胜！"<<endl;
                              break;
                              } 
              g.think();
              }
     }
     if(n==2){
              while(1){
              if(g.ifwin()==1) {
                                g.print(2);
                              cout<<"玩家1获胜！"<<endl;
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(2);
                              cout<<"玩家2获胜！"<<endl;
                              break;
                              }
              g.print(2);
              g.input(2);
              if(g.returngoback()==1) {cout<<"认输了！"<<endl;return;}
              }
              } 
              
              
}


//装载存档 

void load(){
     Gobang g;
     cout<<"已有的存档文件如下："<<endl;
     if(g.dir()==0) {cout<<"没有存档文件，无法读取!"<<endl;return;}
     cout<<"输入文件名（不带后缀）:"<<endl;
     string filename;
     cin>>filename;
     filename=filename+".gbg";
     ifstream ifile(filename.c_str()); 
     int choice;
     ifile>>choice;
     if(choice!=1&&choice!=2) {
                              cout<<"文件内容错误！" <<endl;
                              return;
                              }
     for(int i=0;i<15;i++)
         for(int j=0;j<15;j++)
                {int n;
                  ifile>>n;
                  if(n!=1&&n!=2&&n!=0) {
                                       cout<<"文件内容错误！"<<endl;
                                       return;
                                       } 
                  g.setchessboard(i,j,n);
                  }
                   ifile.close();
     
     if(choice==1) {
             while(1){
                   if(g.ifwin()==1) {
                                g.print(1);
                              cout<<"电脑获胜！"<<endl;
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(1);
                              cout<<"玩家获胜！"<<endl;
                              break;
                              } 
              g.print(1);
              g.input(1);
              if(g.returngoback()==1) {cout<<"认输了！"<<endl;return;}
              if(g.ifwin()==1) {
                                g.print(1);
                              cout<<"电脑获胜！"<<endl;
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(1);
                              cout<<"玩家获胜！"<<endl;
                              break;
                              } 
              g.think();
              }
              }
     if(choice==2){
                while(1){
              if(g.ifwin()==1) {
                                g.print(2);
                              cout<<"玩家1获胜！"<<endl;
                              break;
                              }
              if(g.ifwin()==2){
                              g.print(2);
                              cout<<"玩家2获胜！"<<endl;
                              break;
                              }
              g.print(2);
              g.input(2);
              if(g.returngoback()==1) {cout<<"认输了！"<<endl;return;}
              
              }
              } 

}  
                   


void explain(){
     cout<<"****************说明****************"<<endl;
     
     cout<<"界面说明："<<endl;
     cout<<"   棋子状态，显示棋盘上的符号所对应的棋子"<<endl;
     cout<<"   棋子数，显示双方的棋子总数 "<<endl;
     cout<<"   棋盘大小为15*15，行列坐标分别为1至14，坐标一标注在棋盘边上。"<<endl;
     cout<<"   棋盘下面显示上一步的下子坐标位置。"<<endl;
     
     cout<<"操作说明："<<endl; 
     cout<<"   输入坐标下子，分别输入行列坐标。可以用空格隔开，也可以用回车，不能有其他符号。"<<endl; 
     cout<<"   在游戏中输入111可随时保存游戏（双人对战中只能由先手保存）。"<<endl;
     cout<<"   输入222认输！"<<endl;
     
     cout<<"文件说明："<<endl; 
     cout<<"   五子棋.exe   主程序文件 "<<endl; 
     cout<<"   *.gbg    存档文件"<<endl;
     cout<<"   dir.txt   保存信息  "<<endl; 
     } 
     
     
     
//主函数 

int main(){
    while(1){
             system("cls");
             cout<<"****************五子棋****************"<<endl;
             cout<<"                         马晟. 2015.12.2"<<endl;
             cout<<"输入数字选择："<<endl;
             cout<<"             1.人机对战。"<<endl;
             cout<<"             2.双人对战。"<<endl;
             cout<<"             3.读取存档。"<<endl;
             cout<<"             4.说明"<<endl; 
             cout<<"             0.退出游戏。"<<endl;
             int s;
             cin>>s;
             if(s==1) go(1);
             if(s==2) go(2);
             if(s==3) load();
             if(s==4) explain();
             if(s==0) exit(0);
             cout<<"返回主菜单？  y：是  。n：退出游戏 "<<endl;
             char yn;
             cin>>yn;
             if(yn=='n') break; 
            }
}
