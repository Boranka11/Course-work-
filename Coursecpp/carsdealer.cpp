#include <iostream>
#include <openssl/md5.h>
#include <string>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <cctype>
#include <algorithm>

#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
string enc(string& password, int s);  

//string calcbit(const string& input)
///{
//    unsigned char digit[MD5_DIGEST_LENGTH];
//    MD5((const unsigned char*)input.c_str(), input.size(), digit);
//    stringstream ss;
 //   for(int i =0; i<MD5_DIGEST_LENGTH; i++)
//    {
 //       ss << hex << setw(2) <<setfill('0') << (int)digit[i];
 //           }
////            return ss.str();
//}//;

class Create;

class Registr{
    protected:
    const string Exist_user ="userinfo.txt";
    bool check_registr(string& username)
   {

   ifstream file("userinfo.txt");
   string line;
   while (getline(file, line))
   {
    if(line.find(username) != string::npos)
    {
        return true;
    } 
   }
   file.close();
   ifstream file2("Newuser.txt");
   if(file2.is_open())
   {
    string line_new;
    while(getline(file2, line_new))
    {
if(line_new.find(username) != string::npos)
{
    file2.close();
    return true;
}
    }
    file2.close();
   }
   
return false;
 
     } 
       bool check_password(string& password)
     {
        int key_1 = 2;
        string encrypted_1 = enc(password, key_1);
        string line;
        ifstream file3("userinfo.txt");
        while(getline(file3, line))
        {
    if(line.find( encrypted_1) != string::npos)
    {
        return true;
    }
        }
        file3.close();
        ifstream file4("Newuser.txt");
        string line_new2;
        while (getline(file4, line_new2))
        {
            if(line_new2.find(encrypted_1) != string::npos)
            {
                file4.close();
                return true;
            }
        }
        file4.close();
        return false;
     }
  
 public:
  
 virtual bool proverka() {
    string username;
    string password;
     cout << "أهلاًPut user nameأهلاً" << endl;
    getline(cin, username);
    cout << "بيدورPut passwordبيدور" << "\n";
    getline(cin,password);
    if(check_registr(username)) {
        if(check_password(password)) {
 cout << "Privet" << username <<endl;
return true;
        }
    }
    
return false;
 }
 
     
     
};
string enc(string& password, int s)
{
    string res = "";
    for (int i = 0; i < password.length(); i++ )
    if(isupper(password[i]))
    {
        res += char((password[i] + s - 65) % 26 + 65);
    } else if (islower(password[i]))
    {
        res += char((password[i] + s - 97) % 26 + 97);
    }
    else
    {
        res += password[i];
    }
    return res;
}
string decrypt(string text, int s)
{
string result = "";
s = s%26;
for (int k = 0; k < text.length(); k++)
{
    if (isupper(text[k]))
    {
      result += char((text[k] - s - 65 + 26) % 26 + 65);
    }else if (islower(text[k])) {
            result += char((text[k] - s - 97 + 26) % 26 + 97);
        } else {
            result += text[k]; 
        }

}
return result;
};

