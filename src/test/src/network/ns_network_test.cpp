#include <limits.h>
#include "../../../network/ns_network.h"
#include "../../../network/ns_timer.h"
#include "gtest/gtest.h"
#include <memory>

using namespace ns_ns;

TEST(test_network, network_creation)
{
    // router(int nodeID, int numbInterfaces, double xAxis, double yAxis);
    std::shared_ptr<router> router_1 (new router(0, 2, 1.1, 1.1));
    std::shared_ptr<router> router_2 (new router(1, 2, 2.2, 2.2));
    std::shared_ptr<router> router_3 (new router(2, 2, 3.3, 3.3));

    EXPECT_EQ(0, router_1->get_node_id()); 
    EXPECT_EQ(1, router_2->get_node_id()); 
    EXPECT_EQ(2, router_3->get_node_id());

    // router_interface(int nodeID, int interfaceID, std::string mac, std::string ip, int mask, int interfaceQueue, double interfaceSpeed);
    std::shared_ptr<router_interface> router_if_1_1 (new router_interface(0, 0, "00:00:00:00:00:01", "192.168.0.1", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_1_2 (new router_interface(0, 1, "00:00:00:00:00:02", "192.168.2.1", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_1_3 (new router_interface(0, 2, "00:00:00:00:00:07", "192.168.3.1", 24, 10, 100));
    std::shared_ptr<router_interface> router_if_2_1 (new router_interface(1, 0, "00:00:00:00:00:03", "192.168.0.2", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_2_2 (new router_interface(1, 1, "00:00:00:00:00:04", "192.168.1.1", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_3_1 (new router_interface(2, 0, "00:00:00:00:00:05", "192.168.1.2", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_3_2 (new router_interface(2, 1, "00:00:00:00:00:06", "192.168.2.2", 24, 10, 100.1));
    std::shared_ptr<router_interface> router_if_3_3 (new router_interface(2, 2, "00:00:00:00:00:08", "192.168.3.2", 24, 10, 100));

    EXPECT_EQ(0, router_if_1_1->get_interface_id()); 
    EXPECT_EQ(1, router_if_1_2->get_interface_id());
    EXPECT_EQ(2, router_if_1_3->get_interface_id());
    EXPECT_EQ(0, router_if_2_1->get_interface_id()); 
    EXPECT_EQ(1, router_if_2_2->get_interface_id());
    EXPECT_EQ(0, router_if_3_1->get_interface_id()); 
    EXPECT_EQ(1, router_if_3_2->get_interface_id());
    EXPECT_EQ(2, router_if_3_3->get_interface_id());

    std::string mac_address[] = {"00:00:00:00:00:01", "00:00:00:00:00:02", "00:00:00:00:00:03",
                                 "00:00:00:00:00:04", "00:00:00:00:00:05", "00:00:00:00:00:06"};

    router_if_1_1->set_interface_address(mac_address[0]);
    router_if_1_2->set_interface_address(mac_address[1]);
    router_if_2_1->set_interface_address(mac_address[2]);
    router_if_2_2->set_interface_address(mac_address[3]);
    router_if_3_1->set_interface_address(mac_address[4]);
    router_if_3_2->set_interface_address(mac_address[5]);
   
    EXPECT_EQ(mac_address[0], router_if_1_1->get_interface_address()); 
    EXPECT_EQ(mac_address[1], router_if_1_2->get_interface_address()); 
    EXPECT_EQ(mac_address[2], router_if_2_1->get_interface_address()); 
    EXPECT_EQ(mac_address[3], router_if_2_2->get_interface_address()); 
    EXPECT_EQ(mac_address[4], router_if_3_1->get_interface_address()); 
    EXPECT_EQ(mac_address[5], router_if_3_2->get_interface_address()); 

    router_1->add_interface(router_if_1_1); 
    router_1->add_interface(router_if_1_2);
    router_1->add_interface(router_if_1_3);
    router_2->add_interface(router_if_2_1); 
    router_2->add_interface(router_if_2_2);
    router_3->add_interface(router_if_3_1); 
    router_3->add_interface(router_if_3_2);
    router_3->add_interface(router_if_3_3);
   
    std::shared_ptr<router_link> router_link_1 (new router_link(0));
    std::shared_ptr<router_link> router_link_2 (new router_link(1));
    std::shared_ptr<router_link> router_link_3 (new router_link(2));
    std::shared_ptr<router_link> router_link_4 (new router_link(3));

    // create_link(router* src_router, router_interface* src_if, router* dst_router, router_interface* dst_if, double link_delay, double link_weight);
    EXPECT_EQ(0, router_link_1->create_link(router_1, router_if_1_1, router_2, router_if_2_1, 100.2, 10.2));    
    EXPECT_EQ(1, router_link_1->create_link(router_1, router_if_1_2, router_1, router_if_1_2, 100.2, 10.2));    
    EXPECT_EQ(1, router_link_1->create_link(router_1, router_if_1_1, router_2, router_if_2_1, 100.2, 10.2));   
    EXPECT_EQ(0, router_link_2->create_link(router_2, router_if_2_2, router_3, router_if_3_1, 100.2, 10.2));    
    EXPECT_EQ(0, router_link_3->create_link(router_3, router_if_3_2, router_1, router_if_1_2, 100, 10));    
    EXPECT_EQ(0, router_link_4->create_link(router_1, router_if_1_3, router_3, router_if_3_3, 1000, 100));   

    EXPECT_EQ(10.2, router_link_1->get_link_cost());
    EXPECT_EQ(10.2, router_link_2->get_link_cost());
    EXPECT_EQ(10, router_link_3->get_link_cost());
    EXPECT_EQ(100, router_link_4->get_link_cost());
    
    std::shared_ptr<router_network> network (new router_network);

    network->add_router(router_1);
    network->add_router(router_2);
    network->add_router(router_3);
   
    std::shared_ptr<router> r_temp = network->get_router(0);
    EXPECT_EQ(0, r_temp->get_node_id());
    r_temp = network->get_router(1);
    EXPECT_EQ(1, r_temp->get_node_id());
    r_temp = network->get_router(2);
    EXPECT_EQ(2, r_temp->get_node_id());
    //r_temp = network->get_router(3);
    //EXPECT_EQ(NULL, r_temp);
    
    EXPECT_EQ(3, network->number_of_routers()); 
    
    network->add_link(router_link_1);
    network->add_link(router_link_2);
    network->add_link(router_link_3);
    network->add_link(router_link_4);
     
    EXPECT_EQ(4, network->number_of_links());
    
    std::shared_ptr<router_link> temp = network->find_link(router_1->get_node_id(), router_2->get_node_id());
    EXPECT_EQ("00:00:00:00:00:01", temp->get_src_if()->get_interface_address()); 
    network->calculate_shortest_path(UNDIRECTED_GRAPH, LINK_DELAY);
    r_temp = network->get_router(0);
    EXPECT_EQ(2, r_temp->get_routing_table()->get_num_of_routing_table_entries()); 
    r_temp = network->get_router(1);
    EXPECT_EQ(2, r_temp->get_routing_table()->get_num_of_routing_table_entries()); 
    r_temp = network->get_router(2);
    EXPECT_EQ(2, r_temp->get_routing_table()->get_num_of_routing_table_entries());
}

TEST(test_network, shortest_path_creation)
{
    shortest_path adjacency_list(6);
    // 0 = a
    adjacency_list.add_edge(DIRECTED_GRAPH, 0, 5, 14);
    adjacency_list.add_edge(DIRECTED_GRAPH, 0, 1, 7);
    adjacency_list.add_edge(DIRECTED_GRAPH, 0, 2, 9);
    // 1 = b
    adjacency_list.add_edge(DIRECTED_GRAPH, 1, 0, 7);
    adjacency_list.add_edge(DIRECTED_GRAPH, 1, 2, 10);
    adjacency_list.add_edge(DIRECTED_GRAPH, 1, 3, 15);
    // 2 = c
    adjacency_list.add_edge(DIRECTED_GRAPH, 2, 0, 9);
    adjacency_list.add_edge(DIRECTED_GRAPH, 2, 1, 10);
    adjacency_list.add_edge(DIRECTED_GRAPH, 2, 3, 11);
    adjacency_list.add_edge(DIRECTED_GRAPH, 2, 5, 2);
    // 3 = d
    adjacency_list.add_edge(DIRECTED_GRAPH, 3, 1, 15);
    adjacency_list.add_edge(DIRECTED_GRAPH, 3, 2, 11);
    adjacency_list.add_edge(DIRECTED_GRAPH, 3, 4, 6);
    // 4 = e
    adjacency_list.add_edge(DIRECTED_GRAPH, 4, 3, 6);
    adjacency_list.add_edge(DIRECTED_GRAPH, 4, 5, 9);
    // 5 = f
    adjacency_list.add_edge(DIRECTED_GRAPH, 5, 0, 14);
    adjacency_list.add_edge(DIRECTED_GRAPH, 5, 2, 2);
    adjacency_list.add_edge(DIRECTED_GRAPH, 5, 4, 9);
 
    std::vector<double> min_distance;
    std::vector<int> previous;
    adjacency_list.dijikstra_compute_paths(0, min_distance, previous);
    std::vector<int> path;
    adjacency_list.dijkstra_get_shortest_path_to(path, 4, previous);
    std::vector<int> expected_path;
    expected_path.push_back(4);  
    expected_path.push_back(5);  
    expected_path.push_back(2);  
    expected_path.push_back(0);  
    EXPECT_EQ(expected_path, path); 
}

TEST(test_network, shortest_path_creation_2)
{
    shortest_path adjacency_list(3);
    
    // 0 = a
    adjacency_list.add_edge(DIRECTED_GRAPH, 0, 1, 1);
    adjacency_list.add_edge(DIRECTED_GRAPH, 0, 2, 1);
    
    // 1 = b
    adjacency_list.add_edge(DIRECTED_GRAPH, 1, 0, 1);
    adjacency_list.add_edge(DIRECTED_GRAPH, 1, 2, 1);
    
    // 2 = c
    adjacency_list.add_edge(DIRECTED_GRAPH, 2, 0, 1);
    adjacency_list.add_edge(DIRECTED_GRAPH, 2, 1, 1);
 
    std::vector<double> min_distance;
    std::vector<int> previous;
    adjacency_list.dijikstra_compute_paths(0, min_distance, previous);
    std::vector<int> path;
    adjacency_list.dijkstra_get_shortest_path_to(path, 2, previous);
    std::vector<int> expected_path;
    expected_path.push_back(2);  
    expected_path.push_back(0);  
    EXPECT_EQ(expected_path, path); 
    
    min_distance.clear();
    previous.clear();
    adjacency_list.dijikstra_compute_paths(1, min_distance, previous);
    path.clear();
    adjacency_list.dijkstra_get_shortest_path_to(path, 2, previous);
    expected_path.clear();
    expected_path.push_back(2);  
    expected_path.push_back(1);  
    EXPECT_EQ(expected_path, path); 
    
    min_distance.clear();
    previous.clear();
    adjacency_list.dijikstra_compute_paths(2, min_distance, previous);
    path.clear();
    adjacency_list.dijkstra_get_shortest_path_to(path, 0, previous);
    expected_path.clear();
    expected_path.push_back(0);  
    expected_path.push_back(2);  
    EXPECT_EQ(expected_path, path); 
}

TEST(test_network, shortest_path_creation_3)
{
    shortest_path adjacency_list(7);
    
    // 0 = a
    adjacency_list.add_edge(UNDIRECTED_GRAPH, 0, 1, 1);
    
    // 1 = b
    adjacency_list.add_edge(UNDIRECTED_GRAPH, 1, 2, 1);
    
    // 2 = c
    adjacency_list.add_edge(UNDIRECTED_GRAPH, 2, 3, 1);
    
    // 3 = d
    adjacency_list.add_edge(UNDIRECTED_GRAPH, 3, 4, 1);
    
    // 4 = e
    adjacency_list.add_edge(UNDIRECTED_GRAPH, 4, 5, 1);
    
    // 5 = f
    adjacency_list.add_edge(UNDIRECTED_GRAPH, 5, 6, 1);
    
    std::vector<double> min_distance;
    std::vector<int> previous;
    adjacency_list.dijikstra_compute_paths(1, min_distance, previous);
    EXPECT_EQ(1, min_distance[0]); 
    EXPECT_EQ(0, min_distance[1]); 
    EXPECT_EQ(1, min_distance[2]); 
    EXPECT_EQ(2, min_distance[3]); 
    EXPECT_EQ(3, min_distance[4]); 
    EXPECT_EQ(4, min_distance[5]); 
    EXPECT_EQ(5, min_distance[6]); 
    std::vector<int> path;
    adjacency_list.dijkstra_get_shortest_path_to(path, 2, previous);
    std::vector<int> expected_path;
    expected_path.push_back(2);  
    expected_path.push_back(1);  
    EXPECT_EQ(expected_path, path); 
    
    min_distance.clear();
    previous.clear();
    adjacency_list.dijikstra_compute_paths(0, min_distance, previous);
    path.clear();
    adjacency_list.dijkstra_get_shortest_path_to(path, 6, previous);
    expected_path.clear();
    expected_path.push_back(6);  
    expected_path.push_back(5);  
    expected_path.push_back(4);  
    expected_path.push_back(3);  
    expected_path.push_back(2);  
    expected_path.push_back(1);  
    expected_path.push_back(0);  
    EXPECT_EQ(expected_path, path);
    EXPECT_EQ(0, min_distance[0]); 
    EXPECT_EQ(1, min_distance[1]); 
    EXPECT_EQ(2, min_distance[2]); 
    EXPECT_EQ(3, min_distance[3]); 
    EXPECT_EQ(4, min_distance[4]); 
    EXPECT_EQ(5, min_distance[5]); 
    EXPECT_EQ(6, min_distance[6]); 
}

TEST(test_network, timer_test)
{
    timer t;
   
    t.start_timer();
    EXPECT_EQ(true, t.is_timer_running());
   
    sleep(1);
 
    t.stop_timer();
    EXPECT_EQ(false, t.is_timer_running());

    EXPECT_EQ(1, t.get_elapsed_time_in_sec());

    t.reset_timer();
    sleep(1);
    EXPECT_EQ(1, t.get_elapsed_time_in_sec());
 
    t.stop_timer();
    EXPECT_EQ(false, t.is_timer_running());
}
