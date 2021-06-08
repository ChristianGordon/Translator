#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;


//=================================================
// File translator.cpp
//=================================================


ofstream outFile;

//Global decleration of functions
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();


//=====================================================
// File scanner.cpp 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA
// RE:(vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+
bool word (string s)
{
  int state = 0; //start state 0 is q0
  int charpos = 0;//character position in string

  while(s[charpos] != '\0')//while not at the end of string
    {
      //initial transitions from state 0 or q0
      if(state == 0 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
        state = 1; //state 1 is q0q1
      else if(state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
        state = 4; //state 4 is qy
      else if(state == 0 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
        state = 5; //state 5 is qsa
      else if(state == 0 && s[charpos] == 'c')
        state = 3; //state 3 is qc
      else if(state == 0 && s[charpos] =='s')
        state = 6; //state 6 is qs
      else if(state == 0 && s[charpos] == 't')
        state = 7; //state 7 is qt

      //transitions from state 1 or q0q1
      else if(state == 1 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
        state = 4; //state 4 is qy
      else if(state == 1 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
        state = 5; //state 5 is qsa
      else if(state == 1 && s[charpos] == 'c')
	state = 3; //state 3 is qc
      else if(state == 1 && s[charpos] == 's')
        state = 6; //state 6 is qs
      else if(state == 1 && s[charpos] == 't')
        state = 7; //state 7 is qt
      else if(state == 1 && s[charpos] == 'n')
        state = 2;//state 2 is q0qy
      else if(state == 1 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
        state = 1; //account for the loop on q0q1

      //transitions from state 2 or q0qy
      else if(state == 2 && (s[charpos] == 'b' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
        state = 4; //state 4 is qy
      else if(state == 2 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
        state = 5; //state 5 is qsa
      else if(state == 2 && s[charpos] == 'c')
        state = 3; //state 3 is qc
      else if(state == 2 && s[charpos] == 's')
        state = 6; //state 6 is qs
      else if(state == 2 && s[charpos] == 't')
        state = 7; //state 7 is qt
      else if(state == 2 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
        state = 1;

      //to get from qsa, qy, qs, and qt back to q0q1
      else if(state == 5 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
        state = 1;
      else if(state == 4 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
        state = 1;
      else if(state == 7 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
        state = 1;
      else if(state == 6 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
        state = 1;

      //the different characters that can get to qsa
      else if(state == 3 && s[charpos] == 'h')
        state = 5;
      else if(state == 6 && s[charpos] == 'h')
        state = 5;
      else if(state == 7 && s[charpos] == 's')
        state = 5;
      else if(state == 4 && s[charpos] == 'y')
        state = 5;

      //returns false if no character fits any definition
      else
        return (false);
      charpos++;
    }
  //Check if we ended in a final state (q0, q0q1, q0qy)
  if(state == 0 || state == 1 || state == 2)
    return(true);
  else return(false);

}

// PERIOD DFA
// RE: .
bool period (string s)
{  // check if the character is a period and return true if it is
  if(s == ".")
    return (true);
  else
    return(false);
}

// ------ Three  Tables -------------------------------------


// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, SUBJECT, OBJECT, DESTINATION, PRONOUN, CONNECTOR};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "SUBJECT", "OBJCT", "DESTINATION", "PRONOUN", "CONNECTOR" };

// ** Need the reservedwords table to be set up here.
string reservedWords[30] = {"masu", "masen", "mashita", "masendeshita", "desu", "deshita", "o", "wa", "ni", "watashi", "anata", "kare", "kanojo", "sore", "mata", "soshite", "shikashi", "dakara", "eofm"};


//Array maps to the reserved words array. Order matters
string wordType[30] = {"VERB","VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS","OBJECT","SUBJECT","DESTINATION","PRONOUN","PRONOUN","PRONOUN","PRONOUN","PRONOUN","CONNECTOR","CONNECTOR","CONNECTOR","CONNECTOR","EOFM"};



//global varaibles
string function;
bool repeat = false;


string saved_lexeme;
bool  token_available = false;
tokentype saved_token;

string savedEword;
//Table for translation
vector<string> wordJ ;
vector <string> wordE ;

// ------------ Scanner and Driver -----------------------

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself

void scanner(tokentype& saved_token, string& wordFromFile)
{
  int count = -1;
  fin>>wordFromFile;//grabs word form file and stores into wordFromFile
  if(wordFromFile == "eofm"){//if word = eofm
    cout<<"Scanner called using word: "<<wordFromFile<<endl; //print the word
    cout<<endl; // new line
    cout<<"Successfully parsed <story>.\n" <<endl;
    exit(1); //end of the file so stop
  }
  else if(word(wordFromFile))//if not eofm
    {
      for(int i = 0; i < 19; i++) //loop through reserved words array
        {
          if(reservedWords[i] == wordFromFile)//compares each word in array with pulled word
            count = i;//increments count if word is reserved
        }
      if(count < 0)//if no words pulled were reserved word
        {
          if(wordFromFile[wordFromFile.size()-1] == 'I' || wordFromFile[wordFromFile.size()-1] == 'E')//if the last token of word is I or E
	    saved_token = WORD2;//set token to WORD2
          else
            saved_token = WORD1;//set token to WORD1
        }
      else if(count == 0)//masu
        saved_token = VERB;
      else if(count == 1)//masen
        saved_token = VERBNEG;
      else if(count == 2)//mashita
        saved_token = VERBPAST;
      else if(count == 3)//masendeshita
        saved_token = VERBPASTNEG;
      else if(count == 4)//desu
        saved_token = IS;
      else if(count == 5)//deshita
        saved_token = WAS;
      else if(count == 6)//o
        saved_token = OBJECT;
      else if(count == 7)//wa
        saved_token = SUBJECT;
      else if(count == 8)//ni
        saved_token = DESTINATION;
      else if(count == 9 || count == 10 || count == 11 || count == 12 || count == 13)//watashi, Anita, Kare, kanoio, sore
	saved_token = PRONOUN;
      else if(count == 14 || count == 15 || count == 16 || count == 17)//mata, soshite, shikashi, Dakara
        saved_token = CONNECTOR;
    }
  else if(period(wordFromFile))//if word is a period
    saved_token = PERIOD;
  else//if there are no matching reserved words
    {
      cout<<"Scanner called using word: "<<wordFromFile<<endl; //print the word we are scanning
      cout <<"\nLexical error: " << wordFromFile << " is not a valid token" << endl; //print error message
      saved_token = ERROR; //tokentype is error
    } //end of else
  count = -1;  //reset the counter
  saved_lexeme = wordFromFile;//when saved_token is updated, saved_lexeme = the string returned from scanner function
} //end of scanner


//Function getEword: takes the current saved lexeme and checks it against the translation table  
void getEword()
{
  bool found = false; //sets bool to false
  for(int a =0;a< wordJ.size(); a++) //loops through saved translated word
    {
      if(wordJ[a]==saved_lexeme) //compares each letter to lexeme 
        {
          savedEword = wordE[a]; //if word is lexeme adds it to vector E
          found = true; //sets bool to true
        }
    }
  if(found == false) //if lexeme is NOT found
    {savedEword = saved_lexeme;} //changes word to lexeme

}

//Function gen: generates a file output based on our saved line and our token or savedEword      
void gen(string line_type)
{
  if(line_type == "TENSE") //If internal rep is "TENSE"
    {outFile<< line_type<< "  "<< tokenName[saved_token] <<endl;} //writes it to file with saved_token
  else{
    outFile<< line_type<< "  "<< savedEword <<endl; //else, wrate it with saved E word
  }
}


//=================================================
// File parser.cpp 
//=================================================

ofstream errorfile;
string EC;

void syntax_error1(tokentype expected)
{//throws error if lexeme is found rather than token
  cout<<"SYNTAX ERROR: expected "<< tokenName[expected]  << " but found "<<  saved_lexeme <<endl;
  //exit (1); //halting
  
}

void syntax_error2(string parserFunct, string saved_lexeme)
{//throws error if lexeme is found in parser
  cout<<"SYNTAX ERROR: unexpected "<< saved_lexeme << " found in "<< parserFunct <<endl;
  exit (1); //halting
}

// ** Need the updated match and next_token (with 2 global vars)

tokentype next_token()
{
  if (!token_available) // if there is no saved token yet
    {
      scanner(saved_token, saved_lexeme); // call scanner to grab a new token
      cout<<"Scanner called using word: "<< saved_lexeme <<endl;
      token_available = true; // mark that fact that you have saved it
    }
  return saved_token;    // return the saved token
}

bool match(tokentype expected)
{
  if (next_token() != expected)
    {
      syntax_error1(expected); // call syntax error1 message
      //EC part: to skip token or assume correct token was there
      if (errorfile.is_open()) {
        errorfile << "SYNTAX ERROR: expected " << tokenName[expected] << " but found " <<
          saved_lexeme << "\n";
      }
      cout << "Skip or replace the token? (s or r) ";
      cin >> EC;
      if (EC == "s") { // skip a token, check if next token is matched expected
        token_available = false;
        match(expected);
      }
      else if (EC == "r") {// replace a token, assume it is matched expected
        token_available = false;
        cout << "Matched " << tokenName[expected] << endl;
      }
    }
  else
    {
      token_available = false;
      cout << "Matched " << tokenName[expected] << endl;
      return true;
    }
}


// ----- RDP functions - one per non-term -------------------

//Grammar:<story> ::= <s>{<s>}
void story()
{
  cout<<"Processing <story>"<<endl;
  s();          
  //while()  call more s()
  while (true && (saved_lexeme != "eofm"))     
    { //loop while not at end of file and can continue to parse
      outFile<<endl;
      s();
    }
  cout<<"\nSuccessfully parsed story"<<endl;
}

//Grammar:<s> ::= [CONNECTOR #getEword# #gen("CONNECTOR")]<noun> #getEword# SUBJECT #gen("ACTOR")<after subject>
void s()
{
  next_token();
  if(saved_lexeme != "eofm")           
    { //while not at end of file
      cout<<"Processing <s>"<<endl;

      if(next_token() == CONNECTOR)    
        { //If token is a connector
          match(CONNECTOR); //call match to check for expected token
          getEword(); //checks current lexeme and compares to translation table
          gen("CONNECTOR"); //generates a file output based on connector and our token
        }

      noun(); //processes noun
      match(SUBJECT); //call match to check for expected token
      gen("ACTOR"); //generates a file output based on actor and our token
      afterSubject(); //generates a tense to word
    }
}

//Grammar:<noun> ::= WORD1|PRONOUN
void noun()
{
  cout<<"Processing <noun>"<<endl;
  switch(next_token()) // look ahead at next token
    {
    case  WORD1: //if noun
      match(WORD1); //saves for expected token
      getEword(); //checks lexeme against translator
      break;
    case  PRONOUN: //if pronoun
      match(PRONOUN); //svaes for expected token
      getEword(); //checks lexeme agianst translator
      break;
    default:
      syntax_error2(saved_lexeme, "noun"); // none of the alternatives found
    }
}

//Grammar: <after subject> ::= <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD | <noun> #getEword# <>after noun>                                                                             
void afterSubject()
{
  cout<<"Processing <afterSubject>"<<endl;

  switch(next_token()) // look ahead at next token
    {
    case  WORD2: //if verb
      verb();
      tense();
      match(PERIOD);    
      break;
    case  WORD1: //if noun
      noun();
      afterNoun();
      break;
    case PRONOUN: //if pronoun
      noun();
      afterNoun();
      break;
    default:
      syntax_error2(saved_lexeme, "afterSubject"); // none of the alternatives found
    }
}

//Grammar: <verb> ::= WORD2
void verb()
{
  cout<<"Processing <verb>"<<endl;

  switch(next_token()) // look ahead at next token
    {
    case  WORD2: //if verb
      match(WORD2); //saves expected token
      getEword(); //checks lexeme 
      gen("ACTION");
      break;
    default:
      syntax_error2(saved_lexeme, "verb");  // none of the alternatives found
    }
}

//Grammar: <be> ::= IS | WAS
void be()
{
  cout<<"Processing <be>"<<endl;
  gen("DESCRIPTION");
  switch(next_token()) // look ahead at next token
    {
    case  IS: //current tense
      match(IS);
      gen("TENSE");
      break;
    case  WAS: //past tense
      match(WAS);
      gen("TENSE");
      break;
    default:
      syntax_error2(saved_lexeme, "be");  // none of the alternatives found
    }
}

//Grammar:<after noun> ::= <be> #gen("DESCRIPTION")# #gen("TENSE")# PERIOD  | DESTINATION #gen("TO")#<verb> #getEword# #gen("ACTION")# <tense> #gen("Tense")# PERIOD | OBJECT #gen("OBJECT")# <after object\>
void afterNoun()
{
  cout<<"Processing <afterNoun>"<<endl;

  switch(next_token()) // look ahead at next token
    {
    case  IS: //current tense
      be();
      match(PERIOD); //saves expected token
      break;
    case  WAS: //past tense
      be();             
      match(PERIOD); //saves expected token
      break;
    case DESTINATION: //location
      match(DESTINATION); //saves expected token
      gen("TO"); //generates file output with TO and our token
      verb(); //checks verb
      tense(); //checks tense
      match(PERIOD); //saves expected token
      break;
    case OBJECT:        
      match(OBJECT); //saves expected token
      gen("OBJECT"); //genreates file output with Object and our token
      afterObject();
      break;
    default:
      syntax_error2(saved_lexeme, "afterNoun");  // none of the alternatives found
    }

}

//Grammar:<after object> ::= <verb> #getEword# #gen("ACTION")#<tense> #gen("TENSE")# PERIOD | <noun> #getEword# DESTINATION #gen("TO")# <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD     
void afterObject()
{
  cout<<"Processing <afterObject>"<<endl;

  switch(next_token())
    {
    case WORD2: //if verb
      verb();
      tense();
      match(PERIOD);
      break;    
    case WORD1: //if noun
      noun();
      match(DESTINATION);
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    case PRONOUN: //if pronoun
      noun();
      match(DESTINATION);
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    default:
      syntax_error2(saved_lexeme, "afterObject"); // none of the alternatives found
    }
}

//Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
void tense()
{
  cout<<"Processing <tense>"<<endl;

  switch(next_token()) // look ahead at next token
    {
    case  VERBPAST: //verb in past tense
      match(VERBPAST); //saves verb and token tense
      gen("TENSE");
      break;
    case  VERBPASTNEG: //verb in present tense
      match(VERBPASTNEG); //saves verb and token tense
      gen("TENSE");
      break;    
    case  VERB: //verb
      match(VERB); //saves verb and token tense
      gen("TENSE");
      break;
    case  VERBNEG: //verb future tense
      match(VERBNEG); //saves verb and token tense
      gen("TENSE");
      break;
    default:
      syntax_error2(saved_lexeme, "tense"); // none of the alternatives found
    }
}


// -------------------------------------------
// The final test driver to start the translator
// Done by  Christian/Luis/Nineveh
int main()
{
  //** opens the lexicon.txt file and reads it in
  ifstream input;
  //strings to store words in file
  string tJ;
  string tE;
  //opens lexicon file
  input.open("lexicon.txt");
  cout<<"opening file"<<endl;

  while(input) //while there are words left in file
    {
      
      input>> tJ; //store first word in tJ
      input>> tE; //store second word in tE
      wordJ.push_back(tJ); //push first word into stack
      wordE.push_back(tE); //push second word into different stack
    }

  input.close(); //closes lexicon.txt
  //opens the output file translated.txt
  outFile.open("translated.txt");

  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str()); //open file of user input
 
  //Syntax EC: write error messages to errors.txt file
  cout << "Do you want to trace error messages? (y or n)";
  cin >> EC;
  if (EC == "y") {
    errorfile.open("errors.txt", ios::app);
  }
  //calls the <story> to start parsing
  story();
  //closes the input file
  errorfile.close();
  fin.close();
  //closes translated.txt
  outFile.close();
}// end
