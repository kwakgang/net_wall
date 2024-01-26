#include <iostream>
#include <net_wall.h>
int main()
{
    net_wall::net_wall* wall = NULL;
    net_wall::net_wall_rule* rule = NULL;
    try {
        std::cout << (net_wall::Init() == true ? "Success" : throw net_wall::permission_denied("COM Initialization failed")) << std::endl;
        net_wall::Initialize(&wall, net_wall::FWProfile::__PUBLIC);
        
        //net_wall::GetRule("QLang", wall, &rule);
        //net_wall::GetRule("CF1 Data Logger", wall, &rule);
        //net_wall::RemoveRule(wall, "CF1 Data Logger");
        //net_wall::GetRule("dbeaver", wall, &rule);
        // ---------------------------------------------------------------
        // TODO: RemoveAllRules(wall, name),
        //       RemoveRule(wall, name, index),
        //       GetRuleCount(wall, name),
        //       GetRule(wall, name, index),
        //       구현할 것.
        // ---------------------------------------------------------------
        net_wall::GetRule("Skype", wall, &rule);
        int nRuleCount = net_wall::GetRuleCount(wall);
        net_wall::FWProfile profiles = net_wall::GetProfile(rule);
        net_wall::Bound bound = net_wall::GetBound(rule);
        net_wall::FWAction action = net_wall::GetDefaultInboundAction(wall);
        bool bBlock = net_wall::IsBlockAllInboundTraffic(wall);

        std::cout << (short)profiles << std::endl;
        std::cout << (profiles == (net_wall::__PUBLIC | net_wall::__PRIVATE | net_wall::__DOMAIN)) << std::endl;
        net_wall::SetProfile(rule, net_wall::FWProfile(net_wall::__PUBLIC | net_wall::__PRIVATE | net_wall::__DOMAIN));
        net_wall::Cleanup(rule);
        
        
        // Firewall enable/disable test
        net_wall::SetEnabled(wall, false); //Disable the firewall in admin mode only work
        Sleep(5000);//Sleep for five seconds
        net_wall::SetEnabled(wall, true);//Enable the firewall in admin mode only work
        net_wall::Cleanup(wall);
    }
    catch (net_wall::permission_denied& pm) {
        std::cerr << pm.what << std::endl;
        net_wall::Cleanup(wall);
    }
    net_wall::Free();
    return 0;
}