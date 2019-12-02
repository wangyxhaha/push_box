/** 
* made by 王宇轩 
* 需要ege图形库 
* 需要编译指令
* "-lgraphics64 -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid -mwindows"
*/
#define chx 640 //窗口大小 
#define chy 480
#include <graphics.h>
#include <windows.h>
#include <fstream>
#include "./headfile/box.h"
using namespace std;

int mapx,mapy; //地图大小 
int box_num; //箱子个数 
int player_firstx,player_firsty; //玩家初始位置 
Box box_lastwhere[1000]; //箱子结束位置 
BOX box[1000]; //箱子类 
bool map1[1000][1000]; //储存地图 0代表地 1代表墙 

int main(){
	ifstream fin; //文件读入 
	fin.open("./map/in.map");
	if (fin.fail()){ //打开失败 
		MessageBox(NULL,"Can't open: in.map\n\nUnable to load","ERROR",MB_OK);
		return 0;
	}
	else{ //打开成功->继续读入 
		/*读入地图*/ 
		fin >> mapx >> mapy; //读入地图范围 
		if (fin.eof()){ //如果提前输入完毕 
			MessageBox(NULL,"Map content error","ERROR",MB_OK);
			fin.close();
			return 0;
		}
		if (mapx>1000 || mapx<=0 || mapy<=0 || mapy>1000){ //如果地图范围过大或过小 
			MessageBox(NULL,"Map is too large or too small\n\n(0 < x,y < 1000)","ERROR",MB_OK);
			fin.close();
			return 0;
		}
		for (int i=0;i<mapx;i++){ //读入地图 
			for (int j=0;j<mapy;j++){
				fin >> map1[i][j];
				if (fin.eof()){ //如果提前输入完毕 
					MessageBox(NULL,"Map content error","ERROR",MB_OK);
					fin.close();
					return 0;
				}
			}
		}
		/*读入箱子*/
		fin >> box_num; //读入箱子数量 
		if (fin.eof()){ //如果提前输入完毕 
			MessageBox(NULL,"Map content error","ERROR",MB_OK);
			fin.close();
			return 0;
		}
		if (box_num>1000 || box_num<=0){ //如果箱子数量太多或太少 
			MessageBox(NULL,"Boxes are too few or too many\n\n(0 < box_num < 1000)","ERROR",MB_OK);
			fin.close();
			return 0;
		}
		for (int i=0;i<box_num;i++){ //输入箱子初始位置 
			int tx,ty;
			fin >> tx >> ty;
			if (fin.eof()){ //如果提前输入完毕 
				MessageBox(NULL,"Map content error","ERROR",MB_OK);
				fin.close();
				return 0;
			}
			box[i].set_where(tx,ty); //初始化箱子类 
		}
		for (int i=0;i<box_num;i++){ //输入箱子结束位置 
			fin >> box_lastwhere[i].x >> box_lastwhere[i].y;
			if (fin.eof()){ //如果提前输入完毕 
				MessageBox(NULL,"Map content error","ERROR",MB_OK);
				fin.close();
				return 0;
			}
		}
		/*读入玩家信息*/
		fin >> player_firstx >> player_firsty; //读入玩家初始位置 
		if (fin.eof()){ //如果提前输入完毕 
			MessageBox(NULL,"Map content error","ERROR",MB_OK);
			fin.close();
			return 0;
		}
	}
	fin.close(); //读入完毕关闭文件 
	/*测试输出*/
	for (int i=0;i<mapx;i++){
		for (int j=0;j<mapy;j++){
			printf("%d ",map1[i][j]);
		}
		printf("\n");
	} 
	/**/ 
    initgraph(chx,chy); //初始化窗口 
    setbkcolor(EGERGB(0x1c,0x24,0x3c)); //设置背景颜色 
	char press_down; //判断键入 
    do{
		press_down=getch();
	}while (press_down!=' ');
	int player_nowx=player_firstx,player_nowy=player_firsty;
    while (is_run()){
    	/*绘制*/
    	cleardevice();
    	for (int i=0;i<mapx;i++){ //绘制墙和地 
    		for (int j=0;j<mapy;j++){
    			print_block((chx/2)+(player_nowx-i)*60,(chy/2)+(player_nowy-j)*60,map1[i][j]);
			}
		}
		for (int i=0;i<box_num;i++){ //绘制箱子 
			print_block((chx/2)+(player_nowx-box[i].get_whereX())*60,(chy/2)+(player_nowy-box[i].get_whereY())*60,2);
		}
		for (int i=0;i<box_num;i++){ //绘制箱子终点 
			print_block((chx/2)+(player_nowx-box_lastwhere[i].x)*60,(chy/2)+(player_nowy-box_lastwhere[i].y)*60,3);
		}
		print_player(); //绘制玩家 
		/*侦测按键*/
    	press_down=getch();
    	if (press_down=='o'){ //判断退出键 
    		break;
		}
		if (press_down=='a'){ //判断移动键 
			if (player_nowx+1<mapx && !map1[player_nowx+1][player_nowy]){ //判断是否是墙 
				bool tump=1,tump2=1;
				for (int i=0;i<box_num;i++){ //判断是否是箱子 
					if (box[i].get_whereX()==player_nowx+1 && box[i].get_whereY()==player_nowy){ //如果是，判断是否能移动 
						if (player_nowx+2<mapx && !map1[player_nowx+2][player_nowy]){
							for (int j=0;j<box_num;j++){ //判断再下一个是否是箱子 
								if (box[j].get_whereX()==player_nowx+2 && box[j].get_whereY()==player_nowy){ //如果是，不移动 
									tump2=0;
									break;
								}
							}
							if (tump2){
								box[i].set_where(1,0);
							}
						}
						else tump=0;
						break;
					}
				}
				if (tump && tump2){
					player_nowx++;
				}
			}
		}
		if (press_down=='d'){
			if (player_nowx-1>=0 && !map1[player_nowx-1][player_nowy]){
				bool tump=1,tump2=1;
				for (int i=0;i<box_num;i++){ //判断是否是箱子 
					if (box[i].get_whereX()==player_nowx-1 && box[i].get_whereY()==player_nowy){ //如果是，判断是否能移动 
						if (player_nowx-2>=0 && !map1[player_nowx-2][player_nowy]){
							for (int j=0;j<box_num;j++){ //判断再下一个是否是箱子 
								if (box[j].get_whereX()==player_nowx-2 && box[j].get_whereY()==player_nowy){ //如果是，不移动 
									tump2=0;
									break;
								}
							}
							if (tump2){
								box[i].set_where(-1,0);
							}
						}
						else tump=0;
						break;
					}
				}
				if (tump && tump2){
					player_nowx--;
				}
			}
		}
		if (press_down=='w'){
			if (player_nowy+1<mapy && !map1[player_nowx][player_nowy+1]){
				bool tump=1,tump2=1;
				for (int i=0;i<box_num;i++){ //判断是否是箱子 
					if (box[i].get_whereX()==player_nowx && box[i].get_whereY()==player_nowy+1){ //如果是，判断是否能移动 
						if (player_nowy+2<mapy && !map1[player_nowx][player_nowy+2]){
							for (int j=0;j<box_num;j++){ //判断再下一个是否是箱子 
								if (box[j].get_whereX()==player_nowx && box[j].get_whereY()==player_nowy+2){ //如果是，不移动 
									tump2=0;
									break;
								}
							}
							if (tump2){
								box[i].set_where(0,1);
							} 
						}
						else tump=0;
						break;
					}
				}
				if (tump && tump2){
					player_nowy++;
				}
			}
		}
		if (press_down=='s'){
			if (player_nowx-1>=0 && !map1[player_nowx][player_nowy-1]){
				bool tump=1,tump2=1;
				for (int i=0;i<box_num;i++){ //判断是否是箱子 
					if (box[i].get_whereX()==player_nowx && box[i].get_whereY()==player_nowy-1){ //如果是，判断是否能移动 
						if (player_nowy-2>=0 && !map1[player_nowx][player_nowy-2]){
							for (int j=0;j<box_num;j++){ //判断再下一个是否是箱子 
								if (box[j].get_whereX()==player_nowx && box[j].get_whereY()==player_nowy-2){ //如果是，不移动 
									tump2=0;
									break;
								}
							}
							if (tump2){
								box[i].set_where(0,-1);
							}
						}
						else tump=0;
						break;
					}
				}
				if (tump && tump2){
					player_nowy--;
				}
			}
		}
		/*判断胜利*/
		printf("^\n");
		{
			int good_num=0;
			for (int i=0;i<box_num;i++){
				for (int j=0;j<box_num;j++){
					if (box_lastwhere[i].x==box[j].get_whereX() && box_lastwhere[i].y==box[j].get_whereY()){
						good_num++;
						printf("%d %d\n",box_lastwhere[i].x,box_lastwhere[i].y);
					}
				}
			}
			if (good_num==box_num){
				cleardevice();
				print_win();
				getch();
				break;
			}
		}
		printf("*\n");
	}
	closegraph();
    return 0;
}

