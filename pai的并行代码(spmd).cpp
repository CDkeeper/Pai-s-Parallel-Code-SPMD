#include<stdio.h>
#include<time.h>
#include<mpi.h>  //导入mpi头文件 
using namespace std;
const int N = 1e8; //定义划分区间数 
double pai = 0; //存储运算pai的结果 
int main(int argc, char* argv[]) {
    clock_t startTime, endTime; //定义时间变量用于记录进程耗费时间 
    int idnub, amount, root;  // idnub对于当前进程的标号，amount指代进程数量，root指代根进程 
    double tmpcal = 0, pai = 0; //tmpcal存储每一个进程计算的结果，并通过后续操作汇总到pai 
    startTime = clock(); //程序开始 
    MPI_Init(&argc, &argv);  //注意从此刻开始已经进入并行模式，以下所有执行操作都是对每一个进程而言的 
    MPI_Comm_rank(MPI_COMM_WORLD, &idnub); //获取进程标号 
    MPI_Comm_size(MPI_COMM_WORLD, &amount); //获取进程数 
    root = 0; //告诉每一个进程根进程是零
    for (int i = idnub; i < N; i += amount) {  //如果i从0开始那么就到N-1结束否则结果不准确 
        double tmp = (i + 0.5) / N; //用来表示公式中的( i + 0.5 ) / N
        tmpcal += 4 / (1 + tmp * tmp); //加上每一区间运算结果 
    }
    MPI_Reduce(&tmpcal, &pai, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD); //参数分别为当前计算结果，汇总结果，数组维度，数据类型，操作名称，计算进程，通信器 
    pai /= N; //除以N,由于pai定义为double类型，所以无需对分母转换为double类型，自动向高精度对齐
    endTime = clock(); //记录程序结束时间 
    if (idnub == root) { //当此结点为根进程时，因为数据其实存储在根进程的缓冲区下 
        printf("Name:Chen Da\tStudent id:1004192118\n\n\n");
        printf("Calculation time:%ld ms\n pai is approximately:%.12f", endTime - startTime, pai);    //打印耗时和结果 	
    }
    MPI_Finalize(); //结束MPI的并行过程  
    return 0;
}
