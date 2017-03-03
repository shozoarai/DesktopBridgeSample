// WinRtHelper.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"


using namespace std;

using namespace Platform;
using namespace concurrency;
using namespace Windows::Foundation;

using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

typedef void(WINAPI *FILERECEIVED)(PCWSTR name);		// コールバック関数の型定義
FILERECEIVED fileReceivedCallback;					// コールバック関数の変数定義

void OnStrageSelected(IAsyncOperation<StorageFile ^> ^asyncOperation, AsyncStatus asyncStatus);

// 結果を受け取る場合は、コールバックを引数で渡します
bool WINAPI OpenFilePicker(HWND hWnd, void* pfnFileReceived)
{
	// コールバック関数
	fileReceivedCallback = (FILERECEIVED)pfnFileReceived;

	// UI を持つ Windows Runtime オブジェクトは、ウィンドウ ハンドルで初期化します
	IInitializeWithWindow* pIInitializeWithWindow;
	// テスト用途で FileOpenPicker を使用します
	FileOpenPicker ^picker = ref new FileOpenPicker();
	// FileOpenPicker を IInspectable へキャスト
	IInspectable* iInspectable = reinterpret_cast<IInspectable*>(picker);
	// IInspectable より、IInitializeWithWindow を取得して初期化
	if (SUCCEEDED(iInspectable->QueryInterface(IID_PPV_ARGS(&pIInitializeWithWindow))))
	{
		pIInitializeWithWindow->Initialize((HWND)(void *)hWnd);

		picker->FileTypeFilter->Append(".txt");
		picker->FileTypeFilter->Append(".doc");
		picker->FileTypeFilter->Append(".pptx");

		auto filePickerAsyncOperation = picker->PickSingleFileAsync();
		// Completed イベント ハンドラ で継続処理を記述しています
		filePickerAsyncOperation->Completed =
			ref new AsyncOperationCompletedHandler<StorageFile ^>(&OnStrageSelected);

		// IInitializeWithWindow インターフェースを開放します
		pIInitializeWithWindow->Release();

		return true;
	}

	return false;
}

// ピッカーが終了した場合に呼ばれるイベント
void OnStrageSelected(IAsyncOperation<StorageFile ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// 結果を受け取る場合は、引き渡されたコールバックを呼び出します
	auto storageFile = asyncOperation->GetResults();
	PCWSTR returnData = nullptr;
	if (storageFile)
	{
		// Nameプロパティ(String)より wchar_t へ
		String ^name = storageFile->Name;
		returnData = name->Data();
	}

	// コールバックを呼び出します
	if (fileReceivedCallback)
	{
		fileReceivedCallback(returnData);
	}

}

