// StoreCppHelper.cpp : Defines the exported functions for the DLL application.
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
// 	Define License callback function type for CheckLicense.
APPLICENSERECEIVED AppLicenseReceivedCallback;
APPLICENSEINTERNALRECEIVED AppLicenseInternalReceivedCallback;

bool GetAppLicenseInternal(void* pfnAppLicenseReceivedCallback, bool isInternal);
void OnGetAppLicenseOperation(IAsyncOperation<StoreAppLicense ^> ^asyncOperation, AsyncStatus asyncStatus);

///////////////////////////////////////////////////////////////////
//  Definition GetAppLicense function
//
//  Get AppLicense Information
///////////////////////////////////////////////////////////////////
bool WINAPI GetAppLicense(void* pfnAppLicenseReceivedCallback)
{

	return GetAppLicenseInternal(pfnAppLicenseReceivedCallback, false);
}

// pfnAppLicenseReceivedCalaback
//      isInternal = false, APPLICENSERECEIVED			: for external program, such as WPF App.
//      isInternal = true,  APPLICENSEINTERNALRECEIVED	: for another code files, such as Listing.cpp.
bool GetAppLicenseInternal(void* pfnAppLicenseReceivedCallback, bool isInternal)
{
	if (isInternal)
	{
		AppLicenseInternalReceivedCallback = (APPLICENSEINTERNALRECEIVED)pfnAppLicenseReceivedCallback;
	}
	else
	{
		AppLicenseReceivedCallback = (APPLICENSERECEIVED)pfnAppLicenseReceivedCallback;
	}

	StoreContext^ context = StoreContext::GetDefault();

	auto appLicenseOperation = context->GetAppLicenseAsync();
	appLicenseOperation->Completed =
		ref new AsyncOperationCompletedHandler<StoreAppLicense ^>(&OnGetAppLicenseOperation);

	return true;
}

void OnGetAppLicenseOperation(IAsyncOperation<StoreAppLicense ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// Get StoreAppLicense object.
	auto appLicense = asyncOperation->GetResults();
	bool isActive = false;
	bool isTrial = false;
	bool isInactive;
	bool isFull;
	// Check AppLicense information
	if (appLicense->IsActive)
	{
		isActive = true;
		if (appLicense->IsTrial)
		{
			isTrial = true;
		}
	}
	isInactive = !isActive;
	isFull = !isTrial;
	// for external program
	if (AppLicenseReceivedCallback != nullptr)
	{
		AppLicenseReceivedCallback(isActive, isTrial, isInactive, isFull);
		AppLicenseReceivedCallback = nullptr;
	}
	// for another code files
	if (AppLicenseInternalReceivedCallback)
	{
		AppLicenseInternalReceivedCallback(appLicense);
		AppLicenseInternalReceivedCallback = nullptr;
	}
}

