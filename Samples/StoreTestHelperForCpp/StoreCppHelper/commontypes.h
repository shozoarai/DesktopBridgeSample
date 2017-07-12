#pragma once

// 	Callback type definition of StoreAppLicense
typedef void(WINAPI *APPLICENSERECEIVED)(bool isActive, bool isTrial, bool isInactive, bool isFull);
typedef void(*APPLICENSEINTERNALRECEIVED)(Windows::Services::Store::StoreAppLicense^ appLicense);

//  Callback type definition of file name for listing
typedef void(WINAPI *RESULTFILERECEIVED)(PCWSTR filename);

//  Callback type definition of purchase action
typedef void(WINAPI *RESULTPURCHASERECEIVED)(bool result, PCWSTR msg);

//  Callback type definition of cunsumable balance
typedef void(WINAPI *RESULTBALANCERECEIVED)(bool result, UINT quantity, PCWSTR msg);

//  Callback type definition of  report consumable fulfillment
typedef void(WINAPI *RESULTPURCHASERECEIVED)(bool result, PCWSTR msg);
