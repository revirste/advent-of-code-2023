// 6/27/2024
// Figure out why CurrentRoundIsPossible() is behaving weird when it comes to detecting the ';' vs the ',' to determine
// the current round draw.
// WIP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_CUBES_RED = 12;
const int MAX_CUBES_BLUE = 13;
const int MAX_CUBES_GREEN = 14;

int gameNumber = 0;
bool currentGameStatus;


// pass in: "1 green, 6 red, 4 blue;"
bool CurrentRoundIsPossible(string currentRound) {
    bool IsGamePossible = true;
    int firstDigitPos;
    int nextCommaPos;
    int nextSemicolonPos;
    int nextPunctuationPos;
    string currentCubeDraw;

    // find out how many types of cubes were pulled
    int numRoundsPlayed = 0;
    for (int i = 0; i < currentRound.size(); ++i) {
        if ((currentRound.at(i) == ';') || (currentRound.at(i) == ',')) {
            ++numRoundsPlayed;
        }
    }


    for (int i = 0; i < numRoundsPlayed; ++i) {
    
        // find out where the first digit is and its relation to the next punctuation mark, putting that in a substr
        if (isdigit(currentRound.at(i))) {
            firstDigitPos = currentRound.find(currentRound.at(i));
            
            // find out the pos of the closest punctuation mark
            nextCommaPos = currentRound.find(',');
            nextSemicolonPos = currentRound.find (';');
            if (nextCommaPos < nextSemicolonPos) {
                nextPunctuationPos = nextCommaPos;
            }
            else {
                nextPunctuationPos = nextSemicolonPos;
            }

            // break out the current draw into its own substring so we can evaluate it
            if (nextPunctuationPos != string::npos) {
                currentCubeDraw = currentRound.substr(0, nextPunctuationPos);
            }
            else {
                currentCubeDraw = currentRound.substr(0, string::npos);
            }

        }

        // debug print statements
        std::cout << "(DEBUG) CURRENT ROUND: " << currentRound << std::endl;
        std::cout << "(DEBUG) CURRENT CUBE DRAW: " << currentCubeDraw << std::endl;
        std::cout << "(DEBUG) firstDigitPos: " << firstDigitPos << std::endl;
        std::cout << "(DEBUG) nextCommaPos: " << nextCommaPos << std::endl;
        std::cout << "(DEBUG) nextSemicolonPos: " << nextSemicolonPos << std::endl;
        std::cout << "(DEBUG) nextPunctuationPos: " << nextPunctuationPos << std::endl;



        currentRound = currentRound.substr(nextPunctuationPos + 1, string::npos);

        // is "red", "green" or "blue" in the current cube substr? If so, compare the number of items drawn to the threshold
        if (currentCubeDraw.find("red") != string::npos) {
            for (int i = 0; i < currentCubeDraw.length(); ++i) {
                if (isdigit(currentCubeDraw.at(i))) {
                    std::cout << "red has " << currentCubeDraw.at(i) << std::endl;
                    if (currentCubeDraw.at(i) > MAX_CUBES_RED) {
                        IsGamePossible = false;
                    }
                }
            }
        }
        if (currentCubeDraw.find("green") != string::npos) {
            for (int i = 0; i < currentCubeDraw.length(); ++i) {
                if (isdigit(currentCubeDraw.at(i))) {
                    std::cout << "green has " << currentCubeDraw.at(i) << std::endl;
                    if (currentCubeDraw.at(i) > MAX_CUBES_GREEN) {
                        IsGamePossible = false;
                    }
                }
            }
        }
        if (currentCubeDraw.find("blue") != string::npos) {
            for (int i = 0; i < currentCubeDraw.length(); ++i) {
                if (isdigit(currentCubeDraw.at(i))) {
                    std::cout << "blue has " << currentCubeDraw.at(i) << std::endl;
                    if (currentCubeDraw.at(i) > MAX_CUBES_BLUE) {
                        IsGamePossible = false;
                    }
                }
            }
        }
        std::cout << "###################################################" << std::endl;
    }
    
    return IsGamePossible;
}



void ParseCurrentGame(string inputGame) {
    string tempSubStr;
    bool IsGamePossible;

    // Trim the beginning of the string out
    int colonPos = inputGame.find(':');
    inputGame = inputGame.substr(colonPos + 2, string::npos);
    std::cout << inputGame << std::endl;


    // find out how many rounds were played
    int numRoundsPlayed = 0;
    for (int i = 0; i < inputGame.size(); ++i) {
        if (inputGame.at(i) == ';') {
            ++numRoundsPlayed;
        }
    }


   //for (int i = 0; i < numRoundsPlayed; ++i) {
        for (int i = 0; i < inputGame.size(); ++i) {
            if (isdigit(inputGame.at(i))) {            
                // Find the occurance of first digit and first semicolon. This will represent the current round of the current game.
                int firstDigitPos = inputGame.find(inputGame.at(i));
                int nextSemicolonPos = inputGame.find(';');

                // Trim this round off of the whole string, store in its own string so we can evaluate if its valid or not
                if (nextSemicolonPos != string::npos) {
                    tempSubStr = inputGame.substr(0, nextSemicolonPos + 1);
                }
                else {
                    tempSubStr = inputGame.substr(0, string::npos);
                }
                
                // Redeclare inputGame so that it trims off the substring that we just stored into tempSubStr, for further evaluation later
                inputGame = inputGame.substr(nextSemicolonPos + 1, string::npos);;

            
                if (CurrentRoundIsPossible(tempSubStr)) {
                   // std::cout << "This round is not possible! " << std::endl;
                }
                else {
                  //  std::cout << "This round is possbile! " << std::endl;
                }
            }
        }
    }
//}





int main() {
    ifstream GameFile("input.txt");
    string currentGame;
    
    while (GameFile.good() && (gameNumber < 1)) {
        gameNumber++;
        getline(GameFile, currentGame);
        ParseCurrentGame(currentGame);

        // if the current game is indeed possible, then add the current gameID to the running total
    }

    GameFile.close();
    return 0;
}