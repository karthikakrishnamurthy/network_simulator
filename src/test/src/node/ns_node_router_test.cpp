#include <limits.h>
#include "gtest/gtest.h"
#include "../../../node/ns_node_router.h"

using namespace ns_ns;

TEST(test_router, router_creation)
{
    // router(int nodeID, int numbInterfaces, double xAxis, double yAxis);
    std::shared_ptr<router> router_1 (new router(1, 1, 1.1, 1.1));
    std::shared_ptr<router> router_2 (new router(2, 2, 2.2, 2.2));

    // Check whether nodes are created properly by checking router id
    EXPECT_EQ(1, router_1->get_node_id()); 
    EXPECT_EQ(2, router_2->get_node_id()); 
}

TEST(test_router, router_if_list_creation)
{
    // Create two routers
    std::shared_ptr<router> router_1 (new router(1, 1, 1.1, 1.1));
    std::shared_ptr<router> router_2 (new router(2, 2, 2.2, 2.2));

    EXPECT_EQ(1, router_1->get_node_id()); 
    EXPECT_EQ(2, router_2->get_node_id()); 

    // router_interface(int nodeID, int interfaceID, std::string mac, std::string ip, int mask, int interfaceQueue, double interfaceSpeed);
    std::shared_ptr<router_interface> router_if_1 (new router_interface(1, 1, "00:00:00:00:00:01", "192.169.0.0", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_2 (new router_interface(1, 2, "00:00:00:00:00:02", "192.169.1.0", 24, 10, 100.1));

    // Check whether interfaces are created properly by checking interface id
    EXPECT_EQ(1, router_if_1->get_interface_id()); 
    EXPECT_EQ(2, router_if_2->get_interface_id());

    std::string mac_address_1 = "00:00:00:00:00:01";
    std::string mac_address_2 = "00:00:00:00:00:02";

    // Configure MAC address for interfaces
    router_if_1->set_interface_address(mac_address_1);
    router_if_2->set_interface_address(mac_address_2);
  
    // Check whether MAC addresses are configured properly 
    EXPECT_EQ(mac_address_1, router_if_1->get_interface_address()); 
    EXPECT_EQ(mac_address_2, router_if_2->get_interface_address()); 

    // Add interfaces to router 1
    router_1->add_interface(router_if_1); 
    router_1->add_interface(router_if_2);

    // Get created interfaces and check interface id
    std::shared_ptr<router_interface> router_if_3 = router_1->get_interface(1); 
    EXPECT_EQ(1, router_if_3->get_interface_id());
    std::shared_ptr<router_interface> router_if_4 = router_1->get_interface(2); 
    EXPECT_EQ(2, router_if_4->get_interface_id());
    
    // Following interface is not present
    std::shared_ptr<router_interface> router_if_5 = router_2->get_interface(1); 
    //EXPECT_EQ(NULL, router_if_5);

    // Check interface presence with MAC address
    router_if_3 = router_1->get_interface(mac_address_1); 
    EXPECT_EQ(mac_address_1, router_if_3->get_interface_address());
    
    // Following interface is not present
    router_if_3 = router_2->get_interface(mac_address_1); 
    //EXPECT_EQ(NULL, router_if_3);
}



