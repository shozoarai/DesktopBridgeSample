// WinRtHelper.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
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
// ���ʂ��󂯎��ꍇ�́A�R�[���o�b�N�������œn���܂�
bool WINAPI OpenFilePicker(HWND hWnd, void* pfnFileReceived)
{
	// Callback function
	fileReceivedCallback = (FILERECEIVED)pfnFileReceived;

	// Initialize of Window handle for Windows Runtime Object with UI.
	// UI ������ Windows Runtime �I�u�W�F�N�g�́A�E�B���h�E �n���h���ŏ��������܂�
	IInitializeWithWindow* pIInitializeWithWindow;
	// Use FileOpenPicker for test porpose.
	// �e�X�g�p�r�� FileOpenPicker ���g�p���܂�
	FileOpenPicker ^picker = ref new FileOpenPicker();
	// Cast from FileOpenPicker to IInspectable
	// FileOpenPicker �� IInspectable �փL���X�g
	IInspectable* iInspectable = reinterpret_cast<IInspectable*>(picker);
	// Get IInitializeWithWindow from IInspectable, then initialize.
	// IInspectable ���AIInitializeWithWindow ���擾���ď�����
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
				// Name�v���p�e�B(String)��� wchar_t ��
				String ^name = file->Name;
				returnData = name->Data();
			}

			// Call callback function.
			// �R�[���o�b�N���Ăяo���܂�
			if (fileReceivedCallback)
			{
				fileReceivedCallback(returnData);
			}
		});

		// Release IInitializeWithWindow.
		// IInitializeWithWindow �C���^�[�t�F�[�X���J�����܂�
		pIInitializeWithWindow->Release();

		return true;
	}

	return false;
}

