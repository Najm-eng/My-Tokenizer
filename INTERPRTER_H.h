#ifndef INTERPRTER_H
#define INTERPRTER_H

#include <cctype>             
#include <fstream>            
#include <iomanip>            
#include <iostream>           
#include <map>                
#include <sstream>            
#include <string>            
#include <cstdlib>
#include <stack>
 

using namespace std;

class Table_Row
{
	private:      
        bool isInit;         
        long long Value; 

	public:
        /* Constructor */
        Table_Row (bool isInitialized = false, long long Value = 0)
        {
            this -> isInit = isInitialized; 
            this -> Value = Value;
        }
		
        bool isInitialized (void) { return isInit; }
        
        long long getValue (void) { return Value; }
		
        void initialize (void) { isInit = true; }
        
        void setValue (long long Value) { this -> Value = Value; }
}; 


class Token
{
    private:       
        string name; 
        char type;   
    public:

        Token (char type = '0', string name = "")
        {
            this -> name = name;
            this -> type = type;
        }
	
        Token (const Token & t2)
        {
            this -> name = t2.name;
            this -> type = t2.type;
        }
        friend class Tokenizer;
	
        string getName (void) const { return name; }
    
        char getType (void) const { return type; }
};  


class Tokenizer
{
    private:
        long iter;                                  
        string code;                                
        long currLine;                              
        long currCol;                               
        string currLinestr;                         
        map<string, Table_Row>* Table; 

    public:

