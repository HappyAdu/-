/*******************************************************************************
*
*                 	 粒子群优化算法
*--------------------------------------------------------------------------------
* 算法题目		 : 例题5.1
* 算法说明       :w是惯量权重，一般取0-1之间数字，这儿取0.5
*                  c1,c2为加速系数，通常取固定值2.0
*                  r1,r2为[0-1]随机数
* 注意	         :对于越界的位置需要进行合法性的调整

                求最小值则只需要对函数f进行改动以及204行的update sum计算进行改动。
                如果求最大值，则不仅仅改动上述过程，还包括64行的判断以及204行的判断

                改动x域值则只需要手动输入，改变群体只需要define N 群体数
*******************************************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define N 3


/********************************************************************
*函数名：init_helper()
*函数功能：初始化辅助函数
*函数输入：unsigned top ,unsigned bottom  上边界，下边界
*输出:无
**********************************************************************************/

void init_helper(int top,int bottom,float arr[N][6]) //位置 速度 个人历史最好位置6个数（x，y）形式
{

    int i,j;

    srand((unsigned)time(NULL));

    for(i = 0;i<N;i++)
    {
        for(j=0;j<4;j++)
        {
            arr[i][j]=rand()%(top-bottom+1)+bottom;//产生[bottom,top]之间的随机数
        }
        arr[i][4]=arr[i][0];
        arr[i][5]=arr[i][1];

    }

}

/************************************************************************
*函数名：f(）
*函数功能：计算每个解
*函数输入：particle[][]
*函数输出：无
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
     printf("最小坐标为:  ");
    for(i=0;i<2;i++)
    {
        history_best[i]=gbest[i];
        gbest[i] = particle[j][i];
        printf("%5.2f  ",gbest[i]);
    }
    printf("\n");
    printf("全局最优函数值和当前最小值位置分别为 ");
    printf("%5.2f   ",M_in[0][0]);
    printf("%5.2f\n",M_in[0][1]+1);
    printf("全局最优坐标为");
    for(i=0;i<2;i++)
      {
          printf("  %5.2f  ",gbest[i]);
      }
    printf("\n");
    printf("历史最优坐标：");
    for(i=0;i<2;i++)
      {
          printf("  %5.2f  ",history_best[i]);
      }
     printf("\n");

}

/*******************************************************************************
*函数名称：init（）
*函数功能：初始化
*输入：
*输出：
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
*函数名称：update（int top,int bottom,float particle[N][6],float gbest[2],float history_best[2]）
*函数功能:更新速度和位置
*输入：int top,int bottom,float particle[N][6],float gbest[2]
*输出：无
********************************************************************************/
void update(int top,int bottom,float particle[N][6],float gbest[2],float w,float c,float r1,float r2,float history_best[2])
{
   int i,j=2,k;

   for(i=0;i<N;i++)
   {
        srand((unsigned)time(NULL));
        r1=rand()/(double)(32768);
        r2=rand()/(double)(32768);

        //更新速度
        particle[i][j]=w*particle[i][j]+c*r1*(particle[i][j+2]-particle[i][0])+c*r2*(gbest[0]-particle[i][0]);
        particle[i][j+1]=w*particle[i][j+1]+c*r1*(particle[i][j+3]-particle[i][1])+c*r2*(gbest[1]-particle[i][1]);

        // 对越界数进行处理，大于大边界取top，小于下边界取bottom
        for(k=0;k<2;k++)
        {
            if(particle[i][j+k]>10)
                particle[i][j+k]=10;
            else if(particle[i][j+k]<-10)
            particle[i][j+k]=-10;
        }


        // 更新位置
        particle[i][0]+=particle[i][j];
        particle[i][1]+=particle[i][j+1];

         // 对越界数进行处理，大于大边界取top，小于下边界取bottom
        for(k=0;k<2;k++)
        {
            if(particle[i][k]>10)
                particle[i][k]=10;
            else if(particle[i][k]<-10)
            particle[i][k]=-10;
        }

   }
    printf("更新后位置速度为，此时个人历史最优尚未更新\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<6;j++)
        {
            printf("%5.2f   ",particle[i][j]);
        }
        printf("\n");
    }
   update_helpaer(particle,gbest,history_best);
   printf("更新后位置速度为，此时个人历史最优已经更新\n");
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
*函数名称：update_helper（float particle[N][6],float gbest[2],float history_best[2]）
*函数功能:更新个人历史最优以及全局最优位置
*输入：float particle[N][6],float gbest[2] float history_best[2]
*输出：无
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


// 主函数main（）

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



    printf("解为：");
    for(i=0;i<2;i++)
    {
        printf("%5.2f  ",gbest[i]);
    }


}
