
#include "football_league_headers.h"
#include <iostream>
#include <string>
#include <cstring>
#pragma warning (disable:4996)

using namespace std;


/***********************************************************************************
* Function name: initializingLeague
* Input: League& league
* Output: void
* Function Operation: fills all leagues' fields with 0/NULL.
***********************************************************************************/
void initializingLeague(League& league)
{
	league.LeaguePlayersArray = NULL;
	league.LeaguePlayersNumber = 0;
	league.LeagueTeamsArray = NULL;
	league.LeagueTeamsNumber = 0;
}


/***********************************************************************************
* Function name: printMenu
* Input: none
* Output: void
* Function Operation: print menu
***********************************************************************************/
void printMenu()
{
	cout << "Welcome to Soccer League Management System\n"
		"Choose  one of the following options:\n"
		"(1)  Add a Player\n"
		"(2)  Add a Team\n"
		"(3)  Delete a Player\n"
		"(4)  Delete a Team\n"
		"(5)  Team: Player Recommendations\n"
		"(6)  Team: Buy a player\n"
		"(7)  Team: Remove a player\n"
		"(8)  Print list of all Players sorted by their salary\n"
		"(9)  Print a list of all Teams sorted by their budget\n"
		"(10) Print a list of players for a specific team\n"
		"(11) Exit \n\n";
}


/***********************************************************************************
* Function name: stringToInt
* Input: char* str(pointer to string from user)
* Output: int sum(the sum of the string that changed to int)
* Function Operation: changed string(char array[]) to int.
***********************************************************************************/
int stringToInt(char* str)
{
	int sum = 0;
	int multiply = 1;
	//go from the last char in string to first char
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		//if not valid for this program
		if (!isdigit(str[i]))
		{
			return 0;
		}
		//if valid
		else
		{
			//multiply = 1 -> add digit units, 
			//multiply = 10 -> add tens digit,
			//multiply = 100 -> add hundreds digit, etc.
			sum = sum + ((str[i] - '0') * multiply);
			multiply *= 10;
		}
	}
	return sum;
}


/***********************************************************************************
* Function name: getInfoFromUser
* Input: none.
* Output:  char* userInfo(pointer to string)
* Function Operation: changed string(char array[]) to int.
***********************************************************************************/
char* getInfoFromUser()
{
	char* userInfo = new char[MAX_SIZE_NAME];
	cin >> userInfo;
	return userInfo;
}


/***********************************************************************************
* Function name: getInfoFromUser
* Input: League& league
* Output:  bool stop(return to main. false- don't end the loop. true - end the loop.)
* Function Operation: call func that print the menu. get user selection.
					  by switch and user selection get into the right case and call to the right function.
					  in the end return 'stop' to 'main()'.
***********************************************************************************/
bool operate(League& league)
{
	bool stop = false;
	printMenu();
	char* userInfo = getInfoFromUser();
	int num = stringToInt(userInfo);
	switch (num)
	{
	case 1: addPlayer(getPlayerPrice(), getPlayerName(), league); break;
	case 2: addTeam(getTeamBudget(), getTeamName(), league); break;
	case 3: deletePlayer(getPlayerName(), league); break;
	case 4: deleteTeam(getTeamName(), league); break;
	case 5: playerRecommendations(getTeamName(), league); break;
	case 6: buyPlayer(getPlayerName(), getTeamName(), league); break;
	case 7: removePlayer(getPlayerName(), getTeamName(), league); break;
	case 8: printPlayersByPrice(league); break;
	case 9: printTeamsByBudget(league); break;
	case 10: printTeamPlayers(getTeamName(), league); break;
	case 11: {
		stop = true;
		deleteInTheEnd(league);
		break;
	}
	default: cout << "Error: Try Again!\n"; break;
	}
	delete[] userInfo;
	return stop;
}


/***********************************************************************************
* Function name: getTeamName
* Input: none
* Output:  char* teamName(pointer to string)
* Function Operation: call func that get string from user. return pointer to the string.
***********************************************************************************/
char* getTeamName()
{
	cout << "Enter name of Team: \n";
	char* teamName = getInfoFromUser();
	return teamName;
}


/***********************************************************************************
* Function name: getPlayerName
* Input: none
* Output:  char* playerName(pointer to string)
* Function Operation: call func that get string from user. return pointer to the string.
***********************************************************************************/
char* getPlayerName()
{
	cout << "Enter name of Player: \n";
	char* playerName = getInfoFromUser();
	return playerName;
}


