// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "UnitAlert.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;

using namespace std;

// ---------------------------------------------------------------------------
void TFormMain::PreviewEvent(TRichEdit *pedit)
{
	pedit->DefAttributes->Name = "MS Sans Serif";
	pedit->DefAttributes->Size = 24;
	pedit->DefAttributes->Color = clRed;
	pedit->DefAttributes->Style = pedit->DefAttributes->Style << fsBold;

	pedit->Lines->Text = EditName->Text;
	pedit->Lines->Add("");

	pedit->SelAttributes->Size = 12;
	pedit->SelAttributes->Color = clBlack;

	pedit->Lines->Add(MemoDescr->Text);
}

// ---------------------------------------------------------------------------
void TFormMain::EventSelected()
{
	int ind = ListBoxEvents->ItemIndex;
	if (ind == -1)
		return;

	tEve *peve = (tEve*)pEveLst->Items[ind];
	EditName->Text = peve->Name;
	MemoDescr->Text = peve->Descr;
	PreviewEvent(RichEditPreview);
}

// ---------------------------------------------------------------------------
void TFormMain::Save()
{
	int it1, it2;
	AnsiString str1;

	str1.printf("%sEvents.lsb", tl_GetProgramPath());
	fstream fs(str1.c_str(), ios::out | ios::binary | ios::trunc);

	it1 = pEveLst->Count;
	fs.write((char*)&it1, sizeof(it1));
	for (int i = 0; i < it1; i++)
	{
		tEve *peve = (tEve*)pEveLst->Items[i];
		it2 = peve->Name.Length();
		fs.write((char*)&it2, sizeof(it2));
		fs.write((char*)peve->Name.c_str(), it2);
		it2 = peve->Descr.Length();
		fs.write((char*)&it2, sizeof(it2));
		fs.write((char*)peve->Descr.c_str(), it2);
	}
	fs.close();
}

// ---------------------------------------------------------------------------
void TFormMain::Load()
{
	int it1, it2;
	char *buf1;
	AnsiString str1;

	str1.printf("%sEvents.lsb", tl_GetProgramPath());
	if (!FileExists(str1))
		return;
	fstream fs(str1.c_str(), ios::in | ios::binary);

	fs.read((char*)&it1, sizeof(it1));
	for (int i = 0; i < it1; i++)
	{
		tEve *peve = new tEve;

		fs.read((char*)&it2, sizeof(it2));
		buf1 = new char[it2 + 1];
		*(buf1 + it2) = '\0';
		fs.read(buf1, it2);
		peve->Name = buf1;
		delete[]buf1;

		fs.read((char*)&it2, sizeof(it2));
		buf1 = new char[it2 + 1];
		*(buf1 + it2) = '\0';
		fs.read(buf1, it2);
		peve->Descr = buf1;
		delete[]buf1;

		pEveLst->Add(peve);
	}
	fs.close();
}

// ---------------------------------------------------------------------------
void TFormMain::UpdateListBox()
{
	ListBoxEvents->Clear();
	for (int i = 0; i < pEveLst->Count; i++)
	{
		AnsiString str1;
		tEve *peve = (tEve*)pEveLst->Items[i];
		str1.printf("%d - %s", i, peve->Name);
		ListBoxEvents->Items->Add(str1);
	}
}

// ---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner)
{
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::EditNameChange(TObject *Sender)
{
	PreviewEvent(RichEditPreview);
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonAddClick(TObject *Sender)
{
	if (EditName->Text.IsEmpty() || MemoDescr->Text.IsEmpty())
	{
		ShowMessage("Please input required data.");
		return;
	}

	tEve *peve = new tEve;
	peve->Name = EditName->Text;
	peve->Descr = MemoDescr->Text;
	pEveLst->Add(peve);
	Save();
	UpdateListBox();
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonApplyClick(TObject *Sender)
{
	int ind = ListBoxEvents->ItemIndex;
	if (ind == -1)
	{
		ShowMessage("No event selected.");
		return;
	}
	if (EditName->Text.IsEmpty() || MemoDescr->Text.IsEmpty())
	{
		ShowMessage("Please input required data.");
		return;
	}

	tEve *peve = (tEve*)pEveLst->Items[ind];
	peve->Name = EditName->Text;
	peve->Descr = MemoDescr->Text;
	Save();
	UpdateListBox();
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonDeleteClick(TObject *Sender)
{
	int ind = ListBoxEvents->ItemIndex;
	if (ind == -1)
	{
		ShowMessage("No event selected.");
		return;
	}
	delete(tEve*)(pEveLst->Items[ind]);
	pEveLst->Delete(ind);
	Save();
	UpdateListBox();
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	EditName->Text = "";
	MemoDescr->Text = "";
	RichEditPreview->Lines->Clear();

	pEveLst = new TList;
	Load();
	UpdateListBox();
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	delete pEveLst;
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::ListBoxEventsKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	EventSelected();
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::ListBoxEventsMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
	EventSelected();
}

// ---------------------------------------------------------------------------
AnsiString tl_GetModuleName()
{
	wchar_t buf[MAX_PATH];
	GetModuleFileName(NULL, buf, MAX_PATH);
	return (AnsiString)buf;
}

// ---------------------------------------------------------------------------
AnsiString tl_GetProgramPath() // пути всегда с завершающей косой
{
	static AnsiString Path = tl_GetModuleName();
	return Path.SubString(1, Path.LastDelimiter("\\"));
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;
	AnsiString str1;

	if (ParamCount() == 0)
	{
		// show settings gui
	}
	else if (ParamCount() == 1)
	{
		// show alert
		int ind;

		ind = ParamStr(1).ToIntDef(-1);
		if (ind == -1 || ind > pEveLst->Count - 1)
		{
			str1.printf("Invalid parameter. Found %d, must be from 0 to %d", ind,
				pEveLst->Count - 1);
			ShowMessage(str1);
			goto exit;
		}
		FormAlert->PreviewEvent(ind);
		FormAlert->Show();
		SetForegroundWindow(FormAlert->Handle);
	}
	else
	{
		// error
		str1.printf("Invalid number of parameters. Found %d, must be 1", ParamCount());
		ShowMessage(str1);
	}
exit:
}

// ---------------------------------------------------------------------------
