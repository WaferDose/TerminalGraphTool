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
    float a, b, c;
    char *signValues;
    int width, height;
    int termCount = 0;
    functionTerm *term;
    //void OLDgenerateSignValues();
    double calculateValue(int x,int y);
public:
    //void OLDsetValues(float C1, float C2, float C3);
    void input(string);
    void printGraph();
    void DEBUG_print_signValues();
    //void OLDprintGraph();
    //void OLDDEBUG_print_signValues();
    void DEBUG_print_terms();
    graph(int x, int y);
    ~graph();
};

// void graph::OLDgenerateSignValues()
// {
//     for(int y=height;y>0;y--)
//     {
//         for(int x=1;x<width;x++)
//         {
//             if(((a*x*x+b*x+c)-y)<0)
//             {
//                 signValues[(y-1)*width+(x-1)] = 1;
//             }
//             else
//             {
//                 signValues[(y-1)*width+(x-1)] = -1;
//             }
//         }
//     }
// }

double graph::calculateValue(int x,int y)
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

// void graph::OLDsetValues(float C1, float C2, float C3)
// {
//     a = C1;
//     b = C2;
//     c = C3;
// }

void graph::input(string str)
{
    bool badStringFlag, constFlag, varFlag, expectNumberFlag;              // constflag, varflag indeicate whether const/var stage is done (complete)
    termCount = 0;
    multiVarFlag = 0;

            // 3XY+4-XXYY // 5Y + 6XX // 0.1y // 0X //     // +3 // 3- // 3 // 3X3 //
    cout << "Type : C1{x:0,1,2}{y:0,1,2}+C2{x:0,1,2}{y:0,1,2}+...+Cn{x:0,1,2}{y:0,1,2} (=0)" << endl << "e.g. 31XXY+2Y+5 (=0)" << endl;
    do
    {
        if(badStringFlag)
            cout << "Please try again" << endl;
        badStringFlag = 0, expectNumberFlag = 0;
        cin >> str;
        for(int i=0;i<str.length();i++)
        {
            if(!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'|| toupper(str[i]) == 'X' || toupper(str[i]) == 'Y' || str[i] == '+' || str[i] == '-'))
            {
                badStringFlag = 1; cout << "DEBUG 1" << endl;
                break;
            }
        }
        if(badStringFlag)
            continue;

        if(str[0] == '+')
        {
            badStringFlag = 1; cout << "DEBUG 2" << endl;
            continue;
        }
        

        termCount = 1;
        for(int i=1;i<str.length();i++)
        {
            if(toupper(str[i]) == 'Y')
                multiVarFlag = 1;
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
            badStringFlag = 1; cout << "DEBUG 3" << endl;
            continue;
        }
        if((termCount == 1) && j != str.length())
        {
            badStringFlag = 1;  cout << "DEBUG 10" << endl;
        }
        if((termCount == 1) && !varFlag)
        {
            badStringFlag = 1;  cout << "DEBUG 11" << endl;
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
                badStringFlag = 1; cout << "DEBUG 8" << endl;
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
                badStringFlag = 1; cout << "DEBUG 4" << endl;
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
                badStringFlag = 1; cout << "DEBUG 9" << endl;
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
                badStringFlag = 1; cout << "DEBUG 5" << endl;
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
    int ind=0, xcount, ycount;
    for(int i=0;i<termCount;i++)
    {
        xcount = 0; ycount = 0;
        if((atof(str.c_str()+ind) == 0) && str[ind] != '0')
        {
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
    }
}

void graph::printGraph()
{
    for(int y=height-1;y>0;y--)
    {
        cout << "|";
        for(int x=1;x<width-1;x++)
        {
            if((calculateValue(x-1,y-1) > 0) && (calculateValue(x-1,y) > 0) && (calculateValue(x,y-1) > 0) && (calculateValue(x,y) > 0) || (calculateValue(x-1,y-1) < 0) && (calculateValue(x-1,y) < 0) && (calculateValue(x,y-1) < 0) && (calculateValue(x,y) < 0))
            {
                cout << "  ";
            }
            else cout << "##";
        }
        cout << endl;
    }
    for(int x=0;x<width;x++)
    {
        cout << "==";
    }
    cout << endl;
}

// void graph::OLDprintGraph()
// {
//     OLDgenerateSignValues();
//     for(int y=height-1;y>0;y--)
//     {
//         cout << "|";
//         for(int x=1;x<width-1;x++)
//         {
//             if((signValues[(y-1)*width+(x-1)] == 1) && (signValues[(y-1)*width+(x)] == 1) && (signValues[(y)*width+(x-1)] == 1) && (signValues[(y)*width+(x)] == 1) || (signValues[(y-1)*width+(x-1)] == -1) && (signValues[(y-1)*width+(x)] == -1) && (signValues[(y)*width+(x-1)] == -1) && (signValues[(y)*width+(x)] == -1))
//             {
//                 cout << "  ";
//             }
//             else cout << "##";
//         }
//         cout << endl;
//     }
//     for(int x=0;x<width;x++)
//     {
//         cout << "==";
//     }
//     cout << endl;
// }

graph::graph(int x=104, int y=50)
{
    width = x;
    height = y;
    term = new functionTerm[0];
    signValues = new char [(x-1)*(y-1)];
    a = b = 0;
    c = 5;
}

graph::~graph()
{
    delete [] term;
}

// void graph::OLDDEBUG_print_signValues()
// {
//     for(int y=height;y>0;y--)
//     {
//         cout << "|";
//         for(int x=1;x<width;x++)
//         {
//             if(((a*x*x+b*x+c)-y)<0)
//             {
//                 cout << "++";
//             }
//             else
//             {
//                 cout << "--";
//             }
//         }
//         cout << endl;
//     }
//     for(int x=0;x<width;x++)
//     {
//         cout << "==";
//     }
//     cout << endl;
// }

void graph::DEBUG_print_signValues()
{
    for(int y=height;y>0;y--)
    {
        cout << "|";
        for(int x=1;x<width;x++)
        {
            if(calculateValue(x,y)<0)
            {
                cout << "--";
            }
            else
            {
                cout << "++";
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

int main()
{
    graph mainGraph;
    string str_input;
    //cout << "Type : C1{x:0,1,2}{y:0,1,2}+C2{x:0,1,2}{y:0,1,2}+...+Cn{x:0,1,2}{y:0,1,2} (=0)" << endl << "e.g. 31XXY+2Y+5 (=0)" << endl;
    //cout << "Type C1,C2,C3 where: C1x^2 + C2x + C1 (=0)" << endl << "e.g. 31, 2, 5  (C1, C2, C3)" << endl;
    //cin >> input;
    mainGraph.input(str_input);
    mainGraph.DEBUG_print_terms();
    mainGraph.DEBUG_print_signValues();
    mainGraph.printGraph();
    //mainGraph.OLDsetValues(1,1,0);
    //mainGraph.OLDDEBUG_print_signValues();
    //mainGraph.OLDprintGraph();
    cin >> str_input;
    return 0;
}


// TO DO:

//     Make input less hardcoded (e.g.3XYX4 could be acceptable)
//     NO

//     xx should automatically be 1xx not 0xx

//