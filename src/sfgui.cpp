#include "sfgui.h"

void Clicky::run()
{
    if (state == "menu")
        menu();
    else if (state == "join")
        join();
}
    
void Clicky::menu()
{
    joinButt->GetSignal(sfg::Widget::OnLeftClick).Connect(&Clicky::onJoinButtClick, this);
    hostButt->GetSignal(sfg::Widget::OnLeftClick).Connect(&Clicky::onHostButtClick, this);
    /*instructButt->GetSignal(sfg::Widget::OnLeftClick).Connect(&Clicky::onInstructButtClick, this);
    optionsButt->GetSignal(sfg::Widget::OnLeftClick).Connect(&Clicky::onOptionsButtClick, this);*/

    menuBox->Pack(joinButt, false);
    menuBox->Pack(hostButt, false);
    menuBox->Pack(instructButt, false);
    menuBox->Pack(optionsButt, false);
    desktop.Add(menuBox);
}

void Clicky::join()
{}

//menu
void Clicky::onJoinButtClick()
{
    state = "join";
}

void Clicky::onHostButtClick()
{
    state = "host";
}

/* void onInstructButtClick();
{
    state = "instructions";
}

void onOptionsButtClick();
{
    state = "options";
}   */
