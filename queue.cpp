#include<iostream>
#include<cmath>
using namespace std;
class Queue{
	int que[10];
	int head;
	int tail;
public:
	Queue(int he=-1,int ta=-1):head(he),tail(ta){}
	void q_push(int num);
	int q_pop();
};
void Queue::q_push(int num)
{
	try
	{
		if(head-tail==1 || (head==0 && tail==9))
		{
			throw head-tail;
		}
		if(tail==-1 && head==-1){
			tail=0;
			head=0;
			que[head]=num;
		}
		else if(tail==9)
		{
			tail=0;
			que[tail]=num;
		}
		else
		{
			que[++tail]=num;
		}
	}
	catch(int)
	{
		cout<<"Error! The queue is full."<<endl;
	}
}
int Queue::q_pop()
{
	try
	{
		if(head==-1 && tail==-1){
			throw head;
		}
		if(head==tail)
		{
			int temp=que[head];
			head=-1;
			tail=-1;
			cout<<"POP:"<<temp<<endl;
			return temp;
		}
		else if(head==9)
		{
			head=0;
			cout<<"POP:"<<que[9]<<endl;
			return que[9];
		}
		else{
			cout<<"POP:"<<que[head]<<endl;
			return que[head++];
		}
	}
	catch(int)
	{
		cout<<"Error! The queue is empty."<<endl;
	}
}
int main(){
	Queue qqq;
	qqq.q_push(10);
	for(int i=0;i<10;i++)
	{
		qqq.q_push(i);
	}
	qqq.q_pop();
	qqq.q_pop();
	return 0;
}
