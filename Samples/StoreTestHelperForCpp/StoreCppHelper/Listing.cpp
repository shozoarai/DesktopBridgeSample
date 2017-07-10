// Listing.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

using namespace std;

using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Services::Store;


String^ ADDON_LICENSE = "addon-license.txt";
String^ ADDON_DURABLE_LIST = "addon-durable.txt";
String^ ADDON_LIST = "addon-list.txt";


///////////////////////////////////////////////////////////////////
//
// 	Define Addon license callback function type for GetDurableAddonLicense.
//  Used by GetDurableAddonList and function.
typedef void(WINAPI *RESULTFILERECEIVED)(PCWSTR filename);
RESULTFILERECEIVED resultFileReceivedCallback = nullptr;
String^ fileData = "";			// FileData
String^ outputFilename = "";		// FileName

void OnGetAddonLicenseOperation(IAsyncOperation<StoreAppLicense ^> ^asyncOperation, AsyncStatus asyncStatus);
void WriteData(String^ filename, String^ list);
void OnFileCreateOperation(IAsyncOperation<StorageFile ^> ^asyncOperation, AsyncStatus asyncStatus);
void OnWriteTextOperation(IAsyncAction^ asyncOperation, AsyncStatus asyncStatus);

///////////////////////////////////////////////////////////////////
//
// 	Define Addon list callback function type for GetAddonList
void OnStoreQueryResultOperation(IAsyncOperation<StoreProductQueryResult ^> ^asyncOperation, AsyncStatus asyncStatus);

///////////////////////////////////////////////////////////////////
//
// 	Define Addon list callback function type for GetAddonLicense.
void OnAddonQueryResultOperation(IAsyncOperation<StoreProductQueryResult ^> ^asyncOperation, AsyncStatus asyncStatus);


///////////////////////////////////////////////////////////////////
//  Definition GetDurableAddonLicense function
//
//  Get add-on list of licensed durable add-on.
///////////////////////////////////////////////////////////////////
bool WINAPI GetDurableAddonLicense(void* pfnResultFileRecievedCallback)
{
	fileData = "";
	outputFilename = "";
	resultFileReceivedCallback = (RESULTFILERECEIVED)pfnResultFileRecievedCallback;

	StoreContext^ context = StoreContext::GetDefault();

	auto licenseOperation = context->GetAppLicenseAsync();
	licenseOperation->Completed =
		ref new AsyncOperationCompletedHandler<StoreAppLicense ^>(&OnGetAddonLicenseOperation);

	return true;
}

void OnGetAddonLicenseOperation(IAsyncOperation<StoreAppLicense ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// Get StoreAppLicense object.
	auto appLicense = asyncOperation->GetResults();

	// concat durable add-on product information
	String^ list = "";
	if (appLicense->IsActive)
	{
		auto addonList = appLicense->AddOnLicenses;
		auto iterable = addonList->First();

		// Form addon to string
		for (auto item : addonList)
		{
			if (list != "")
			{
				list += "\n";
			}
			list += item->Key + "\t" + item->Value->SkuStoreId;
		}
		// Write duravle add-on list.
		WriteData(ADDON_DURABLE_LIST, list);
	}
	else
	{
		WriteData(ADDON_DURABLE_LIST, "");
	}

}

// Write Data
void WriteData(String^ filename, String^ list)
{
	// Create new file with replace or new. 
	fileData = list;
	auto folder = ApplicationData::Current->LocalFolder;

	auto fileCreateOperation = folder->CreateFileAsync(filename, CreationCollisionOption::ReplaceExisting);
	fileCreateOperation->Completed =
		ref new AsyncOperationCompletedHandler<StorageFile^>(&OnFileCreateOperation);

}

void OnFileCreateOperation(IAsyncOperation<StorageFile ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// Write date to file.
	auto file = asyncOperation->GetResults();

	outputFilename = file->Path;
	auto writeTextOperation = FileIO::WriteTextAsync(file, fileData);
	writeTextOperation->Completed =
		ref new AsyncActionCompletedHandler(&OnWriteTextOperation);
}

