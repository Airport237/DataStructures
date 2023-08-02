#include <iostream>
#include "AVL.h"
#include "sstream"
#include <fstream>

string verifyNextWord(string word)
{
    for (char c : word)
    {
        if(!isalpha(c) && !isspace(c))
            return "!";
    }
    return word;
}

string verifyUFID(string ufid)
{
    for (char c : ufid)
    {
        if(!isdigit(c))
            return "!";
    }
    if (ufid.size() != 8)
        return "!";
    return ufid;
}




int main() {
    AVLTree tree;
//    for (int i = 0; i < 18;i++)
//    {
//        tree.Insert(to_string(i),to_string(i));
//        tree.printPreorder();
//        cout << endl;
//    }



//    fstream fp_in("test.txt", ios::out);
//
    string numberInputs;
    cin >> numberInputs;

    for(int i = 0; i < stoi(numberInputs) + 1; i++)
    {
        string line;
        getline(cin,line);
        istringstream in(line);
        string command;
        in >> command;
        //Reads the name
        if (command == "insert")
        {
            string next;
            getline(in, next, '"');
            getline(in, next, '"');
            string name = next;
            name = verifyNextWord(name);
            if (name != "!")
            {
                getline(in, next, ' ');
                getline(in, next, ' ');
                string ufid = next;
                ufid = verifyUFID(ufid);
                if (ufid != "!")
                {
                    tree.Insert(name, ufid);
                } else
                    cout << "unsuccessful";
            } else
                cout << "unsuccessful";
            cout << endl;
        } else if (command == "search")
        {
            string next;
            getline(in, next, ' ');
            getline(in, next, '"');
            getline(in, next, '"');
            string name = next;
            if (isalpha(name[0]))
            {
                name = verifyNextWord(name);
                if (name != "!")
                {
                    tree.SearchName(name);
                } else
                {
                    cout << "unsuccessful";
                    cout << endl;
                }
            }
            if(isdigit(name[0]))
            {
                name = verifyUFID(name);
                if (name != "!")
                {
                    tree.SearchID(stoi(name));
                } else
                    cout << "unsuccessful";
                cout << endl;
            }
        }else if (command == "printLevelCount") {
            tree.printLevelCount();
            cout << endl;
        }
        else if (command == "printInorder")
        {
            tree.printInorder();
            cout << endl;
        }
        else if (command == "remove")
        {
            string next;
            getline(in, next, ' ');
            getline(in, next, ' ');
            string name = next;
            name = verifyUFID(name);
            if (name != "!")
            {
                tree.Remove(stoi(name));
            } else
                cout << "unsuccessful";
            cout << endl;
        } else if (command == "removeInorder")
        {
            string next;
            getline(in, next, ' ');
            getline(in, next, ' ');
            string name = next;
            if (isdigit(*name.c_str()))
            {
                if (name.size() == 1 or name.size()==2 or name.size()==3)
                    tree.removeInorder(stoi(name));
            }   else
                cout << "unsuccessful";
            cout << endl;
        } else if(command == "printInorder")
        {
            tree.printInorder();
            cout << endl;
        }

        else if (command == "printPreorder")
        {
            tree.printPreorder();
            cout << endl;
        }
        else if (command == "printPostorder")
        {
            tree.printPostorder();
            cout << endl;
        } else if ("");
        else
            cout << "unsuccessful";
    }
    tree.destruct();
    return 0;
}
