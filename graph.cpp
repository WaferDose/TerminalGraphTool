#include <iostream>

using namespace std;

class functionTerm
{
private:
    int power;         // Power = x*3 + y
    float constant;     // Can take negatives too
public:
    int getPower();
    float getConst();
    void setPower(int);
    void setConst(float);
};

int functionTerm::getPower()
{
    return power;
}

float functionTerm::getConst()
{
    return constant;
}

void functionTerm::setPower(int num)
{
    power = num;
}

void functionTerm::setConst(float num)
{
    constant = num;
}

class graph
{
private:
    bool multiVarFlag;
    char drawChar;
    int width, height;
    int termCount;
    functionTerm *term;
    double calculateValue(float x,float y);
public:
    int getWidth();
    int getHeight();
    void input(string);
    void printGraph();
    void changeWidth(int);
    void changeHeight(int);
    void changeDrawChar(char);
    void DEBUG_print_signValues();
    void DEBUG_print_terms();
    graph(int x, int y);
    ~graph();
};


double graph::calculateValue(float x,float y)
{
    double value = 0,temp;
    for(int i=0;i<termCount;i++)
    {
        temp = 1;
        for(int j=0;j<(term[i].getPower())/3;j++)
            temp *= x;
        for(int j=0;j<(term[i].getPower())%3;j++)
            temp *= y;
        value += (term[i].getConst()) * temp;
    }
    return value;
}

int graph::getWidth()
{
    return width;
}

int graph::getHeight()
{
    return height;
}

