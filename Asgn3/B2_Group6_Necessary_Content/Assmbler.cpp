#include<bits/stdc++.h>

using namespace std;

map<std::string , std::string> ins_map ;
map<std::string , std::string> type_map ;

void init() {
    ins_map["nor"] = "0000"; type_map["0000"] = "R" ;
    ins_map["or"] = "0001";  type_map["0001"] = "R" ;
    ins_map["add"] = "0010"; type_map["0010"] = "R" ;
    ins_map["sw"] = "0011"; type_map["0011"] = "i" ;
    ins_map["subi"] = "0100"; type_map["0100"] = "I" ;
    ins_map["sub"] = "0101"; type_map["0101"] = "R" ;
    ins_map["andi"] = "0110"; type_map["0110"] = "I" ;
    ins_map["addi"] = "0111"; type_map["0111"] = "I" ;
    ins_map["ori"] = "1000"; type_map["1000"] = "I" ;
    ins_map["beq"] = "1001"; type_map["1001"] = "I2" ;
    ins_map["bneq"] = "1010"; type_map["1010"] = "I2" ;
    ins_map["srl"] = "1011"; type_map["1011"] = "S" ;
    ins_map["j"] = "1100";   type_map["1100"] = "J" ;
    ins_map["and"] = "1101"; type_map["1101"] = "R" ;
    ins_map["lw"] = "1110"; type_map["1110"] = "i" ;
    ins_map["sll"] = "1111"; type_map["1111"] = "S" ;
    ins_map["$zero"] = "0101";
    ins_map["$t0"] = "0000";
    ins_map["$t1"] = "0001";
    ins_map["$t2"] = "0010";
    ins_map["$t3"] = "0011";
    ins_map["$t4"] = "0100";
}
#define pb push_back

int lineCount= 0;
vector <pair <std::string,int> > lab_adress;

vector<std::string> split(std::string& s) {
    vector<std::string> _elements;
    std::string item = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ' || s[i] == ',' || s[i] == '\t') {
            if (item != "") {
                _elements.pb(item);
                item = "";
            }
        }
        else item += s[i];
    }


    if (item != "")
        _elements.pb(item);

    return _elements;
}

std::string hex_converter(std::string str) {
    std::string hex = "";
    for (int i = 0; i < str.size(); i += 4) {
        std::string temp = str.substr(i, 4);
        if (temp == "0000") {
            hex += "0";
        } else if (temp == "0001") {
            hex += "1";
        } else if (temp == "0010") {
            hex += "2";
        } else if (temp == "0011") {
            hex += "3";
        } else if (temp == "0100") {
            hex += "4";
        } else if (temp == "0101") {
            hex += "5";
        } else if (temp == "0110") {
            hex += "6";
        } else if (temp == "0111") {
            hex += "7";
        } else if (temp == "1000") {
            hex += "8";
        } else if (temp == "1001") {
            hex += "9";
        } else if (temp == "1010") {
            hex += "a";
        } else if (temp == "1011") {
            hex += "b";
        } else if (temp == "1100") {
            hex += "c";
        } else if (temp == "1101") {
            hex += "d";
        } else if (temp == "1110") {
            hex += "e";
        } else if (temp == "1111") {
            hex += "f";
        }
    }
    return hex;
}

bool check(std::string str) {
    if(str == "nor" || str == "or" || str == "add" || str == "sw" || str == "subi" || str == "sub" || str == "andi" || str == "addi" || str == "ori" || str == "beq" || str == "bneq" || str == "srl" || str == "j" || str == "and" || str == "lw" || str == "sll") {
        return true ;
    }
    return false ;
}

void push_(std::string line){
    vector<std::string> v = split(line);
    if(!check(v[0]))
        lab_adress.pb({v[0], lineCount});
}

std::string return_register(std::string str) {
    return str ;
}

vector<std::string> copy(vector<std::string>v) {
    vector<std::string>temp ;
    for(int j = 1 ; j < v.size() ; j++) {
       temp.pb(v[j]) ;
    }
    return temp ;
}

