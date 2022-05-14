// ---------------------------------------------------------------------------

#ifndef UnitAlertH
#define UnitAlertH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

// ---------------------------------------------------------------------------
class TFormAlert : public TForm
{
__published: // IDE-managed Components
	TButton *ButtonClose;
	TRichEdit *RichEdit;

	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private: // User declarations
public: // User declarations
	__fastcall TFormAlert(TComponent* Owner);

	void __fastcall CreateParams(TCreateParams &Params);

	void PreviewEvent(int ind);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFormAlert *FormAlert;
// ---------------------------------------------------------------------------
#endif
