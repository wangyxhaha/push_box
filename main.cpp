/** 
* made by ������ 
* ��Ҫegeͼ�ο� 
* ��Ҫ����ָ��
* "-lgraphics64 -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid -mwindows"
*/
#define chx 640 //���ڴ�С 
#define chy 480
#include <graphics.h>
#include <windows.h>
#include <fstream>
#include "./headfile/box.h"
using namespace std;

int mapx,mapy; //��ͼ��С 
int box_num; //���Ӹ��� 
int player_firstx,player_firsty; //��ҳ�ʼλ�� 
Box box_lastwhere[1000]; //���ӽ���λ�� 
BOX box[1000]; //������ 
bool map1[1000][1000]; //�����ͼ 0����� 1����ǽ 

int main(){
	ifstream fin; //�ļ����� 
	fin.open("./map/in.map");
	if (fin.fail()){ //��ʧ�� 
		MessageBox(NULL,"Can't open: in.map\n\nUnable to load","ERROR",MB_OK);
		return 0;
	}
	else{ //�򿪳ɹ�->�������� 
		/*�����ͼ*/ 
		fin >> mapx >> mapy; //�����ͼ��Χ 
		if (fin.eof()){ //�����ǰ������� 
			MessageBox(NULL,"Map content error","ERROR",MB_OK);
			fin.close();
			return 0;
		}
		if (mapx>1000 || mapx<=0 || mapy<=0 || mapy>1000){ //�����ͼ��Χ������С 
			MessageBox(NULL,"Map is too large or too small\n\n(0 < x,y < 1000)","ERROR",MB_OK);
			fin.close();
			return 0;
		}
		for (int i=0;i<mapx;i++){ //�����ͼ 
			for (int j=0;j<mapy;j++){
				fin >> map1[i][j];
				if (fin.eof()){ //�����ǰ������� 
					MessageBox(NULL,"Map content error","ERROR",MB_OK);
					fin.close();
					return 0;
				}
			}
		}
		/*��������*/
		fin >> box_num; //������������ 
		if (fin.eof()){ //�����ǰ������� 
			MessageBox(NULL,"Map content error","ERROR",MB_OK);
			fin.close();
			return 0;
		}
		if (box_num>1000 || box_num<=0){ //�����������̫���̫�� 
			MessageBox(NULL,"Boxes are too few or too many\n\n(0 < box_num < 1000)","ERROR",MB_OK);
			fin.close();
			return 0;
		}
		for (int i=0;i<box_num;i++){ //�������ӳ�ʼλ�� 
			int tx,ty;
			fin >> tx >> ty;
			if (fin.eof()){ //�����ǰ������� 
				MessageBox(NULL,"Map content error","ERROR",MB_OK);
				fin.close();
				return 0;
			}
			box[i].set_where(tx,ty); //��ʼ�������� 
		}
		for (int i=0;i<box_num;i++){ //�������ӽ���λ�� 
			fin >> box_lastwhere[i].x >> box_lastwhere[i].y;
			if (fin.eof()){ //�����ǰ������� 
				MessageBox(NULL,"Map content error","ERROR",MB_OK);
				fin.close();
				return 0;
			}
		}
		/*���������Ϣ*/
		fin >> player_firstx >> player_firsty; //������ҳ�ʼλ�� 
		if (fin.eof()){ //�����ǰ������� 
			MessageBox(NULL,"Map content error","ERROR",MB_OK);
			fin.close();
			return 0;
		}
	}
	fin.close(); //������Ϲر��ļ� 
	/*�������*/
	for (int i=0;i<mapx;i++){
		for (int j=0;j<mapy;j++){
			printf("%d ",map1[i][j]);
		}
		printf("\n");
	} 
	/**/ 
    initgraph(chx,chy); //��ʼ������ 
    setbkcolor(EGERGB(0x1c,0x24,0x3c)); //���ñ�����ɫ 
	char press_down; //�жϼ��� 
    do{
		press_down=getch();
	}while (press_down!=' ');
	int player_nowx=player_firstx,player_nowy=player_firsty;
    while (is_run()){
    	/*����*/
    	cleardevice();
    	for (int i=0;i<mapx;i++){ //����ǽ�͵� 
    		for (int j=0;j<mapy;j++){
    			print_block((chx/2)+(player_nowx-i)*60,(chy/2)+(player_nowy-j)*60,map1[i][j]);
			}
		}
		for (int i=0;i<box_num;i++){ //�������� 
			print_block((chx/2)+(player_nowx-box[i].get_whereX())*60,(chy/2)+(player_nowy-box[i].get_whereY())*60,2);
		}
		for (int i=0;i<box_num;i++){ //���������յ� 
			print_block((chx/2)+(player_nowx-box_lastwhere[i].x)*60,(chy/2)+(player_nowy-box_lastwhere[i].y)*60,3);
		}
		print_player(); //������� 
		/*��ⰴ��*/
    	press_down=getch();
    	if (press_down=='o'){ //�ж��˳��� 
    		break;
		}
		if (press_down=='a'){ //�ж��ƶ��� 
			if (player_nowx+1<mapx && !map1[player_nowx+1][player_nowy]){ //�ж��Ƿ���ǽ 
				bool tump=1,tump2=1;
				for (int i=0;i<box_num;i++){ //�ж��Ƿ������� 
					if (box[i].get_whereX()==player_nowx+1 && box[i].get_whereY()==player_nowy){ //����ǣ��ж��Ƿ����ƶ� 
						if (player_nowx+2<mapx && !map1[player_nowx+2][player_nowy]){
							for (int j=0;j<box_num;j++){ //�ж�����һ���Ƿ������� 
								if (box[j].get_whereX()==player_nowx+2 && box[j].get_whereY()==player_nowy){ //����ǣ����ƶ� 
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
				for (int i=0;i<box_num;i++){ //�ж��Ƿ������� 
					if (box[i].get_whereX()==player_nowx-1 && box[i].get_whereY()==player_nowy){ //����ǣ��ж��Ƿ����ƶ� 
						if (player_nowx-2>=0 && !map1[player_nowx-2][player_nowy]){
							for (int j=0;j<box_num;j++){ //�ж�����һ���Ƿ������� 
								if (box[j].get_whereX()==player_nowx-2 && box[j].get_whereY()==player_nowy){ //����ǣ����ƶ� 
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
				for (int i=0;i<box_num;i++){ //�ж��Ƿ������� 
					if (box[i].get_whereX()==player_nowx && box[i].get_whereY()==player_nowy+1){ //����ǣ��ж��Ƿ����ƶ� 
						if (player_nowy+2<mapy && !map1[player_nowx][player_nowy+2]){
							for (int j=0;j<box_num;j++){ //�ж�����һ���Ƿ������� 
								if (box[j].get_whereX()==player_nowx && box[j].get_whereY()==player_nowy+2){ //����ǣ����ƶ� 
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
				for (int i=0;i<box_num;i++){ //�ж��Ƿ������� 
					if (box[i].get_whereX()==player_nowx && box[i].get_whereY()==player_nowy-1){ //����ǣ��ж��Ƿ����ƶ� 
						if (player_nowy-2>=0 && !map1[player_nowx][player_nowy-2]){
							for (int j=0;j<box_num;j++){ //�ж�����һ���Ƿ������� 
								if (box[j].get_whereX()==player_nowx && box[j].get_whereY()==player_nowy-2){ //����ǣ����ƶ� 
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
		/*�ж�ʤ��*/
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

