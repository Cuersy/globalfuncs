#include<math.h>
#include<random>
#include <iostream>
#include <Windows.h>
#include <WinINet.h>
#pragma comment(lib, "WinINet.lib")
#include<iostream>
#include<vector>
#include<string>

#include "globalfuncs.h"
std::string httppost(const std::string& url, const std::string& postData) {
    std::wstring wUrl(url.begin(), url.end());

    HINTERNET internt = InternetOpen(L"HTTP Example", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (internt == NULL) {
        std::cerr << "Failed to initialize WinINet." << std::endl;
        return "";
    }

    HINTERNET baglanti = InternetOpenUrl(internt, wUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (baglanti == NULL) {
        std::cerr << "Failed to open URL." << std::endl;
        InternetCloseHandle(internt);
        return "";
    }

    DWORD bytesWritten = 0;
    if (!InternetWriteFile(baglanti, postData.c_str(), static_cast<DWORD>(postData.length()), &bytesWritten)) {
        std::cerr << "Failed to send POST data." << std::endl;
        InternetCloseHandle(baglanti);
        InternetCloseHandle(internt);
        return "";
    }

    char buffer[4096];
    std::string response;
    DWORD bytesRead = 0;

    while (InternetReadFile(baglanti, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        response.append(buffer, bytesRead);
    }

    InternetCloseHandle(baglanti);
    InternetCloseHandle(internt);

    return response;
}
std::wstring getcookie(const std::string& url) {
    std::wstring wUrl(url.begin(), url.end());
    HINTERNET internt, baglanti;
    DWORD bufferL = 4096;
    wchar_t buffer[4096];
    internt = InternetOpen(L"Slm", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (internt == NULL) {
        std::cout << "InternetOpen" << std::endl;
    }
    baglanti = InternetOpenUrl(internt, wUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (baglanti == NULL) {
        std::cout << "InternetOpenUrl" << std::endl;
        InternetCloseHandle(internt);
    }
    if (InternetGetCookie(wUrl.c_str(), NULL, buffer, &bufferL)) {
        std::wstring cookie(buffer);
        return cookie;
    }
    else {
        DWORD error = GetLastError();
        std::wcout << L"Cookie Hata kodu: " << error << std::endl;
    }
    InternetCloseHandle(baglanti);
    InternetCloseHandle(internt);

    return L"";
}
std::string httpget(const std::string& url) {
    std::wstring wUrl(url.begin(), url.end());
    HINTERNET internt = InternetOpen(L"Slm", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (internt == NULL) {
        std::cerr << "An error occured." << std::endl;
        return "";
    }

    HINTERNET baglanti = InternetOpenUrl(internt, wUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (baglanti == NULL) {
        std::cerr << "URL ACAMADIM." << std::endl;
        InternetCloseHandle(internt);
        return "";
    }

    char buffer[4096];
    std::string response;
    DWORD bytesRead = 0;

    while (InternetReadFile(baglanti, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        response.append(buffer, bytesRead);
    }

    InternetCloseHandle(baglanti);
    InternetCloseHandle(internt);

    return response;
}
auto jsonparse(std::string data) {
    try {
        std::string parsed;

    }
    catch (...) {
        std::cout << "Error occured!";
    }
}
int randnum() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int min = 1000000;
    int max = 9999999;
    std::uniform_int_distribution<> dis(min, max);
    int randomNum = dis(gen);
    return randomNum;
}
std::string encryptnumber(std::string number) {
    std::vector<int> numbers;
    std::string encrypted = "THIS_NUMBER_ENCRYPTED_BY_CUERSY____";
    int cnt = 0;
    int numberlen = number.length();
    for (int i = 0; i < numberlen; i++) {
        int num = int(number[i] - '0');
        numbers.push_back( num );
        if (num == 0 ) { encrypted += "_";}
        cnt++;
    }
    for (int i = 0; i < numberlen; i++) {
        encrypted += std::to_string(randnum()) + std::to_string(numbers[i]);
    }
    for (int i = 0; i <= 10; i++) {
        encrypted += std::to_string(randnum());
    }
    return encrypted;
}
std::string decryptnumber(std::string encrypted) {
    // 8 - _
    std::string decrypted;
    int _count = 0;
    for ( int i = 4; i< encrypted.length() ; i++) {
        if ( encrypted[i] == '_' ) {
            if ( encrypted[i+1] != '_' && _count > 4) { _count++; break;} else { _count++; }
        }
    }
    std::string encryptedNumber = encrypted.substr((35 + (_count-8)), encrypted.length() - (35) - 70);
    for (int i = 7; i < encryptedNumber.length() -6; i += 8) {
        decrypted += encryptedNumber[i];
    }

    return decrypted;
}

bool tccheck(std::string tc) {
    int ilkontoplam = 0;
    for (int i = 0; i < 10; ++i) {
        ilkontoplam += tc[i] - '0';
    }
    int ilkontoplamilkbasamak = ilkontoplam % 10;
    int onbir = tc[10] - '0';
    if (onbir == ilkontoplamilkbasamak) {
        return true;
    }
    else {
        return false;
    }
}
bool ikincialgoritma(std::string tc) {
    bool sonuc;
    // ilk
    int ilktoplam = 0;
    int ilkson = 0;
    for (int i = 0; i <= 8; i += 2) {
        ilktoplam += int(tc[i] - '0');
    }
    ilkson = ilktoplam * 7;
    // ikinci
    int ikincitoplam = 0;
    int ikincison = 0;
    for (int i = 1; i < 9; i += 2) {
        ikincitoplam += int(tc[i] - '0');
    }
    ikincison = ikincitoplam * 9;
    // Son
    int enson = ikincison + ilkson;
    int ensonrakam = enson % 10;
    if (ensonrakam == int(tc[9] - '0')) {
        sonuc = true;
    }
    else {
        sonuc = false;
    }
    return sonuc;
}
bool ucuncualgoritma(std::string tc) {
    bool sonuc;
    int rakamtoplam = 0;
    for (int i = 0; i <= 8; i += 2) {
        rakamtoplam += tc[i] - '0';
    }
    rakamtoplam = rakamtoplam * 8;
    int rakamtoplamson = rakamtoplam % 10;
    if (rakamtoplamson == int(tc[10] - '0')) {
        sonuc = true;
    }
    else {
        sonuc = false;
    }
    return sonuc;
}
bool istc(std::string tc) {
    if ((tccheck(tc) == true) && (ikincialgoritma(tc) == true) && (ucuncualgoritma(tc) == true)) {
        return true;
    }
    else {
        return false;
    }

}
void greet() {
    std::cout << "Hello, world!" << std::endl;
}
