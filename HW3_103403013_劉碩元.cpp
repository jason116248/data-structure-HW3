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
    int team[1000];

    void ENQUEUE(int number, int Tim,mpointer mptr)
    {
        ptr1 = NULL;
        team[space] = Tim;
        if(space==0)
        {
            space++;
            ptr1 = (mpointer) malloc(space * sizeof(method));

        }
        else
        {
            space++;
            ptr1 =  (mpointer) realloc( mptr, sizeof(method)* space  );
        }

        (ptr1+space-1)->value = number;

    }

    void ENQUEUE(int number,int Tim,int isPlace, mpointer mptr)
    {
        int k=0,temp;
        ptr1 = NULL;
        space++;
        ptr1 = (mpointer) malloc(space * sizeof(method));
        for(int i=0; i<space; i++)
        {
            if(i == isPlace)
            {
                (ptr1+i)->value = number;
                temp = team[i];
                team[i] = Tim;
            }

            else
            {
                (ptr1+i)->value = (mptr+k)->value;
                if(k == isPlace)
                    team[i] = temp;
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

            mpointer dptr =(ptr1+1);
            ptr1 = NULL;
            space--;
            ptr1 = (mpointer) malloc( sizeof(method)* space );

            for(int i=0; i < space; i++)
            {
                (ptr1+i)->value = (dptr+i)->value;
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
        vector<myset> mylist;

        int teamNum,num;

        ifs >> teamNum;
        if(teamNum==0)
			break;

        for(int i=0; i<teamNum; i++)
        {
            mylist.push_back(myset());
        }

        for(int k=0; k < teamNum; k++)
        {
            ifs >> mylist.at(k).elementNum;
            for(int j=0; j < mylist.at(k).elementNum; j++)
            {
                ifs >> num;
                mylist.at(k).var.push_back(num);
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
                {
                    flag_enqueue = mylist.at(s).sameTeam(enqueueNum);
                    if(flag_enqueue)
                        break; // means that the element belongs to this team
                }
                team = s;

                if(enqueue_count != 2)
                {
                    M1.ENQUEUE(enqueueNum,team,ptr1);
                    enqueue_count++;
                }
                else
                {

                    //if there is at least one element in the queue is in the same team with insertion
                    for(int i=space-1; i>=0; i--)
                    {
                        if(team == M1.team[i])
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
