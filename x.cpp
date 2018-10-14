#include <bits/stdc++.h>
#include <tuple>
#include "Airport.h"
#include "unistd.h"
#define che
#define debug(...) fprintf(stderr,__VA_ARGS__);fflush(stderr);
#define fi first
#define se second
#define MK make_pair
#define PB push_back
using namespace std;

typedef long long LL;
typedef pair<int ,int> PII;
const string Title[3] = {"The Scheduled airplane on the path",
                         "The queue for landing",
                         "The queue for taking off"};

set<int> repeat_num,fresh_num;
Airport a(1,2);
bool RandomFlight(){
    int num =0;
    while ( num==0 || repeat_num.count(num))
        num = rand()%10000;
        // for (int i=0; i<2; ++i) name += char(rand()%26+'A');
    repeat_num.insert(num);
    fresh_num.insert(num);
    if (rand()%2) return a.message(1, num,10000,0);
        else return a.message(0, num, rand()%10+10,1);
}
void ColorfulPrint(int number,int rest_fuel){
    string state= number ? to_string(number) : "";

    while (state.size() && state.size()<4) state= "0"+state;
    if ( rest_fuel >=0){
        state+=" remaining fuel: "+to_string(rest_fuel);
    }
    while ( state.size()<20) state=" "+state;
    if ( fresh_num.count(number)) state = "\033[;30m"+state+"\033[0m";
        else state= "\033[;32m"+state+"\033[0m";
    printf("%s",state.c_str());
}
void PrintConsole(const vector<Plane> column[]){
    system("clear");
    int n=0;
    for (int i=0; i<3; ++i) n= max(n, (int)column[i].size());
    for (int i=0; i<n; ++i){
        for (int j=0; j<3; ++j){
            int number=0; int fuel=-1;
            if (  i<column[j].size() ){
                number= column[j][i].getNum();
                if ( j==1) fuel = column[j][i].getFuel();
            }
            ColorfulPrint(number,fuel);
        }
        puts("");
    }
    sleep(1.3);
}
typedef pair<string, int> PSI;

int main(){
    vector<Plane> s[3];
    for (int T=1; ; ++T){   // each round of one hour
//        vector<Plane> current_takeoff=a.show_takeoff();
//        vector<Plane> current_land=a.show_land();
        // PrintConsole(s);
        // s[rand()%3].push_back( RandomFlight());
        // for (int i=0; i<3 ; ++i) t[i]= s[i];

        int fatal= false;
        s[0] = a.show_takeoff();
        vector<Plane> tmp= a.show_land();
        s[0].insert(s[0].end(),tmp.begin(), tmp.end());
        fresh_num.clear();

        int newComen= rand()%10+1, flyN= s[0].size();

        for (int i=1, curCome=newComen, curfly= flyN; i<=newComen+flyN; ++i){
            double r= rand()*1.0/32768;
            debug("i=%d, curCome=%d, curfly= %d\n", i, curCome, curfly);
            if ( r < curfly*1.0/(curCome+curfly)){
                s[0].erase(s[0].begin());
                --curfly;
            }   else{
                fatal |= RandomFlight();
                bool ok =false;
                tuple<bool , vector<Plane> , vector<Plane> > tmp=a.request();
                debug("ok on request\n");
                ok= get<0>(tmp);
                s[1] = get<1>(tmp);
                                debug("ok on tie\n");

                s[2] = get<2>(tmp);

                fatal |= ok;
                --curCome;
            }

            sleep(2);
            PrintConsole(s);
        }
    }
    return 0;
}
