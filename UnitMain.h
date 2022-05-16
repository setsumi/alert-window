// ---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
// ---------------------------------------------------------------------------
#include <fstream>

// ---------------------------------------------------------------------------
class tEve
{
public:
	String Name;
	String Descr;

	tEve()
	{
	}

	tEve(String name, String descr) : Name(name), Descr(descr)
	{
	}
};

// ---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published: // IDE-managed Components
	TRichEdit *RichEditPreview;
	TEdit *EditName;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TButton *ButtonAdd;
	TButton *ButtonApply;
	TButton *ButtonDelete;
	TListBox *ListBoxEvents;
	TLabel *Label4;
	TTimer *Timer1;
	TRichEdit *MemoDescr;
	TStatusBar *StatusBar1;

	void __fastcall EditNameChange(TObject *Sender);
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall ButtonApplyClick(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ListBoxEventsKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ListBoxEventsMouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall MemoDescrChange(TObject *Sender);

private: // User declarations
public: // User declarations
	__fastcall TFormMain(TComponent* Owner);

	TList *pEveLst;

	void PreviewEvent(TRichEdit *pedit);
	void Save();
	void Load();
	void UpdateListBox();
	void EventSelected();
};

// ---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
// ---------------------------------------------------------------------------
#endif
