using namespace std;

void print_block(int x,int y,int kind){
	setcolor(EGERGB(0x0,0x0,0x0)); //设置边缘颜色 
	if (kind==0){ //如果是地 
		setfillcolor(EGERGB(0x7f,0x7f,0x7f));
		bar(x-30,y-30,x+30,y+30);
	}
	if (kind==1){ //如果是墙 
		setfillcolor(EGERGB(0x4d,0x45,0x8f));
		bar(x-30,y-30,x+30,y+30);
	}
	if (kind==2){ //如果是箱子 
		setfillcolor(EGERGB(0xa4,0x79,0x22));
		bar(x-30,y-30,x+30,y+30);
	}
	if (kind==3){ //如果是箱子终点 
		setcolor(EGERGB(0xc1,0x0,0x0));
		line(x-25,y-30,x+30,y+25);
		line(x-30,y-25,x+25,y+30);
		line(x-30,y+25,x+25,y-30);
		line(x-25,y+30,x+30,y-25);
	}
//	bar(x-30,y-30,x+30,y+30);
	return;
}

void print_win(){
	setcolor(EGERGB(0xc1,0x0,0x0));
	outtextxy(100,100,"You Win");
	return;
}

void print_player(){
	setcolor(EGERGB(0x29,0x98,0x7c));
	setfillcolor(EGERGB(0x29,0x98,0x7c));
	circle(chx/2,chy/2,25);
	floodfill(chx/2,chy/2,EGERGB(0x29,0x98,0x7c));
	return;
}