void OnWriteTextOperation(IAsyncAction^ asyncOperation, AsyncStatus asyncStatus)
{
	asyncOperation->GetResults();

	if (resultFileReceivedCallback)
	{
		// callback with file name.
		resultFileReceivedCallback(outputFilename->Data());
		resultFileReceivedCallback = nullptr;
	}
}


///////////////////////////////////////////////////////////////////
//  Definition GetAddonList function
//
//  Get add-on list 
///////////////////////////////////////////////////////////////////
bool WINAPI GetAddonList(void* pfnResultFileRecievedCallback)
{
	fileData = "";
	outputFilename = "";
	resultFileReceivedCallback = (RESULTFILERECEIVED)pfnResultFileRecievedCallback;

	StoreContext^ context = StoreContext::GetDefault();
	// set filter
	auto filterList = ref new Platform::Collections::Vector<String^>({ "Durable", "Consumable", "UnmanagedConsumable" });
	
	auto storeQueryResultOperation = context->GetAssociatedStoreProductsAsync(filterList);
	storeQueryResultOperation->Completed =
		ref new AsyncOperationCompletedHandler<StoreProductQueryResult^>(&OnStoreQueryResultOperation);
	return true;
}

void OnStoreQueryResultOperation(IAsyncOperation<StoreProductQueryResult ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// Get StoreProductQueryResult object.
	auto storeProductQueryResult = asyncOperation->GetResults();

	if (storeProductQueryResult->ExtendedError.Value != S_OK)
	{
		WriteData(ADDON_LIST, "");
		return;
	}
	if (storeProductQueryResult->Products->Size == 0)
	{
		WriteData(ADDON_LIST, "");
		return;
	}

	// Concat add-on product information.
	String^ list = "";
	for (auto item : storeProductQueryResult->Products)
	{
		if (list != "")
		{
			list += "\n";
		}
		list += item->Value->StoreId + "\t" +
			item->Value->Title + "\t" +
			item->Value->Price->FormattedPrice + "\t" +
			item->Value->ProductKind;
	}
	// Write add-on information to file.
	WriteData(ADDON_LIST, list);

}


///////////////////////////////////////////////////////////////////
//  Definition GetAddonLicense function
//
//  Get add-on list of lincensed add-on.
///////////////////////////////////////////////////////////////////
bool WINAPI GetAddonLicense(void* pfnResultFileRecievedCallback)
{
	fileData = "";
	outputFilename = "";
	resultFileReceivedCallback = (RESULTFILERECEIVED)pfnResultFileRecievedCallback;

	StoreContext^ context = StoreContext::GetDefault();

	// set filter
	auto filterList = ref new Platform::Collections::Vector<String^>({ "Durable", "Consumable", "UnmanagedConsumable" });
	// Get add-on list of lincensed add-on
	auto storeQueryResultOperation = context->GetUserCollectionAsync(filterList);
	storeQueryResultOperation->Completed =
		ref new AsyncOperationCompletedHandler<StoreProductQueryResult^>(&OnAddonQueryResultOperation);
	return true;

}

void OnAddonQueryResultOperation(IAsyncOperation<StoreProductQueryResult ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// Get StoreProductQueryResult object.
	auto storeProductQueryResult = asyncOperation->GetResults();

	if (storeProductQueryResult->ExtendedError.Value != S_OK)
	{
		WriteData(ADDON_LICENSE, "");
		return;
	}
	if (storeProductQueryResult->Products->Size == 0)
	{
		WriteData(ADDON_LICENSE, "");
		return;
	}

	// Concat add-on information
	String^ list = "";
	for (auto item : storeProductQueryResult->Products)
	{
		if (list != "")
		{
			list += "\n";
		}
		list += item->Value->StoreId + "\t" +
			item->Value->Title + "\t" +
			item->Value->Price->FormattedPrice + "\t" +
			item->Value->ProductKind;
	}
	// Write add-on information to file
	WriteData(ADDON_LICENSE, list);

}