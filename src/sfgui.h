#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

class Clicky
{
    public:
        void menu();
        void join();
        void host();

    private:
        sfg::SFGUI sfgui;
        sfg::Box::Ptr box(sfg::Box::Create(sfg::Box::VERTICAL, 26.0f));

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


