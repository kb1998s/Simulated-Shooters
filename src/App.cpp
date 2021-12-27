//============================================================================
// Name        : App.cpp
// Author      : Vito Luong

//============================================================================
#include "../src/random.cpp"
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
using namespace std;
//struct coordinate that I mainly used
struct coordinates{
		int x=0;
		int y=0;
	};
class Board{

public:

	struct coordinates zone[72];
	//populate board zone
	void populate_zone(){
		int count=0;
		for(int i=0;i<7;i++){
			for(int k=0;k<8;k++){
				zone[count].x=i;
				zone[count].y=k;
				count++;
			}
		}
	}
};

//class store H information
class Helicopter{
	CRandom rand;

public:
	int score=0;
	struct coordinates zone[56];
	struct coordinates position;
	//constructor
	Helicopter(Board *board){}
	~Helicopter(){}
	///////////////////////////////////////////////////////////////////////////
	void populate_zone(){
		int count=0;
		for(int i=0;i<7;i++){
			for(int k=1;k<9;k++){
				zone[count].x=i;
				zone[count].y=k;
				//cout<<"testing "<< zone[count].x<< " "<<zone[count].y<<endl;
				count++;
			}
		}
	}
	//initial position
	void pos_ini(){
		rand.getRandomPublic(0, 55);
		int num = rand.getRandomPublic(0, 55);
		position = zone[num];
		cout<<"H's original position is ["<<position.x<<"]["<<position.y<<"]"<<endl;
	}
	//randomly move
	void move(){
		struct coordinates moved;
		bool checked=false;
		while(!checked){
		rand.getRandomPublic(position.x-1, position.x+1);
		moved.x = rand.getRandomPublic(position.x-1, position.x+1);
		moved.y = rand.getRandomPublic(position.y-1, position.y+1);
		for(int i=0;i< 55;i++){
			if(moved.x == zone[i].x && moved.y ==zone[i].y &&moved.x != position.x &&moved.y != position.y){
				position =moved;
				cout<<"H is moving into this position ["<<position.x<<"]["<<position.y<<"]"<<endl;

				//cout<<position.x<<" "<<position.y<<endl;
				checked=true;
				break;
			}
		}
		}

	}

};

//class store T info
class Top{
	CRandom rand;

public:
	int score=0;
	struct coordinates zone[7];
	struct coordinates position;
	//constructor
	Top(Board *board){}
	~Top(){}
	///////////////////////////////////////////////////////////////////////////
	void populate_zone(){
		int count=0;
		for(int i=0;i<6;i++){

				zone[count].x=i;
				zone[count].y=0;
				count++;

		}
	}
	//initial position
	void pos_ini(){
		rand.getRandomPublic(0, 6);
		int num = rand.getRandomPublic(0, 6);
		position = zone[num];
		cout<<"T's original position is ["<<position.x<<"]["<<position.y<<"]"<<endl;
	}
	//randomly move
	void move(){
		struct coordinates moved;
		bool checked=false;
		while(!checked){
		rand.getRandomPublic(position.x-1, position.x+1);
		moved.x = rand.getRandomPublic(position.x-1, position.x+1);
		moved.y = position.y;
		for(int i=0;i< 7;i++){
			if(moved.x == zone[i].x && moved.x != position.x){
				position =moved;
				cout<<"T is moving into this position ["<<position.x<<"]["<<position.y<<"]"<<endl;
				checked=true;
				break;
			}
		}
		}

	}

};

