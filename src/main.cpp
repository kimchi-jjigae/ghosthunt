#include <iostream>
#include <framework/application/application.h>

int main()
{ 
    ApplicationImplementation ghosthunt;

    ghosthunt.setup();
    ghosthunt.run();
    ghosthunt.destroy();

    std::cout << "hej\n";
}

