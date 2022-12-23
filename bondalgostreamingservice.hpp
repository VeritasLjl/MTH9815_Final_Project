//
//  bondalgostreamingservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondalgostreamingservice_h
#define bondalgostreamingservice_h

#include"soa.hpp"
#include "util.hpp"
#include "pricingservice.hpp"
#include "streamingservice.hpp"

template<typename T>
class AlgoStream{
  
public:
    const string GetProductID(){return productId;}
    PriceStream<T>& GetPriceStream(){return priceStream;}
    AlgoStream(string _productId, PriceStream<T>& _priceStream): productId(_productId),priceStream(_priceStream){}
private:
    string productId;
    PriceStream<T> priceStream;
};


class BondAlgoStreamingService: public Service<string, AlgoStream<Bond>>{
public:
    // Get data on our service given a key
    AlgoStream<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(AlgoStream<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<AlgoStream<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<AlgoStream<Bond>>* >& GetListeners() const override;
    
    void AddPrice(Price<Bond> ps);

private:
    map<string,AlgoStream<Bond>*> bondAlgoStreamingBook;
    vector<ServiceListener<AlgoStream<Bond>>*> listenerBook;
};

AlgoStream<Bond>& BondAlgoStreamingService::GetData(string key) {
    return *bondAlgoStreamingBook[key];
}

void BondAlgoStreamingService::OnMessage(AlgoStream<Bond> &data){
    // Use product id as the key for the getting data function
    for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
        (*i)->ProcessUpdate(data);
    }
}

void BondAlgoStreamingService::AddListener(ServiceListener<AlgoStream<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<AlgoStream<Bond>>*>& BondAlgoStreamingService::GetListeners() const{
    return listenerBook;
}

void BondAlgoStreamingService::AddPrice(Price<Bond> ps){
    Bond b = ps.GetProduct();
    double up = ps.GetMid()+ps.GetBidOfferSpread()/2.0;
    double down = ps.GetMid()-ps.GetBidOfferSpread()/2.0;
    PriceStreamOrder bidorder = PriceStreamOrder(down, 1000000, 2000000, BID);
    PriceStreamOrder offerorder = PriceStreamOrder(up, 1000000, 2000000, OFFER);
    if(bondAlgoStreamingBook.count(b.GetProductId())==0){
        PriceStream<Bond> ps = PriceStream<Bond>(b,bidorder,offerorder);
        bondAlgoStreamingBook[b.GetProductId()] = new AlgoStream<Bond>(b.GetProductId(),ps);
        OnMessage(*bondAlgoStreamingBook[b.GetProductId()]);
    }
    else{
        PriceStream<Bond> ps = PriceStream<Bond>(b,bidorder,offerorder);
        delete bondAlgoStreamingBook[b.GetProductId()];
        bondAlgoStreamingBook[b.GetProductId()] = new AlgoStream<Bond>(b.GetProductId(),ps);
        OnMessage(*bondAlgoStreamingBook[b.GetProductId()]);
    }
}

#endif /* bondalgostreamingservice_h */
