#pragma once

// #include <Security/SecureText.h>
#include <UndoRedoManager.h>
#include <Timers/Timer.h>
#include <Threading/Syncronizer.h>

#include <Drawing/Container.h>
#include <Drawing/Buttons/ButtonBase.h>
#include <Drawing/Border.h>
#include <Input/TextChangedEventArgs.h>

namespace xit::Drawing
{
    class TextBox : public Container
    {
    private:
        UndoRedoManager undoRedoManager;
        ButtonBase showPasswordButton;
        Label textLabel;
        Label textHintLabel;
        Border caret;
        Border selectionBorder;
        Timer caretTimer;

        std::string viewText;
        std::string internalText;

        size_t textLength;
        // SecureText* secureText;

        size_t caretLineNumber;
        size_t numberOfLines;

        size_t mouseSelectionStartIndex;
        int labelLeft;

        bool isCaretVisible;
        bool isEditEnabled;
        bool isPassword;
        bool acceptsReturn;

        size_t caretIndex;
        size_t selectionStart;
        size_t selectionLength;

        Size totalSize;
        std::string invalidCharacters;
        size_t invalidCharactersLength;

    public:
        __always_inline bool GetIsEditEnabled() { return isEditEnabled; }
        void SetIsEditEnabled(bool value);

        __always_inline bool GetIsPassword() { return isPassword; }
        void SetIsPassword(bool value);

        const char PasswordCharacter = '*';

        __always_inline const std::string &GetText() const { return viewText; }
        void SetText(const std::string &value);

        inline std::string GetPassword() { return internalText; }

        __always_inline const std::string &GetHintText() const { return textHintLabel.GetText(); }
        __always_inline void SetHintText(const std::string &value) { textHintLabel.SetText(value); }

        // __always_inline const std::string &GetHintTextSource() const { return textHintLabel.GetTextSource(); }
        // __always_inline void SetHintTextSource(const std::string &value) { textHintLabel.SetTextSource(value); }

        __always_inline const TextWrapping &GetTextWrapping() const { return textLabel.GetTextWrapping(); }
        __always_inline void SetTextWrapping(const TextWrapping &value) { textLabel.SetTextWrapping(value); }

        __always_inline const std::string &GetFontName() const { return textLabel.GetFontName(); }
        __always_inline void SetFontName(const std::string &value) { textLabel.SetFontName(value); }

        __always_inline int GetFontSize() const { return textLabel.GetFontSize(); }
        __always_inline void SetFontSize(int value) { textLabel.SetFontSize(value); }

        __always_inline bool GetAcceptsReturn() { return acceptsReturn; }
        void SetAcceptsReturn(bool value)
        {
            if (acceptsReturn != value)
            {
                acceptsReturn = value;
            }
        }

        __always_inline const std::string &GetInvalidCharacters() const { return invalidCharacters; }
        void SetInvalidCharacters(const std::string &value);

        __always_inline HorizontalAlignment GetTextAlignment() const { return textLabel.GetHorizontalAlignment(); }
        void SetTextAlignment(const HorizontalAlignment &value);

        __always_inline size_t GetCaretIndex() const { return caretIndex; }
        void SetCaretIndex(size_t value);

        __always_inline size_t SelectionStart() const { return selectionStart; }
        void SetSelectionStart(size_t value);

        __always_inline size_t SelectionLength() const { return selectionLength; }
        void SetSelectionLength(size_t value);

        Event<TextChangedEventArgs&> TextChanged;

        TextBox();
        ~TextBox();

    private:
        void CheckInvalidCharacters();

        void CaretBlink(EventArgs &e);
        void UpdateCaret();
        void UpdateSelection();
        void UpdateForeground();

        size_t GetMouseCharacterIndex(int mouseXPosition);

        void UpdateTextHintLabel();

        void UpdateVisibleText();
        void ShowPasswordButton_ActiveChanged(IsActiveProperty &sender, EventArgs &e);
        void HandleControl(KeyEventArgs &e, bool isSelection);

    protected:
        void OnForegroundChanged(EventArgs &e) override;

        void OnClick() override;

        void OnGotKeyboardFocus(EventArgs &e) override;
        void OnLostKeyboardFocus(EventArgs &e) override;

        void OnKeyDown(KeyEventArgs &e) override;

        void OnInputPressed(MouseEventArgs &e) override;
        void OnInputReleased(MouseEventArgs &e) override;

        void OnInputMove(MouseEventArgs &e) override;

        int OnMeasureWidth(int available) override;
        int OnMeasureHeight(int available) override;

        void OnSizeChanged(const Size &newSize) override;

        void OnUpdate(const Rectangle &bounds) override;
        void OnRender() override;

        virtual void OnTextChanged(TextChangedEventArgs &e);

    public:
        void SetDPIScale(float scaleX, float scaleY) override;

        void Insert(size_t index, const std::string &s);
        void Insert(size_t index, char c);
        void Remove(size_t index, size_t count);
        void SelectAll();
        void Erase();
    };
}
