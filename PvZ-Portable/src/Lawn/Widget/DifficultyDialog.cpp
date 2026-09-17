#include "../Board.h"
#include "GameButton.h"
#include "../Cutscene.h"
#include "AlmanacDialog.h"
#include "../LawnCommon.h"
#include "../../LawnApp.h"
#include "../System/Music.h"
#include "../../Resources.h"
#include "DifficultyDialog.h"
#include "../../ConstEnums.h"
#include "Lawn/Widget/LawnDialog.h"
#include "SexyAppBase.h"
#include "graphics/Color.h"
#include <cstdint>

using namespace Sexy;

DifficultyDialog::DifficultyDialog(LawnApp* theApp, bool theFromGameSelector) :
	LawnDialog(theApp, Dialogs::DIALOG_DIFFICULTY, true, "[DIFFICULTY_HEADER]", "", "", Dialog::BUTTONS_NONE)
{
	mApp = theApp;
	mFromGameSelector = theFromGameSelector;
	SetColor(Dialog::COLOR_BUTTON_TEXT, Color(255, 255, 100));

	mBackButton = MakeButton(DifficultyDialog::DifficultyDialog_Back, this, "[BACK]");
	mSwitchButton = MakeButton(DifficultyDialog::DifficultyDialog_Switch, this, ">");

	Resize(0, 0, 650, 500);
}

DifficultyDialog::~DifficultyDialog()
{
	delete mBackButton;
	delete mSwitchButton;
}

int DifficultyDialog::GetPreferredHeight(int theWidth)
{
	(void)theWidth;
	return 1000;
}

void DifficultyDialog::AddedToManager(Sexy::WidgetManager* theWidgetManager)
{
	Dialog::AddedToManager(theWidgetManager);
	AddWidget(mBackButton);
	AddWidget(mSwitchButton);
}

void DifficultyDialog::RemovedFromManager(Sexy::WidgetManager* theWidgetManager)
{
	Dialog::RemovedFromManager(theWidgetManager);
	RemoveWidget(mBackButton);
	RemoveWidget(mSwitchButton);
}

void DifficultyDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
	LawnDialog::Resize(theX, theY, theWidth, theHeight);

	mSwitchButton->Resize(200, 355 , 209, 46);
	mBackButton->Resize(200, 400 , 209, 46);
}

void DifficultyDialog::Draw(Sexy::Graphics* g)
{
	LawnDialog::Draw(g);

	Color aTextColor;
	switch (mApp->mDifficulty)
	{
		case (GameDifficulty::DIFFICULTY_EASY):
			aTextColor = Color(0,255,0);
			PvzpDrawString(g, 	"Easy", 314, 140, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_CENTER);
			PvzpDrawString(g, 	"- All buffs from Normal", 40, 170, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- More extra starting sun and conveyor speed", 40, 200, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- Zomboss is slowed permanently", 40, 230, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- Zombies are slowed on spawn for 15 seconds", 40, 260, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			break;
		case (GameDifficulty::DIFFICULTY_NORMAL):
			aTextColor = Color(255,255,0);
			PvzpDrawString(g, 	"Normal", 314, 140, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_CENTER);
			PvzpDrawString(g, 	"- All buffs from Hard", 40, 170, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- Waves are stalled when Zomboss is present", 40, 200, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- Faster conveyor belts", 40, 230, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- Extra starting sun", 40, 260, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			break;
		case (GameDifficulty::DIFFICULTY_HARD):
			aTextColor = Color(255,0,0);
			PvzpDrawString(g, 	"Hard", 314, 140, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_CENTER);
			PvzpDrawString(g, 	"- 4x time before the first wave", 40, 170, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- Sunshrooms grow instantly", 40, 200, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- Level specific rebalancing", 40, 230, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			break;
		case (GameDifficulty::DIFFICULTY_UNALTERED):
			aTextColor = Color(150,0,0);
			PvzpDrawString(g, 	"Unaltered", 314, 140, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_CENTER);
			PvzpDrawString(g, 	"- No buffs", 40, 170, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			PvzpDrawString(g, 	"- Untested, likely impossible", 40, 200, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_LEFT);
			break;
		default:
			break;
	}
}

void DifficultyDialog::SliderVal(int theId, double theVal)
{
}

void DifficultyDialog::KeyDown(Sexy::KeyCode theKey)
{
	if (mApp->mBoard)
	{
		mApp->mBoard->DoTypingCheck(theKey);
	}

	if (theKey == KeyCode::KEYCODE_SPACE || theKey == KeyCode::KEYCODE_RETURN)
	{
		Dialog::ButtonDepress(Dialog::ID_OK);
	}
	else if (theKey == KeyCode::KEYCODE_ESCAPE)
	{
		Dialog::ButtonDepress(Dialog::ID_CANCEL);
	}
}

void DifficultyDialog::ButtonPress(int theId)
{
	(void)theId;
	mApp->PlaySample(SOUND_GRAVEBUTTON);
}

void DifficultyDialog::ButtonDepress(int theId)
{
	LawnDialog::ButtonDepress(theId);

	switch (theId)
	{
	case (DifficultyDialog::DifficultyDialog_Back):
		mApp->KillDialog(Dialogs::DIALOG_DIFFICULTY);
		mApp->DoExtraOptions(mFromGameSelector);
		break;
	case (DifficultyDialog::DifficultyDialog_Switch):
		mApp->mDifficulty = (GameDifficulty)((int32_t)(mApp->mDifficulty) + 1);
		if (mApp->mDifficulty == GameDifficulty::NUM_DIFFICULTY_COUNT)
			mApp->mDifficulty = GameDifficulty::DIFFICULTY_EASY;
		break;
	}
}