std::string  bin_coverter(std::string line) {
    std::string instruction="";
    vector<std::string> v = split(line);
    std::string item = v[0];
    // instruction
    if(check(item) == true) {
        instruction = instruction + ins_map[item] ;
    }
    else {
        lab_adress.pb(make_pair(item, lineCount));
        vector<std::string> temp;
        for (int j=1; j<v.size(); j++){
            temp.pb(v[j]);
        }
        v=temp;
        item = v[0];
        // instruction
        instruction+=ins_map[item] ;
    }


    // R format : sub, or, and, add, nor
    if((type_map[instruction]) == "R") {
        instruction = instruction + ins_map[return_register(v[2])]+ins_map[return_register(v[3])] + ins_map[return_register(v[1])] ;

        return instruction;
    }

    // S format : srl, sll
    else if((type_map[instruction]) == "S"){

        instruction+=ins_map[return_register(v[2])]+ins_map[return_register(v[1])] ;
        int const_int = stoi(v[3]) ;
        std::string const_str="0000";

        for(int j=0; const_int > 0; j++) {
            if(const_int % 2)   const_str[const_str.size()-j-1] = '1' ;
            else const_str[const_str.size()-j-1] = '0' ;
            const_int/=2 ;
        }

        instruction+=const_str;

        return instruction;
    }

    // I format cnst : ori, addi, andi, subi
    else if((type_map[instruction]) == "I"){
        instruction= instruction + ins_map[return_register(v[2])]+ins_map[return_register(v[1])] ;

        int const_int = stoi(v[3]);
        std::string const_str = bitset<4>(const_int).to_string();


        instruction= instruction + const_str;

        return instruction;
    }

    // I format control : beq, bneq
    else if((type_map[instruction]) == "I2"){
        //cout <<"I2 typeeeeee "<< endl;
        instruction+=ins_map[return_register(v[1])]+ins_map[return_register(v[2])] ;

        int bAddress;
        for(int j=0; j<lab_adress.size(); j++){
            if(lab_adress[j].first == v[3] + ":") {
                bAddress = lab_adress[j].second;
                break ;
            }
        }

        cout << "base : " << bAddress <<" line cnt ; " << lineCount << endl;
        int const_int=(bAddress-lineCount-1) ; //+1?
        std::string const_str = bitset<4>(const_int).to_string();

        instruction+=const_str;

        return instruction;
    }

    // I format memory : sw, lw
    else if((type_map[instruction]) == "i"){

        std::string cnst;
        std::stringstream ss(v[2]);
        if (getline(ss,item,'('))  cnst = item;
        if (getline(ss,item,')'))  instruction+=ins_map[return_register(item)] ;
        instruction+=ins_map[return_register(v[1])] ;
        // instruction+=" "; //for debugging

        int const_int = stoi(cnst) ;
        std::string const_str = bitset<4>(const_int).to_string();

        instruction+=const_str;

        return instruction;
    }

    // J format : j
    else if((type_map[instruction]) == "J"){

        int jmp_addess ;
        for(int j=0; j<lab_adress.size(); j++){
            if(lab_adress[j].first == v[1]+":" )  jmp_addess = lab_adress[j].second ;
        }
        int const_int = jmp_addess + 1 ;
        std::string const_str = bitset<8>(const_int).to_string() ;

        instruction+=const_str ;
        instruction+="0000";

        return instruction ;
    }

    else return instruction ;
}

int main ()
{
    init() ;
    std::string line;
    ifstream fin ("input.txt");
    ofstream fout ("machine.bin");
    ofstream hex_out("machine_.hex") ;

    while(getline(fin,line)){
        //cout << line << endl;
        push_(line);
        lineCount++ ;
    }
    fin.close() ;
    fin.open("input.txt") ;
    lineCount=0;
    while (getline (fin,line)) {
        std::string str_bin= bin_coverter(line);
        if(str_bin == "") continue ;
        hex_out << hex_converter(str_bin) << endl ;
        for(int i = 0 ; i < str_bin.size() ; i+=4) {
            fout << str_bin.substr(i,4) ;
            if(i!=str_bin.size() -1 ) fout << " " ;
        }
        fout << endl;
        lineCount++;
    }
    fin.close();
    fout.close();
    hex_out.close() ;
    return 0;
}

