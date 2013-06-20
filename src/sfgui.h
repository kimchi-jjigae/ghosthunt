#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Clicky
{
    public:
        void run();
        void menu();
        void join();
        void host();

        //menu
        void onJoinButtClick();
        void onHostButtClick();
        void onInstructButtClick();
        void onOptionsButtClick();

        //join
        void onConnectButtClick();
        void onBackButtClick();

        //host

    private:
        sfg::SFGUI sfgui;
        sf::RenderWindow renwin(sf::VideoMode(800, 600), "Hejsan!")
        sfg::Box::Ptr menuBox(sfg::Box::Create(sfg::Box::VERTICAL, 26.0f));
        sfg::Box::Ptr joinBox(sfg::Box::Create(sfg::Box::VERTICAL, 26.0f));
        sfg::Box::Ptr hostBox(sfg::Box::Create(sfg::Box::VERTICAL, 26.0f));
        sfg::Desktop desktop;
        sf::Event event;
        sf::Clock clock;
        std::string state = "menu";

        //menu
        sfg::Button::Ptr joinButt(sfg::Button::Create("JOIN GAME"));
        sfg::Button::Ptr hostButt(sfg::Button::Create("HOST GAME"));
        //sfg::Button::Ptr instructButt(sfg::Button::Create("Instructions"));
        //sfg::Button::Ptr optionsButt(sfg::Button::Create("Options"));

        //join
        sfg::Label::Ptr joinLabel = sfg::Label::Create("Join a game");
        sfg::Label::Ptr joinIPLabel = sfg::Label::Create("IP:");
        sfg::Button::Ptr joinConnectButt(sfg::Button::Create("JOIN GAME"));
        sfg::Button::Ptr joinBackButt(sfg::Button::Create("Back"));

        //host
        sfg::Label::Ptr hostWaitLabel = sfg::Label::Create("Waiting for the other player to connect");
        sfg::Label::Ptr hostIPLabel = sfg::Label::Create("Your IP:");
        sfg::Button::Ptr hostBackButt(sfg::Button::Create("Back"));
};

void Clicky::run()
{

    if (state == "menu")
        menu();
    else if (state == "join")
        join();

    renwin.resetGLStates();
    while (renwin.isOpen())
    {
        while (renwin.pollEvent(event))
        {
            desktop.HandleEvent(event);
            if (event.type == sf::Event::Closed)
            {   
                renwin.close();
            }   
        }

        desktop.Update(clock.restart().asSeconds());

        renwin.clear();
        sfgui.Display(renwin);
        renwin.display();
    } 
}
    
void Clicky::menu()
{
    joinButt(sfg::Widget::OnLeftClick).Connect(&Clicky::onJoinButtClick, this);
    hostButt(sfg::Widget::OnLeftClick).Connect(&Clicky::onHostButtClick, this);
    instructButt(sfg::Widget::OnLeftClick).Connect(&Clicky::onInstructButtClick, this);
    optionsButt(sfg::Widget::OnLeftClick).Connect(&Clicky::onOptionsButtClick, this);

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

int main()
{
    Clicky clicky;
    clicky.run();
}
