using namespace std;

void BOX::set_where(int x,int y){
	bx+=x,by+=y;
	return;
}

int BOX::get_whereX(){
	return bx;
}

int BOX::get_whereY(){
	return by;
}

//bool BOX::if_knock_wall(int x,int y){
//	;
//}

