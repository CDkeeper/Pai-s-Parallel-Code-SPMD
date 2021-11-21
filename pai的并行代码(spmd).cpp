#include<stdio.h>
#include<time.h>
#include<mpi.h>  //����mpiͷ�ļ� 
using namespace std;
const int N = 1e8; //���廮�������� 
double pai = 0; //�洢����pai�Ľ�� 
int main(int argc, char* argv[]) {
    clock_t startTime, endTime; //����ʱ��������ڼ�¼���̺ķ�ʱ�� 
    int idnub, amount, root;  // idnub���ڵ�ǰ���̵ı�ţ�amountָ������������rootָ�������� 
    double tmpcal = 0, pai = 0; //tmpcal�洢ÿһ�����̼���Ľ������ͨ�������������ܵ�pai 
    startTime = clock(); //����ʼ 
    MPI_Init(&argc, &argv);  //ע��Ӵ˿̿�ʼ�Ѿ����벢��ģʽ����������ִ�в������Ƕ�ÿһ�����̶��Ե� 
    MPI_Comm_rank(MPI_COMM_WORLD, &idnub); //��ȡ���̱�� 
    MPI_Comm_size(MPI_COMM_WORLD, &amount); //��ȡ������ 
    root = 0; //����ÿһ�����̸���������
    for (int i = idnub; i < N; i += amount) {  //���i��0��ʼ��ô�͵�N-1������������׼ȷ 
        double tmp = (i + 0.5) / N; //������ʾ��ʽ�е�( i + 0.5 ) / N
        tmpcal += 4 / (1 + tmp * tmp); //����ÿһ���������� 
    }
    MPI_Reduce(&tmpcal, &pai, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD); //�����ֱ�Ϊ��ǰ�����������ܽ��������ά�ȣ��������ͣ��������ƣ�������̣�ͨ���� 
    pai /= N; //����N,����pai����Ϊdouble���ͣ���������Է�ĸת��Ϊdouble���ͣ��Զ���߾��ȶ���
    endTime = clock(); //��¼�������ʱ�� 
    if (idnub == root) { //���˽��Ϊ������ʱ����Ϊ������ʵ�洢�ڸ����̵Ļ������� 
        printf("Name:Chen Da\tStudent id:1004192118\n\n\n");
        printf("Calculation time:%ld ms\n pai is approximately:%.12f", endTime - startTime, pai);    //��ӡ��ʱ�ͽ�� 	
    }
    MPI_Finalize(); //����MPI�Ĳ��й���  
    return 0;
}
