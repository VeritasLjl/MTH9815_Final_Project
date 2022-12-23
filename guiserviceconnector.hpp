//
//  guiserviceconnector.h
//  Trading System
//
//  Created by 廖佳珑 on 12/23/22.
//

#ifndef guiserviceconnector_h
#define guiserviceconnector_h

#include "soa.hpp"
#include "util.hpp"
#include "guiservice.hpp"

template<typename T>
class GUIServiceConnector:public Connector<GUIService<T>>{
public:
    GUIServiceConnector(GUIService<T>* _guiservice){
        guiservice = _guiservice;
    }
    
    void Publish(GUIService<T> &gui) override;
    
private:
    GUIService<T>* guiservice;
};

template<typename T>
void GUIServiceConnector<T>:: Publish(GUIService<T> &gui){
//    ofstream output;
    string filename ="gui.txt";
    filename = PATH + filename;
//    output.open(filename);
    guiservice->Traverse(filename);
//    output.close();
}

#endif /* guiserviceconnector_h */
