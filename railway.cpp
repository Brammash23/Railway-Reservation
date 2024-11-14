
#include <iostream>
using namespace std;
class passenger
{
    private:
    int id;
    string name;
    int price=5000;
    int seats=20;
    
    
    public:

    void setdata()
    {
        cout<<"Enter your Name:";
        cin>>name;
        cout<<"Enter Your Flight ID:";
        cin>>id;
    }
    string print()
    {
        return name;
    }
    
    int idle()
    {
        return id;
    }
    
     int showprice(int count)
    {
        if(count>0)
        {
          return price+(count*200);    
        }
        
        else
        {
            return price*1;
        }
      
    }
    
    int balanceseat(int count)
    {
        
       return seats-count; 
    }
    
     int reducedprice(int count)
    {
        if(count>0)
        {
          return price-(count*200);    
        }
        
        else
        {
            return price*1;
        }
      
    }
    
    int reducedseat(int can)
    {
        
       return seats-can; 
    }
    
     void printpass()
    {
        cout<<"Name:"<<name<<"--"<<"ID:"<<id<<endl;
    }
    
    void deletedata(string h,int ij)
    {
      name=h;
      id=ij;
    }
  
    
};



int main()
{
    int count=0,q=0,ij,can=0;
    string g,h;
    int n;
    int opt;
    passenger nw[20],details;
    while(opt!=4)
    {
     cout<<"1.BOOK 2.Cancel 3.Print 4.Exit"<<endl;
     cout<<"Enter Your Choice:"<<endl;
     cin>>opt;
     
     switch(opt)
     {
         case 1:
         cout<<"Price is:"<<details.showprice(count)<<endl;
         cout<<"Remaining is:"<<details.balanceseat(count)<<endl;
         cout<<"How many Seats gonna book?"<<endl;
         cin>>n;
         for(int i=q;i<n+q;i++)
         {
            nw[i].setdata();
            count++;
            cout<<"Price is:"<<details.showprice(count)<<endl;
            cout<<"Remaining is:"<<details.balanceseat(count)<<endl;
         }
         q=count;
         
         break;
         
         case 2:
         cout<<"Enter your Name to Cancel:";
         cin>>g;
         for(int i=0;i<count;i++)
         {
             if(nw[i].print()==g)
             {
                 h=nw[i+1].print();
                 ij=nw[i+1].idle();
                 nw[i].deletedata(h,ij);
                 count--;
                 can++;
             }
         }
         cout<<"Price is:"<<details.reducedprice(count)<<endl;
         cout<<"Remaining is:"<<details.reducedseat(can)<<endl;
         break;
         
         case 3:
         for(int i=0;i<count;i++)
         {
             nw[i].printpass();
         }
          cout<<"Price is:"<<details.showprice(count)<<endl;
          cout<<"Remaining is:"<<details.balanceseat(count)<<endl;
          break;
         
        
        
     }
        
    }
 
    

    
    return 0;
}
