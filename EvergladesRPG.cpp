/**
Lost in the Everglades in an RPG(Role - Playing - Game) between a playerand the computer.

A group of tourists has been lost in the Evergladesand a ranger must rescue them before time runs out.

The Everglades are represented by a 5x5 matrix.The ranger(R) starts the rescue at the upper - left corner of the park, the group of tourists(T) are lost at the lower - right corner.The ranger has 12 gongs of time to find and rescue the tourists before they perish.

During the journey, the ranger might find dangers(hungry alligator, swarm of giant mosquitoes, venomous spider, or python).

When the ranger finds a danger, they can choose to fight them, or hide and wait for them to leave.
**/

#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <iomanip>

using namespace std;

// Function Prototypes
void showInstructions();
void showMenu();
int determineThreat(int &);
int threatMove(int);

// Main function
int main()
{
	// Constants and variables
	int choice;		//menu choice
	const int INSTRUCTIONS = 1,	//instructions choice
		PLAY = 2,				//play choice
		QUIT = 3;				//quit choice
	const int rows = 5,			//number of rows and collumns
		collumns = 5;
	string grid[rows][collumns];
	int lcollumns,
		lrows;
	int gongs;

	
	do
	{
		// Display menu and get user's choice.
		showMenu();
		cin >> choice;

		switch (choice)
		{
				case INSTRUCTIONS:
					showInstructions();
					break;
													
				case PLAY:
					gongs = 12;

					cout << "\nLost in the Everglades ... \n";
					cout << "\nSAVE THE LOST TOURISTS!!!\n\n";
					

					//inside the do loop
					int row=0,
						collumn=0;
					
					// Start the game
					do
					{

						//display grid
						cout << "       0     1     2     3     4\n";
						for (lcollumns = 0; lcollumns < collumns; lcollumns++)
						{
							cout << " " << lcollumns << " ";

							for (lrows = 0; lrows < rows; lrows++)
							{
								grid[lrows][lcollumns] = " *";

								grid[4][4] = " T";

								grid[row][collumn] = " R";
																
								cout << " | " << grid[lrows][lcollumns] << " ";

							}
							cout << " | \n";
						}
						
						// prompt user for cell move
						cout << "\nEnter next cell (row & col): ";
						cin >> row >> collumn;

						int THREAT = 1,
							NOTHING = 2;

						// determine if Threat or Nothing
						random_device torn;
						uniform_int_distribution<int> roll(THREAT, NOTHING);
															

						if (roll(torn) == THREAT) // THREAT
						{

							int threatType;
							int move = 0;

							// Threats parallel arrays
							string dangerName[] = { "Hungry Alligator", "Swarm of Giant Mosquitos", "Venomous Spider", "Python" };
							char dangerFill[] = { 'A','M','S','P' };

							determineThreat(threatType);			
												
							cout << " ---> Watch out! There is a " << dangerName[threatType] << endl << endl;
	
							//modification
							grid[row][collumn] = dangerFill[threatType];
							
							// user choice on threat
							move = threatMove(move);
																					
							if (move == 1)			//Wait
							{
								//move to desired cell
								grid[row][collumn] = " R";
								grid[row - 1][collumn - 1] = " ";
								
								//gong count
								gongs = gongs - 5;

								cout << "\n ---> " << dangerName[threatType] << " is gone ... You Advance!\n";
							}
							else if (move == 2)		//FIGHT IT
							{
								int WIN = 1;
								int LOSE = 2;

								random_device oneortwo;
								uniform_int_distribution<int> WorL(WIN, LOSE);

								int decision = WorL(oneortwo);

								if (WorL(oneortwo) == 1)		//fight and win
								{
									//move to desired cell
									grid[row][collumn] = " R";
									grid[row - 1][collumn - 1] = " ";
									//gong count
									gongs = gongs - 2;

									cout << "You fight the " << dangerName[threatType] << " and win ... You Advance!\n";
								}
								else	//fight and loose
								{
									//go back to initial cell
									grid[row][collumn] = dangerFill[threatType];
									grid[row - 1][collumn - 1] = " ";
									grid[row][collumn] = grid[row-1][collumn - 1];
																		
									cout << "You fight the " << dangerName[threatType] << " and loose ... Retreat!\n";

									//gong count
									gongs = gongs - 3;
								}
							}


						}

						if (roll(torn) == NOTHING)	// NOTHING
						{
							cout << "\nCell (" << row << "," << collumn << ") is Free ... You Advance!\n";
							//gong count
							gongs -= 1;
							grid[row][collumn] = " R";
							
						}
					
						// Display gongs
						cout << "\nGongs Left: " << gongs << endl << endl;

						// check if game end
						if (row == 4 and collumn == 4 or gongs == 0 or gongs < 0)
						{
							cout << " --------------------------------------------------------------------";
							cout << "\n|THE TOURISTS HAVE BEEN SAVED! WELL DONE, AND THANK YOU FOR PLAYING!|\n";
							cout << " --------------------------------------------------------------------";
							break;
						}

						
					} while (grid[4][4] != " R" or gongs != 0 or gongs < 0);
					
			
		}
	} while (choice != QUIT);
	
	return 0;
}

void showInstructions()
{
	cout << "\nINSTRUCTIONS: " << endl
		<< "- A group of tourists (T) has been lost in the everglades!\n- The ranger (R) must rescue the Tourists, before time runs out.\n"
		<< "- The ranger will have 12 GONGS of time to find and rescue the tourists before they perish.\n"
		<< "- During the journey, the ranger might find dangers (hungry alligator, swarm of giant mosquitoes, venomous spider, or python).\n"
		<< "- When the ranger finds ranger, they can choose to FIGHT, or HIDE AND WAIT for them to leave.\n"
		<< "- If the Ranger waits: \n\t+ Moves to the desired cell\n\t+ Looses 5 gongs of time\n"
		<< "- If the Ranger FIGHTS and WINS: \n\t+ Moves to the desired cell\n\t+ Looses 2 gongs of time\n"
		<< "- If the Ranger FIGHTS and LOSES: \n\t+ Goes back to the initial cell\n\t+ Looses 3 gongs of time\n\t+ The danger remains in the cell\n"
		<< "- If the Ranger moves to a cell with NO DANGER: \n\t+ Looses 1 gong of time"
		<< "- The game ENDS when: \n"
		<< "\t+ The Ranger RESCUES the group of Tourists\n"
		<< "\t+ The TIME EXPIRES and the fate of the tourists is forever unknown!" << endl;
}

void showMenu()
{
	cout << "\n\nWELCOME TO THE EVERGLADES ... \n" << endl;
	cout << "Ready to play the game?\n";
	cout << "\t1. See Rules\n"
		<< "\t2. Play Game\n"
		<< "\t3. Quit\n";
	cout << "Choice: ";
}

int determineThreat(int &threatType)
{
	// Threat calculator
	const int MIN = 0;
	const int MAX = 3;

	random_device engine;
	uniform_int_distribution<int> threatValue(MIN, MAX);

	threatType = threatValue(engine);

	return threatType;
}

int threatMove(int move)
{
	cout << "Choose your next move\n"
		<< "\t1. Wait until it leaves.\n"
		<< "\t2. FIGHT IT.\n";
	cout << "Move: ";
	cin >> move;

	return move;
}