/***********************************************************************************
* Function name: getPlayerPrice
* Input: none
* Output:  int playerPrice
* Function Operation: call func that get string from user. 
					  call func that return the numeric value of the string.
					  return the numeric value.
***********************************************************************************/
int getPlayerPrice()
{
	cout << "Enter player salary: \n";
	char* userInfo = getInfoFromUser();
	int playerPrice = stringToInt(userInfo);
	delete[] userInfo;
	return playerPrice;
}


/***********************************************************************************
* Function name: getTeamBudget
* Input: none
* Output:  int teamBudget
* Function Operation: call func that get string from user.
					  call func that return the numeric value of the string.
					  return the numeric value.
***********************************************************************************/
int getTeamBudget()
{
	cout << "Enter starting budget: \n";
	char* userInfo = getInfoFromUser();
	int teamBudget = stringToInt(userInfo);
	delete[] userInfo;
	return teamBudget;
}


/***********************************************************************************
* Function name: addPlayer
* Input: int playerPrice, char* playerName(pointer to string), League& league
* Output:  void
* Function Operation: add new player to 'LeaguePlayersArray' and initialzied it with input/NULL.
***********************************************************************************/
void addPlayer(int playerPrice, char* playerName, League& league)
{
	//copy old array
	Player* temp;
	temp = league.LeaguePlayersArray;
	league.LeaguePlayersArray = new Player[league.LeaguePlayersNumber + 1];
	for (int i = 0; i < league.LeaguePlayersNumber; i++)
	{
		league.LeaguePlayersArray[i] = temp[i];
	}
	//add new player to array
	league.LeaguePlayersArray[league.LeaguePlayersNumber].PlayerName = playerName;
	league.LeaguePlayersArray[league.LeaguePlayersNumber].PlayerPrice = playerPrice;
	league.LeaguePlayersArray[league.LeaguePlayersNumber].TeamOfThePlayer = NULL;
	league.LeaguePlayersNumber++;
	delete[] temp;
}


/***********************************************************************************
* Function name: addTeam
* Input: int initialTeamAccount, char* teamName(pointer to string), League& league
* Output:  void
* Function Operation: add new Team to 'LeagueTeamsArray' and initialzied it with input/NULL/0.
***********************************************************************************/
void addTeam(int initialTeamAccount, char* teamName, League& league)
{
	//copy old array
	Team* temp;
	temp = league.LeagueTeamsArray;
	league.LeagueTeamsArray = new Team[league.LeagueTeamsNumber + 1];
	for (int i = 0; i < league.LeagueTeamsNumber; i++)
	{
		league.LeagueTeamsArray[i] = temp[i];
	}
	//add new team to array
	league.LeagueTeamsArray[league.LeagueTeamsNumber].TeamName = teamName;
	league.LeagueTeamsArray[league.LeagueTeamsNumber].TeamAccount = initialTeamAccount;
	league.LeagueTeamsArray[league.LeagueTeamsNumber].TeamPlayersCounter = 0;
	league.LeagueTeamsArray[league.LeagueTeamsNumber].PlayersOfTheTeam = NULL;
	league.LeagueTeamsNumber++;
	delete[] temp;
}


/***********************************************************************************
* Function name: deleteTeamFieldFromPlayer
* Input: int indexToDelete, League& league
* Output:  void
* Function Operation: if there is players in the team(if not null), change the pointer to the team from all team's 
				      players to NULL.
***********************************************************************************/
void deleteTeamFieldFromPlayer(int indexToDelete, League& league)
{
	//for easy read:
	Team* thisTeam = &league.LeagueTeamsArray[indexToDelete];
	//if there are players in the team
	if (thisTeam->PlayersOfTheTeam != NULL)
	{
		//change the pointer to the team from all team's players to NULL
		for (int q = 0; q < league.LeagueTeamsArray[indexToDelete].TeamPlayersCounter; q++)
		{
			thisTeam->PlayersOfTheTeam[q]->TeamOfThePlayer = NULL;
		}
		delete[] thisTeam->PlayersOfTheTeam;
		thisTeam->PlayersOfTheTeam = NULL;
		thisTeam->TeamPlayersCounter = 0;
	}
}


