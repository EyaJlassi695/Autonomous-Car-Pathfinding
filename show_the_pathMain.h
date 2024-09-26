/***************************************************************
 * Name:      show_the_pathMain.h
 * Purpose:   Defines Application Frame
 * Author:    Eya~Aymen ()
 * Created:   2024-03-21
 * Copyright: Eya~Aymen ()
 * License:
 **************************************************************/

#ifndef SHOW_THE_PATHMAIN_H
#define SHOW_THE_PATHMAIN_H
#include <iostream>
#include "classes.hpp"
//(*Headers(show_the_pathFrame)
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/tglbtn.h>
//*)

class show_the_pathFrame: public wxFrame
{
    public:

        show_the_pathFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~show_the_pathFrame();

    private:
        wxString filePath; // Chemin du fichier sélectionné

        //(*Handlers(show_the_pathFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnFilePickerCtrl1FileChanged(wxFileDirPickerEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnToggleButton1Toggle(wxCommandEvent& event);
        void OnToggleButton1Toggle1(wxCommandEvent& event);
        //*)

        //(*Identifiers(show_the_pathFrame)
        static const long ID_FILEPICKERCTRL1;
        static const long ID_STATICBITMAP1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_TOGGLEBUTTON1;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(show_the_pathFrame)
        wxFilePickerCtrl* FilePickerCtrl1;
        wxPanel* Panel1;
        wxStaticBitmap* StaticBitmap1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStatusBar* StatusBar1;
        wxToggleButton* ToggleButton1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SHOW_THE_PATHMAIN_H