class Create : public Registr {
public:
bool create()
{
string username;
string password;
cout<<"Put new name" << endl;
cin.ignore();
getline(cin,username);
if(check_registr(username)) {
    cout << "EST ACCOUNT " << endl;
    return false; 
}
cout << "New password" << endl;
getline(cin,password);
ofstream file_create("Newuser.txt", ios::app);
if(!file_create.is_open())
{
cout<< "Oshibka" << endl;
return false;
}
int key = 2;
string encrypeted = enc(password, key);
file_create << "Name:" << username << endl;
file_create << "Parrol" <<":" << encrypeted << endl;
file_create <<"&&&&&&&&&&&&&&&&&&&&&&.\n";
cout<< "continue" << endl;
return true;
}
};d
void find_dream()
{
    cout << "Put dream mark" << "\n";
 string dream_mark;
 string line_dream;
  cin.ignore();
 getline (cin, dream_mark);

 bool iffind = false;
 string car_find;
 ifstream dream("dreampar.txt");
while ( getline (dream, car_find))
{
string lower_car_info = car_find;
 string lower_dream_mark = dream_mark;
        transform(lower_car_info.begin(), lower_car_info.end(), lower_car_info.begin(), ::tolower);
        transform(lower_dream_mark.begin(), lower_dream_mark.end(), lower_dream_mark.begin(), ::tolower);
        if(lower_car_info.find(lower_dream_mark) != string::npos)
        {
            cout << "Nahel " << car_find << endl;
            iffind = true;
        }
}
dream.close();
if(!iffind) {
    cout<< "Not match" << endl;
}
};
int req(){
    string Car_info;
    cout<< "PUT INFO" << endl;
    getline(cin, Car_info);
ofstream reqs("request.txt", ios::app);
string line_req;

    reqs << "INfo" << Car_info << "\n";
reqs.close();
return 0;
};
int request_menu(){
int choise_req;
 
cout<< "1 -- Make requset" << "\n"
<< "2 -- Exit to main" << "\n" ;
cin >> choise_req;
switch(choise_req){
    case 1:
   req();
   break;
   case 2:
  
  break;
}
return 0;


};


static size_t Nazad(void* content, size_t size, size_t nmemb, string* response)
{
    response->append((char*) content, size * nmemb);
    return size *nmemb;
};
void ai_govno()
{
    CURL* curl;
    CURLcode respond;
    string response;
   
    string vopros;
     cout<< "Put your vopros" << endl;
     cin.ignore();
    getline(cin,vopros);
    curl = curl_easy_init();
    if(curl){
    string url = "http://localhost:11434/api/generate";
    json request = {
  {"model","deepseek-r1:7b"},
  {"prompt", vopros},
  {"stream", false}
    };
 string data_js = request.dump();
 struct curl_slist* headers = NULL;
 headers = curl_slist_append(headers, "Content-Type: application/json");
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_js.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Nazad);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  respond = curl_easy_perform(curl);
  if(respond != CURLE_OK) {
    cerr << "OShibka " << curl_easy_strerror(respond) << endl;
  } else {
    try{
        json j = json::parse(response);
        if(j.contains("response"))
        {
            cout << "OTVET " << j["response"].get<string>() << endl;

        }
        else {
            cerr << "OShibka" << endl;
            cout << "POlniy otvet" << response << endl;
        }
    } catch (json::exception& e) {
        cerr << "OSHIBKA" << e.what() << endl;
    }
  }
  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);
    }
}

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
       Registr *rigist_sys= new Registr();
   Create *create_sys= new Create();
   if(!rigist_sys->proverka())
   {
cout << "User nety takogo xoches soozdat 'y/n'" << endl;
char choise_registr;
cin >> choise_registr;
if(tolower(choise_registr) == 'y')
{
    create_sys->create();
   
}
else {
    cout << "Goodbye debil" << endl;
    return 0;
}
   }
 auto find = [](void) {
ifstream list("carlist.txt");
string list_read;
while (getline (list, list_read))
{
    cout << list_read << endl;
}
 };



int choise;
do {
cout << 
 "\n"<<
" 1 - Display all car in shop.\n" 
<< " 2 - Find a car of your dream.\n" 
<< "3 - Make request about car repair .\n "
<< "4 - Exit .\n"
<< "5 - AI helper\n" ;
cin >> choise;

switch(choise)
{
 case 1:
 find();
break;
 case 2:
 find_dream();
 break;
 case 3:
 cout << "Continue" << endl;
 request_menu();
 break;
 case 4 :
 cout << "Exit...." << endl;
 return 0;
break;
 case 5:
 ai_govno();
 break;
 
 default :
 cout << "eRor";

}
} while ( choise != 4);
curl_global_cleanup();
return 0;
 
 }
 
 