/***********************************************************************************
* Function name: deleteTeam
* Input: char* teamName(pointer to string)
* Output:  void
* Function Operation: check if team exist and get the index in the Array.
					  if there is players in the team change the pointer change the pointer to the team from
					  all players to NULL. delete team from LeagueTeamsArray.
***********************************************************************************/
void deleteTeam(char* teamName, League& league)
{
	//if exist- return index, not exist - return -1.
	int indexToDelete = teamExist(teamName, league);
	if (indexToDelete == -1)
	{
		cout << " " << teamName << " does not exist in the database.\n";
		delete[] teamName;
		return;
	}
	//compare pointer to team from the player in this team to NULL
	deleteTeamFieldFromPlayer(indexToDelete, league);
	//delete team from LeagueTeamsArray
	int i;
	Team* temp;
	temp = league.LeagueTeamsArray;
	league.LeagueTeamsNumber--;
	league.LeagueTeamsArray = new Team[league.LeagueTeamsNumber];
	//copy the array without indexToDelete 
	for (i = 0; i < indexToDelete; i++)
	{
		league.LeagueTeamsArray[i] = temp[i];
	}
	for (; i < league.LeagueTeamsNumber; i++)
	{
		league.LeagueTeamsArray[i] = temp[i + 1];
	}
	delete[] temp[indexToDelete].TeamName;
	delete[] temp[indexToDelete].PlayersOfTheTeam;
	delete[] temp;
	//if there are not Teams in league
	if (league.LeagueTeamsNumber == 0)
	{
		delete[] league.LeagueTeamsArray;
		league.LeagueTeamsArray = NULL;
	}
	cout << teamName << " team has been deleted from the database.\n";
	delete[] teamName;
}


/***********************************************************************************
* Function name: deletePlayerFromTeam
* Input: int indexToDelete
* Output:  void
* Function Operation: if there are not players in the team-return. else- delete player from the team data base.
***********************************************************************************/
void deletePlayerFromTeam(int indexToDelete, League& league)
{
	//for easy read(next 2 lines):
	Player* playerToDel = &league.LeaguePlayersArray[indexToDelete];
	Team* oldTeamOfPlayer = league.LeaguePlayersArray[indexToDelete].TeamOfThePlayer;
	//if there are not players in the team - return
	if (oldTeamOfPlayer != NULL)
	{
		int s, r;
		oldTeamOfPlayer->TeamPlayersCounter--;
		//add player price to team account
		oldTeamOfPlayer->TeamAccount += playerToDel->PlayerPrice;//dsfsda
		// delete the player from the team
		Player** temp;
		temp = oldTeamOfPlayer->PlayersOfTheTeam;
		oldTeamOfPlayer->PlayersOfTheTeam = new Player * [oldTeamOfPlayer->TeamPlayersCounter];
		for (s = 0, r = 0; s < oldTeamOfPlayer->TeamPlayersCounter; s++, r++)
		{
			if (temp[s] == playerToDel)
			{
				r++;
				//in the next command we will skip the player we want to delete
			}
			oldTeamOfPlayer->PlayersOfTheTeam[s] = temp[r];
		}
		//if there are not players in team
		if (0 == oldTeamOfPlayer->TeamPlayersCounter)
		{
			delete[] oldTeamOfPlayer->PlayersOfTheTeam;
			oldTeamOfPlayer->PlayersOfTheTeam = NULL;
		}
		league.LeaguePlayersArray[indexToDelete].TeamOfThePlayer = NULL;
		delete[] temp;
	}
}


/***********************************************************************************
* Function name: deletePlayerFromTeam
* Input: int indexToDelete
* Output:  void
* Function Operation: if there are not players in the team-return. else- delete player from the team data base.
***********************************************************************************/
void deletePlayer(char* playerName, League& league)
{
	//if exist- return index, not exist - return -1.
	int indexToDelete = playerExist(playerName, league);
	if (indexToDelete == -1)
	{
		cout << playerName << " does not exist in the database.\n";
		delete[] playerName;
		return;
	}
	//compare pointer to this player from his team to NULL
	deletePlayerFromTeam(indexToDelete, league);
	//copy the array without indexToDelete 
	int i = 0;
	Player* tempPlayersArray;
	tempPlayersArray = league.LeaguePlayersArray;
	league.LeaguePlayersNumber--;
	league.LeaguePlayersArray = new Player[league.LeaguePlayersNumber];
	for (i = 0; i < indexToDelete; i++)
	{
		league.LeaguePlayersArray[i] = tempPlayersArray[i];
	}
	for (; i < league.LeaguePlayersNumber; i++)
	{
		league.LeaguePlayersArray[i] = tempPlayersArray[i + 1];
	}
	//if there are not players in league
	if (0==league.LeaguePlayersNumber)
	{
		delete[] league.LeaguePlayersArray;
		league.LeaguePlayersArray = NULL;
	}
	cout << playerName << " has been deleted from the database.\n";
	delete[] tempPlayersArray[indexToDelete].PlayerName;
	delete[] tempPlayersArray[indexToDelete].TeamOfThePlayer;
	delete[] tempPlayersArray;
	delete[] playerName;
}


