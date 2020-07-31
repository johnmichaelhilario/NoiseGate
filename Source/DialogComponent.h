/*
  ==============================================================================

    DialogComponent.h
    Created: 31 Jul 2020 2:28:26pm
    Author:  John Michael Hilario

  ==============================================================================
*/

#pragma once


#include "JUCEHEADER.h"
using namespace juce;

class PluginDialog :public Component{

    public:
        
        void callAlert(String pluginTitle, String pluginDescription, String companyName) {
        

                AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
                pluginTitle,
                pluginDescription + '\n' + companyName,
                "OK");
        }
    
    private:

        AppLookAndFeelCls appLookAndFeel;

};