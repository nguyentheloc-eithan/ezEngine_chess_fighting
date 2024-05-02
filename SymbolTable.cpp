#include "SymbolTable.h"

void SymbolTable::run(string filename)
{

    fstream newfile;
    newfile.open(filename,ios::in);
    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        int level = 0;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            string a = getAction(tp);
            if(a == "INSERT")
            {
                string var = getVar(tp);
                int f = findPos(var);
                if(f != -1 )//tim thay va cung level
                {
                    table->moveToPos(f);
                    symbol test = table->getValue();
                    if(test.level == level)
                    {
                        Redeclared* a = new Redeclared(tp);
                        cout<<a->what();
                        return;
                    }
                }
                string typet = getType(tp);
                symbol t;
                t.indentifier = var;
                t.type = typet;
                t.level = level;
                table->append(t);
                cout<<"success"<<endl;
            }
            else if(a == "ASSIGN")
            {
                string var = getVar(tp);
                int find = this->findPos(var);
                if(find != -1)
                {
                    table->moveToPos(find);
                    symbol temp = table->getValue();
                    string val = getType(tp);
                    if(val[0] == 'n')
                    {
                        if(temp.type == "number")
                        {
                            temp.value = val;
                            cout<<"success"<<endl;
                        }
                        else
                        {
                            TypeMismatch* a = new TypeMismatch(tp);
                            cout<<a->what();
                            return;
                        }
                    }
                    if(val[0] == 39)
                    {
                        if(temp.type == "string")
                        {
                            temp.value = val;
                            cout<<"success"<<endl;
                        }
                        else
                        {
                            TypeMismatch* a = new TypeMismatch(tp);
                            cout<<a->what();
                            return;
                        }
                    }
                }
                else
                {
                    Undeclared* a = new Undeclared(tp);
                    cout<<a->what();
                    return;
                }
            }
            else if(a == "BEGIN")
            {
                level++;
            }
            else if(a== "END")
            {
                if(level == 0)
                {
                    UnknownBlock* a = new UnknownBlock;
                    cout<<a->what();
                    return;
                }
                level--;
            }
            else if(a == "LOOKUP")
            {
                string var = getVar(tp);
                int find = findMaxlevel(var);
                if(find == -1)
                {
                    Undeclared* error = new Undeclared(tp);
                    cout<<error->what();
                    return;
                }
                table->moveToPos(find);
                symbol res = table->getValue();
                cout<<res.level<<"\n";
            }
            else if(a == "PRINT")
            {
                symbol buffer[100];
                int k = 0;
                table->moveToEnd();
                table->prev();
                symbol res = table->getValue();
                buffer[k++] = res;
                table->prev();
                for(int i = table->length() - 1; i > -1; i--, table->prev()){
                    res = table->getValue();
                    bool check = false;
                    for(int j = 0; j < k; j++){
                        if(res.indentifier == buffer[j].indentifier){
                            check = true;
                            break;
                        }
                    }
                    if(!check){
                        buffer[k++] = res;
                    }
                }
                cout << buffer[k - 1].indentifier << "//" << buffer[k - 1].level;
                for(int i = k - 2; i  > -1; i--){
                    cout << " " << buffer[i].indentifier << "//" << buffer[i].level;
                }
            }
            else if(a == "RPRINT")
            {
                symbol buffer[100];
                int k = 0;
                table->moveToEnd();
                table->prev();
                symbol res = table->getValue();
                buffer[k++] = res;
                table->prev();
                for(int i = table->length() - 1; i > -1; i--, table->prev()){
                    res = table->getValue();
                    bool check = false;
                    for(int j = 0; j < k; j++){
                        if(res.indentifier == buffer[j].indentifier){
                            check = true;
                            break;
                        }
                    }
                    if(!check){
                        buffer[k++] = res;
                    }
                }
                cout << buffer[0].indentifier << "//" << buffer[0].level;
                for(int i = 1; i  < k; i++){
                    cout << " " << buffer[i].indentifier << "//" << buffer[i].level;
                }
            }
        }
        if(level > 0)
        {
            UnclosedBlock* a = new UnclosedBlock(level);
            cout<<a->what();
        }
        newfile.close(); //close the file object.
    }
}
string SymbolTable::getAction(string tp) {
    string action = "";
    int i = 0;
    while(tp[i] != '\0' && tp[i] != ' ')
    {
        action += tp[i];
        i++;
    }
    return action;
}
string SymbolTable::getVar(string tp) {
    string variable = "";
    int i = 0;
    while(tp[i] != '\0' && tp[i] != ' ')
    {
        i++;
    }
    i++;
    while(tp[i] != '\0' && tp[i] != ' ')
    {
        variable += tp[i];
        i++;
    }
    return variable;
}
string SymbolTable::getType(string tp) {
    int i = 0;
    while(tp[i] != '\0' && tp[i] != ' ')
    {
        i++;
    }
    i++;
    while(tp[i] != '\0' && tp[i] != ' ')
    {
        i++;
    }
    i++;
    string type = "";
    while(tp[i] != '\0')
    {
        type += tp[i];
        i++;
    }
    return type;
}
int SymbolTable::findPos(string var) {
    int n = table->length();
    table->moveToStart();
    for(int i = 0; i < n;i++)
    {
        table->moveToPos(i);
        symbol t = table->getValue();
        if(var == t.indentifier)
        {
            return i;
        }
    }
    return -1;
}
int SymbolTable::findMaxlevel(string var) {
    int find = -1;
    int maxlevel = -1;
    int n = table->length();
    table->moveToStart();
    for(int i = 0; i < n;i++)
    {
        table->moveToPos(i);
        symbol t = table->getValue();
        if(var == t.indentifier && maxlevel < t.level)
        {
            find = i;
            maxlevel = t.level;
        }
    }
    return find;
}