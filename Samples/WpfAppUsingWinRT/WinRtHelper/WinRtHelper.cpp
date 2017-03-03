// WinRtHelper.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"


using namespace std;

using namespace Platform;
using namespace concurrency;
using namespace Windows::Foundation;

using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

typedef void(WINAPI *FILERECEIVED)(PCWSTR name);		// �R�[���o�b�N�֐��̌^��`
FILERECEIVED fileReceivedCallback;					// �R�[���o�b�N�֐��̕ϐ���`

void OnStrageSelected(IAsyncOperation<StorageFile ^> ^asyncOperation, AsyncStatus asyncStatus);

// ���ʂ��󂯎��ꍇ�́A�R�[���o�b�N�������œn���܂�
bool WINAPI OpenFilePicker(HWND hWnd, void* pfnFileReceived)
{
	// �R�[���o�b�N�֐�
	fileReceivedCallback = (FILERECEIVED)pfnFileReceived;

	// UI ������ Windows Runtime �I�u�W�F�N�g�́A�E�B���h�E �n���h���ŏ��������܂�
	IInitializeWithWindow* pIInitializeWithWindow;
	// �e�X�g�p�r�� FileOpenPicker ���g�p���܂�
	FileOpenPicker ^picker = ref new FileOpenPicker();
	// FileOpenPicker �� IInspectable �փL���X�g
	IInspectable* iInspectable = reinterpret_cast<IInspectable*>(picker);
	// IInspectable ���AIInitializeWithWindow ���擾���ď�����
	if (SUCCEEDED(iInspectable->QueryInterface(IID_PPV_ARGS(&pIInitializeWithWindow))))
	{
		pIInitializeWithWindow->Initialize((HWND)(void *)hWnd);

		picker->FileTypeFilter->Append(".txt");
		picker->FileTypeFilter->Append(".doc");
		picker->FileTypeFilter->Append(".pptx");

		auto filePickerAsyncOperation = picker->PickSingleFileAsync();
		// Completed �C�x���g �n���h�� �Ōp���������L�q���Ă��܂�
		filePickerAsyncOperation->Completed =
			ref new AsyncOperationCompletedHandler<StorageFile ^>(&OnStrageSelected);

		// IInitializeWithWindow �C���^�[�t�F�[�X���J�����܂�
		pIInitializeWithWindow->Release();

		return true;
	}

	return false;
}

// �s�b�J�[���I�������ꍇ�ɌĂ΂��C�x���g
void OnStrageSelected(IAsyncOperation<StorageFile ^> ^asyncOperation, AsyncStatus asyncStatus)
{
	// ���ʂ��󂯎��ꍇ�́A�����n���ꂽ�R�[���o�b�N���Ăяo���܂�
	auto storageFile = asyncOperation->GetResults();
	PCWSTR returnData = nullptr;
	if (storageFile)
	{
		// Name�v���p�e�B(String)��� wchar_t ��
		String ^name = storageFile->Name;
		returnData = name->Data();
	}

	// �R�[���o�b�N���Ăяo���܂�
	if (fileReceivedCallback)
	{
		fileReceivedCallback(returnData);
	}

}

