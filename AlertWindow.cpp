// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
// ---------------------------------------------------------------------------
USEFORM("UnitMain.cpp", FormMain);
USEFORM("UnitAlert.cpp", FormAlert);

// ---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormAlert), &FormAlert);

		if (ParamCount() > 0)
		{
			Application->ShowMainForm = false;
		}

		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
// ---------------------------------------------------------------------------