/***********************************************************************************
* Function name: playerRecommendations
* Input: char* teamName(pointer to string), League& league
* Output:  void
* Function Operation: check which player the team can buy and print him.
***********************************************************************************/
void playerRecommendations(char* teamName, League& league)
{
	//if exist- return index, not exist - return -1.
	int teamIndex = teamExist(teamName, league);
	if (teamIndex == -1)
	{
		cout << "Team " << teamName << " does not exist in the database.\n";
		delete[] teamName;
		return;
	}
	//if there are not players in the league
	if (league.LeaguePlayersArray == NULL)
	{
		cout << "There are not player in the league\n";
		delete[] teamName;
		return;
	}
	bool printedFirstNote = false;
	bool canBuy = false;
	//print by 'for' loop the relevant players to buy
	for (int j = 0; j < league.LeaguePlayersNumber; j++)
	{
		if (league.LeagueTeamsArray[teamIndex].TeamAccount >= league.LeaguePlayersArray[j].PlayerPrice)
		{
			if (!printedFirstNote)
			{
				printedFirstNote = true;
				canBuy = true;
				cout << "The players " << teamName << " can acquire: " << endl;
			}
			cout << league.LeaguePlayersArray[j].PlayerName << endl;
		}
	}
	//if there are not relevant players to buy this team
	if (!canBuy)
	{
		cout << "Team " << teamName << " is unable to afford any players in the database." << endl;
	}
	delete[] teamName;
	return;
}


/***********************************************************************************
* Function name: buyPlayer
* Input: char* playerName(pointer to string), char* teamName(pointer to string), League& league
* Output:  void
* Function Operation: check if player and team exist, if player is not already in the team,
					  if team has enough money.
					  delete the player from old team and add player to new team.
***********************************************************************************/
void buyPlayer(char* playerName, char* teamName, League& league)
{
	//if exist- return index, not exist - return -1.
	int teamIndex = teamExist(teamName, league);
	int playerIndex = playerExist(playerName, league);
	if (playerIndex == -1)
	{
		cout << playerName << " does not exist in the database.\n";
		delete[] playerName;
		delete[] teamName;
		return;
	}
	if (teamIndex == -1)
	{
		cout << "Team " << teamName << " does not exist in the database.\n";
		delete[] playerName;
		delete[] teamName;
		return;
	}
	//if player already in team
	if (IsPlayerInTeam(playerName, teamName, playerIndex,league))
	{
		cout << "error: player already in the team\n";
		delete[] playerName;
		delete[] teamName;
		return;
	}
	//for easy read:(next two lines):
	Player* thisPlayer = &league.LeaguePlayersArray[playerIndex];
	Team* thisTeam = &league.LeagueTeamsArray[teamIndex];
	//if team does not has enough money
	if (thisPlayer->PlayerPrice > thisTeam->TeamAccount)
	{
		cout << "error: team doesn't have enough money to buy this player\n";
		delete[] playerName;
		delete[] teamName;
		return;
	}
	//delete from original team 
	deletePlayerFromTeam(playerIndex, league);
	//Add player to new team
	//copy old list to the new array
	thisTeam->TeamPlayersCounter++;
	thisTeam->TeamAccount -= thisPlayer->PlayerPrice;
	Player** tempTeamPlayers = thisTeam->PlayersOfTheTeam;
	thisTeam->PlayersOfTheTeam =new Player * [thisTeam->TeamPlayersCounter];
	for (int i = 0; i < thisTeam->TeamPlayersCounter - 1; i++)
	{
		thisTeam->PlayersOfTheTeam[i] = tempTeamPlayers[i];
	}
	//add new player to the new array
	thisTeam->PlayersOfTheTeam[thisTeam->TeamPlayersCounter - 1] = thisPlayer;
	delete[] tempTeamPlayers;
	//change player's field - playerTeam
	thisPlayer->TeamOfThePlayer = thisTeam;
	cout << playerName << " has been added to the " << teamName << " team.\n";
	cout << teamName << " remaining budget: " << league.LeagueTeamsArray[teamIndex].TeamAccount << "\n";
	delete[] playerName;
	delete[] teamName;
}


