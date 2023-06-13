// main.cpp: 定义应用程序的入口点。
#pragma once
#include <iostream>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/http_struct.h>

using namespace std;




int main() {
    const char* ip = "127.0.0.1";
    ev_uint16_t port = 8888;

	std::cout << "libevent" << std::endl;
    WSADATA wdSockMsg;
    int s = WSAStartup(MAKEWORD(2, 2), &wdSockMsg);

    if (0 != s)
    {
        switch (s)
        {
        case WSASYSNOTREADY: printf("重启电脑，或者检查网络库");   break;
        case WSAVERNOTSUPPORTED: printf("请更新网络库");  break;
        case WSAEINPROGRESS: printf("请重新启动");  break;
        case WSAEPROCLIM:  printf("请关闭不必要的软件，以确保有足够的网络资源"); break;
        }
    }

    if (2 != HIBYTE(wdSockMsg.wVersion) || 2 != LOBYTE(wdSockMsg.wVersion))
    {
        cout << "网络库版本错误" << endl;
        return 0;
    }

    event_config* evt_config = event_config_new();
    struct event_base* base = event_base_new_with_config(evt_config);
    struct evhttp* http = evhttp_new(base);
    evhttp_set_default_content_type(http, "text/html; charset=utf-8");

    evhttp_set_timeout(http, 30);
    // 设置路由
    //evhttp_set_cb(http, "/", api_index, this);

    evhttp_bind_socket(http, ip, port);
    event_base_dispatch(base);

    event_base_free(base);
    evhttp_free(http);
    event_config_free(evt_config);

	return 0;
}
