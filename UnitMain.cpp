// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <XMLDoc.hpp>
// #include <XMLIntf.hpp>
// #include <ComObj.hpp>

#include "UnitMain.h"
#include "UnitAlert.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;

using namespace std;

// ---------------------------------------------------------------------------
String tl_GetModuleName()
{
	wchar_t buf[MAX_PATH];
	GetModuleFileName(NULL, buf, MAX_PATH);
	return (String)buf;
}

// ---------------------------------------------------------------------------
String tl_GetProgramPath() // path with trailing '\'
{
	static String Path = tl_GetModuleName();
	return Path.SubString(1, Path.LastDelimiter(L"\\"));
}

// ---------------------------------------------------------------------------
void TFormMain::PreviewEvent(TRichEdit *pedit)
{
	pedit->Lines->Clear();
	pedit->DefAttributes->Name = L"MS Sans Serif";
	pedit->DefAttributes->Size = 24;
	pedit->DefAttributes->Color = clRed;
	pedit->DefAttributes->Style = pedit->DefAttributes->Style << fsBold;

	pedit->Lines->Text = EditName->Text;
	pedit->Lines->Add(L"");

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
	CoInitialize(0);
	String str1;
	_di_IXMLDocument document = interface_cast<Xmlintf::IXMLDocument>
		(new TXMLDocument(NULL));
	document->Active = true;
	document->SetEncoding(L"UTF-8");
	document->Options = document->Options << doNodeAutoIndent;
	_di_IXMLNode root = document->CreateNode(L"Root", ntElement, L"");
	document->DocumentElement = root;

	for (int i = 0; i < pEveLst->Count; i++)
	{
		tEve *peve = (tEve*)pEveLst->Items[i];
		_di_IXMLNode node1;
		str1.printf(L"Event%d", i);
		node1 = document->CreateNode(str1, ntElement, L"");
		node1->Attributes[L"Name"] = peve->Name;
		node1->Attributes[L"Description"] = peve->Descr;
		root->ChildNodes->Add(node1);
	}

	str1.printf(L"%sEvents.xml", tl_GetProgramPath());
	document->SaveToFile(str1);
	CoUninitialize();
}

// ---------------------------------------------------------------------------
void TFormMain::Load()
{
	CoInitialize(0);
	String str1;
	str1.printf(L"%sEvents.xml", tl_GetProgramPath());
	if (!FileExists(str1))
		return;

	const _di_IXMLDocument document = interface_cast<Xmlintf::IXMLDocument>
		(new TXMLDocument(NULL));
	document->LoadFromFile(str1);

	// find root node
	const _di_IXMLNode root = document->ChildNodes->FindNode(L"Root");
	if (root != NULL)
	{
		// traverse child nodes
		for (int i = 0; i < root->ChildNodes->Count; i++)
		{
			tEve *peve = new tEve(L"read error", L"read error");
			const _di_IXMLNode node = root->ChildNodes->Get(i);
			// get attributes
			if (node->HasAttribute(L"Name"))
			{
				peve->Name = node->Attributes[L"Name"];
			}
			if (node->HasAttribute(L"Description"))
			{
				peve->Descr = node->Attributes[L"Description"];
			}
			pEveLst->Add(peve);
		}
	}
	CoUninitialize();
}

// ---------------------------------------------------------------------------
void TFormMain::UpdateListBox()
{
	ListBoxEvents->Clear();
	for (int i = 0; i < pEveLst->Count; i++)
	{
		String str1;
		tEve *peve = (tEve*)pEveLst->Items[i];
		str1.printf(L"%d - %s", i, peve->Name);
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
void __fastcall TFormMain::MemoDescrChange(TObject *Sender)
{
	PreviewEvent(RichEditPreview);
}

// ---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonAddClick(TObject *Sender)
{
	if (EditName->Text.IsEmpty() || MemoDescr->Text.IsEmpty())
	{
		ShowMessage(L"Please input required data.");
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
		ShowMessage(L"No event selected.");
		return;
	}
	if (EditName->Text.IsEmpty() || MemoDescr->Text.IsEmpty())
	{
		ShowMessage(L"Please input required data.");
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
		ShowMessage(L"No event selected.");
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
	EditName->Text = L"";
	MemoDescr->Text = L"";
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
void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;
	String str1;

	if (ParamCount() == 0) // show settings gui
	{
	}
	else if (ParamCount() == 1) // show alert
	{
		const String parm = ParamStr(1);
		const int ind = parm.ToIntDef(-1);

		// 1. find event by name
		for (int i = 0; i < pEveLst->Count; i++)
		{
			tEve *peve = (tEve*)pEveLst->Items[i];
			if (peve->Name == parm)
			{
				FormAlert->PreviewEvent(i);
				FormAlert->Show();
				return;
			}
		}

		// 2. event by number
		if (ind >= 0 && ind < pEveLst->Count)
		{
			FormAlert->PreviewEvent(ind);
			FormAlert->Show();
			return;
		}

		// not found
		str1.printf(L"Event \'%s\' not found.", parm);
		ShowMessage(str1);
		Close();
	}
	else // wrong arguments
	{
		str1.printf(L"Invalid number of parameters. Found %d, expected 1", ParamCount());
		ShowMessage(str1);
		Close();
	}
}

// ---------------------------------------------------------------------------
