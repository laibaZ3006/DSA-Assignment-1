#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

struct Token
{
    string type;
    string value;
};

struct Variable
{
    string name;
    int value;
};

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool isLetter(char ch)
{
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z');
}

bool isOperator(char ch)
{
    return ch == '+' || ch == '-' ||
           ch == '*' || ch == '/';
}

bool isOpeningBracket(char ch)
{
    return ch == '(' || ch == '[' || ch == '{';
}

bool isClosingBracket(char ch)
{
    return ch == ')' || ch == ']' || ch == '}';
}

bool bracketsMatch(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

vector<Token> tokenize(string expression)
{
    vector<Token> tokens;

    for (int i = 0; i < expression.length();)
    {

        if (expression[i] == ' ')
        {
            i++;
        }

        
        else if (isDigit(expression[i]))
        {
            string number = "";

            while (i < expression.length() &&
                   isDigit(expression[i]))
            {
                number += expression[i];
                i++;
            }

            tokens.push_back({"NUMBER", number});
        }

        else if (isLetter(expression[i]) ||
                 expression[i] == '_')
        {
            string variable = "";

            while (i < expression.length() &&
                   (isLetter(expression[i]) ||
                    isDigit(expression[i]) ||
                    expression[i] == '_'))
            {
                variable += expression[i];
                i++;
            }

            tokens.push_back({"VARIABLE", variable});
        }
        else if (isOperator(expression[i]))
        {
            string op = "";
            op += expression[i];

            tokens.push_back({"OPERATOR", op});
            i++;
        }
        else if (isOpeningBracket(expression[i]))
        {
            string br = "";
            br += expression[i];

            tokens.push_back({"OPEN", br});
            i++;
        }

        else if (isClosingBracket(expression[i]))
        {
            string br = "";
            br += expression[i];

            tokens.push_back({"CLOSE", br});
            i++;
        }

        else
        {
            cout << "Syntax Error" << endl;
            return {};
        }
    }

    return tokens;
}

vector<string> infixToPostfix(vector<Token> tokens)
{
    vector<string> postfix;
    stack<char> st;

    for (int i = 0; i < tokens.size(); i++)
    {
        Token current = tokens[i];

        if (current.type == "NUMBER" ||
            current.type == "VARIABLE")
        {
            postfix.push_back(current.value);
        }

        else if (current.type == "OPEN")
        {
            st.push(current.value[0]);
        }

        else if (current.type == "CLOSE")
        {
            while (!st.empty() &&
                   !isOpeningBracket(st.top()))
            {
                string op = "";
                op += st.top();

                postfix.push_back(op);

                st.pop();
            }

            if (st.empty())
            {
                cout << "Bracket Error" << endl;
                return {};
            }

            if (!bracketsMatch(st.top(),
                               current.value[0]))
            {
                cout << "Bracket Error" << endl;
                return {};
            }

            st.pop();
        }

        else if (current.type == "OPERATOR")
        {
            char currentOp = current.value[0];

            while (!st.empty() &&
                   isOperator(st.top()) &&
                   precedence(st.top()) >= precedence(currentOp))
            {
                string op = "";
                op += st.top();

                postfix.push_back(op);

                st.pop();
            }

            st.push(currentOp);
        }
    }
    while (!st.empty())
    {
        if (isOpeningBracket(st.top()))
        {
            cout << "Bracket Error" << endl;
            return {};
        }

        string op = "";
        op += st.top();

        postfix.push_back(op);

        st.pop();
    }

    return postfix;
}
int getValue(string name,
             vector<Variable> vars)
{
    for (int i = 0; i < vars.size(); i++)
    {
        if (vars[i].name == name)
        {
            return vars[i].value;
        }
    }

    return 0;
}
int evaluatePostfix(vector<string> postfix)
{
    vector<Variable> variables;

    for (int i = 0; i < postfix.size(); i++)
    {
        string token = postfix[i];

        if (isLetter(token[0]) ||
            token[0] == '_')
        {
            bool exists = false;

            for (int j = 0; j < variables.size(); j++)
            {
                if (variables[j].name == token)
                {
                    exists = true;
                    break;
                }
            }

            if (!exists)
            {
                Variable v;

                v.name = token;

                cout << "Enter value for "
                     << token << ": ";

                cin >> v.value;

                variables.push_back(v);
            }
        }
    }

    stack<int> st;

    for (int i = 0; i < postfix.size(); i++)
    {
        string token = postfix[i];

        
        if (isDigit(token[0]))
        {
            st.push(stoi(token));
        }

        
        else if (isLetter(token[0]) ||
                 token[0] == '_')
        {
            st.push(getValue(token, variables));
        }

    
        else
        {
            if (st.size() < 2)
            {
                cout << "Expression Error" << endl;
                return 0;
            }

            int b = st.top();
            st.pop();

            int a = st.top();
            st.pop();

            if (token == "+")
            {
                st.push(a + b);
            }

            else if (token == "-")
            {
                st.push(a - b);
            }

            else if (token == "*")
            {
                st.push(a * b);
            }

            else if (token == "/")
            {
                if (b == 0)
                {
                    cout << "Math Error" << endl;
                    return 0;
                }

                st.push(a / b);
            }
        }
    }

    return st.top();
}


int main()
{
    string expression;

    
    cout << "Enter Infix Expression: ";
    getline(cin, expression);

    vector<Token> tokens =
        tokenize(expression);

    if (tokens.size() == 0)
    {
        return 0;
    }

    
    vector<string> postfix =
        infixToPostfix(tokens);


    if (postfix.size() == 0)
    {
        return 0;
    }

    
    cout << endl;
    cout << "Postfix Expression: ";

    for (int i = 0; i < postfix.size(); i++)
    {
        cout << postfix[i] << " ";
    }

    cout << endl << endl;


    int result = evaluatePostfix(postfix);
    cout << endl;
    cout << "Final Result = "
         << result << endl;

    return 0;
}