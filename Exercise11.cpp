
#include <iostream>
#include <utility>
#include <vector>
#include <array>

using namespace std;

const int N = 10, M = 10;
const int NUM_SIMULATIONS = 100;
const vector<int> ITERATIONS = {100, 250, 500, 1000};

enum class Cell : char {
    Clean = '.',
    Dirty = '*',
    Wall = '#'
};

struct Agent{
    int x, y, score;
    Agent() : x(1), y(1), score(5) {}

    void cleanTile(vector<vector<Cell> > env){
        if(env[x][y] == Cell::Dirty){
            env[x][y] = Cell::Clean;
            score += 10;
        }
        score--;
    }//cleanTile

    void moveAgent(char move){
        if(move == 'L' && y > 1){
            y--;
        }else if(move == 'R' && y < M - 2){
            y++;
        }else if (move == 'D'  && x > N - 2){
            x++;
        }else{
            return; //NOOP
        }
        score--;
    }//moveAgent
};//Agent

class Environment{
    private: 
        vector<vector<Cell> > env;
        int rows, cols;

    public:
        Environment(const int &rows, const int &cols):
        rows(N), cols(M), env(N, std::vector<Cell>(M, Cell::Clean)){
            for(size_t r = 0; r < N; r++){
                for(size_t c = 0; c < M; c++){
                    if(r == 0 || r == N - 1 || c == 0 || c == M - 1){
                        env[r][c] = Cell::Wall;
                    }else{
                        env[r][c] = (rand() % 2) ? Cell::Clean : Cell::Dirty;
                    }//else
                }//for
            } //first for
        }//env

        void runEnviroment(int maxIter){
            int totalScore = 0;
            for(size_t i = 0; i < NUM_SIMULATIONS; i++){
                Environment enviro(N, M); 
                Agent agent; 
                for(size_t j = 0; j < maxIter; j++){
                    if(env[agent.x][agent.y] == Cell::Dirty){
                        agent.cleanTile(enviro.env);
                    }else{
                        agent.moveAgent((rand() % 4 == 0) ? 'L' : ((rand() % 3 == 0) ? 'R' : ((rand() % 2 == 0) ? 'D' : 'N')));
                    }
                    totalScore += agent.score;
                }
                cout << maxIter << "\n iterations: " << totalScore / NUM_SIMULATIONS << "\n";
            }//for
        }//runEnviro
};//Environment




int main(){
    Environment env(N,M);
    for(auto iter : ITERATIONS){
        env.runEnviroment(iter);
    }
};

