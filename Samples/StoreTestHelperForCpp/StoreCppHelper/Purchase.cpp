// Purchase.cpp : Defines the exported functions for the DLL application.
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
// 	Define App Purchase callback function type for RequestPurchaseApp.
typedef void(WINAPI *RESULTPURCHASERECEIVED)(bool result, PCWSTR msg);
static RESULTPURCHASERECEIVED resultPurchaseReceivedCallback;
StoreContext^ storeContext;
StoreProductResult^ storeProductResult;

void OnStoreProductResultOperation(IAsyncOperation<StoreProductResult ^> ^asyncOperation, AsyncStatus asyncStatus);
void OnStoreAppPurchaseLicenseOperation(IAsyncOperation<StoreAppLicense ^> ^asyncOperation, AsyncStatus asyncStatus);
void OnAppStorePurchaseResultOperation(IAsyncOperation<StorePurchaseResult ^> ^asyncOperation, AsyncStatus asyncStatus);

///////////////////////////////////////////////////////////////////
//
// 	Define Addon Purchase callback function type for RequestPurchaseAddon.
void OnAddonStorePurchaseResultOperation(IAsyncOperation<StorePurchaseResult ^> ^asyncOperation, AsyncStatus asyncStatus);


///////////////////////////////////////////////////////////////////
//  Definition RequestPurchaseApp function
//
//  Purchase App.  License state change from trial to full license.
///////////////////////////////////////////////////////////////////
bool WINAPI RequestPurchaseApp(HWND hWnd, void* pfnResultPurchaseReceivedCallback)
{
	resultPurchaseReceivedCallback = (RESULTPURCHASERECEIVED)pfnResultPurchaseReceivedCallback;

	// Initialize of Window handle for Windows Runtime Object with UI.
	// UI を持つ Windows Runtime オブジェクトは、ウィンドウ ハンドルで初期化します
	IInitializeWithWindow* pIInitializeWithWindow;

	storeContext = StoreContext::GetDefault();
	// Cast from StoreContext to IInspectable
	// StoreContext を IInspectable へキャスト
	IInspectable* iInspectable = reinterpret_cast<IInspectable*>(storeContext);
	// Get IInitializeWithWindow from IInspectable, then initialize.
	// IInspectable より、IInitializeWithWindow を取得して初期化
	if (SUCCEEDED(iInspectable->QueryInterface(IID_PPV_ARGS(&pIInitializeWithWindow))))
	{
		pIInitializeWithWindow->Initialize((HWND)(void *)hWnd);
		// Get StoreProduct
		auto stroreProductResultOperation = storeContext->GetStoreProductForCurrentAppAsync();
		stroreProductResultOperation->Completed =
			ref new AsyncOperationCompletedHandler<StoreProductResult^>(&OnStoreProductResultOperation);

		// Release IInitializeWithWindow.
		// IInitializeWithWindow インターフェースを開放します
		pIInitializeWithWindow->Release();

		return true;
	}

	return false;

}

void OnStoreProductResultOperation(IAsyncOperation<StoreProductResult ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	String^ msg = "";
	// Check StoreProduct
	storeProductResult = asyncOperation->GetResults();

	if (storeProductResult->ExtendedError.Value != S_OK)
	{
		msg = "Error:" + storeProductResult->ExtendedError.Value.ToString();
		resultPurchaseReceivedCallback(false, msg->Data());
		resultPurchaseReceivedCallback = nullptr;
		return;
	}

	// Check App license.
	auto storeAppPurchaseLicenseOperation = storeContext->GetAppLicenseAsync();
	storeAppPurchaseLicenseOperation->Completed =
		ref new AsyncOperationCompletedHandler<StoreAppLicense^>(&OnStoreAppPurchaseLicenseOperation);
}

void OnStoreAppPurchaseLicenseOperation(IAsyncOperation<StoreAppLicense ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// Check App license.
	auto storeAppLicense = asyncOperation->GetResults();
	if (storeAppLicense->IsActive)
	{
		String^ msg = "You already bought this app and have a fully-licensed version.";
		resultPurchaseReceivedCallback(false, msg->Data());
		return;
	}

	// Request purchase app
	auto storePurchaseResultOperation = storeProductResult->Product->RequestPurchaseAsync();
	storePurchaseResultOperation->Completed =
		ref new AsyncOperationCompletedHandler<StorePurchaseResult^>(&OnAppStorePurchaseResultOperation);
}

