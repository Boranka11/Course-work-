#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <cctype>
#include <algorithm>
#include <nlohmann/json.hpp> // Для работы с JSON
using json = nlohmann::json;
using namespace std;

// Класс регистрации
class Registr {
protected:
    bool check_registr(string& username) {
        ifstream file("userinfo.txt");
        string line;
        while(getline(file, line)) {
            if(line.find(username) != string::npos) return true;
        }
        file.close();
        return false;
    }

public:
    virtual bool proverka() {
        string username;
        cout << "Put user name: ";
        getline(cin, username);
        return check_registr(username);
    }
};

// Класс создания аккаунта
class Create : public Registr {
public:
    bool create() {
        string username;
        cout << "Put new name: ";
        getline(cin, username);
        
        if(check_registr(username)) {
            cout << "Account exists!" << endl;
            return false;
        }

        ofstream file("userinfo.txt", ios::app);
        file << username << endl;
        file.close();
        cout << "Account created!" << endl;
        return true;
    }
};

// Обратный вызов для CURL
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response) {
    response->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void ai_advice() {
    
}
// Функция для советов DeepSeek
void car_advice() {
    CURL* curl;
    CURLcode res;
    string response;

    cout << "Ask car question: ";
    string question;
    getline(cin, question);

    curl = curl_easy_init();
    if(curl) {
        string url = "http://localhost:11434/api/generate";
        json request = {
            {"model", "deepseek-r1:7b"},
            {"prompt", question},
            {"stream", false}
        };
        string json_data = request.dump();

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            cerr << "Error: " << curl_easy_strerror(res) << endl;
        } else {
            try {
                json j = json::parse(response);
                if(j.contains("response")) {
                    cout << "\n🤖 Ответ:\n" << j["response"].get<string>() << endl;
                } else {
                    cerr << "Ошибка: неверный формат ответа" << endl;
                    cout << "Полный ответ: " << response << endl;
                }
            } catch (json::exception& e) {
                cerr << "JSON Error: " << e.what() << endl;
            }
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
}

// Главное меню
int main() {
    curl_global_init(CURL_GLOBAL_ALL);
    
    Registr reg;
    Create cr;

    if(!reg.proverka()) {
        cout << "Create account? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        
        if(tolower(choice) == 'y') {
            if(!cr.create()) return 1;
        } else {
            cout << "Goodbye!" << endl;
            return 0;
        }
    }

    auto show_cars = [](){
        ifstream file("carlist.txt");
        string line;
        while(getline(file, line)) cout << line << endl;
    };

    int choice;
    do {
        cout << "\n1. Show cars\n"
             << "2. Find dream car\n"
             << "3. Repair request\n"
             << "4. Exit\n"
             << "5. Get AI Advice\n"
             << "Choice: ";
             
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                show_cars();
                break;
            case 2:
                // Ваша функция поиска
                break;
            case 3:
                // Ваша функция ремонта
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            case 5:
                car_advice();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while(choice != 4);

    curl_global_cleanup();
    return 0;
}