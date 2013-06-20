#pragma once
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Box.hpp>
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
        sfg::Box::Ptr menuBox = sfg::Box::Create(sfg::Box::VERTICAL, 26.0f);
        sfg::Box::Ptr joinBox = sfg::Box::Create(sfg::Box::VERTICAL, 26.0f);
        sfg::Box::Ptr hostBox = sfg::Box::Create(sfg::Box::VERTICAL, 26.0f);
        sfg::Desktop desktop;
        std::string state = "menu";

        //menu
        sfg::Button::Ptr joinButt = sfg::Button::Create("JOIN GAME");
        sfg::Button::Ptr hostButt = sfg::Button::Create("HOST GAME");
        //sfg::Button::Ptr instructButt(sfg::Button::Create("Instructions"));
        //sfg::Button::Ptr optionsButt(sfg::Button::Create("Options"));

        //join
        sfg::Label::Ptr joinLabel = sfg::Label::Create("Join a game");
        sfg::Label::Ptr joinIPLabel = sfg::Label::Create("IP:");
        sfg::Button::Ptr joinConnectButt = sfg::Button::Create("JOIN GAME");
        sfg::Button::Ptr joinBackButt = sfg::Button::Create("Back");

        //host
        sfg::Label::Ptr hostWaitLabel = sfg::Label::Create("Waiting for the other player to connect");
        sfg::Label::Ptr hostIPLabel = sfg::Label::Create("Your IP:");
        sfg::Button::Ptr hostBackButt = sfg::Button::Create("Back");
};
