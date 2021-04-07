#pragma once
#if WIN32
#define NET_WALL_CALL __stdcall
#ifdef NET_WALL_BUILD_MODE
#define NET_WALL_API __declspec(dllexport)
#else
#define NET_WALL_API __declspec(dllimport)
#pragma comment(lib,"net_wall.lib")
#endif
#include <Windows.h>
#include <netfw.h>
#pragma comment(lib,"ole32.lib")
#endif
enum FWProfile {
	__DOMAIN, __PUBLIC, __PRIVATE,__ALL
};
typedef struct network{
	FWProfile profile;
#if WIN32
	INetFwPolicy2* pNetFwPolicy2=NULL;
	HRESULT hrComInit = S_FALSE;
#endif
}net_wall;

extern "C" {
	void NET_WALL_API NET_WALL_CALL  Initialize(net_wall*,FWProfile);
	void NET_WALL_API NET_WALL_CALL Cleanup(net_wall*);
	bool NET_WALL_API NET_WALL_CALL IsEnabled(net_wall*);
	void NET_WALL_API NET_WALL_CALL SetEnabled(net_wall*, bool);
#if WIN32 
	bool NET_WALL_API NET_WALL_CALL IsBlockAllInboundTraffic(net_wall*);
	void NET_WALL_API NET_WALL_CALL SetBlockAllInboundTraffic(net_wall*, bool);

#endif
}