//class store R info
class Right{
	CRandom rand;

public:
	int score=0;
	struct coordinates zone[7];
	struct coordinates position;
	//constructor
	Right(Board *board){}
	~Right(){}
	///////////////////////////////////////////////////////////////////////////
	void populate_zone(){
		int count=0;
		for(int i=1;i<8;i++){

				zone[count].x=7;
				zone[count].y=i;

				count++;

		}
	}
	//initial position
	void pos_ini(){
		rand.getRandomPublic(0, 6);
		int num = rand.getRandomPublic(0, 6);
		position = zone[num];
		cout<<"R's original position is ["<<position.x<<"]["<<position.y<<"]"<<endl;

	}
	//randomly move
	void move(){
		struct coordinates moved;
		bool checked=false;
		while(!checked){
		rand.getRandomPublic(position.y-1, position.y+1);
		moved.y = rand.getRandomPublic(position.y-1, position.y+1);
		moved.x = position.x;
		for(int i=0;i< 7;i++){
			if(moved.y == zone[i].y  && moved.y != position.y){
				//cout<<"zone: "<<zone[i].x<< " "<<zone[i].y<<endl;
				position =moved;
				cout<<"R is moving into this position ["<<position.x<<"]["<<position.y<<"]"<<endl;

				//cout<<position.x<<" "<<position.y<<endl;
				checked=true;
				break;
			}
		}
		}

	}
};

//class store Rocket info
class Rocket{
public:
	bool done = false;
	CRandom rand;

	public:
		struct coordinates zone[72];
		struct coordinates position;
		//constructor
		Rocket(Board *board){}
		~Rocket(){}
		///////////////////////////////////////////////////////////////////////////
		void populate_zone(){
				int count=0;
				for(int i=0;i<7;i++){
					for(int k=0;k<8;k++){
						zone[count].x=i;
						zone[count].y=k;
						//cout<<"testing "<< zone[count].x<< " "<<zone[count].y<<endl;
						count++;
					}
				}
			}
		//initial position
		void pos_ini(Top *T){
			position.x= T->position.x;
			position.y=T->position.y;
		}
		void pos_ini(Right *R){
			position.x= R->position.x;
			position.y= R->position.y;
		}
		void pos_ini(Helicopter *H){
			position.x= H->position.x;
			position.y= H->position.y;
		}

		//randomly move
		bool shoot(Top *T){
			bool checked=false;

			position.y = position.y+1;


			for(int i=0;i<72;i++){
				//cout<<zone[i].x<<" "<<zone[i].y<<endl;
				if(position.x == zone[i].x && position.y ==zone[i].y){
					//cout<<"rocket at coordinate "<<position.x<<" "<<position.y<<endl;
					checked = true;
					break;
				}
			}
			return checked;
		}

		//shoot for T
		bool shoot_up(Helicopter *H, bool done[]){
			bool checked =true;
			position.y= position.y-1;
			for(int i=0;i<72;i++){
				if(position.x == zone[i].x && position.y ==zone[i].y){
				checked = false;
				break;
				}
			}
			done[position.x]=checked;
			return checked;
		}

		//shoot right for H
		bool shoot_right(Helicopter *H, bool done[]){
					bool checked =true;
					position.x= position.x+1;
					for(int i=0;i<72;i++){
						if(position.x == zone[i].x && position.y ==zone[i].y){
						checked = false;
						break;
						}
					}
					done[position.y]=checked;
					return checked;
				}

		//shoot down for R
		bool shoot_down_left(Right *R){
			bool checked =true;
			position.x= position.x-1;
			position.y= position.y+1;
			for(int i=0;i<72;i++){
			if(position.x == zone[i].x && position.y ==zone[i].y){
				checked = false;
				break;
				}
			}
			return checked;
		}
		//shoot up for R
		bool shoot_up_left(Right *R){
			bool checked =true;
			position.x= position.x-1;
			position.y= position.y-1;
			for(int i=0;i<72;i++){
			if(position.x == zone[i].x && position.y ==zone[i].y){
				checked = false;
				break;
				}
			}
				return checked;
				}
	};


//class store Grid info
class Grid{
	char grid[8][9];
public:
	Grid(Board *board){}
	~Grid(){}