void OnAppStorePurchaseResultOperation(IAsyncOperation<StorePurchaseResult ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// Check app purchase result.
	auto storePurchaseResult = asyncOperation->GetResults();
	String^ msg = "";
	bool result = false;
	storeProductResult = nullptr;

	if (storePurchaseResult->ExtendedError.Value != S_OK)
	{
		msg = "Error:" + storePurchaseResult->ExtendedError.Value.ToString();
		resultPurchaseReceivedCallback(result, msg->Data());
		resultPurchaseReceivedCallback = nullptr;
		return;
	}
	switch (storePurchaseResult->Status)
	{
	case StorePurchaseStatus::AlreadyPurchased:
		msg = "You already bought this app and have a fully-licensed version.";
		break;

	case StorePurchaseStatus::Succeeded:
		// License will refresh automatically using the StoreContext.OfflineLicensesChanged event
		msg = "To buy App was successful.";
		result = true;
		break;

	case StorePurchaseStatus::NotPurchased:
		msg = "Product was not purchased, it may have been canceled.";
		break;

	case StorePurchaseStatus::NetworkError:
		msg = "Product was not purchased due to a Network Error.";
		break;

	case StorePurchaseStatus::ServerError:
		msg = "Product was not purchased due to a Server Error.";
		break;

	default:
		msg = "Product was not purchased due to an Unknown Error.";
		break;
	}

	storeContext = nullptr;

	if (resultPurchaseReceivedCallback)
	{
		resultPurchaseReceivedCallback(result, msg->Data());
		resultPurchaseReceivedCallback = nullptr;
	}
}


///////////////////////////////////////////////////////////////////
//  Definition RequestPurchaseAddon function
//
//  Purhase add-on.
///////////////////////////////////////////////////////////////////
bool WINAPI RequestPurchaseAddon(HWND hWnd, PCWSTR itemid, void* pfnResultPurchaseReceivedCallback)
{
	String^ itemID = ref new String(itemid);

	resultPurchaseReceivedCallback = (RESULTPURCHASERECEIVED)pfnResultPurchaseReceivedCallback;

	// Initialize of Window handle for Windows Runtime Object with UI.
	// UI を持つ Windows Runtime オブジェクトは、ウィンドウ ハンドルで初期化します
	IInitializeWithWindow* pIInitializeWithWindow;

	auto storeContext = StoreContext::GetDefault();
	// Cast from StoreContext to IInspectable
	// StoreContext を IInspectable へキャスト
	IInspectable* iInspectable = reinterpret_cast<IInspectable*>(storeContext);
	// Get IInitializeWithWindow from IInspectable, then initialize.
	// IInspectable より、IInitializeWithWindow を取得して初期化
	if (SUCCEEDED(iInspectable->QueryInterface(IID_PPV_ARGS(&pIInitializeWithWindow))))
	{
		pIInitializeWithWindow->Initialize((HWND)(void *)hWnd);
		// Putchase add-on
		auto strorePurchaseResultOperation = storeContext->RequestPurchaseAsync(itemID);
		strorePurchaseResultOperation->Completed =
			ref new AsyncOperationCompletedHandler<StorePurchaseResult^>(&OnAddonStorePurchaseResultOperation);

		// Release IInitializeWithWindow.
		// IInitializeWithWindow インターフェースを開放します
		pIInitializeWithWindow->Release();

		return true;
	}

	return false;

}

void OnAddonStorePurchaseResultOperation(IAsyncOperation<StorePurchaseResult ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// Check add-on purchase result
	auto storePurchaseResult = asyncOperation->GetResults();

	String^ msg = "";
	bool result = false;

	if (storePurchaseResult->ExtendedError.Value != S_OK)
	{
		msg = "Error:" + storePurchaseResult->ExtendedError.Value.ToString();
		resultPurchaseReceivedCallback(result, msg->Data());
		resultPurchaseReceivedCallback = nullptr;
		return;
	}

	switch (storePurchaseResult->Status)
	{
	case StorePurchaseStatus::AlreadyPurchased:
		msg = "You already bought this AddOn.";
		break;

	case StorePurchaseStatus::Succeeded:
		msg = "To buy AddOn was successful.";
		result = true;
		break;

	case StorePurchaseStatus::NotPurchased:
		msg = "AddOn was not purchased, it may have been canceled.";
		break;

	case StorePurchaseStatus::NetworkError:
		msg = "AddOn was not purchased due to a Network Error.";
		break;

	case StorePurchaseStatus::ServerError:
		msg = "AddOn was not purchased due to a Server Error.";
		break;

	default:
		msg = "AddOn was not purchased due to an Unknown Error.";
		break;
	}

	if (resultPurchaseReceivedCallback)
	{
		resultPurchaseReceivedCallback(result, msg->Data());
		resultPurchaseReceivedCallback = nullptr;
	}
}


