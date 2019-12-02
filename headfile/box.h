/*
* made by 王宇轩
* 此头文件声明了箱子类和一些函数 
*/ 

using namespace std;

struct Box{
	int x,y;
};

class BOX{
	int bx,by;
	public:
		void set_where(int x,int y);
		int get_whereX();
		int get_whereY();
//		bool if_knock_wall(int x,int y);
};

void print_block(int x,int y,int kind);
void print_win();
void print_player();

#include "box.cpp"
#include "print.cpp"

