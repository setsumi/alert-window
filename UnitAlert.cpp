// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitAlert.h"
#include "UnitMain.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAlert *FormAlert;

// ---------------------------------------------------------------------------
BOOL BringWindowToFront(HWND hwnd)
{
	DWORD lForeThreadID;
	DWORD lThisThreadID;
	BOOL lReturn = TRUE;

	// Make a window, specified by its handle (hwnd)
	// the foreground window.

	// If it is already the foreground window, exit.
	if (hwnd != GetForegroundWindow())
	{

		// Get the threads for this window and the foreground window.
		lForeThreadID = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
		lThisThreadID = GetWindowThreadProcessId(hwnd, NULL);

		// By sharing input state, threads share their concept of
		// the active window.
		if (lForeThreadID != lThisThreadID)
		{
			// Attach the foreground thread to this window.
			AttachThreadInput(lForeThreadID, lThisThreadID, TRUE);
			// Make this window the foreground window.
			lReturn = SetForegroundWindow(hwnd);
			// Detach the foreground window's thread from this window.
			AttachThreadInput(lForeThreadID, lThisThreadID, FALSE);
		}
		else
		{
			lReturn = SetForegroundWindow(hwnd);
		}

		// Restore this window to its normal size.
		if (IsIconic(hwnd))
		{
			ShowWindow(hwnd, SW_RESTORE);
		}
		else
		{
			ShowWindow(hwnd, SW_SHOW);
		}
	}
	return lReturn;
}

// ---------------------------------------------------------------------------
void TFormAlert::PreviewEvent(int ind)
{
	tEve *peve = (tEve*)FormMain->pEveLst->Items[ind];

	RichEdit->Lines->Clear();
	// RichEdit->DefAttributes->Name = L"MS Sans Serif";
	RichEdit->DefAttributes->Size = 12;
	RichEdit->DefAttributes->Color = clBlack;
	RichEdit->DefAttributes->Style = RichEdit->DefAttributes->Style << fsBold;

	RichEdit->SelAttributes->Size = 24;
	RichEdit->SelAttributes->Color = clRed;
	RichEdit->Lines->Add(peve->Name);

	RichEdit->Lines->Add(L"");
	RichEdit->Lines->Add(peve->Descr);
}

// ---------------------------------------------------------------------------
__fastcall TFormAlert::TFormAlert(TComponent* Owner) : TForm(Owner)
{
}

// ---------------------------------------------------------------------------
void __fastcall TFormAlert::ButtonCloseClick(TObject *Sender)
{
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TFormAlert::FormClose(TObject *Sender, TCloseAction &Action)
{
	FormMain->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TFormAlert::FormShow(TObject *Sender)
{
	MessageBeep(-1);
	Timer1->Enabled = true;
}

// ---------------------------------------------------------------------------
void __fastcall TFormAlert::CreateParams(TCreateParams &Params)
{
	TForm::CreateParams(Params);
	Params.WndParent = 0; // unowned. Unowned windows naturally appear on the taskbar.
	// Params.ExStyle |= WS_EX_APPWINDOW;
	// https://stackoverflow.com/questions/30809532/how-to-correctly-have-modeless-form-appear-in-taskbar
}

// ---------------------------------------------------------------------------
void __fastcall TFormAlert::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	switch (Key)
	{
	case VK_ESCAPE:
		Close();
		break;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TFormAlert::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;
	BringWindowToFront(Handle);
	::SetWindowPos(Handle, HWND_TOP, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_DRAWFRAME | SWP_FRAMECHANGED);

}
// ---------------------------------------------------------------------------
