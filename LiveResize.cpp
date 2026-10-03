#ifdef _WIN32
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <commctrl.h>      //for SetWindowSubclass, link with -lcomctl32
#endif

#include "LiveResize.hpp"

namespace{

    //real size of the window's drawing area, even in the middle of a drag
    sf::Vector2u getClientSize(const sf::RenderWindow& window){
    #ifdef _WIN32
        RECT rect;
        if(GetClientRect(window.getNativeHandle(),&rect))
            return {static_cast<unsigned>(rect.right),static_cast<unsigned>(rect.bottom)};
    #endif
        return window.getSize();
    }

#ifdef _WIN32
    //windows calls this for every message sent to the window, we only care about size changes
    LRESULT CALLBACK resizeProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR data){

        LRESULT result=DefSubclassProc(hwnd,msg,wParam,lParam);       //let SFML handle the message first

        if(msg==WM_SIZE && wParam!=SIZE_MINIMIZED){
            reinterpret_cast<LiveResize*>(data)->redrawNow();
        }
        return result;
    }
#endif

}

LiveResize::LiveResize(sf::RenderWindow& window, std::function<void()> redraw):targetWindow(window),redrawCallback(redraw){
#ifdef _WIN32
    SetWindowSubclass(targetWindow.getNativeHandle(),resizeProc,1,reinterpret_cast<DWORD_PTR>(this));
#endif
}

LiveResize::~LiveResize(){
#ifdef _WIN32
    RemoveWindowSubclass(targetWindow.getNativeHandle(),resizeProc,1);       //fails harmlessly if the window is already closed
#endif
}

void LiveResize::redrawNow(){
    if(busy||!redrawCallback) return;

    busy=true;
    redrawCallback();
    busy=false;
}

std::optional<sf::Vector2u> LiveResize::applyView(sf::RenderWindow& window){

    sf::Vector2u realSize=getClientSize(window);        //actual size right now
    sf::Vector2u oldSize=window.getSize();              //size SFML still remembers

    if(realSize.x==0||realSize.y==0||oldSize.x==0||oldSize.y==0) return std::nullopt;     //window minimized

    //SFML makes the viewport from its old size, so scale it until it matches the real size
    //(when both sizes are equal this is just the normal full window view)
    float scaleX=static_cast<float>(realSize.x)/oldSize.x;
    float scaleY=static_cast<float>(realSize.y)/oldSize.y;

    sf::View view(sf::FloatRect({0.f,0.f},{static_cast<float>(realSize.x),static_cast<float>(realSize.y)}));
    view.setViewport(sf::FloatRect({0.f,1.f-scaleY},{scaleX,scaleY}));
    window.setView(view);

    return realSize;
}
