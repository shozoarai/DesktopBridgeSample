# How to use Windows Runtime API from Desktop App
This sample show how to use Windows Runtime API from Desktop Windows App. This sample contain two projects.
- WinRtHelper: This is the Win32 DLL project. But set C++ compiler switch use /Zw /Gm-, So use [C++/CX](http://go.microsoft.com/fwlink/p/?LinkId=255561).
- WpfAppUsingWinRT: This is WPF Project by C#. It have two features. First, direct consume Windows Runtime by reference Windows metadata. Last, indirect consume Windows Runtime via C Dynamic Link Library.

# Windows �����^�C�� API ���f�X�N�g�b�v �A�v������g�p������@
- WinRtHelper: ���̃v���W�F�N�g�́AWin32 �� DLL �v���W�F�N�g�ł��B�ʏ�� DLL �v���W�F�N�g�ƈقȂ�̂́A�R���p�C�� �X�C�b�`�� /Zw �� /Gm- ���g�p���āA[C++/CX](http://go.microsoft.com/fwlink/p/?LinkId=255561) �ŋL�q���Ă��邱�Ƃł��B
-  WpfAppUsingWinRT: ���̃v���W�F�N�g�́AC# �� WPF �v���W�F�N�g�ł��B2�̋@�\�������Ă��܂��B1 �ڂ́AC# ���� Windows �����^�C�����g�p����@�\�ł��B�Ō�́A�֐����G�N�X�|�[�g���� DLL ����� Windows �����^�C�����g�p������@�ł��B
