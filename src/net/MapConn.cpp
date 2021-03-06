#include "MapConn.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

namespace modou
{
  MapConn::MapConn(std::string ip, uint16_t port)
  {
    struct in_addr addr;
    int flag, ret;
    struct sockaddr_in serverAddr;
    if (inet_aton(ip.c_str(), &addr) == 0) {
      std::cerr << "error loing server ip" << std::endl;
      return;
    }
    mSock = socket(AF_INET, SOCK_STREAM, 0);
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = addr.s_addr;
    serverAddr.sin_port = htons(port);
    
    ret = connect(mSock, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
    if (ret < 0) {
      std::cerr << "connect error" << strerror(errno) << std::endl;
      return;
    }
    flag = fcntl(mSock, F_GETFL, 0);
    fcntl(mSock, F_SETFL, flag | O_NONBLOCK);
  }
  
  MapConn::~MapConn()
  {
    
  }

  int MapConn::netGetMapNpcs(std::vector< npc_info* > &npcs)
  {
    int len;
    int i;
    get_npc_by_map_pos_pkg *pkg = (get_npc_by_map_pos_pkg *)calloc(1, sizeof(get_npc_by_map_pos_pkg));

    pkg->flag = GET_NPC_BY_MAP_POS;
    
    npcs_list_pkg *pkg2 = (npcs_list_pkg *)calloc(1, sizeof(*pkg2));
    std::cout << " send nget npc get pkg" << std::endl;
    send(mSock, pkg, sizeof(*pkg), 0);
    std::cout << " send ok " << std::endl;
    while(len = recv(mSock, pkg2, sizeof(*pkg2), 0 )) {
      if (len > 0) {
	std::cout << pkg2->num << std::endl;
	for(i = 0; i < pkg2->num; i++) {
	  npc_info *npc = (npc_info *)calloc(1, sizeof(npc_info));
	  while(len = recv(mSock, npc, sizeof(*npc), 0)) {
	    if (len > 0) {
	      npcs.push_back(npc);
	    } else {
	      break;
	    }
	  }
	}
      } else {
	break;
      }
    }
    return 0;
  }

  
  
}
