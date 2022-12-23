//
//  bondinquiryservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef bondinquiryservice_h
#define bondinquiryservice_h

#include "soa.hpp"
#include "inquiryservice.hpp"
#include "products.hpp"
#include "util.hpp"


class BondInquiryService: public InquiryService<Bond>{
public:
    
    BondInquiryService();
    
    // Get data on our service given a key
    Inquiry<Bond>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(Inquiry<Bond> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<Inquiry<Bond>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<Inquiry<Bond>>* >& GetListeners() const override;
    
    // Send a quote back to the client
    void SendQuote(const string &inquiryId, double price) {}

    // Reject an inquiry from the client
    void RejectInquiry(const string &inquiryId) {}

private:
    
    map<string, Inquiry<Bond>*> priceBook;
    vector<ServiceListener<Inquiry<Bond>>*> listenerBook;
};

BondInquiryService::BondInquiryService(){
    priceBook = std::map<string, Inquiry<Bond>*>();
    listenerBook = std::vector<ServiceListener<Inquiry<Bond>>*>();
}

Inquiry<Bond>& BondInquiryService::GetData(string key) {
    return *priceBook[key];
}

void BondInquiryService::OnMessage(Inquiry<Bond> &data){
    // Use product id as the key for the getting data function
    for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
        (*i)->ProcessUpdate(data);
    }
}

void BondInquiryService::AddListener(ServiceListener<Inquiry<Bond>> *listener){
    listenerBook.push_back(listener);
}

const vector<ServiceListener<Inquiry<Bond>>*>& BondInquiryService::GetListeners() const{
    return listenerBook;
}


#endif /* bondinquiryservice_h */
