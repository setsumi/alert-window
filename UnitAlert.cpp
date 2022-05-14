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
void TFormAlert::PreviewEvent(int ind)
{
	tEve *peve = (tEve*)FormMain->pEveLst->Items[ind];

    RichEdit->Lines->Clear();
	RichEdit->DefAttributes->Name = L"MS Sans Serif";
	RichEdit->DefAttributes->Color = clRed;
	RichEdit->DefAttributes->Size = 24;
	RichEdit->DefAttributes->Style = RichEdit->DefAttributes->Style << fsBold;

	RichEdit->Lines->Text = peve->Name;
	RichEdit->Lines->Add(L"");

	RichEdit->SelAttributes->Color = clBlack;
	RichEdit->SelAttributes->Size = 12;

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
