#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

class Clicky
{
    public:

    private:
        //menu
        sfg::Button::Ptr joinButt(sfg::Button::Create("Click me! :D"));
        sfg::Button::Ptr hostButt(sfg::Button::Create("Click me! :D"));
        sfg::Button::Ptr instructButt(sfg::Button::Create("Click me! :D"));
        sfg::Button::Ptr optionsButt(sfg::Button::Create("Click me! :D"));

        sfg::SFGUI sfgui;
        sfg::Label::Ptr label;

        sfg::Button::Ptr button(sfg::Button::Create("Click me! :D"));
};


