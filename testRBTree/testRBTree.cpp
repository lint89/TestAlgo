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
	PRBT point;//����һ��ָ��point,ָ��ǰ����Ԫ�ص��常�ڵ�(�Բ���ڵ�ĸ���Ϊ��үү�ڵ����ָ��Ϊ����)
	while(NULL!=newnote->Pparent&&newnote->Pparent->notecolor==Red)//��ָ��new��ָ��ò����
		//�ڵ㣬����ڵ㲻Ϊ���ڵ�����ɫΪ��
		//�����ѭ��
	{	
		if(newnote->Pparent->Pparent->Plchild==newnote->Pparent)//���丸�׽ڵ�Ϊ��үү�ڵ������ʱ��
		{
			point=newnote->Pparent->Pparent->Prchild;//ָ�����常�ڵ�
			if(point!=NULL&&point->notecolor==Red)//����常�ڵ㲻Ϊ�ջ�����ɫΪ��
			{
				point->notecolor=Black;//����丸�׺��常����ɫ�����ɺ�ɫ��үү�ڵ㻻�ɺ�ɫ
				newnote->Pparent->notecolor=Black;
				point->Pparent->notecolor=Red;
				newnote=point->Pparent;//�Ѳ���λ��ָ����үү

			}
			else
			{
				if(newnote->Pparent->Prchild==newnote)//�������λ��Ϊ�丸�ڵ���Һ���
				{	
					newnote=newnote->Pparent;//�Ѳ���λ��ָ�����ĸ��ף�����������ת
					Left_Rotate(newnote,root);
				}
				newnote->Pparent->notecolor=Black;//����λ���丸�����óɺ�ɫ
				newnote->Pparent->Pparent->notecolor=Red;//��үү�ĳɺ�ɫ
				Right_Rotate(newnote->Pparent->Pparent,root);	//����үү�ڵ�����
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
	root->notecolor=Black;//������ڵ���ɺ�ɫ
	return root;
}




PRBT F_I_key( PRBT root,key x)
{
	PRBT point,newnote,point1;//���������ֵ�γɲ���㣬����
	newnote=new RBT;
	newnote->value=x;

	point=root;//��������ʼ������Ԫ�صĴ�С��Ѱ����Ҫ�����λ��
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


	newnote->Pparent=point1;//��������ڵ�Ԫ��

	if(point1==NULL)//�ж��Ƿ�������
		root=newnote;
	else{
			if(newnote->value<point1->value)
				point1->Plchild=newnote;
			else point1->Prchild=newnote;
	}
	newnote->notecolor=Red;
	newnote->Plchild=NULL;
	newnote->Prchild=NULL;

	return Fix_RBT(root,newnote);//������
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
	