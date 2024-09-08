#include<string>
#ifndef HEADER_H
#define HEADER_H
int randnum();
std::string encryptnumber(std::string number);
std::string decryptnumber(std::string number);
std::string httppost(const std::string& url, const std::string& postData);
std::string httpget(const std::string& url);
bool istc(std::string tc);
#endif