        Tokenizer (string fileName = "", map<string, Table_Row>* Table = 0)
        {
            this -> iter = -1;
            this -> currLine = 1;
            this -> currCol = -1;
            this -> Table = Table;
		   
            if (fileName != "")
            {
                int i = 0;
                while (fileName[i] == '\'' || fileName[i] == '"' || isspace(fileName[i]))
                {
                    fileName = fileName.substr(1);
                    i++;
                }
                
                i = fileName.length()-1;
                while (fileName[i] == '\'' || fileName[i] == '"' || isspace(fileName[i]))
                {
                    fileName = fileName.substr(0, fileName.length()-1);
                    i--;
                }
			   
                if (fileName.find(".txt") == string::npos)
                    fileName += ".txt"; 
  			   	  
                ifstream infile(fileName.c_str());
                cout << "\t" << fileName.c_str() << endl; 
                if (infile.is_open())
                {
            
                    code.assign ((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
                      
                    infile.close();
                    cout << endl << "The file " << endl
                         << "\t" << fileName << endl << "has successfully opened." 
                         << endl << endl << "Interpreting the code..." << endl << endl;
                }
                else
                    cout << endl << "Error: the file " << endl << "\t" << fileName << endl
                         << "whose you name you entered could not open." << endl;
            }
		   
            this -> currLinestr = this -> code;
        }    
		
    
        
        long getCurrLine (void) { return currLine; }
        
        long getCurrCol (void) { return currCol; }

        string getRemainingCode (void) { return currLinestr; }
		
     
        void next (Token& t1)
        { 
            iter++; 
            currCol++; 
            if (iter >= code.length())
                t1.type = '5'; 
            else
            {
                map<string, Table_Row>::iterator mapIter; 
			   	   
                while ((isspace(code[iter]) || code[iter] == 0) && iter < code.length())
                {
                    if (code[iter] == '\n')
                    {                   		
                        currLine++;
                        currCol = -1;            
                        currLinestr = currLinestr.substr(currLinestr.find("\n") + 1);
                    }
                    iter++;
                    currCol++;
                }
                               
                if (iter >= code.length())
                {
		   		   t1.type = '5'; 
                   return;
				}
				                  
                switch(code[iter])
                {
                    case '=':
                    case ';':
                    case '+':
                    case '-':
                    case '*':
                    case '(':
                    case ')': t1.type = '3'; 
                              t1.name = to_string(code[iter]);
                              break;
                    case '0': t1.type = '2'; 
                              break;
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9': t1.type = '2'; 
                              t1.name = ""; 
                              do
                              {
                                  t1.name += to_string(code[iter]);
                                  iter++;
                                  currCol++;
                              } while (iter < code.length() && isdigit(code[iter]));
                              iter--;
                              currCol--;
                              break;
                    case 'a':
                    case 'b':		
                    case 'c':	
                    case 'd':		
                    case 'e':
                    case 'f':		
                    case 'g':	
                    case 'h':	
                    case 'i':
                    case 'j':		
                    case 'k':	
                    case 'l':	
                    case 'm':
                    case 'n':		
                    case 'o':	
                    case 'p':	
                    case 'q':
                    case 'r':		
                    case 's':	
                    case 't':	
                    case 'u':
                    case 'v':		
                    case 'w':	
                    case 'x':	
                    case 'y':
                    case 'z':
                    case 'A':	
                    case 'B':	
                    case 'C':
                    case 'D':		
                    case 'E':	
                    case 'F':	
                    case 'G':
                    case 'H':		
                    case 'I':	
                    case 'J':		
                    case 'K':	
                    case 'L':	
                    case 'M':
                    case 'N':		
                    case 'O':	
                    case 'P':	
                    case 'Q':
                    case 'R':		
                    case 'S':	
                    case 'T':	
                    case 'U':	
                    case 'V':	
                    case 'W':
                    case 'X':		
                    case 'Y':	
                    case 'Z':	
                    case '_': t1.type = '1'; 
                              t1.name = ""; 
                              do
                              {
                                  t1.name += to_string(code[iter]);
                                  iter++;
                                  currCol++;
                              } while (iter < code.length() && (isalnum(code[iter]) || code[iter] == '_'));
                              iter--;
                              currCol--;
		    					
                            
                              mapIter = (*Table).find(t1.name);
                             
                              if (mapIter == (*Table).end())
                                  (*Table)[t1.name] = Table_Row ();
									    
						        break;
                    default: t1.type = '0'; 
                             t1.name = to_string(code[iter]);
                }
            }
        }
		
        template <class T>
        static string to_string (T obj)
        {
            ostringstream mystream;
            mystream << obj;
            return mystream.str();
        }
};   


class syntax
{
    private:

        map<string, Table_Row>* Table; 
        Tokenizer* myTokenizer;                     
        int* ER;                                
        stack<Token> tokens;                        
        stack<short> precedence;                   
	    
        bool processBinary (void)
        {
            Token temp1 = tokens.top(); 
            tokens.pop();
            Token temp2 = tokens.top(); 
            tokens.pop();
            Token temp3 = tokens.top(); 
            tokens.pop();
            long long tempNum1 = 0, tempNum2 = 0;
		 	 
            if (temp1.getType() == '1') 
            {
                if (((*Table)[temp1.getName()]).isInitialized())
                    tempNum1 = ((*Table)[temp1.getName()]).getValue();
                else
                {
                    
                    (*ER)++;
                    cout <<  "syntax Error on line " << (*myTokenizer).getCurrLine()<<endl;
                    cout << endl << "--------------------------------------------------------" << endl;
                    return false;
                }
            }
            else 
                tempNum1 = atol(temp1.getName().c_str());
                 
            if (temp3.getType() == '1') 
            {
                if (((*Table)[temp3.getName()]).isInitialized())
                    tempNum2 = ((*Table)[temp3.getName()]).getValue();
                else
                {
                    //printSemanticError (temp3.getName());
                    (*ER)++;
                    cout <<  "syntax Error on line " << (*myTokenizer).getCurrLine()<<endl;
                    cout << endl << "--------------------------------------------------------" << endl;
                    return false;
                }
            }
            else // temp3.getType() == '2' [Otherwise, convert the numeric literal into an integer.]
                tempNum2 = atol(temp3.getName().c_str());
		 	 
            switch (temp2.getName()[0]) // Push the computed literal into the stack, based on the operation.
            {
                case '+': tokens.push(Token ('2', Tokenizer::to_string(tempNum2 + tempNum1)));
                          break;
                case '-': tokens.push(Token ('2', Tokenizer::to_string(tempNum2 - tempNum1)));
                          break;
                case '*': tokens.push(Token ('2', Tokenizer::to_string(tempNum2 * tempNum1)));
            }
			      
            precedence.pop();
            return true;
        }
		

        bool processUnary (void)
        {
            Token temp1 = tokens.top();
            tokens.pop();
            Token temp2 = tokens.top(); 
            tokens.pop();
            long long tempNum1 = 0;
		 	 
            if (temp1.getType() == '1') 
            {
                if (((*Table)[temp1.getName()]).isInitialized())
                    tempNum1 = ((*Table)[temp1.getName()]).getValue();
                else
                {
                    
                    (*ER)++;
                    cout <<  "syntax Error on line " << (*myTokenizer).getCurrLine()<<endl;
                    cout << endl << "--------------------------------------------------------" << endl;                    
                    return false;
                }
            }
            else 
                tempNum1 = atol(temp1.getName().c_str());
                 
            tokens.push(Token ('2', Tokenizer::to_string(0-tempNum1))); 
             
            precedence.pop();
            return true;
        }
		


    public:
        /* Optional Constructor: */
        syntax (map<string, Table_Row>* Table = 0, 
                   Tokenizer* myTokenizer = 0, int* errors = 0)
        {
            this -> Table = Table;
            this -> myTokenizer = myTokenizer;
            this -> ER = errors;
            precedence.push (4); 
        }
        

        syntax (const syntax & analyzer)
        {
            this -> Table = analyzer.Table;
            this -> myTokenizer = analyzer.myTokenizer;
            this -> ER = analyzer.ER; 
            this -> tokens = analyzer.tokens;
            this -> precedence = analyzer.precedence;
        }
        
     
        void initialize (void)
        {
            stack<Token> s1;
            tokens = s1;
            stack<short> s2;
            precedence = s2;
            precedence.push(4); 
        }

        bool process (const Token & t1, short precedenceOfToken)
        {	 

            if ((precedenceOfToken < precedence.top() || precedence.top() == 0) && precedenceOfToken != 4)
            {
                if (t1.getName() != "(") 
                    tokens.push(t1); 
                if (precedenceOfToken != -1) 
                    precedence.push(precedenceOfToken); 
            }
            else 
            {
                if (precedenceOfToken==1){
                        if (t1.getName() == "-"){   
                            Token temp = tokens.top();
                            tokens.pop();
                        if (temp.getName() == "-")
                            precedence.pop();
                        else 
                            tokens.push( Token('3', "-") );
                            }
                }
                if (precedenceOfToken==2){
                        if (!processUnary ()) 
                        return false;
                        while (precedence.top() == 2) 
                                 if (!processBinary ())
                                    return false;
                             tokens.push (t1); 
                             precedence.push(2); 
                             
                }
                if (precedenceOfToken==3){
                        while (precedence.top() == 1) 
                             {
                                 if (!processUnary ()) 
                                     return false;
                             }
                             while (precedence.top() == 2) 
                                 if (!processBinary ())
                                     return false;
							  	     
                             while (precedence.top() == 3) 
                                 if (!processBinary ())
                                     return false; 
                             tokens.push (t1); 
                             precedence.push(3); 
                             
                }
                if (precedenceOfToken==4){
                         while (precedence.top() != 0 && precedence.top() != 4)
                            {

                                if (precedence.top() == 3 || precedence.top() == 2)
                                {
                                    if (!processBinary ())
                                        return false;
                                }
                                else if (precedence.top() == 1) 
                                    if (!processUnary ())
                                        return false;
                            }
								  
                            if (precedence.top() == 0) 
                                precedence.pop();
                            else 
                            {
                                Token temp1 = tokens.top(); 
                                tokens.pop(); 
                                Token temp2 = tokens.top(); 
                                tokens.pop(); 
                                long long tempNum1 = 0;

                                if (temp1.getType() == '1') 
                                {
                                    if (((*Table)[temp1.getName()]).isInitialized())
                                        tempNum1 = ((*Table)[temp1.getName()]).getValue();
                                    else
                                    {
                                        (*ER)++;
                                        cout << "syntax Error on line " << (*myTokenizer).getCurrLine()<<endl;
                                        cout << endl << "--------------------------------------------------------" << endl;
                                        return false;
                                        
                                    }
                                }
                                else 
                                    tempNum1 = atol (temp1.getName().c_str());
						             
                                ((*Table)[temp2.getName()]).initialize();
                                ((*Table)[temp2.getName()]).setValue(tempNum1); 
                            }
                             
                }
           
            }
            return true;
        }

        
};   


class interpreter
{
    private:       
        map<string, Table_Row>* Table;
        Token token_t;
        Tokenizer Token_Izer;
        syntax Semetic_Izer;
        int ER;
        int O_Parenthes;
	    
	    
    public:
        interpreter (string fileName, map<string, Table_Row>* Table)
        {
             this ->Table = Table;
             ER = 0;
             O_Parenthes = 0;
             token_t = Token ('0', "");
             Token_Izer = Tokenizer (fileName, Table);
              Semetic_Izer = syntax (this -> Table, &Token_Izer, &ER);
              Token_Izer.next (token_t); 
             while ( token_t.getType () != '5')
                 if (matchID () && matchAssign () && matchExp () && Semetic_Izer.process(token_t, 4))
                 {
                      if (O_Parenthes > 0)
                            printSyntaxError ();
		      Token_Izer.next(token_t); // Retrieve the next token.
                 }
                 else
                      skipAfterNextSemicolon ();
			 
             if ( ER > 0)
                 printErrors ();
             else
             for (map<string, Table_Row>::iterator it = (*Table).begin(); 
                 it != (*Table).end(); 
                 it++)
                     cout << it->first << " = " << (it->second).getValue() << endl;

        }
	    

        void skipAfterNextSemicolon (void)
        {
             while (token_t.getType() != '5' && token_t.getName()[0] != ';')
                Token_Izer.next(token_t); // Retrieve the next token.
             Token_Izer.next(token_t); // We need the token that is right after the semicolon.
             Semetic_Izer.initialize(); // Clear the information in the syntax Analyzer.
             O_Parenthes = 0;
        }
           
        void printErrors (void)
        {
             cout << "Totall of: " << ER << " Errors."
                  << endl << "--------------------------------------------------------" << endl;
        }

        void printSyntaxError ()
        {
             
             ER++;
             cout << "Syntax Error on line " << Token_Izer.getCurrLine()<<endl;
		 	 
          
             cout << endl << "--------------------------------------------------------" << endl;
        }
 
        bool matchID (void)
        {
             if(token_t.getType()=='1'){
                  Semetic_Izer.process(token_t, -1); 
                  Token_Izer.next(token_t);
                  return true;

             }
             else if (token_t.getType()=='3'&&token_t.getName()[0]==';'){
                  printSyntaxError ();
                  return false;
             }
             else{
                  printSyntaxError ();
                  return false;
             }
         
            Token_Izer.next(token_t); 
            return false;
        }
		
        bool matchAssign (void)
        {
             if (token_t.getType()=='3'&&token_t.getName()[0]=='='){
                  Token_Izer.next(token_t); 
                  return true;
             }
             else if (token_t.getType()=='3'&&token_t.getName()[0]==';'){
                  printSyntaxError ();
                  return false;
             }
             else{
                  printSyntaxError ();
                  return false;
             }
         
            Token_Izer.next(token_t); 
            return false;
        }
		

        bool matchExp (void)
        {
            if (token_t.getType() == '5')
            {
                 printSyntaxError ();
                 return false;		
            }
			   
            if (matchFact () && matchTermPrime () && matchExpPrime ())
                 return true;
            return false;
        }
		
        bool matchSemicolon (void)
        {
            Semetic_Izer.process(token_t, 4); 
            return true;
        }
		
        bool matchExpPrime (void)
        {
            switch (token_t.getType())
            {
                 case '0': printSyntaxError ();
                           break;
                 case '1': 
                 case '2': printSyntaxError ();
                           break;
                 case '3': switch (token_t.getName()[0])
                           {
                                case ';': 
                                case '*': return true;
                                case '(': printSyntaxError ();
                                          break;
                                case ')': if (O_Parenthes > 0)
                                          {
                                               O_Parenthes--;
                                               Semetic_Izer.process(token_t, 4); 
                                               Token_Izer.next(token_t); 
                                               return true;
                                          }
                                          else
                                          {
                                               printSyntaxError ();
                                               return false;
                                          }
                                case '+':
                                case '-': Semetic_Izer.process(token_t, 3); 
                                          Token_Izer.next(token_t); 
                                          if (matchExp())
                                               return true;
                                          return false;
                                case '=': printSyntaxError ();
                                
                           }
                           break;
                 case '5': printSyntaxError ();
            }
            return false;
        }
	    
        bool matchFact (void)
        {
            switch (token_t.getType())
            {
                 case '1': 
                 case '2': Semetic_Izer.process(token_t, -1); 
                           Token_Izer.next(token_t); 
                           return true;
                 case '0': printSyntaxError ();
                           break;
                 case '3': switch (token_t.getName()[0])
                           {
                                case ';': printSyntaxError ();
                                          break;
                                case ')': printSyntaxError ();
                                          break;
                                case '(': O_Parenthes++;
                                          Semetic_Izer.process(token_t, 0); 
                                          Token_Izer.next(token_t); 
                                          if (matchExp ())
                                               return true;
                                          return false;
                                case '+':
                                case '-': Semetic_Izer.process(token_t, 1); 
                                          Token_Izer.next(token_t); 
                                          if (matchFact ())
                                               return true;
                                          return false;
                                case '=': printSyntaxError ();
                                          break;
                                case '*': printSyntaxError ();
                                
                           }
                           break;
                 case '5': printSyntaxError ();
            }
            return false;
        }
	    
        bool matchTermPrime (void)
        {
            switch (token_t.getType())
            {
                 case '0': printSyntaxError ();
                           break;
                 case '1': 
                 case '2': printSyntaxError ();
                           break;
                 case '3': switch (token_t.getName()[0])
                           {
                                case '*': Semetic_Izer.process(token_t, 2); 
                                          Token_Izer.next(token_t); 
                                          if (matchFact () && matchTermPrime ())
                                               return true;
                                          return false;
                                case ')': if (O_Parenthes > 0)
                                          {
                                               O_Parenthes--;
                                               Semetic_Izer.process(token_t, 4); 
                                               Token_Izer.next(token_t); 
                                               return true;
                                          }
                                          else
                                          {
                                               printSyntaxError ();
                                               return false;
                                          }
                                case '+':
                                case '-':
                                case ';': return true;
                                case '(': printSyntaxError ();
                                          break;
                                case '=': printSyntaxError ();
                            
                           }
                           break;
                 case '5': printSyntaxError ();
            }
            return false;
        }    

};  

#endif