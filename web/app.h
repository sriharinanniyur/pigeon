// Written by Srihari Nanniyur.
#ifndef __pigeon_app_h__
#define __pigeon_app_h__

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class App : public Wt::WApplication {
public:
    App(const Wt::WEnvironment& env);
private:
    Wt::WLineEdit *username_edit;
    Wt::WLineEdit *password_edit;
};

#endif
