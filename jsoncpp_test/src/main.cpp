#pragma once
#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>


int main() {

	std::cout << "json_test" << std::endl;

    Json::Value root;
    root["id"] = 1001;
    root["data"] = "hello world";
    std::string request = root.toStyledString();
    std::cout << "request is:" << request << std::endl;
    Json::FastWriter fastWriter;
    std::string requestSimple = fastWriter.write(root);
    std::cout << "requestSimple is:" << requestSimple << std::endl;

    Json::Value root2;
    Json::Reader reader;
    reader.parse(request, root2);
    std::cout << "msg id is " << root2["id"] << " msg is " << root2["data"] << std::endl;

    getchar();
	return 0;
}
