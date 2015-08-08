#include <iostream>
#include <time.h>
#include <stdlib.h>
typedef int key ;

using namespace std;

enum color
{
	Black = 1,
	Red = 0
};

typedef struct RBT
{	struct RBT *Pparent;
	struct RBT *Plchild,*Prchild;
	color notecolor;
	key value;
} RBT, *PRBT;

void Left_Rotate(PRBT a,PRBT &root)
{	PRBT b;
	b=a->Prchild;
	if(b==NULL)
		return;
	a->Prchild=b->Plchild;
	if(b->Plchild!=NULL)
		b->Plchild->Pparent=a;
	b->Pparent=a->Pparent;
	if(a==root)
		root =b;
	else if(a==a->Pparent->Plchild)
	{
        a->Pparent->Plchild = b;
    }
    else
    {
        a->Pparent->Prchild = b;
    }
	b->Plchild=a;
	a->Pparent=b;
}

void Right_Rotate(PRBT a,PRBT &root)//
{	PRBT b;
	b=a->Plchild;
	if(b==NULL)
		return;
	a->Plchild=b->Prchild;
	if(b->Prchild!=NULL)
		b->Prchild->Pparent=a;
	b->Pparent=a->Pparent;
	if(a==root)
	{
		root=b;	
	}
	else if(a==a->Pparent->Plchild)
	{
        a->Pparent->Plchild= b;
    }
    else
    {
        a->Pparent->Prchild = b;
    }
	b->Prchild=a;
	a->Pparent=b;
}

void Read_RBT(PRBT point)
{	cout<<"value:"<<point->value;
	if(point->notecolor==Red)
	{
		cout<<"  color:Red  ";
	}
	else cout<<"  color:Black";	
	if(point->Plchild!=NULL)
	{
		cout<<"  left_child:"<<point->Plchild->value;
		cout<<"  ";
	}
	if(point->Prchild!=NULL)
	{
		cout<<"  right_child:"<<point->Prchild->value;
		cout<<"  ";
	}
	cout<<endl;

}




void show_RBT(PRBT root)
{	
	if(root!=NULL)
	{	
		if(root->Plchild!=NULL)
		{
			show_RBT(root->Plchild);
		}
		Read_RBT(root);
		if(root->Prchild!=NULL)
		{
			show_RBT(root->Prchild);
		}
	}
	
}

PRBT Fix_RBT(PRBT root,PRBT newnote)
{
	PRBT point;//设置一个指针point,指向当前插入元素的叔父节点(以插入节点的父亲为其爷爷节点的左指针为例子)
	while(NULL!=newnote->Pparent&&newnote->Pparent->notecolor==Red)//当指针new，指向该插入的
		//节点，这个节点不为根节点且颜色为红
		//则进入循环
	{	
		if(newnote->Pparent->Pparent->Plchild==newnote->Pparent)//当其父亲节点为其爷爷节点的左孩子时候
		{
			point=newnote->Pparent->Pparent->Prchild;//指向其叔父节点
			if(point!=NULL&&point->notecolor==Red)//如果叔父节点不为空或者颜色为红
			{
				point->notecolor=Black;//则把其父亲和叔父的颜色都换成黑色。爷爷节点换成红色
				newnote->Pparent->notecolor=Black;
				point->Pparent->notecolor=Red;
				newnote=point->Pparent;//把插入位置指向其爷爷

			}
			else
			{
				if(newnote->Pparent->Prchild==newnote)//如果插入位置为其父节点的右孩子
				{	
					newnote=newnote->Pparent;//把插入位置指向它的父亲，并对其左旋转
					Left_Rotate(newnote,root);
				}
				newnote->Pparent->notecolor=Black;//插入位置其父亲设置成黑色
				newnote->Pparent->Pparent->notecolor=Red;//把爷爷改成红色
				Right_Rotate(newnote->Pparent->Pparent,root);	//对其爷爷节点右旋
			}
		}
		else
		{
			 point=newnote->Pparent->Pparent->Plchild;
			if(point!=NULL&&point->notecolor==Red)
			{
				point->notecolor=Black;
				newnote->Pparent->notecolor=Black;
				newnote->Pparent->Pparent->notecolor=Red;
				newnote=newnote->Pparent->Pparent;

			}
			else
			{
				if(newnote->Pparent->Plchild==newnote)
				{	
					newnote=newnote->Pparent;
					Right_Rotate(newnote,root);
				}
				newnote->Pparent->notecolor=Black;
				newnote->Pparent->Pparent->notecolor=Red;
				Left_Rotate(newnote->Pparent->Pparent,root);	
			}
		}
	}
	root->notecolor=Black;//把其根节点设成黑色
	return root;
}




PRBT F_I_key( PRBT root,key x)
{
	PRBT point,newnote,point1;//按照输入的值形成插入点，并把
	newnote=new RBT;
	newnote->value=x;

	point=root;//从树根开始，按照元素的大小，寻找需要插入的位置
	point1=NULL;
	while (NULL != point)
    {
        point1 = point;
        if (newnote->value < point->value)
        {
            if (NULL != point->Plchild)
            {
                point = point->Plchild;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (NULL != point->Prchild)
            {
                point = point->Prchild;
            }
            else
            {
                break;
            }
        }
    }


	newnote->Pparent=point1;//插入这个节点元素

	if(point1==NULL)//判断是否是树根
		root=newnote;
	else{
			if(newnote->value<point1->value)
				point1->Plchild=newnote;
			else point1->Prchild=newnote;
	}
	newnote->notecolor=Red;
	newnote->Plchild=NULL;
	newnote->Prchild=NULL;

	return Fix_RBT(root,newnote);//调整数
}

void main()
{
	int i;
	int array[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    PRBT root = NULL;    
    for (i = 0; i < 9; i++)
    {
		root = F_I_key(root, array[i]);
    }
	PRBT root1 = root;
	cout << "root:" << root->value << endl;
	show_RBT(root1);
}
	