	//Setting up the grid with all objecy
	void grid_print(Helicopter *H, Top *T, Right *R, vector <Rocket*> Top_rockets, vector <Rocket*> Heli_Up_rockets,bool done_up[],vector <Rocket*> Heli_Right_rockets,bool done_right[],vector <Rocket*> R_down_rockets,vector <Rocket*> R_up_rockets){

		for(int y=0;y<9; y++){
			for(int x=0;x<8;x++){
				if(H->position.x==x && H->position.y==y){
					grid[x][y]='H';
				}else if(T->position.x==x && T->position.y==y){
					grid[x][y]='T';
				}else if(R->position.x==x && R->position.y==y){
					grid[x][y]='R';

				}else{
				grid[x][y] = '-';
				}
				//Setting up top rocket
				//Top rocket
				if(Top_rockets.size()>0){
					for(int i=0; i<Top_rockets.size();i++){
						if(H->position.x== Top_rockets[i]->position.x && H->position.y== Top_rockets[i]->position.y && Top_rockets[i]->position.x  ==x && Top_rockets[i]->position.y == y){
							grid[x][y]='X';

							cout<<"H took a hit from T's bomb at ["<<Top_rockets[i]->position.x<<"]["<< Top_rockets[i]->position.y<<"]"<<endl;
							Top_rockets.erase(Top_rockets.begin()+i);
							T->score+=20;
							cout<<"T score is now: "<<T->score<<endl;
						}else if(Top_rockets[i]->position.x  ==x && Top_rockets[i]->position.y == y){
							grid[x][y]='!';

						}

					}
				}

				//Heli Up rocket
				if(Heli_Up_rockets.size()>0){
					for(int i=0; i<Heli_Up_rockets.size();i++){

						if(T->position.x== Heli_Up_rockets[i]->position.x && T->position.y== Heli_Up_rockets[i]->position.y && Heli_Up_rockets[i]->position.x  ==x && Heli_Up_rockets[i]->position.y == y){
							grid[x][y]='X';
							done_up[Heli_Up_rockets[i]->position.x]=true;
							cout<<"T took a hit from H's rocket ["<<Heli_Up_rockets[i]->position.x<<"]["<< Heli_Up_rockets[i]->position.y<<"]"<<endl;
							Heli_Up_rockets.erase(Heli_Up_rockets.begin()+i);
							H->score+=20;
							cout<<"H score is now: "<<H->score<<endl;
						}else if(Heli_Up_rockets[i]->position.x  ==x && Heli_Up_rockets[i]->position.y == y){
							grid[x][y]='^';

						}

						}
						}

				//Heli Right rockets
				if(Heli_Right_rockets.size()>0){
					for(int i=0; i<Heli_Right_rockets.size();i++){

						if(R->position.x== Heli_Right_rockets[i]->position.x && R->position.y== Heli_Right_rockets[i]->position.y && Heli_Right_rockets[i]->position.x  ==x && Heli_Right_rockets[i]->position.y == y){
							grid[x][y]='X';
							done_up[Heli_Right_rockets[i]->position.y]=true;
							cout<<"R took a hit from H's rocket ["<<Heli_Right_rockets[i]->position.x<<"]["<< Heli_Right_rockets[i]->position.y<<"]"<<endl;
							Heli_Right_rockets.erase(Heli_Right_rockets.begin()+i);
							H->score+=20;
							cout<<"H score is now: "<<H->score<<endl;
						}else if(Heli_Right_rockets[i]->position.x  ==x && Heli_Right_rockets[i]->position.y == y){
							grid[x][y]='>';

									}

						}
					}

				//Right Rockets
				//down
				if(R_down_rockets.size()>0){
					for(int i=0; i<R_down_rockets.size();i++){
						if(H->position.x== R_down_rockets[i]->position.x && H->position.y== R_down_rockets[i]->position.y && R_down_rockets[i]->position.x  ==x && R_down_rockets[i]->position.y == y){
							grid[x][y]='X';

							cout<<"H took a hit from R's energy wave ["<<R_down_rockets[i]->position.x<<"]["<< R_down_rockets[i]->position.y<<"]"<<endl;
							R_down_rockets.erase(R_down_rockets.begin()+i);
							R->score+=20;
							cout<<"R score is now: "<<R->score<<endl;
						}else if(R_down_rockets[i]->position.x  ==x && R_down_rockets[i]->position.y == y){
							grid[x][y]='(';
							}
							}
						}
				//up
				if(R_up_rockets.size()>0){
					for(int i=0; i<R_up_rockets.size();i++){
						if(H->position.x== R_up_rockets[i]->position.x && H->position.y== R_up_rockets[i]->position.y && R_up_rockets[i]->position.x  ==x && R_up_rockets[i]->position.y == y){
							grid[x][y]='X';

							cout<<"H took a hit from R's energy wave ["<<R_up_rockets[i]->position.x<<"]["<< R_up_rockets[i]->position.y<<"]"<<endl;
							R_up_rockets.erase(R_up_rockets.begin()+i);
							R->score+=20;
							cout<<"R score is now: "<<R->score<<endl;
						}else if(T->position.x== R_up_rockets[i]->position.x && T->position.y== R_up_rockets[i]->position.y && R_up_rockets[i]->position.x  ==x && R_up_rockets[i]->position.y == y){
							grid[x][y]='O';

							cout<<"T took a hit from R's energy wave ["<<R_up_rockets[i]->position.x<<"]["<< R_up_rockets[i]->position.y<<"]"<<endl;
							cout<<"However, T is immune to ally's damage"<<endl;
						}else if(R_up_rockets[i]->position.x  ==x && R_up_rockets[i]->position.y == y){
							grid[x][y]='(';
						}
					}
				}

			}
		}

		//printing to the console
		for(int y=0;y<9; y++){
			for(int x=0;x<8;x++){
				printf(" %c |", grid[x][y]);

			}
			printf("\n");
		}

	}
};

