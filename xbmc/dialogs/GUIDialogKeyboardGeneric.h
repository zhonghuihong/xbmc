/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "guilib/GUIKeyboard.h"
#include "guilib/GUIDialog.h"
#include "utils/Variant.h"

enum KEYBOARD {CAPS, LOWER, SYMBOLS };

class CGUIDialogKeyboardGeneric : public CGUIDialog, public CGUIKeyboard
{
  public:
    CGUIDialogKeyboardGeneric();

    //CGUIKeyboard Interface
    virtual bool ShowAndGetInput(char_callback_t pCallback, const std::string &initialString, std::string &typedString, const std::string &heading, bool bHiddenInput);
    virtual void Cancel();
    virtual int GetWindowId() const;

    //CGUIDialog Interface
    virtual void FrameMove();
    void SetHeading(const std::string& heading);
    void SetText(const std::string& aTextString);
    void InputText(const std::string& aTextString);
    void InputTextEditing(const std::string& aTextString, int start, int length);
    std::string GetText() const;
    bool IsConfirmed() { return m_bIsConfirmed; };
    void SetHiddenInput(bool hiddenInput) { m_hiddenInput = hiddenInput; };
    void Character(WCHAR wch);
    void OnPasteClipboard(void);

  protected:
    virtual void OnInitWindow();
    virtual bool OnAction(const CAction &action);
    virtual bool OnMessage(CGUIMessage& message);
    virtual void OnDeinitWindow(int nextWindowID);
    void SetControlLabel(int id, const std::string &label);
    void OnShift();
    void MoveCursor(int iAmount);
    void SetCursorPos(int iPos);
    int GetCursorPos() const;
    void OnSymbols();
    void OnIPAddress();
    void OnOK();

  private:
    void OnClickButton(int iButtonControl);
    void OnRemoteNumberClick(int key);
    void UpdateButtons();
    char GetCharacter(int iButton);
    void UpdateLabel();
    void ResetShiftAndSymbols();
    void Backspace();
    void SendSearchMessage();

    std::wstring m_strEdit;
    int m_iCursorPos;

    // holds the spelling region of keystrokes/text generated from 'input method'
    std::wstring m_strEditing;
    int m_iEditingOffset;
    int m_iEditingLength;

    bool m_bIsConfirmed;
    KEYBOARD m_keyType;
    int m_iMode;
    bool m_bShift;
    bool m_hiddenInput;

    unsigned int m_lastRemoteClickTime;
    WORD m_lastRemoteKeyClicked;
    int m_indexInSeries;
    std::string m_strHeading;
    static const char* s_charsSeries[10];


    char_callback_t m_pCharCallback;
};