/***********************************************************************************
* Function name: teamExist
* Input: char* teamName(pointer to string), League& league
* Output:  void
* Function Operation: if exist return index in array. if not - return -1
***********************************************************************************/
int teamExist(char* teamName, League& thisLeague)
{
	//if there are not teams in the league
	if (thisLeague.LeagueTeamsArray == NULL)
	{
		return -1;
	}
	//try to find team index in array 
	for (int i = 0; i < thisLeague.LeagueTeamsNumber; i++)
	{
		//if find - return index
		if (strcmp(teamName, thisLeague.LeagueTeamsArray[i].TeamName) == 0)
		{
			return i;
		}
	}
	//if not find
	return -1;
}


/***********************************************************************************
* Function name: playerExist
* Input: char* playerName(pointer to string), League& league
* Output:  void
* Function Operation: if exist return index in array. if not - return -1
***********************************************************************************/
int playerExist(char* playerName, League& thisLeague)
{
	//if there are not players in the league
	if (thisLeague.LeaguePlayersArray == NULL)
	{
		return -1;
	}
	//try to find player index in array
	for (int i = 0; i < thisLeague.LeaguePlayersNumber; i++)
	{
		//if find - return index
		if (strcmp(playerName, thisLeague.LeaguePlayersArray[i].PlayerName) == 0)
		{
			return i;
		}
	}
	//if not find
	return -1;
}


/***********************************************************************************
* Function name: removePlayer
* Input: char* playerName(pointer to string), char* teamName(pointer to string), League& league
* Output:  void
* Function Operation: get team and player index, check if the player in team,
					  remove the player from the team.
***********************************************************************************/
void removePlayer(char* playerName, char* teamName, League& league)
{
	//if exist return index in array. if not - return -1
	int playerIndex = playerExist(playerName, league);
	int teamIndex = teamExist(teamName, league);
	if (playerIndex==-1) 
	{
		cout << playerName << " does not exist in the database.\n";
		delete[] playerName;
		delete[] teamName;
		return;
	}
	if (teamIndex == -1)
	{
		cout << "Team " << teamName << " does not exist in the database.\n";
		delete[] playerName;
		delete[] teamName;
		return;
	}
	// if the player is not in team
	if (!IsPlayerInTeam(teamName, playerName, playerIndex, league))
	{
		cout << "No player named " << playerName << " on " << teamName << " team.\n";
		delete[] playerName;
		delete[] teamName;
		return;
	}
	//delete player from team player list
	deletePlayerFromTeam(playerIndex, league);
	//compere player's pointer to his team to NULL
	league.LeaguePlayersArray[playerIndex].TeamOfThePlayer = NULL;
	cout << playerName << " has been removed from the " << teamName << " team.\n";
	delete[] playerName;
	delete[] teamName;
}


/***********************************************************************************
* Function name: IsPlayerInTeam
* Input: char* teamName(pointer to string), char* playerName(pointer to string),
		 int playerIndex(index of player int 'LeaguePlayersArray'), League& thisLeague
* Output:  void
* Function Operation: if player in the team return true, else- false.
***********************************************************************************/
bool IsPlayerInTeam(char* teamName, char* playerName, int playerIndex, League& thisLeague)
{
	//for easy read:
	Team* teamOfPlayer = thisLeague.LeaguePlayersArray[playerIndex].TeamOfThePlayer;
	//if the player does not has a taem
	if (teamOfPlayer == NULL)
	{
		return false;
	}
	//if player in team('teamName'-input)
	if (strcmp(teamOfPlayer->TeamName, teamName) == 0)
	{
		return true;
	}
	//if player is not in team('teamName'-input)
	return false;
}