//setting up for Game
class Game{
public:
	bool done_up[7]={true,true,true,true,true,true,true};
	bool done_right[7]={true,true,true,true,true,true,true};
	CRandom rand;
	//for rockets from T
	vector <Rocket*> Top_rockets;
	void new_Top_rocket(Top *T, Board *board){
		Rocket *r_Top = new Rocket(board);
		r_Top->populate_zone();
		r_Top->pos_ini(T);
		Top_rockets.push_back(r_Top);

	}
	//for rockets from H
	vector <Rocket*> Heli_Up_rockets;
	void new_Heli_Up_rocket(Helicopter *H, Board *board){
		Rocket *r_Heli_up = new Rocket(board);
		r_Heli_up->populate_zone();
		r_Heli_up->pos_ini(H);
		Heli_Up_rockets.push_back(r_Heli_up);

		}
	//upper rockets from H
	vector <Rocket*> Heli_right_rockets;
	void new_Heli_Right_rocket(Helicopter *H,Board *board){
		Rocket *r_Heli_right = new Rocket(board);
		r_Heli_right->populate_zone();
		r_Heli_right->pos_ini(H);
		Heli_right_rockets.push_back(r_Heli_right);

	}

	//down rockets from R
	vector <Rocket*> R_down_rockets;
	void new_R_down_rocket(Right *R, Board *board){
		Rocket *R_down = new Rocket(board);
		R_down->populate_zone();
		R_down->pos_ini(R);
		R_down_rockets.push_back(R_down);
	}
	vector <Rocket*> R_up_rockets;
	void new_R_up_rocket(Right *R, Board *board){
			Rocket *R_up = new Rocket(board);
			R_up->populate_zone();
			R_up->pos_ini(R);
			R_up_rockets.push_back(R_up);
		}
	//play method
	void play(Board *board,Helicopter *H, Top *T, Right *R, Grid *grid){
		bool in_range=true;
		int count=0;

		loop_delay(2.5);
		cout<<"------------------------------------"<<endl;
		cout<<"GAME ON!"<<endl;
		while(count<20){
		loop_delay(2.5);
		cout<<"Round "<<(count+1)<<endl;
		cout<<"------------------------------------"<<endl;
		grid->grid_print(H, T, R,Top_rockets,Heli_Up_rockets,done_up,Heli_right_rockets,done_right,R_down_rockets,R_up_rockets);

		//shoot new Top rocket
		rand.getRandomPublic(0, 2);
		int num = rand.getRandomPublic(0, 2);
		if(num ==1 ){
			new_Top_rocket(T, board);
			cout<<"T dropping a new bomb down "<<endl;
		}else{
			T->move();
		}



		//shoot new UP rocket from Heli
		num= rand.getRandomPublic(0, 3);
		if(num==1 && done_up[H->position.x]==true){
			new_Heli_Up_rocket(H, board);
			cout<<"H shooting a new up rocket "<<endl;
			done_up[H->position.x]=false;

		//shoot new RIGHT rocket from Heli
		}else if(num==2 && done_right[H->position.y]==true){
			new_Heli_Right_rocket(H, board);
			cout<<"H shooting a new right rocket "<<endl;
			done_up[H->position.y]=false;
		}else{
			H->move();
		}

		//shoot new rockets from Right
		num = rand.getRandomPublic(0, 2);
			if(num ==1 ){
			new_R_down_rocket(R, board);
			new_R_up_rocket(R, board);
			cout<<"R shooting 2 side energy waves "<<endl;
			}else{
			R->move();
		}

		//each rocket keep shooting
		for(int i=0;i<Top_rockets.size();i++){
			Top_rockets[i]->shoot(T);
			}

		for(int i=0;i<Heli_Up_rockets.size();i++){
			Heli_Up_rockets[i]->shoot_up(H,done_up);
		}

		for(int i=0;i<Heli_right_rockets.size();i++){
			Heli_right_rockets[i]->shoot_right(H,done_right);
			}

		for(int i=0;i<R_down_rockets.size();i++){
			R_down_rockets[i]->shoot_down_left(R);
			}

		for(int i=0;i<R_up_rockets.size();i++){
			R_up_rockets[i]->shoot_up_left(R);
			}

		cout<<"------------------------------------"<<endl;
		count++;
		}

	}

