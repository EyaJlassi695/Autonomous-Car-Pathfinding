/***************************************************************
 * Name:      show_the_pathApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Eya~Aymen ()
 * Created:   2024-03-21
 * Copyright: Eya~Aymen ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "show_the_pathApp.h"
#include "show_the_pathMain.h"
#include <wx/image.h>

//(*AppHeaders
//*)

IMPLEMENT_APP(show_the_pathApp);

bool show_the_pathApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	show_the_pathFrame* Frame = new show_the_pathFrame(0);
        Frame->SetIcon(wxICON(aaaa));
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