void graph::input(string str)           // tbh (string str) here is useless (as input)
{
    bool badStringFlag, constFlag, varFlag, expectNumberFlag;              // constflag, varflag indeicate whether const/var stage is done (complete)
    termCount = 0;
    multiVarFlag = 0;

            // 3XY+4-XXYY // 5Y + 6XX // 0.1y // 0X //     // +3 // 3- // 3 // 3X3 //
    cout << "Type : C1{x:0,1,2}{y:0,1,2}+C2{x:0,1,2}{y:0,1,2}+...+Cn{x:0,1,2}{y:0,1,2} (=0)" << endl << "e.g. 31XXY+2Y+5 (=0)   (or 3X (=Y) if no Y as input)" << endl;
    do
    {
        if(badStringFlag)
            cout << "Please try again." << endl;
        badStringFlag = 0, expectNumberFlag = 0;
        cin >> str;
        cin.get();
        for(int i=0;i<str.length();i++)
        {
            if(!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'|| toupper(str[i]) == 'X' || toupper(str[i]) == 'Y' || str[i] == '+' || str[i] == '-'))
            {
                badStringFlag = 1;
                break;
            }
        }
        if(badStringFlag)
            continue;

        if(str[0] == '+')
        {
            badStringFlag = 1;
            continue;
        }
        
        for(int i=0;i<str.length();i++)
        {
            if(toupper(str[i]) == 'Y')
            {
                multiVarFlag = 1;
                cout << "MULTI" << endl;
            }
        }
        termCount = 1;
        for(int i=1;i<str.length();i++)
        {
            if(str[i] == '+' || str[i] == '-')
                termCount++;
        }


        // Pre-big loop
        int j = 0;
        constFlag = 0, varFlag = 0;
        if(str[j] == '-')
        {
            j++;
        }
        while((str[j] >= '0' && str[j] <= '9') || str[j] == '.')
        {
            if(str[j] != '.' && expectNumberFlag)
                expectNumberFlag = 0;
            if(str[j] == '.')
            {
                expectNumberFlag = 1;
            }
            constFlag = 1;
            j++;
        }
        while(toupper(str[j]) == 'X' || toupper(str[j]) == 'Y')
        {
            varFlag = 1;
            j++;
        }
        if(!constFlag && !varFlag)
        {
            badStringFlag = 1;
            continue;
        }
        if((termCount == 1) && j != str.length())
        {
            badStringFlag = 1;
        }
        if((termCount == 1) && !varFlag)
        {
            badStringFlag = 1;
        }

        // Big loop
        for(int i=1;i<termCount-1;i++)
        {
            constFlag = 0, varFlag = 0;
            if(str[j] == '+' || str[j] == '-')
            {
                j++;
            }
            else
            {
                badStringFlag = 1;
            }
            while((str[j] >= '0' && str[j] <= '9') || str[j] == '.')
            {
                constFlag = 1;
                j++;
            }
            while(toupper(str[j]) == 'X' || toupper(str[j]) == 'Y')
            {
                varFlag = 1;
                j++;
            }
            if(!constFlag && !varFlag)
            {
                badStringFlag = 1;
                break;
            }
        }
        if(badStringFlag)
            continue;

        // Post-big loop
        if(termCount>1)
        {
            if(str[j] == '+' || str[j] == '-')
            {
                j++;
            }
            else
            {
                badStringFlag = 1;
            }
            constFlag = 0, varFlag = 0;
            while((str[j] >= '0' && str[j] <= '9') || str[j] == '.')
            {
                constFlag = 1;
                j++;
            }
            while(toupper(str[j]) == 'X' || toupper(str[j]) == 'Y')
            {
                varFlag = 1;
                if(j != str.length())
                    j++;
            }
            if(!constFlag && !varFlag)
            {
                badStringFlag = 1;
                continue;
            }
        }
    }
    while(badStringFlag);

    if(!multiVarFlag)
    {
        termCount++;
        str.append("-1Y");
    }

    delete [] term;
    term = new functionTerm[termCount];
    int ind=0, xcount, ycount, offset = 0;
    for(int i=0;i<termCount;i++)
    {
        xcount = 0; ycount = 0;
        if((atof(str.c_str()+ind) == 0) && str[ind+offset] != '0')
        {
            if(str[ind] == '-')
                term[i].setConst(-1);
            else
                term[i].setConst(1);
        }
        else term[i].setConst(atof(str.c_str()+ind));

        if(str[ind] == '+' || str[ind] == '-') {ind++;}
        while((str[ind] >= '0' && str[ind] <= '9') || str[ind] == '.') {ind++;}
        while(toupper(str[ind]) == 'X' || toupper(str[ind]) == 'Y')
        {
            if(toupper(str[ind]) == 'X')
            {
                xcount++;
            }
            if(toupper(str[ind]) == 'Y')
            {
                ycount++;
            }
            ind++;
        }
        term[i].setPower(xcount*3+ycount);          // Power = x*3 + y
        offset = 1;
    }
}

void graph::printGraph()
{
    float corrector;
    for(int y=height-1;y>0;y--)
    {
        corrector = 0;
        if(!(y%10))
        {
            cout << y;
            corrector = 0.5;
        }
        else
        {
            cout << "|";
        }
        for(float x=1+corrector;x<width-1;x+=0.5)
        {
            if((calculateValue(x-1,y-1) > 0) && (calculateValue(x-1,y) > 0) && (calculateValue(x,y-1) > 0) && (calculateValue(x,y) > 0) || (calculateValue(x-1,y-1) < 0) && (calculateValue(x-1,y) < 0) && (calculateValue(x,y-1) < 0) && (calculateValue(x,y) < 0))
            {
                cout << " ";
            }
            else cout << drawChar;
        }
        cout << endl;
    }
    for(int x=0;x<width;x++)
    {
        cout << "==";
    }
    cout << endl;
}

void graph::changeWidth(int temp)
{
    width = temp;
}

void graph::changeHeight(int temp)
{
    height = temp;
}

void graph::changeDrawChar(char temp)
{
    drawChar = temp;
}

graph::graph(int x=104, int y=51)
{
    drawChar = '#';
    termCount = 0;
    changeWidth(x);
    changeHeight(y);
    term = new functionTerm[0];
}

graph::~graph()
{
    delete [] term;
}


void graph::DEBUG_print_signValues()
{
    for(int y=height;y>0;y--)
    {
        cout << "|";
        for(float x=1;x<width;x+=0.5)
        {
            if(calculateValue(x,y)<0)
            {
                cout << "-";
            }
            else
            {
                cout << "+";
            }
        }
        cout << endl;
    }
    for(int x=0;x<width;x++)
    {
        cout << "==";
    }
    cout << endl;
}

void graph::DEBUG_print_terms()
{
    cout << "Term Count : " << termCount << endl;
    for(int i=0;i<termCount;i++)
    {
        cout << "Term[" << i+1 << "] : " << term[i].getConst();
        for(int j=0;j<(term[i].getPower())/3;j++)
            cout << "X";
        for(int j=0;j<(term[i].getPower())%3;j++)
            cout << "Y";
        cout << endl;
    }
}

int main()                                                  // MAIN
{
    graph mainGraph;
    string str_input;
    bool mainLoopflag=1, debugPrintTermsFlag=0, debugPrintSVFlag=0;
    int int_input;
    do
    {
        cout << "Select action : \n";
        cout << " 1. Print\n";
        cout << " 2. Change graph options\n";
        cout << " 3. Debug options\n";
        cout << " 4. Exit" << endl;
        cin >> str_input;
        cin.get();
        int_input = atoi(str_input.c_str());
        switch(int_input)
        {
            case 1 :
            {
                mainGraph.input(str_input);
                if(debugPrintTermsFlag)
                    mainGraph.DEBUG_print_terms();
                if(debugPrintSVFlag)
                    mainGraph.DEBUG_print_signValues();
                mainGraph.printGraph();
                cout << "Press enter to continue" << endl;
                while(cin.get() != '\n');
                break;
            }
            case 2 :
            {
                bool loopflag = 1;
                do
                {
                    cout << " Change graph options : \n";
                    cout << "  1. Change height\n";
                    cout << "  2. Change width\n";
                    cout << "  3. Change draw character\n";
                    cout << "  4. Back" << endl;
                    cin >> str_input;
                    cin.get();
                    int_input = atoi(str_input.c_str());
                    switch(int_input)
                    {
                        case 1 :
                        {
                            cout << "(Current height : " << mainGraph.getHeight() << ")\n";
                            cout << "Change height to : ";
                            cin >> str_input;
                            cin.get();
                            while(!atoi(str_input.c_str()) && str_input[0])
                            {
                                cout << "Invalid input.\nPress enter to continue." << endl;
                                while(cin.get() != '\n');
                                cout << "(Current height : " << mainGraph.getHeight() << ")\n";
                                cout << "Change height to : ";
                                cin >> str_input;
                                cin.get();
                            }
                            mainGraph.changeHeight(atoi(str_input.c_str()));
                            cout << "Succesfully changed height to : " << atoi(str_input.c_str()) << "\n" << "\nPress enter to continue" << endl;
                            while(cin.get() != '\n');
                            break;
                        }
                        case 2 :
                        {
                            cout << "(Current width : " << mainGraph.getWidth() << ")\n";
                            cout << "Change width to : ";
                            cin >> str_input;
                            cin.get();
                            while(!atoi(str_input.c_str()) && str_input[0])
                            {
                                cout << "Invalid input.\nPress enter to continue." << endl;
                                while(cin.get() != '\n');
                                cout << "(Current width : " << mainGraph.getWidth() << ")\n";
                                cout << "Change width to : ";
                                cin >> str_input;
                                cin.get();
                            }
                            mainGraph.changeWidth(atoi(str_input.c_str()));
                            cout << "Succesfully changed width to : " << atoi(str_input.c_str()) << "\n" << "\nPress enter to continue" << endl;
                            while(cin.get() != '\n');
                            break;
                        }
                        case 3 :
                        {
                            char temp;
                            cout << "Change draw character to : ";
                            cin.get(temp);
                            while(cin.get() != '\n');
                            while(!isprint(temp))
                            {
                                cout << "Non-printable character.\nPress enter to continue." << endl;
                                while(cin.get() != '\n');
                                cout << "Change draw character to : ";
                                cin.get(temp);
                                while(cin.get() != '\n');
                            }
                            mainGraph.changeDrawChar(temp);
                            cout << "Succesfully changed draw character to : '" << temp << "'\n" << "\nPress enter to continue" << endl;
                            while(cin.get() != '\n');
                            break;
                        }
                        case 4 : loopflag = 0; break;
                        default : cout << "Invalid input.\nPress enter to continue." << endl; while(cin.get() != '\n'); break;
                    }
                }
                while(loopflag);
                
                break;
            }
            case 3 : 
            {
                bool loopflag = 1;
                do
                {
                    cout << " Debug options : \n";
                    cout << "  1. Print function terms = \"" << debugPrintTermsFlag << "\"\n";
                    cout << "  2. Print sign values = \"" << debugPrintSVFlag << "\"\n";
                    cout << "  3. Back" << endl;
                    cin >> str_input;
                    cin.get();
                    int_input = atoi(str_input.c_str());
                    switch(int_input)
                    {
                        case 1 : debugPrintTermsFlag ? (debugPrintTermsFlag=0) : (debugPrintTermsFlag=1); break;
                        case 2 : debugPrintSVFlag ? (debugPrintSVFlag=0) : (debugPrintSVFlag=1); break;
                        case 3 : loopflag = 0; break;
                        default : cout << "Invalid input.\nPress enter to continue." << endl; while(cin.get() != '\n'); break;
                    }
                }
                while(loopflag);
                
                break;
            }
            case 4 : 
            {
                mainLoopflag = 0;
                break;
            }
            default : 
            {
                cout << "Invalid input.\nPress enter to continue." << endl;
                while(cin.get() != '\n');
                break;
            }
        }
    }
    while(mainLoopflag);

    return 0;
}


// TO DO:

//     Make input less hardcoded (e.g.3XYX4 could be acceptable)
//     NO

//     xx should automatically be 1xx not 0xx    // GOOD

//     Make the grapher better by not hard-printing '##' and print '#' instead    // GOOD i guess

//     BUG: input sets const to 1 (if no const) regarless of - or + in front of it. (x to 1x AND -x to 1x)    // FIXED

//     Make exponents not max out at 2

//     Make (0,0) movable and not hard-locked in bottom left