	//method to print out the score
	void score(Helicopter *H, Right *R, Top*T){
		loop_delay(2.5);
		cout<<"************Here is the Score Board after 20 rounds ************"<<endl;
		cout<<"Player H: "<<H->score<<endl;
		cout<<"Alien R: "<<R->score<<endl;
		cout<<"Alien T: "<<T->score<<endl;
		cout<<"CONGRATULATION ON THE WINNERS"<<endl;
	}
	//time delaying method
	void loop_delay(float num)
	{
	    time_t before = time(0);
	    while (difftime(time(0), before) < num);
	}

	//API
	void API(){
		srand(time(NULL));
		//few words before program start
		cout<<"Welcome to BOTS_FIGHT"<<endl;
		cout<<"A few words before the program start"<<endl;
		cout<<"For displaying purpose, I have replaced a few icons for the rockets"<<endl;
		cout<<"1. Using ! instead of * for rockets from T"<<endl;
		cout<<"2. Using ( instead of M and W for the double rockets from R"<<endl;
		cout<<"Also since the map is 8x9, I believe having the rounds number of 20 will be more suitable than just 5 rounds"<<endl;
		cout<<"This is probably one of my proudest word in C++. Please drop a comment if you enjoy it!"<<endl;
		loop_delay(10);

		//initialize
		cout<<"------------------------------------"<<endl;
		Board *board = new Board();
		board->populate_zone();
		Helicopter *H = new Helicopter(board);
		H->populate_zone();
		H->pos_ini();
		Top *T = new Top(board);
		T->populate_zone();
		T->pos_ini();
		Right *R  = new Right(board);
		R->populate_zone();
		R->pos_ini();
		Grid *grid=new Grid(board);
		cout<<"------------------------------------"<<endl;
		//play
		play(board,H, T, R, grid);
		score(H,R,T);

	}
};
//main method
int main() {

	Game game;
	game.API();

	return 0;
}
