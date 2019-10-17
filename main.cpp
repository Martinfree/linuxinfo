#include "info.h"
#include <iostream>
#include <gtkmm.h>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#endif
#define GTimeVal GDateTime
// The class mainwindow inherits from Gtk::Window
class mainwindow : public Gtk::Window
{
	// Constructor and destructor
public:    
	mainwindow();
	virtual                 ~mainwindow();
	
protected:
	void                    messageInfo();
	void                    messageProc();
	void                    messageMem();
	void                    messagePart();
	void                    messageAuthor();
	
	//Override default signal handler:
	//    virtual bool on_draw(const Cairo::RefPtr& cr);
	
	//Member widgets:
	Gtk::Button             buttonInfo;
	Gtk::Button             buttonProc;
	Gtk::Button             buttonMem;
	Gtk::Button             buttonPart;
	Gtk::Button             buttonAuthor;
	Gtk::Button             buttonQuit;
	Gtk::VBox               mainLayout;
	
};

mainwindow::mainwindow()
{
	this->resize(400,200);
	
	// Add the info message button
	buttonInfo.add_label("System info"); //Information
	buttonInfo.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::messageInfo));
	mainLayout.pack_start(buttonInfo);
	
	// Add the warning message button
	buttonProc.add_label("Processor"); //Warnings
	buttonProc.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::messageProc));
	mainLayout.pack_start(buttonProc);
	
	// Add the question message button
	buttonMem.add_label("Memory"); //question
	buttonMem.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::messageMem));
	mainLayout.pack_start(buttonMem);
	
	// Add the error message button
	buttonPart.add_label("Partitions");
	buttonPart.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::messagePart));
	mainLayout.pack_start(buttonPart);
	
	// Add the other message button
	buttonAuthor.add_label("Created by");
	buttonAuthor.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::messageAuthor));
	mainLayout.pack_start(buttonAuthor);
	
	// Add the Quit button
	buttonQuit.add_label("Quit");
	buttonQuit.signal_pressed().connect(sigc::mem_fun(*this,&mainwindow::close));
	mainLayout.pack_start(buttonQuit);
	
	// Display the main grid in the main window
	mainLayout.show_all();
	
	// Insert the grid in the main window
	add(mainLayout);
	
}


// Destructor of the class
mainwindow::~mainwindow()
{}


// Display message info
void mainwindow::messageInfo()
{
    version(stats.version);

	Gtk::MessageDialog dialog(*this,stats.version ,false,Gtk::MESSAGE_INFO);
	//dialog.set_secondary_text("And this is the secondary text that explains things.");
	dialog.run();
}

// Display warning message
void mainwindow::messageProc()
{
    sysinfo(&info);
    stats.processors = cpuinfo(stats.cpuinfo);
    sprintf(stats.processes,"Processes run now : %d",info.procs);
    sprintf(stats.cpuinfo,"%s%s",stats.cpuinfo,stats.processes);
	
    Gtk::MessageDialog dialog(*this, stats.cpuinfo,false,Gtk::MESSAGE_WARNING);
    //dialog.set_secondary_text(stats.processes);
	dialog.run();
}

// Display a question message
void mainwindow::messageMem()
{
    sysinfo(&info);
    sprintf(stats.memory,"Total ram: %lu Mb\n",info.totalram/1024);
    sprintf(stats.memory,"%sAvaillable memory: %lu Mb\n",stats.memory,info.freeram/1024);
    sprintf(stats.memory,"%sMemory used: %lu Mb",stats.memory,info.totalram-info.freeram/1024);
  	
    Gtk::MessageDialog dialog(*this, stats.memory,false,Gtk::MESSAGE_INFO);
	int Answer=dialog.run();
	
	// Process user choice
	/*switch(Answer)
	{
	case(Gtk::RESPONSE_OK):
		std::cout << "OK clicked." << std::endl;
		break;
	case(Gtk::RESPONSE_CANCEL):
		std::cout << "Cancel clicked." << std::endl;
		break;
	default:
		std::cout << "Unexpected button clicked." << std::endl;
		break;
	}*/
}

// Display error message
void mainwindow::messagePart()
{
    partitions(stats.partitions);
	Gtk::MessageDialog dialog(*this, stats.partitions,false,Gtk::MESSAGE_ERROR);
	dialog.run();
}

// Display other message
void mainwindow::messageAuthor()
{
	Gtk::MessageDialog dialog(*this, "Created by LNTU student, group KB-31",true,Gtk::MESSAGE_OTHER);
	dialog.set_secondary_text("Varchenko Leonid, for testing computer environment",true);
	dialog.run();
}



int main(int argc,char *argv[]){
// Initialize gtkmm
	//general();
    Gtk::Main app(argc, argv);
	// Create the window
	mainwindow w;
	// Start main loop
	Gtk::Main::run(w);
   //    general();
   return 0;
}
