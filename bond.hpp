//
//  bond.h
//  Trading System
//
//  Created by 廖佳珑 on 12/22/22.
//

#ifndef bond_h
#define bond_h

#include <vector>
#include <map>
#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace boost::gregorian;

vector<string> bondCusip={
"91282CFX4", // 2y
"91282CGA3", // 3y
"91282CFZ9", // 5y
"91282CFY2", // 7y
"91282CFV8", // 10y
"912810TM0", // 20y
"912810TL2"}; // 30y

vector<float> bondCoupon={
0.04505, // 2y
0.04093, // 3y
0.03974, // 5y
0.03890, // 7y
0.03625, // 10y
0.04027, // 20y
0.03513}; // 30y

vector<date> bondMaturity={
date(2024,Dec,30), // 2y
date(2025,Dec,15), // 3y
date(2027,Dec,30), // 5y
date(2029,Dec,30), // 7y
date(2032,Dec,15), // 10y
date(2042,Dec,30), // 20y
date(2052,Dec,15)}; // 30y

map<string,float> bondRisk={
{"91282CFX4",0.02}, // 2y
{"91282CGA3",0.03}, // 3y
{"91282CFZ9",0.05}, // 5y
{"91282CFY2",0.06}, // 7y
{"91282CFV8",0.09}, // 10y
{"912810TM0",0.09}, // 20y
{"912810TL2",0.2}}; // 30y

#endif /* bond_h */
