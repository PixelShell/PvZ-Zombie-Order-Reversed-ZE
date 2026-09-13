#ifndef __DIFFICULTYDIALOG_H__
#define __DIFFICULTYDIALOG_H__

#include "Lawn/Widget/LawnDialog.h"
#include "widget/SliderListener.h"

class LawnApp;
class LawnStoneButton;
class NewLawnButton;
namespace Sexy
{
    class Slider;
    class Checkbox;
};

class DifficultyDialog : public LawnDialog, public Sexy::SliderListener
{
protected:
    enum
    {
        DifficultyDialog_Slider,
        DifficultyDialog_Back,
        DifficultyDialog_Switch,
    };

public:
    LawnApp*				mApp;
    LawnStoneButton*	    mBackButton;
	LawnStoneButton*		mSwitchButton;
    bool                    mFromGameSelector;
    
    DifficultyDialog(LawnApp* theApp, bool theFromGameSelector);
    ~DifficultyDialog() override;

    int						GetPreferredHeight(int theWidth) override;
    void					AddedToManager(Sexy::WidgetManager* theWidgetManager) override;
    void					RemovedFromManager(Sexy::WidgetManager* theWidgetManager) override;
    void					Resize(int theX, int theY, int theWidth, int theHeight) override;
    void					Draw(Sexy::Graphics* g) override;
    void					SliderVal(int theId, double theVal) override;
    void					ButtonPress(int theId) override;
    void					ButtonDepress(int theId) override;
    void					KeyDown(Sexy::KeyCode theKey) override;
};

#endif
