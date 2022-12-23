//
//  main.cpp
//  Trading System
//
//  Created by 廖佳珑 on 12/22/22.
//

#include <iostream>
#include "bond.hpp"
#include "bondalgoexecutionservice.hpp"
#include "bondalgoexecutionservicelistener.hpp"
#include "bondalgostreamingservice.hpp"
#include "bondalgostreamingservicelistener.hpp"
#include "bondexecutionservice.hpp"
#include "bondexecutionservicelistener.hpp"
#include "bondhistoricaldataservice.hpp"
#include "bondmarketdataservice.hpp"
#include "bondmarketdataserviceconnector.hpp"
#include "bondinquiryservice.hpp"
#include "bondpricingserviceconnector.hpp"
#include "bondpositionservice.hpp"
#include "bondpositionservicelistener.hpp"
#include "bondpricingservice.hpp"
#include "bondriskservice.hpp"
#include "bondriskservicelistener.h"
#include "bondstreamingservice.hpp"
#include "bondstreamingservicelistener.hpp"
#include "bondtradebookingservice.hpp"
#include "bondtradebookingserviceconnector.hpp"
#include "data.hpp"
#include "executionservice.hpp"
#include "guiservice.hpp"
#include "guiserviceconnector.hpp"
#include "guiservicelistener.hpp"
#include "historicaldataservice.hpp"
#include "inquiryservice.hpp"
#include "marketdataservice.hpp"
#include "positionservice.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include "riskservice.hpp"
#include "soa.hpp"
#include "streamingservice.hpp"
#include "tradebookingservice.hpp"
#include "util.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // get everything initialized, e.g. the printing setting, DEBUG mode can be open in util
    init();
    
    
//    BondPriceGenerator();
//    BondTradeGenerator();
//    BondMarketDateGenerator();

    BondPricingService bps = BondPricingService();
    BondPricingSerciveConnector bpsc = BondPricingSerciveConnector(&bps);
    
    BondAlgoStreamingService bass = BondAlgoStreamingService();
    BondAlgoStreamingServiceListener bassc = BondAlgoStreamingServiceListener(&bass);
    bps.AddListener(&bassc);
    
    BondStreamingService bss = BondStreamingService();
    BondStreamingServiceListener bssl = BondStreamingServiceListener(&bss);
    bass.AddListener(&bssl);

    BondPositionService bpsts = BondPositionService();
    BondPositionServiceListener bpstsln = BondPositionServiceListener(&bpsts);

    BondTradeBookingService btbs = BondTradeBookingService();
    btbs.AddListener(&bpstsln);

    BondTradeBookingServiceConnector btbsc = BondTradeBookingServiceConnector(&btbs);
    btbsc.Subscribe();
    
    BondAlgoExecutionService baes = BondAlgoExecutionService();
    BondAlgoExecutionServiceListener baesc = BondAlgoExecutionServiceListener(&baes);
    
    BondExecutionService bes = BondExecutionService();
    BondExecutionServiceListener besl = BondExecutionServiceListener(&bes);
    
    baes.AddListener(&besl);
    
    BondMarketDataService bmds = BondMarketDataService();
    BondMarketDataServiceConnector bmdsc= BondMarketDataServiceConnector(&bmds);
    bmds.AddListener(&baesc);
    
    GUIService<Bond> gui = GUIService<Bond>();
    GUIServiceListener<Bond> guil = GUIServiceListener<Bond>(&gui);
    bps.AddListener(&guil);
    
    GUIServiceConnector<Bond> guic = GUIServiceConnector<Bond>(&gui);
    
    
    
    bpsc.Subscribe();
    guic.Publish(gui);
    
    btbsc.Subscribe();
    guic.Publish(gui);
    
    bmdsc.Subscribe();
    
    return 0;
}