/***********************************************************************************
* Function name: printPlayersByPrice
* Input: League& thisLeague
* Output:  void
* Function Operation: print the players in order by price(cheapest to most expensive)
					  side effect, order the 'LeaguePlayersArray' in this order.
***********************************************************************************/
void printPlayersByPrice(League& league)
{
	//for easy read(next line):
	Player* playersArrayPrint = league.LeaguePlayersArray;
	Player temp;
	//if there are not players in the league
	if (league.LeaguePlayersNumber == 0)
	{
		cout << "The league doesn't have players\n";
		return;
	}
	//order and print
	cout << "Player Budget\n";
	int min;
	for (int i = 0; i < league.LeaguePlayersNumber; i++)
	{
		min = i;
		for (int j = i; j < league.LeaguePlayersNumber; j++)
		{
			if (playersArrayPrint[min].PlayerPrice > playersArrayPrint[j].PlayerPrice)
			{
				min = j;
			}
		}
		temp = playersArrayPrint[min];
		playersArrayPrint[min] = playersArrayPrint[i];
		playersArrayPrint[i] = temp;
		cout << playersArrayPrint[i].PlayerName << " " << playersArrayPrint[i].PlayerPrice << "\n";
	}
}


/***********************************************************************************
* Function name: printTeamsByBudget
* Input: League& thisLeague
* Output:  void
* Function Operation: print the Team in order by budget(smallest to biggest)
					  side effect, order the 'LeagueTeamsArray' in this order.
***********************************************************************************/
void printTeamsByBudget(League& league)
{
	//for easy read(next line):
	Team* TeamssArrayPrint = league.LeagueTeamsArray;
	Team temp;
	//if there are not players in the league
	if (league.LeagueTeamsNumber == 0)
	{
		cout << "The league doesn't have Teams\n";
		return;
	}
	// order and print
	cout << "Team Budget\n";
	int min;
	for (int i = 0; i < league.LeagueTeamsNumber; i++)
	{
		min = i;
		for (int j = i; j < league.LeagueTeamsNumber; j++)
		{
			if (TeamssArrayPrint[min].TeamAccount > TeamssArrayPrint[j].TeamAccount)
			{
				min = j;
			}
		}
		temp = TeamssArrayPrint[min];
		TeamssArrayPrint[min] = TeamssArrayPrint[i];
		TeamssArrayPrint[i] = temp;
		cout << TeamssArrayPrint[i].TeamName << " " << TeamssArrayPrint[i].TeamAccount << "\n";
	}
}


/***********************************************************************************
* Function name: printTeamPlayers
* Input: League& thisLeague
* Output:  void
* Function Operation: print the players of the team
***********************************************************************************/
void printTeamPlayers(char* teamName, League& league)
{
	//if exist- return index, not exist - return -1.
	int teamIndex = teamExist(teamName, league);
	if (teamIndex == -1)
	{
		cout << "Team " << teamName << " does not exist in the database.\n";
		delete[] teamName;
		return;
	}
	//next line for easy read:
	int teamPlayerNumber = league.LeagueTeamsArray[teamIndex].TeamPlayersCounter;
	//if there are not teams in the league
	if (teamPlayerNumber == 0)
	{
		cout << "Team " << teamName << " does not  have players.\n";
		return;
	}
	//next line for easy read:
	Player** teamsPlayers = league.LeagueTeamsArray[teamIndex].PlayersOfTheTeam;
	//print players
	cout << "The players on the " << teamName << " Team:\n";
	for (int i = 0; i < teamPlayerNumber; i++)
	{
		cout << teamsPlayers[i]->PlayerName << "\n";
	}
	delete[] teamName;
}


/***********************************************************************************
* Function name: deleteInTheEnd
* Input: League& thisLeague
* Output:  void
* Function Operation: delete all league field at the end of the program
***********************************************************************************/
void deleteInTheEnd(League& league)
{
	//delete all players include player's field
	for (int i = 0; i < league.LeaguePlayersNumber; i++)
	{
		league.LeaguePlayersArray[i].TeamOfThePlayer = NULL;
		delete[] league.LeaguePlayersArray[i].TeamOfThePlayer;
		delete[] league.LeaguePlayersArray[i].PlayerName;
	}
	//delete all Teams include team's field
	for (int i = 0; i < league.LeagueTeamsNumber; i++)
	{
		delete[] league.LeagueTeamsArray[i].PlayersOfTheTeam;
		delete[] league.LeagueTeamsArray[i].TeamName;
	}
	//delete arrays in league
	delete[] league.LeaguePlayersArray;
	delete[] league.LeagueTeamsArray;
	//delete league
	delete& league;
}


/***********************************************************************************
* Function name: deleteInTheEnd
* Input: int teamIndex, int newBudget, League& league
* Output:  void
* Function Operation: change the Team account for specific team.
***********************************************************************************/
void changeTeamAccount(int teamIndex, int newBudget, League& league)
{
	league.LeagueTeamsArray[teamIndex].TeamAccount = newBudget;
}