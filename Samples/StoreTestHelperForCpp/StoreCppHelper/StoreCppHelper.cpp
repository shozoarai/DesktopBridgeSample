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
typedef void(WINAPI *APPLICENSERECEIVED)(bool isActive, bool isTrial, bool isInactive, bool isFull);
APPLICENSERECEIVED appLicenseReceivedCallback;

void OnGetAppLicenseOperation(IAsyncOperation<StoreAppLicense ^> ^asyncOperation, AsyncStatus asyncStatus);

///////////////////////////////////////////////////////////////////
//  Definition GetAppLicense function
//
//  Get AppLicense Information
///////////////////////////////////////////////////////////////////
bool WINAPI GetAppLicense(void* pfnAppLicenseReceivedCallback)
{
	appLicenseReceivedCallback = (APPLICENSERECEIVED)pfnAppLicenseReceivedCallback;

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
	if (appLicenseReceivedCallback != nullptr)
	{
		appLicenseReceivedCallback(isActive, isTrial, isInactive, isFull);
		appLicenseReceivedCallback = nullptr;
	}
}

