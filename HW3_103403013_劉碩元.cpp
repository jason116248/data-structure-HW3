#include <iostream>
#include <vector>
#include <fstream>
#include<algorithm>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
/*using dynamic array in struct method*/
typedef struct myset
{
    vector<int> var;
    int elementNum;
    myset()
    {

    }
    bool sameTeam(int num)
    {
        bool flag = (find(var.begin(), var.end(), num) != var.end());
        return flag;
    }
};
int space = 0;
typedef struct method *mpointer;
mpointer ptr1;
typedef struct method
{
    int value;
    int team[1000];  //用來記錄在queue中的元素是屬於哪一個team的

    void ENQUEUE(int number, int Tim,mpointer mptr)
    {
        ptr1 = NULL;
        team[space] = Tim;
        if(space==0) //完全沒有數字在queue
        {
            space++;
            ptr1 = (mpointer) malloc(space * sizeof(method)); //利用指標指著配置的記憶體

        }
        else
        {
	    //跟前面的元素裡的team都不同，所以直接插在最後面。利用mptr還指著queue時，把ptr1重新分配記憶體大小
            space++;
            ptr1 =  (mpointer) realloc( mptr, sizeof(method)* space  ); 
        }

        (ptr1+space-1)->value = number; //把要新增的數字給新配置的記憶體位置

    }

    void ENQUEUE(int number,int Tim,int isPlace, mpointer mptr)
    {
        int k=0,temp;
        ptr1 = NULL;
        space++;
        ptr1 = (mpointer) malloc(space * sizeof(method)); //把ptr1指向一個完全沒有值的記憶體，以便之後可以填新的值
        for(int i=0; i<space; i++)
        {
            if(i == isPlace) //當i等於要插入新的值的位子時
            {
                (ptr1+i)->value = number;
                temp = team[i]; //原本在這個位子的數字的team是多少被temp記錄下來
                team[i] = Tim; //被新增的數字的team取代
            }

            else
            {
                (ptr1+i)->value = (mptr+k)->value; //讓指著原queue的指標mptr把裡面的值搬到新的記憶體中
                if(k == isPlace)
                    team[i] = temp; //讓原本被temp紀錄的原team給到新的位置
                else
                    team[i] = team[k];
                k++;
            }
        }
    }

    int DEQUEUE()
    {
        int result;

        if(space == 0)
        {
            return -1; //empty
        }
        else if(space==1)
        {
            space--;
            return ptr1->value;
            ptr1 = NULL;
        }
        else
        {
            result = (ptr1+0)->value;
            // consider team[]
            for(int k=0; k<space-1; k++)
                team[k] = team[k+1];

            mpointer dptr =(ptr1+1); //不要第一個值，所以從指在第二個位置
            ptr1 = NULL;
            space--;
            ptr1 = (mpointer) malloc( sizeof(method)* space ); //重新分配新的比原來記憶體空間少一單位的記憶體空間

            for(int i=0; i < space; i++)
            {
                (ptr1+i)->value = (dptr+i)->value; //把原本的值移到新的記憶體空間
            }

        }
        return result;

    }
};

int enqueue_count = 0;
int main()
{
    int flag_while = 1,k=0;
    char file_name[20]= {};

    cout << "Please enter file's name(remember to enter file's format): ";
    cin >> file_name;

    ifstream ifs(file_name,ios::in);
    while(flag_while)
    {
        method M1;
        vector<myset> mylist; //創立myset形態的vector，

        int teamNum,num;

        ifs >> teamNum; //得到總共會有幾個team
        if(teamNum==0)
			break;

        for(int i=0; i<teamNum; i++)
        {
            mylist.push_back(myset()); //代表mylist這個容器內，已經創立了"teamNum"個 myset型態的變數
        }

        for(int k=0; k < teamNum; k++)
        {
            ifs >> mylist.at(k).elementNum; //elementNum 是紀錄一個team內總共有多少個的數字 的變數
            for(int j=0; j < mylist.at(k).elementNum; j++)
            {
                ifs >> num;
                mylist.at(k).var.push_back(num); // 利用mylist內存的 myset形態中的變數(struct)中的內建vector存取這個team內的所有元素
            }
        }
        //enqueue or dequeue
        string next;
        string str_enqueue = "ENQUEUE";
        string str_dequeue = "DEQUEUE";
        string str_stop = "STOP";
        string jump_loop = "0";
        bool flag_enqueue;
        int scenario = 0;
        cout<<"Scenario #"<<++k<<endl;
        while(ifs >> next)
        {
            if(next.compare(jump_loop)==0)
            {
                flag_while = 0;
                break;
            }
            else if(next.compare(str_stop)==0)
            {
                //all the variables that need for the next round should go back to the initial condition
                enqueue_count = 0;
                space = 0;
                free(ptr1);
                break;

            }
            else if(next.compare(str_enqueue)==0)
            {
                int enqueueNum,s, team, insert_place=-1;
                ifs >> enqueueNum;
                for( s=0; s<teamNum; s++)
                {   //去比較接下來要輸入的數字是哪個team,要去mylist中的各個myset形態的變數找
                    flag_enqueue = mylist.at(s).sameTeam(enqueueNum); 
                    if(flag_enqueue)
                        break; // means that the element belongs to this team
                }
                team = s;

                if(enqueue_count != 2) //若queue中沒有任何數字或只有一個數字
                {
                    M1.ENQUEUE(enqueueNum,team,ptr1);
                    enqueue_count++;
                }
                else
                {

                    //if there is at least one element in the queue is in the same team with insertion
                    for(int i=space-1; i>=0; i--)
                    {
                        if(team == M1.team[i]) //如果在queue中找到同一個team的元素，就把此數插入在那個同team的數字後面
                        {
                            insert_place = i+1;
                            break;
                        }
                    }

                    if(insert_place==-1)
                        M1.ENQUEUE(enqueueNum,team,ptr1);// if the insertion is not the same team with all elements in the queue
                    else
                        M1.ENQUEUE(enqueueNum,team,insert_place,ptr1);

                }

            }
            else if(next.compare(str_dequeue)==0)
            {
                int dequeue_num;
                dequeue_num = M1.DEQUEUE();
                cout << dequeue_num << endl;
            }
        }

    }
    return 0;
}
