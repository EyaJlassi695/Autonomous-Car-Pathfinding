/***************************************************************
 * Name:      show_the_pathMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Eya~Aymen ()
 * Created:   2024-03-21
 * Copyright: Eya~Aymen ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "show_the_pathMain.h"
#include <SFML/Graphics.hpp>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/utils.h> // Inclure pour wxExecute
#include <cstdio>
#include <wx/process.h>
#include <iostream>
#include <fstream>
#include "classes.hpp"
#include "interface.hpp"
using namespace std;
double eps = pow(10,-6);

//(*InternalHeaders(show_the_pathFrame)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(show_the_pathFrame)
const long show_the_pathFrame::ID_FILEPICKERCTRL1 = wxNewId();
const long show_the_pathFrame::ID_STATICBITMAP1 = wxNewId();
const long show_the_pathFrame::ID_STATICTEXT1 = wxNewId();
const long show_the_pathFrame::ID_STATICTEXT2 = wxNewId();
const long show_the_pathFrame::ID_TOGGLEBUTTON1 = wxNewId();
const long show_the_pathFrame::ID_PANEL1 = wxNewId();
const long show_the_pathFrame::idMenuQuit = wxNewId();
const long show_the_pathFrame::idMenuAbout = wxNewId();
const long show_the_pathFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(show_the_pathFrame,wxFrame)
    //(*EventTable(show_the_pathFrame)
    //*)
END_EVENT_TABLE()

show_the_pathFrame::show_the_pathFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(show_the_pathFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(800,600));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("C:\\Users\\Utilisateur\\OneDrive - ENSTA Paris\\Bureau\\show the path\\location.ico"))));
    	SetIcon(FrameIcon);
    }
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(400,0), wxSize(800,600), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxColour(255,255,255));
    FilePickerCtrl1 = new wxFilePickerCtrl(Panel1, ID_FILEPICKERCTRL1, wxEmptyString, wxEmptyString, wxEmptyString, wxPoint(336,368), wxSize(408,23), wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
    StaticBitmap1 = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxBitmap(wxImage(_T("C:\\Users\\Utilisateur\\OneDrive - ENSTA Paris\\Bureau\\sim202\\planification\\interface\\fond.jpg")).Rescale(wxSize(240,600).GetWidth(),wxSize(240,600).GetHeight())), wxPoint(0,0), wxSize(240,600), 0, _T("ID_STATICBITMAP1"));
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Plannification de Trajectoire\n"), wxPoint(288,56), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(28,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Californian FB"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Plannifiez votre trajet facilement :\n\n Notre application vous permet de découvrir le chemin le plus court entre un point de départ  et un point d\'arrivée que vous choisissez. \nIl vous suffit de télécharger une image en noir  et blanc représentant la topologie de votre région, puis suivez les instructions pour suivre l\'itinéraire optimal jusqu\'à votre destination."), wxPoint(296,160), wxSize(464,152), 0, _T("ID_STATICTEXT2"));
    ToggleButton1 = new wxToggleButton(Panel1, ID_TOGGLEBUTTON1, _("Next"), wxPoint(696,496), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_FILEPICKERCTRL1,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&show_the_pathFrame::OnFilePickerCtrl1FileChanged);
    Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&show_the_pathFrame::OnToggleButton1Toggle1);
    Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&show_the_pathFrame::OnPanel1Paint,0,this);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&show_the_pathFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&show_the_pathFrame::OnAbout);
    //*)
}

show_the_pathFrame::~show_the_pathFrame()
{
    //(*Destroy(show_the_pathFrame)
    //*)
}

void show_the_pathFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void show_the_pathFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void show_the_pathFrame::OnFilePickerCtrl1FileChanged(wxFileDirPickerEvent& event)
{
        filePath = event.GetPath();

}
void show_the_pathFrame::OnToggleButton1Toggle1(wxCommandEvent& event)
{ // Construire la commande pour exécuter le script Python avec l'entrée du fichier
    wxString scriptPath = "test2.py";
    FILE* pipe = popen(scriptPath.mb_str(), "w");
    if (!pipe) {
        wxLogError("Erreur lors de l'ouverture du pipe.");
        return;
    }

    // Écrire une chaîne dans le pipe (entrée pour le script Python)
    wxString inputString = filePath;
    fputs(inputString.mb_str(), pipe);

    // Fermer le pipe
    pclose(pipe);



    /*   // Commande pour exécuter le script Python ( deuxieme methode qui ne genere pas de pipe)
wxString command = "python test2.py";
wxString input = filePath;
wxExecute(command + " < " + input, wxEXEC_BLOCK | wxEXEC_HIDE_CONSOLE);*/
   //Charger les textures
    string locImage = "position_1.png";
    string objectImage = "180.png";
    string backgroundImage = "background-1.png";

    //detection de contours
    vector<vector<Sommet>> nodes;
    detectAndSaveContours(filePath.ToStdString(), nodes);
    // Choix des sommets
    vector<Sommet> chemin_Physique;
    sf::Vector2f startPos; // Point de début
    sf::Vector2f endPos;   // Point de fin

    GraphVisualizer visualizer (nodes,locImage,objectImage,backgroundImage,chemin_Physique);
    visualizer.visualize(startPos, endPos);

    //initialisation des structures
    vector<Sommet> all_Sommets;
    Sommet A = Sommet(startPos.x,startPos.y);
    all_Sommets.push_back(A);
    Sommet B = Sommet(endPos.x ,endPos.y);
    all_Sommets.push_back(B);
    wxMessageBox("ouverture de fichier", "Error", wxOK | wxICON_ERROR);

    std::ifstream file("coordinates.txt");
    vector<Obstacle> obs;
     float x, y;
     while (!file.eof()) {
        vector<Sommet> v_Sommet;
        while (file >> x >> y && x != -1.0f && y != -1.0f) {
            Sommet cor(x, y);
            v_Sommet.push_back(cor);
        }
        Obstacle Curr = Obstacle(v_Sommet,eps);
        obs.push_back(Curr);
        for(auto iter = (Curr.vertices).begin(); iter!=(Curr.vertices).end();++iter) {
            all_Sommets.push_back(*iter);
        }
    }
    file.close();


    //définissez le graphe et application de l'algorithme
    Graph G= Graph();
    for(int i =0;i<all_Sommets.size();i++) {
        for(int j = i+1; j<all_Sommets.size();j++) {
            G.AddArc(Arcs(all_Sommets[i], all_Sommets[j]));
        }
    }

    arc_planification arc_plan = arc_planification(G, A, B, obs, eps);

    arc_plan.AddAngles();

    vector<Sommet> chemin = arc_plan.trouverCheminMinimal();

    vector<Sommet> Trajectoire;

   /* while (chemin.size()!=0){
            Trajectoire.push_back(chemin.back());
            chemin.pop_back();
    }*/

    visualizer.trajectoire(Trajectoire);

}
void show_the_pathFrame::OnPanel1Paint(wxPaintEvent& event)
{
}
