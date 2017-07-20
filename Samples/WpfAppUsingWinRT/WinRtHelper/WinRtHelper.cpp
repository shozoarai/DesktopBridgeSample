// WinRtHelper.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"


using namespace std;

using namespace Platform;
using namespace concurrency;
using namespace Windows::Foundation;

using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

typedef void(WINAPI *FILERECEIVED)(PCWSTR name);		// Define callback function type.
FILERECEIVED fileReceivedCallback;					// Define variable of cakkback function.

// If you want to receive results, pass callback function pointer.
// 結果を受け取る場合は、コールバックを引数で渡します
bool WINAPI OpenFilePicker(HWND hWnd, void* pfnFileReceived)
{
	// Callback function
	fileReceivedCallback = (FILERECEIVED)pfnFileReceived;

	// Initialize of Window handle for Windows Runtime Object with UI.
	// UI を持つ Windows Runtime オブジェクトは、ウィンドウ ハンドルで初期化します
	IInitializeWithWindow* pIInitializeWithWindow;
	// Use FileOpenPicker for test porpose.
	// テスト用途で FileOpenPicker を使用します
	FileOpenPicker ^picker = ref new FileOpenPicker();
	// Cast from FileOpenPicker to IInspectable
	// FileOpenPicker を IInspectable へキャスト
	IInspectable* iInspectable = reinterpret_cast<IInspectable*>(picker);
	// Get IInitializeWithWindow from IInspectable, then initialize.
	// IInspectable より、IInitializeWithWindow を取得して初期化
	if (SUCCEEDED(iInspectable->QueryInterface(IID_PPV_ARGS(&pIInitializeWithWindow))))
	{
		pIInitializeWithWindow->Initialize((HWND)(void *)hWnd);

		picker->FileTypeFilter->Append(".txt");
		picker->FileTypeFilter->Append(".doc");
		picker->FileTypeFilter->Append(".pptx");

		// create_task.then pattern
		create_task(picker->PickSingleFileAsync()).then([](StorageFile^ file)
		{
			PCWSTR returnData = nullptr;
			if (file)
			{
				// Cast from Platform::String to wchar_t.
				// Nameプロパティ(String)より wchar_t へ
				String ^name = file->Name;
				returnData = name->Data();
			}

			// Call callback function.
			// コールバックを呼び出します
			if (fileReceivedCallback)
			{
				fileReceivedCallback(returnData);
			}
		});

		// Release IInitializeWithWindow.
		// IInitializeWithWindow インターフェースを開放します
		pIInitializeWithWindow->Release();

		return true;
	}

	return false;
}

