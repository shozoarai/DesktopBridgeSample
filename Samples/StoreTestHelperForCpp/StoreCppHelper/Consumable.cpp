// Consumable.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

using namespace std;

using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Services::Store;

///////////////////////////////////////////////////////////////////
//
//  Definition Get Cosumable Balance callback function type for GetConsumableBalanceRemaining
typedef void(WINAPI *RESULTBALANCERECEIVED)(bool result, UINT quantity, PCWSTR msg);
static RESULTBALANCERECEIVED resultBalanceCallback;
void OnCosumableBalanceResultCallback(IAsyncOperation<StoreConsumableResult ^> ^asyncOperation, AsyncStatus asyncStatus);

///////////////////////////////////////////////////////////////////
//
//  Define ReportConsumableFulfillment callback function for ReportConsumableFulfillment
void OnCosumableFulfillmentCallback(IAsyncOperation<StoreConsumableResult ^> ^asyncOperation, AsyncStatus asyncStatus);
typedef void(WINAPI *RESULTPURCHASERECEIVED)(bool result, PCWSTR msg);
static RESULTPURCHASERECEIVED resultPurchaseReceivedCallback;


///////////////////////////////////////////////////////////////////
//  Definition GetConsumableBalanceRemaining function
//
///////////////////////////////////////////////////////////////////
bool WINAPI GetConsumableBalanceRemaining(PCWSTR itemid, void* pfnResultBalanceCallback)
{
	String^ item = ref new String(itemid);
	resultBalanceCallback = (RESULTBALANCERECEIVED)pfnResultBalanceCallback;
	auto storeContext = StoreContext::GetDefault();

	auto storeConsumableResultOperation = storeContext->GetConsumableBalanceRemainingAsync(item);
	storeConsumableResultOperation->Completed =
		ref new AsyncOperationCompletedHandler<StoreConsumableResult^>(&OnCosumableBalanceResultCallback);
	return true;
}

void OnCosumableBalanceResultCallback(IAsyncOperation<StoreConsumableResult ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	auto storeConsumableResult = asyncOperation->GetResults();

	bool result = false;
	UINT balance = 0;
	String^ msg = "";
	String^ extendedError = "";
	if (storeConsumableResult->ExtendedError.Value != S_OK)
	{
		extendedError = storeConsumableResult->ExtendedError.Value.ToString();
	}

	switch (storeConsumableResult->Status)
	{
	case StoreConsumableStatus::Succeeded:
		msg = "Remaining balance: " + storeConsumableResult->BalanceRemaining;
		balance = storeConsumableResult->BalanceRemaining;
		result = true;
		break;

	case StoreConsumableStatus::NetworkError:
		msg = "Could not retrieve balance due to a network error. " +
			"ExtendedError: " + extendedError;
		break;

	case StoreConsumableStatus::ServerError:
		msg = "Could not retrieve balance due to a server error. " +
			"ExtendedError: " + extendedError;
		break;

	default:
		msg = "Could not retrieve balance due to an unknown error. " +
			"ExtendedError: " + extendedError;
		break;
	}

	if (resultBalanceCallback)
	{
		resultBalanceCallback(result, balance, msg->Data());
		resultBalanceCallback = nullptr;
	}
}


///////////////////////////////////////////////////////////////////
//  Definition ReportConsumableFulfillment function
//
//  Report consumable fulfillment of add-on.
///////////////////////////////////////////////////////////////////
bool WINAPI ReportConsumableFulfillment(PCWSTR itemid, UINT quantity, void* pfnPurchaseReceivedCallback)
{
	String^ item = ref new String(itemid);
	resultPurchaseReceivedCallback = (RESULTPURCHASERECEIVED)pfnPurchaseReceivedCallback;

	auto storeContext = StoreContext::GetDefault();
	GUID guid;
	if (FAILED(CoCreateGuid(&guid)))
	{
		String^ msg = "Failed to create a tracking GUID.";
		if (resultPurchaseReceivedCallback)
		{
			resultPurchaseReceivedCallback(false, msg->Data());
			resultPurchaseReceivedCallback = nullptr;
		}
		return false;
	}
	Guid trackId(guid);
	auto storeConsumableResultOperation = storeContext->ReportConsumableFulfillmentAsync(item, quantity, trackId);
	storeConsumableResultOperation->Completed =
		ref new AsyncOperationCompletedHandler<StoreConsumableResult^>(&OnCosumableFulfillmentCallback);
	return true;
}

void OnCosumableFulfillmentCallback(IAsyncOperation<StoreConsumableResult ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	auto storeConsumableResult = asyncOperation->GetResults();

	bool result = false;
	String^ msg = "";
	String^ extendedError = "";
	if (storeConsumableResult->ExtendedError.Value != S_OK)
	{
		extendedError = storeConsumableResult->ExtendedError.Value.ToString();
	}

	// Check ReportConsumableFulfillment Result
	switch (storeConsumableResult->Status)
	{
	case StoreConsumableStatus::Succeeded:
		result = true;
		msg = "The fulfillment was successful. " +
			"Remaining balance:" + storeConsumableResult->BalanceRemaining;
		break;

	case StoreConsumableStatus::InsufficentQuantity:
		msg = "The fulfillment was unsuccessful because the remaining " +
			"balance is insufficient. Remaining balance:" + storeConsumableResult->BalanceRemaining;
		break;

	case StoreConsumableStatus::NetworkError:
		msg = "The fulfillment was unsuccessful due to a network error. " +
			"ExtendedError: " + extendedError;
		break;

	case StoreConsumableStatus::ServerError:
		msg = "The fulfillment was unsuccessful due to a server error. " +
			"ExtendedError: " + extendedError;
		break;

	default:
		msg = "The fulfillment was unsuccessful due to an unknown error. " +
			"ExtendedError: " + extendedError;
		break;
	}
	if (resultPurchaseReceivedCallback)
	{
		resultPurchaseReceivedCallback(result, msg->Data());
		resultPurchaseReceivedCallback = nullptr;
	}

}
