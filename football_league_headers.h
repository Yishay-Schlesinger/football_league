#ifndef football_league_headers
#define football_league_headers

struct Team;

typedef struct Player
{
    char* PlayerName;
    int PlayerPrice;
    Team* TeamOfThePlayer;
}Player;

typedef struct Team
{
    char* TeamName;
    Player** PlayersOfTheTeam;
    int TeamAccount;
    int TeamPlayersCounter;
}Team;

typedef struct League
{
    Team* LeagueTeamsArray;
    int LeagueTeamsNumber;
    Player* LeaguePlayersArray;
    int LeaguePlayersNumber;
}League;

#define MAX_SIZE_NAME 25 

void initializingLeague(League& league);
void addTeam(int initialTeamAccount, char* teamName, League& thisLeague);
void deleteTeam(char* teamName, League& thisLeague);
void addPlayer(int playerPrice, char* playerName, League& thisLeague);
void deletePlayer(char* playerName, League& thisLeague);
void playerRecommendations(char* teamName, League& thisLeague);
void buyPlayer(char* playerName, char* teamName, League& thisLeague);
int teamExist(char* teamName, League& thisLeague);
int playerExist(char* playerName, League& thisLeague);
void removePlayer(char* playerName, char* teamName, League& thisLeague);
bool IsPlayerInTeam(char* teamName, char* playerName, int playerIndex, League& thisLeague);
void printPlayersByPrice(League& league);
void printTeamsByBudget(League& league);
void printTeamPlayers(char* teamName, League& league);
bool operate(League& league);
char* getTeamName();
char* getPlayerName();
int getPlayerPrice();
int getTeamBudget();
int stringToInt(char* str);
void printMenu();
char* getInfoFromUser();
void deleteTeamFieldFromPlayer(int indexToDelete, League& league);
void deletePlayerFromTeam(int indexToDelete, League& league);
void changeTeamAccount(int teamIndex, int newBudget, League& league);
void deleteInTheEnd(League& league);
#endif