//
//  guiservice.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef guiservice_h
#define guiservice_h

#include "util.hpp"
#include "soa.hpp"
#include <random>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

template<typename T>
class GUIService: public PricingService<T>{
public:
    long GetThrottle(){
        static long c = 0;
        static long thres = 300000000;
        long delta = rand()%2047;
        c+=delta;
        if(c>thres)c-=thres;
        return c;
    }
    
    map<string,Price<T>*>* GetGUIServiceBook() {return &GUIServiceBook;}
    
    // Get data on our service given a key
    Price<T>& GetData(string key) override;

    // The callback that a Connector should invoke for any new or updated data
    void OnMessage(Price<T> &data) override;

    // Add a listener to the Service for callbacks on add, remove, and update events
    // for data to the Service.
    void AddListener(ServiceListener<Price<T>> *listener) override;

    // Get all listeners on the Service.
    const vector< ServiceListener<Price<T>>* >& GetListeners() const override;
    
    long Throettle(Price<T>& data);
    
    void Traverse(string filename);
    
private:
    map<string,Price<T>*> GUIServiceBook;
    vector<ServiceListener<Price<T>>*> listenerBook;
};

template<typename T>
Price<T>& GUIService<T>::GetData(string key) {
    return *GUIServiceBook[key];
}

template<typename T>
void GUIService<T>::Traverse(string filename){
    ofstream output;
    output.open(filename);
    for(auto i=GUIServiceBook.begin();i!=GUIServiceBook.end();i++){
        output << "TIMESTAMP:  " << i->first;
        output << "  " << (i->second)->GetProduct() << "  " << (i->second)->GetMid() << "  " << (i->second)->GetBidOfferSpread() << endl;
    }
    output.close();
}


template<typename T>
void GUIService<T>::OnMessage(Price<T> &data){
    // Use product id as the key for the getting data function
    for(auto i = listenerBook.begin(); i!=listenerBook.end(); i++){
        (*i)->ProcessUpdate(data);
    }
}

template<typename T>
void GUIService<T>::AddListener(ServiceListener<Price<T>> *listener){
    listenerBook.push_back(listener);
}

template<typename T>
const vector<ServiceListener<Price<T>>*>& GUIService<T>::GetListeners() const{
    return listenerBook;
}
    
template<typename T>
long GUIService<T>::Throettle(Price<T>& data){
    long th = GetThrottle();
    GUIServiceBook[to_string(th)] = &data;
    return th;
}

#endif /* guiservice_h */
