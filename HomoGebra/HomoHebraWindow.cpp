#include "HomoGebraWindow.h"

namespace HomoGebra
{
HomoGebraWindow::HomoGebraWindow(const sf::VideoMode mode,
                                 const sf::String& title,
                                 const sf::Uint32 style,
                                 const sf::ContextSettings& settings)
    : Window(mode, title, style, settings)
{}

void HomoGebraWindow::onResize() { Window::onResize(); }

void HomoGebraWindow::onCreate() { Window::onCreate(); }
}  // namespace HomoGebra