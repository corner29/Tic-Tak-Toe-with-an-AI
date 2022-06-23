#include <bits/stdc++.h>
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;
#define ll long long
#define ld long double
#define f(i,a,b) for(auto i=a;i<b;i++) 
#define mb make_pair
#define pb push_back
#define vi vector<ll>
#define vl vector<ll>
#define vii vector<ll,ll>
#define vll vector<ll,ll>
#define mpi map<ll,ll>
#define mpl map<ll,ll>

pair<ll,ll> AI(vector<vector<char>>board, ll moveIndex);
bool rowCrossed(vector<vector<char>>board);
bool columnCrossed(vector<vector<char>>board);
void print(vector<vector<char>>board);
void play(ll whoseTurn);
bool diagonalCrossed(vector<vector<char>>board);
bool if_winner(vector<vector<char>>board);
ll minimax(vector<vector<char>>board, ll depth, bool isAI);

void play(ll whoseTurn){ 
	vector<vector<char>>board(3,vector<char>(3,' ')); 
	pair<ll,ll>temp;
	ll moveIndex=0,x=0,y=0,n;
	while (!if_winner(board) && moveIndex!=9) 
	{ 
		if (whoseTurn==1){
			temp=AI(board,moveIndex);
			x=temp.first;y=temp.second;
			board[x][y]='O'; 
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			cout<<"Computer has put O in cell "<<n+1<<endl;
			print(board);moveIndex++;whoseTurn=2; 
		} 
		else if(whoseTurn==2){
			cout<<"Enter the position = ";
			cin>>n;n--;
			x = n / 3;y = n % 3; 
			if(board[x][y]==' ' && n<=8 && n>=0){
				board[x][y]='X'; 
				cout<<"Human has put a X in cell "<<n+1<<endl; 
				print(board);moveIndex++;whoseTurn=1; 
			}
			else if(n<0 or n>8){
				cout<<"Invalid position"<<endl;
			}
			else if(board[x][y]!=' ' && n<9 && n>=0){
				cout<<"Position taken,choose another"<<endl;
			}
		}
	} 
	if (!if_winner(board) && moveIndex==9) 
		cout<<"Draw"<<endl; 
	else{ 
	    whoseTurn=(whoseTurn==1)?2:1;
	    if(whoseTurn==1){
	        cout<<"Computer has won"<<endl; 
	    }
	    else{
	        cout<<"Human has won"<<endl; 
	    }
	} 
} 


bool rowCrossed(vector<vector<char>>board){ 
	f(i,0,3){ 
		if (board[i][0] == board[i][1] and board[i][1] == board[i][2] and board[i][0] != ' ') 
			return true; 
	} 
	return false; 
} 

bool columnCrossed(vector<vector<char>>board){ 
	f(i,0,3) { 
		if (board[0][i] == board[1][i] and board[1][i] == board[2][i] and board[0][i] != ' ') 
			return true; 
	} 
	return false; 
} 

bool diagonalCrossed(vector<vector<char>>board){ 
	if ((board[0][0] == board[1][1] and board[1][1] == board[2][2] and board[0][0] != ' ') or (board[0][2] == board[1][1] and board[1][1] == board[2][0] and board[0][2] != ' ')) 
		return true; 

	return false; 
} 

pair<ll,ll> AI(vector<vector<char>>board, ll moveIndex){
	ll x,y,score,bestScore=INT_MIN;
	f(i,0,3){
		f(j,0,3){
			if(board[i][j]==' '){
				board[i][j]='O';
				score = minimax(board,moveIndex+1,false);
				board[i][j]=' ';
				if(score>bestScore){
					bestScore=score;x=i;y=j;
				}
			}
		}
	}
	return {x,y};
}

bool if_winner(vector<vector<char>>board){ 
	return(rowCrossed(board) or columnCrossed(board) or diagonalCrossed(board)); 
}

ll minimax(vector<vector<char>>board, ll depth, bool isAI){
	ll score=0,bestScore=0;
	if (if_winner(board)){
		if(!isAI){
			return 1;
		}
		return -1;
	}
	else{
		if(depth<9){
		    bestScore=(isAI)?INT_MIN:INT_MAX;
			if(isAI == true){
				f(i,0,3){
					f(j,0,3){
						if (board[i][j]==' '){
							board[i][j]='O';
							score = minimax(board,depth+1,false);
							board[i][j]=' ';
							if(score>bestScore){
								bestScore=score;
							}
						}
					}
				}
				return bestScore;
			}
			else{
				f(i,0,3){
					f(j,0,3){
						if (board[i][j]==' '){
							board[i][j]='X';
							score=minimax(board,depth+1,true);
							board[i][j]=' ';
							if (score<bestScore){
								bestScore=score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else{
			return 0;
		}
	}
	return 0;
}

void print(vector<vector<char>>board){
    cout<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl; 	
    cout<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl; 	
    cout<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl; 
} 


int main() 
{ 
	char cont,choice;
	bool condition=false;
	while(!condition){
	 	cout<<"Do you want to start first?(y/n): "<<endl;
	 	cin>>choice;
		if(choice=='n'){
			play(1);
		}	
		else if(choice=='y'){
			play(2);
		}	
		else{
			cout<<"Invalid choice"<<endl; 
		}
		cout<<"Do you want to quit(y/n): ";cin>>cont;
       	if(cont!='n'){
       	   condition=true;
       	}
	}
	return 0; 
} 
