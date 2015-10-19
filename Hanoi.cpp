/* ****************************************
 * 汉诺塔问题
 * 思路：假设有3个柱子A、B、C，需要将A的n块板移到C上，按顺序排。解法是采用分治方法，先将A的前n-1块移到过渡塔，再将最后一块移动到目的地上。
 * 接着同理将B的前n-2块移到过渡塔A中，再将最后一块移到目的地C上。接着继续这样......
 * 总次数是 2^n - 1
 * ****************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void move_to(int size, char from, char to)
{
}

int Hanoi(int size, char A, char B, char C)
{
	int sum = 0;
	if (size == 1)
		return 1;
	sum += Hanoi(size-1, A, C, B);
	move_to(size, A, C);
	sum += 1;
	sum += Hanoi(size-1, B, A, C);
	return sum;
}

int main ()
{
	char A = 'A', B = 'B', C = 'C';
	int size;
	cout << "The Hanoi size is : ";
	cin >> size;
	cout << "The move count number is : " << Hanoi(size, A, B, C) << endl;
	return 0;
}
