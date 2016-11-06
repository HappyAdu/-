/*******************************************************************************
*
*                 	 ����Ⱥ�Ż��㷨
*--------------------------------------------------------------------------------
* �㷨��Ŀ		 : ����5.1
* �㷨˵��       :w�ǹ���Ȩ�أ�һ��ȡ0-1֮�����֣����ȡ0.5
*                  c1,c2Ϊ����ϵ����ͨ��ȡ�̶�ֵ2.0
*                  r1,r2Ϊ[0-1]�����
* ע��	         :����Խ���λ����Ҫ���кϷ��Եĵ���

                ����Сֵ��ֻ��Ҫ�Ժ���f���иĶ��Լ�204�е�update sum������иĶ���
                ��������ֵ���򲻽����Ķ��������̣�������64�е��ж��Լ�204�е��ж�

                �Ķ�x��ֵ��ֻ��Ҫ�ֶ����룬�ı�Ⱥ��ֻ��Ҫdefine N Ⱥ����
*******************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define N 3


/********************************************************************
*��������init_helper()
*�������ܣ���ʼ����������
*�������룺unsigned top ,unsigned bottom  �ϱ߽磬�±߽�
*���:��
**********************************************************************************/

void init_helper(int top,int bottom,float arr[N][6]) //λ�� �ٶ� ������ʷ���λ��6������x��y����ʽ
{

    int i,j;

    srand((unsigned)time(NULL));

    for(i = 0;i<N;i++)
    {
        for(j=0;j<4;j++)
        {
            arr[i][j]=rand()%(top-bottom+1)+bottom;//����[bottom,top]֮��������
        }
        arr[i][4]=arr[i][0];
        arr[i][5]=arr[i][1];

    }

}

/************************************************************************
*��������f(��
*�������ܣ�����ÿ����
*�������룺particle[][]
*�����������
***************************************************************************/

void f(float particle[N][6],float gbest[2],float history_best[2])
{
    float sum[N],M_in[1][2];
    int i ,j;
    M_in[0][0]=100;
    M_in[0][1]=0;
    for(i=0;i<N;i++)
    {
        sum[i]=particle[i][0]*particle[i][0] + particle[i][1]*particle[i][1];
        if(sum[i]<M_in[0][0])
        {
            M_in[0][0]=sum[i];
            M_in[0][1]=i;
        }
    }
    j=M_in[0][1];
     printf("��С����Ϊ:  ");
    for(i=0;i<2;i++)
    {
        history_best[i]=gbest[i];
        gbest[i] = particle[j][i];
        printf("%5.2f  ",gbest[i]);
    }
    printf("\n");
    printf("ȫ�����ź���ֵ�͵�ǰ��Сֵλ�÷ֱ�Ϊ ");
    printf("%5.2f   ",M_in[0][0]);
    printf("%5.2f\n",M_in[0][1]+1);
    printf("ȫ����������Ϊ");
    for(i=0;i<2;i++)
      {
          printf("  %5.2f  ",gbest[i]);
      }
    printf("\n");
    printf("��ʷ�������꣺");
    for(i=0;i<2;i++)
      {
          printf("  %5.2f  ",history_best[i]);
      }
     printf("\n");

}

/*******************************************************************************
*�������ƣ�init����
*�������ܣ���ʼ��
*���룺
*�����
********************************************************************************/
void init(int top,int bottom,float particle[N][6],float gbest[2],float history_best[2])
{
    int i,j;
    scanf("%d%d",&bottom,&top);
    for(i=0;i<N;i++)
    {
        init_helper(top,bottom,particle);
    }
    f(particle,gbest,history_best);

    for(i=0;i<N;i++)
    {
        for(j=0;j<6;j++)
        {
            printf("%5.2f   ",particle[i][j]);
        }
        printf("\n");
    }
}


/*******************************************************************************
*�������ƣ�update��int top,int bottom,float particle[N][6],float gbest[2],float history_best[2]��
*��������:�����ٶȺ�λ��
*���룺int top,int bottom,float particle[N][6],float gbest[2]
*�������
********************************************************************************/
void update(int top,int bottom,float particle[N][6],float gbest[2],float w,float c,float r1,float r2,float history_best[2])
{
   int i,j=2,k;

   for(i=0;i<N;i++)
   {
        srand((unsigned)time(NULL));
        r1=rand()/(double)(32768);
        r2=rand()/(double)(32768);

        //�����ٶ�
        particle[i][j]=w*particle[i][j]+c*r1*(particle[i][j+2]-particle[i][0])+c*r2*(gbest[0]-particle[i][0]);
        particle[i][j+1]=w*particle[i][j+1]+c*r1*(particle[i][j+3]-particle[i][1])+c*r2*(gbest[1]-particle[i][1]);

        // ��Խ�������д������ڴ�߽�ȡtop��С���±߽�ȡbottom
        for(k=0;k<2;k++)
        {
            if(particle[i][j+k]>10)
                particle[i][j+k]=10;
            else if(particle[i][j+k]<-10)
            particle[i][j+k]=-10;
        }


        // ����λ��
        particle[i][0]+=particle[i][j];
        particle[i][1]+=particle[i][j+1];

         // ��Խ�������д������ڴ�߽�ȡtop��С���±߽�ȡbottom
        for(k=0;k<2;k++)
        {
            if(particle[i][k]>10)
                particle[i][k]=10;
            else if(particle[i][k]<-10)
            particle[i][k]=-10;
        }

   }
    printf("���º�λ���ٶ�Ϊ����ʱ������ʷ������δ����\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<6;j++)
        {
            printf("%5.2f   ",particle[i][j]);
        }
        printf("\n");
    }
   update_helpaer(particle,gbest,history_best);
   printf("���º�λ���ٶ�Ϊ����ʱ������ʷ�����Ѿ�����\n");
   for(i=0;i<N;i++)
  {
    for(j=0;j<6;j++)
    {
        printf("%5.2f   ",particle[i][j]);
    }
        printf("\n");
  }

}

/*******************************************************************************
*�������ƣ�update_helper��float particle[N][6],float gbest[2],float history_best[2]��
*��������:���¸�����ʷ�����Լ�ȫ������λ��
*���룺float particle[N][6],float gbest[2] float history_best[2]
*�������
********************************************************************************/
void update_helpaer(float particle[N][6],float gbest[2],float history_best[2])
{
    float sum[2];
    int i,j;
    for(i=0;i<N;i++)
    {

        sum[0]=particle[i][0]*particle[i][0]+particle[i][1]*particle[i][1];
        sum[1]=particle[i][4]*particle[i][4]+particle[i][5]*particle[i][5];
        if(sum[0]<sum[1])
        {
            particle[i][4]=particle[i][0];
            particle[i][5]=particle[i][1];
        }
    }
    f(particle,gbest,history_best);
}


// ������main����

void main()
{
    int top,
        bottom,
        i=0,
        j;
    float w=0.5,
          c=2.0,
          r1=0.0,
          r2=0.0,
        particle[N][6],
        gbest[2]={-10,10},
        history_best[2],
        pbest[2];

    init(top,bottom,particle,gbest,history_best);
    while(gbest[0]!=history_best[0]&&gbest[1]!=history_best[1])
    {
     update(top,bottom,particle,gbest,w,c,r1,r2,history_best);
    }



    printf("��Ϊ��");
    for(i=0;i<2;i++)
    {
        printf("%5.2f  ",gbest[i]);
    }


}
