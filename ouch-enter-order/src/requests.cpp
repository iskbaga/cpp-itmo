#include "requests.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<unsigned char> create_enter_order_request(
        const std::string & cl_ord_id,
        Side side,
        double volume,
        double price,
        const std::string & symbol,
        OrdType ord_type,
        TimeInForce time_in_force,
        Capacity capacity,
        const std::string & firm,
        const std::string & user)
{
    std::vector<unsigned char> message;
    std::map<Side, char> side_map = {{Side::Buy, 0x42}, {Side::Sell, 0x53}};
    std::map<Capacity, char> capacity_map = {{Capacity::Agency, '1'},
                                             {Capacity::Principal, '2'},
                                             {Capacity::RisklessPrincipal, '7'}};
    std::map<TimeInForce, char> time_in_force_map = {{TimeInForce::Day, '0'}, {TimeInForce::IOC, '3'}};

    // Message type - Enter Order (1 byte)
    PUSH_BYTE('O');

    // ClOrdID (14 bytes)
    PUSH_STRING(cl_ord_id, 14);

    // Side (1 byte)
    PUSH_BYTE(side_map[side]);

    // Volume (4 bytes)
    PUSH_UINT32(volume);

    // Symbol (4 bytes)
    PUSH_UINT32(std::stoull(symbol));

    // Price (4 bytes)
    PUSH_PRICE(price);

    // Firm (4 bytes)
    PUSH_STRING(firm, 4);

    // User (6 bytes)
    PUSH_STRING(user, 6);

    // Order Bit field (4 bytes)
    PUSH_BYTE(9);
    PUSH_BYTE(0);
    PUSH_BYTE(0);
    PUSH_BYTE(0);

    // Time In Force (1 byte)
    PUSH_BYTE(time_in_force_map[time_in_force]);

    // Capacity (1 byte)
    PUSH_BYTE(capacity_map[capacity]);

    return message;
}

std::vector<unsigned char> create_replace_order_request(
        const std::string & old_cl_ord_id,
        const std::string & new_cl_ord_id,
        double total_volume,
        double price,
        TimeInForce time_in_force,
        const std::string & user)
{
    std::vector<unsigned char> message;
    std::map<TimeInForce, char> time_in_force_map = {{TimeInForce::Day, '0'}, {TimeInForce::IOC, '3'}};

    // Message type - Replace Order (1 byte)
    PUSH_BYTE('U');

    // OLD Order Token (14 bytes)
    PUSH_STRING(old_cl_ord_id, 14);

    // NEW Order Token (14 bytes)
    PUSH_STRING(new_cl_ord_id, 14);

    // Volume (4 bytes)
    PUSH_UINT32(total_volume);

    // Price (4 bytes)
    PUSH_REPLACE_PRICE(price);

    // User (6 bytes)
    PUSH_STRING(user, 6);

    // Order Bit field (4 bytes)
    PUSH_BYTE(1);
    PUSH_BYTE(0);
    PUSH_BYTE(0);
    PUSH_BYTE(0);

    // Time In Force (1 byte)
    PUSH_BYTE(time_in_force_map[time_in_force]);

    return message;
}