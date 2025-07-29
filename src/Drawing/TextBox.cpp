#include <Drawing/TextBox.h>
#include <Drawing/TextInsertCommand.h>
#include <Drawing/Brushes/SolidColorBrush.h>
#include <Input/InputHandler.h>
#include <Clipboard.h>
#include <cstring>
#include <Drawing/DebugUtils.h>

namespace xit::Drawing
{
    void SecureClear(void *ptr, size_t size)
    {
        volatile unsigned char *p = reinterpret_cast<volatile unsigned char *>(ptr);
        while (size--)
        {
            *p++ = 0;
        }
    }

    //******************************************************************************
    // Properties
    //******************************************************************************

    void TextBox::SetIsEditEnabled(bool value)
    {
        if (isEditEnabled != value)
        {
            isEditEnabled = value;
        }
    }

    void TextBox::SetIsPassword(bool value)
    {
        if (isPassword != value)
        {
#ifdef DEBUG_TEXTBOX
            std::cout << "[DEBUG] SetIsPassword: Actually changing from " << isPassword << " to " << value << std::endl;
#endif
            isPassword = value;

            // Mark this TextBox's label for identification
            if (isPassword)
            {
                textLabel.SetName("PasswordTextBoxLabel");
            }
            else
            {
                textLabel.SetName("TextBoxTextLabel");
            }

            // Always update visible text when password mode changes
            UpdateVisibleText();

            showPasswordButton.SetIsVisible(isPassword);
        }
        else
        {
#ifdef DEBUG_TEXTBOX
            std::cout << "[DEBUG] SetIsPassword: No change needed, already " << value << std::endl;
#endif
        }
    }

    void TextBox::SetText(const std::string &value)
    {
        if (isEditEnabled && (internalText != value))
        {
            // For password fields, securely erase old content before setting new text
            if (isPassword)
            {
                Erase();
            }

            size_t valueLength = value.length();
            size_t oldTextLength = internalText.length();

            if (oldTextLength != 0)
                internalText.clear();

            internalText = valueLength ? value : "";
            textLength = valueLength;
            UpdateVisibleText();

            TextChangedEventArgs tce(textLength, 0, oldTextLength, 0);

            CheckInvalidCharacters();

            SetCaretIndex(valueLength);

            selectionStart = caretIndex;
            selectionLength = 0;

            UpdateTextHintLabel();

            OnTextChanged(tce);
        }
    }

    void TextBox::SetInvalidCharacters(const std::string &value)
    {
        invalidCharacters = value;
        if (!value.empty())
        {
            invalidCharactersLength = invalidCharacters.length();
        }
    }

    void TextBox::SetTextAlignment(const HorizontalAlignment &value)
    {
        textLabel.SetHorizontalAlignment(value);
        caret.SetHorizontalAlignment(value);
        textHintLabel.SetHorizontalAlignment(value);
        selectionBorder.SetHorizontalAlignment(value);

        UpdateCaret();
    }

    void TextBox::SetCaretIndex(size_t value)
    {
        if (caretIndex != value)
        {
            if (value <= textLength)
                caretIndex = value;
            else
                caretIndex = textLength; // Clamp to valid range

            UpdateCaret();
        }
    }

    void TextBox::SetSelectionStart(size_t value)
    {
        if (selectionStart != value)
        {
            selectionStart = value;
            UpdateSelection();
        }
    }
    void TextBox::SetSelectionLength(size_t value)
    {
        if (selectionLength != value)
        {
            selectionLength = value;
            UpdateSelection();
        }
    }

    //******************************************************************************
    // Constructor
    //******************************************************************************

    TextBox::TextBox()
    {
        SetBrushGroup("TextBox");
        SetLayoutGroup("TextBox");

        SetName("TextBox");

        SetHandleMouse(true);
        SetHandleKeyboard(true);
        SetCanFocus(true);
        SetClipToBounds(true);
        SetUseOrientation(false);

        textLength = 0;

        mouseSelectionStartIndex = 0;
        labelLeft = 0;

        isCaretVisible = false;
        isPassword = false;
        acceptsReturn = false;

        caretIndex = 0;
        selectionStart = 0;
        selectionLength = 0;

        totalSize = 0;
        invalidCharactersLength = 0;

        // Initialize brush pointers
        selectionBackgroundBrush = nullptr;
        hintTextForegroundBrush = nullptr;

        isEditEnabled = true;
        internalText = "";
        viewText = "";

        numberOfLines = 1;
        caretLineNumber = 0;

        SetColumns("*");
        SetRows("*");

        // SetPadding(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);

        selectionBorder.SetWidth(2);
        selectionBorder.SetVisibility(Visibility::Collapsed);
        selectionBorder.SetVerticalAlignment(VerticalAlignment::Center);
        selectionBorder.SetName("TextBoxSelectionBorder");
        AddChild(&selectionBorder);

        textLabel.SetName("TextBoxTextLabel");
        textLabel.SetTextWrapping(TextWrapping::NoWrap);
        textLabel.SetInheritForeground(true);
        textLabel.SetMargin(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        AddChild(&textLabel);

        caret.SetWidth(1);
        caret.SetVerticalAlignment(VerticalAlignment::Center);
        caret.SetName("TextBoxCaret");

        textHintLabel.SetTextWrapping(TextWrapping::NoWrap);
        textHintLabel.SetMargin(UIDefaults::TextBoxPaddingLeft, 0, UIDefaults::TextBoxPaddingRight, 0);
        textHintLabel.SetName("TextBoxTextHintLabel");
        AddChild(&textHintLabel);

        caretTimer.SetInterval(750);

        showPasswordButton.SetBrushGroup("IconButton");
        showPasswordButton.SetLayoutGroup("ButtonInContainer");
        showPasswordButton.SetUniformImageSize(UIDefaults::ButtonImageHeight);
        showPasswordButton.SetShowLabel(false);
        showPasswordButton.SetShowImage(true);
        showPasswordButton.SetImageSource("Resources/Images/Buttons/Eye.png");
        showPasswordButton.SetCanActivate(true);
        showPasswordButton.SetVisibility(Visibility::Collapsed);
        showPasswordButton.SetToolTip("Show/hide password");
        showPasswordButton.IsActiveChanged.Add(&TextBox::ShowPasswordButton_ActiveChanged, this);
        showPasswordButton.SetName("TextBoxShowPasswordButton");
        AddChild(&showPasswordButton);

        showPasswordButton.InputPressed.Add([](InputContent &sender, MouseEventArgs &e) -> void
                                            { e.Handled = true; });
        showPasswordButton.InputReleased.Add([](InputContent &sender, MouseEventArgs &e) -> void
                                             { e.Handled = true; });

        caretTimer.Elapsed.Add(&TextBox::CaretBlink, this);

        UpdateForeground();
    }
    TextBox::~TextBox()
    {
        caretTimer.Stop();
        
        // Clean up dynamically allocated brushes
        if (selectionBackgroundBrush)
        {
            delete selectionBackgroundBrush;
            selectionBackgroundBrush = nullptr;
        }
        if (hintTextForegroundBrush)
        {
            delete hintTextForegroundBrush;
            hintTextForegroundBrush = nullptr;
        }
    }

    //******************************************************************************
    // Private
    //******************************************************************************

    void TextBox::CheckInvalidCharacters()
    {
        SetIsError(
            !invalidCharacters.empty() &&
            invalidCharactersLength > 0 &&
            internalText.find_first_of(invalidCharacters) != std::string::npos);
    }

    void TextBox::CaretBlink(EventArgs &e)
    {
        isCaretVisible = !isCaretVisible;
        Invalidate();
    }
    void TextBox::UpdateCaret()
    {
        int offset = 0;

        totalSize = textLabel.MeasureText();
        std::string fullTextToMeasure = textLabel.GetText();

#ifdef DEBUG_TEXTBOX
        std::cout << "[DEBUG] UpdateCaret() - caretIndex=" << caretIndex << ", textLength=" << textLength << std::endl;
        std::cout << "[DEBUG] UpdateCaret() - totalSize.GetWidth()=" << totalSize.GetWidth() << std::endl;
        std::cout << "[DEBUG] UpdateCaret() - fullTextToMeasure='" << fullTextToMeasure << "' (using viewText)" << std::endl;
        std::cout << "[DEBUG] UpdateCaret() - alignment=" << (int)GetTextAlignment() << " (0=Left, 1=Center, 2=Right, 3=Stretch)" << std::endl;
#endif

        int left;

        if (caretIndex > 0 && GetIsVisible())
        {
            Size size;
            Label::MeasureText(GetFontName(), GetFontSize(), viewText.substr(0, caretIndex), size);
            left = size.GetWidth();
        }
        else
        {
            left = 0;
        }

        if (GetTextAlignment() == HorizontalAlignment::Center)
        {
            offset = -totalSize.GetWidth();
            left <<= 1;
        }
        else if (GetTextAlignment() == HorizontalAlignment::Left ||
                 GetTextAlignment() == HorizontalAlignment::Stretch)
        {
            offset = GetPadding().GetLeft();
            offset += textLabel.GetMargin().GetLeft();
            offset = (int)((float)offset / GetScaleX());

            left = (int)((float)left / GetScaleX());
            
#ifdef DEBUG_TEXTBOX
            std::cout << "[DEBUG] UpdateCaret() - LEFT alignment: offset=" << offset << ", left=" << left << std::endl;
            std::cout << "[DEBUG] UpdateCaret() - LEFT final position=" << (offset + left) << std::endl;
#endif
        }
        else if (GetTextAlignment() == HorizontalAlignment::Right)
        {
            offset = GetPadding().GetRight();
            offset += textLabel.GetMargin().GetRight();
            offset = (int)((float)offset / GetScaleX());

            left = (int)((float)left / GetScaleX());
            
#ifdef DEBUG_TEXTBOX
            std::cout << "[DEBUG] UpdateCaret() - RIGHT alignment: offset=" << offset << ", left=" << left << std::endl;
            std::cout << "[DEBUG] UpdateCaret() - RIGHT final position=" << (offset + left) << std::endl;
#endif
        }

        caret.SetMargin((offset + left), 0, 0, 0);

#ifdef DEBUG_TEXTBOX
        std::cout << "[DEBUG] UpdateCaret() - FINAL: Setting caret margin to " << (offset + left) << std::endl;
        std::cout << "[DEBUG] UpdateCaret() - ===========================================" << std::endl;
#endif

        if (caretTimer.Enabled)
        {
            caretTimer.Stop();
            isCaretVisible = true;
            caretTimer.Start();
        }
    }
    void TextBox::UpdateSelection()
    {
#ifdef DEBUG_TEXTBOX
        std::cout << "[DEBUG] UpdateSelection() - selectionStart=" << selectionStart << ", selectionLength=" << selectionLength << std::endl;
#endif

        bool isVisible = selectionLength > 0;

        if (isVisible)
        {
            int offset = 0;
            int left = 0;

            Size size;
            Label::MeasureText(GetFontName(), GetFontSize(), viewText.substr(selectionStart, selectionLength), size);

            selectionBorder.SetWidth(size.GetWidth() + 1);

            if (selectionStart != 0)
            {
                Label::MeasureText(GetFontName(), GetFontSize(), viewText.substr(0, selectionStart), size);
                left = size.GetWidth();
            }

            if ((GetTextAlignment() == HorizontalAlignment::Left) ||
                (GetTextAlignment() == HorizontalAlignment::Stretch)) // TODO && TextDirection LeftToRight
            {
                offset += textLabel.GetMargin().GetLeft();
                selectionBorder.SetMargin(offset + left, 0, 0, 0);
            }
            else if (GetTextAlignment() == HorizontalAlignment::Center)
            {
                offset = -((textLabel.GetActualWidth() - size.GetWidth()) >> 1);
                offset += textLabel.GetMargin().GetLeft();
                selectionBorder.SetMargin(offset + left, 0, 0, 0);
            }
            else if (GetTextAlignment() == HorizontalAlignment::Right)
            {
                offset += textLabel.GetMargin().GetRight();
                selectionBorder.SetMargin(0, 0, offset + left, 0);
            }
        }

        selectionBorder.SetVisibility(isVisible ? Visibility::Visible : Visibility::Collapsed);
    }
    void TextBox::UpdateForeground()
    {
        const BrushBase *foreground = GetForeground();
        if (foreground)
        {
            // TODO check if this is called during init while items are not fully initialized
            const SolidColorBrush *tmp = dynamic_cast<const SolidColorBrush *>(foreground);

            if (tmp)
            {
                // Clean up old brushes before creating new ones
                if (selectionBackgroundBrush)
                {
                    delete selectionBackgroundBrush;
                    selectionBackgroundBrush = nullptr;
                }
                if (hintTextForegroundBrush)
                {
                    delete hintTextForegroundBrush;
                    hintTextForegroundBrush = nullptr;
                }

                // Create new brushes and store them as member variables
                selectionBackgroundBrush = new SolidColorBrush(tmp);
                selectionBackgroundBrush->SetOpacity(0.15);
                selectionBorder.SetBackground(selectionBackgroundBrush);

                hintTextForegroundBrush = new SolidColorBrush(tmp);
                hintTextForegroundBrush->SetOpacity(0.6);
                textHintLabel.SetForeground(hintTextForegroundBrush);
            }
            caret.SetBackground(foreground);
        }
    }

    size_t TextBox::GetMouseCharacterIndex(int mouseXPosition)
    {
        size_t index = 0;
        int closest = 0;

        Size size = textLabel.MeasureText();
        if (mouseXPosition >= size.GetWidth())
        {
            index = textLength;
            return index;
        }

        for (size_t i = 0; i <= textLength; i++)
        {
            Label::MeasureText(GetFontName(), GetFontSize(), viewText.substr(0, i), size);

            if (size.GetWidth() < mouseXPosition)
            {
                closest = size.GetWidth();
                index = i;
            }
            else
            {
                if (std::abs(size.GetWidth() - mouseXPosition) < std::abs(closest - mouseXPosition))
                {
                    index = i;
                }
                break;
            }
        }

        return index;
    }

    void TextBox::UpdateTextHintLabel()
    {
#ifdef DEBUG_TEXTBOX
        std::cout << "[DEBUG] UpdateTextHintLabel() called, internalText.empty()=" << internalText.empty() << std::endl;
#endif

        if (internalText.empty())
        {
            textHintLabel.SetFontSize(UIDefaults::DefaultFontSize);
            textHintLabel.SetVerticalAlignment(VerticalAlignment::Center);
#ifdef DEBUG_TEXTBOX
            std::cout << "[DEBUG] Set textHintLabel to Center alignment, DefaultFontSize" << std::endl;
#endif
        }
        else
        {
            textHintLabel.SetFontSize(UIDefaults::SmallFontSize);
            textHintLabel.SetVerticalAlignment(VerticalAlignment::Top);
#ifdef DEBUG_TEXTBOX
            std::cout << "[DEBUG] Set textHintLabel to Top alignment, SmallFontSize" << std::endl;
#endif
        }
#ifdef DEBUG_TEXTBOX
        std::cout << "[DEBUG] textLabel VerticalAlignment: " << (int)textLabel.GetVerticalAlignment() << std::endl;
        std::cout << "[DEBUG] textHintLabel VerticalAlignment: " << (int)textHintLabel.GetVerticalAlignment() << std::endl;
#endif
        // textHintLabel.SetVisibility(internalText.empty() ? Visibility::Visible : Visibility::Collapsed);
    }

    void TextBox::UpdateVisibleText()
    {
#ifdef DEBUG_TEXTBOX
        std::cout << "[DEBUG] UpdateVisibleText() called" << std::endl;
        std::cout << "[DEBUG] isPassword=" << isPassword << ", textLength=" << textLength << std::endl;
        std::cout << "[DEBUG] internalText='" << internalText << "'" << std::endl;
#endif

        if (showPasswordButton.GetIsActive() || !isPassword)
        {
            viewText = internalText;
#ifdef DEBUG_TEXTBOX
            std::cout << "[DEBUG] Using internalText: '" << viewText << "'" << std::endl;
#endif
        }
        else
        {
            viewText = textLength > 0 ? std::string(textLength, PasswordCharacter) : "";
#ifdef DEBUG_TEXTBOX
            std::cout << "[DEBUG] Using asterisks: '" << viewText << "'" << std::endl;
#endif
        }

        textLabel.SetText(viewText);
        UpdateCaret();

#ifdef DEBUG_TEXTBOX
        std::cout << "[DEBUG] UpdateVisibleText() complete" << std::endl;
#endif
    }
    void TextBox::ShowPasswordButton_ActiveChanged(IsActiveProperty &sender, EventArgs &e)
    {
        UpdateVisibleText();
        UpdateSelection();
    }

    void TextBox::HandleControl(KeyEventArgs &e, bool isSelection)
    {
        if (e.Key == CKey::Z && undoRedoManager.CanUndo())
        {
            undoRedoManager.Undo();
            e.Handled = true;
            UpdateTextHintLabel();
        }
        else if (e.Key == CKey::Y && undoRedoManager.CanRedo())
        {
            undoRedoManager.Redo();
            e.Handled = true;
            UpdateTextHintLabel();
        }
        else if (e.Key == CKey::A)
        {
            SetSelectionStart(0);
            SetSelectionLength(textLength);
        }
        else if (e.Key == CKey::C)
        {
            if (selectionLength > 0)
            {
                std::string selection = internalText.substr(selectionStart, selectionLength);
                if (!selection.empty())
                {
                    Clipboard::SetText(selection);
                    e.Handled = true;
                }
            }
            else if (textLength > 0)
            {
                std::string selection = internalText.substr(0, textLength);
                if (!selection.empty())
                {
                    Clipboard::SetText(selection);
                    e.Handled = true;
                }
            }
        }
        else if (e.Key == CKey::X)
        {
            if (selectionLength > 0)
            {
                std::string selection = internalText.substr(selectionStart, selectionLength);
                if (!selection.empty())
                {
                    Clipboard::SetText(selection);
                    TextChangedEventArgs tce(0, 0, isSelection ? selectionLength : 1, selectionStart);

                    std::string removedText = internalText.substr(tce.RemovedOffset, tce.RemovedLength);
                    auto command = std::make_unique<TextInsertCommand>(this, tce.RemovedOffset, removedText, true);
                    undoRedoManager.SetNextCommand(std::move(command));

                    Remove(selectionStart, selectionLength);
                    selectionLength = 0;
                    UpdateSelection();
                    OnTextChanged(tce);
                }

                e.Handled = true;
                UpdateVisibleText();
            }
            else if (textLength > 0)
            {
                Clipboard::SetText(internalText);
                TextChangedEventArgs tce(0, 0, isSelection ? selectionLength : 1, selectionStart);

                std::string removedText = internalText.substr(tce.RemovedOffset, tce.RemovedLength);
                auto command = std::make_unique<TextInsertCommand>(this, tce.RemovedOffset, removedText, true);
                undoRedoManager.SetNextCommand(std::move(command));

                Remove(0, textLength);
                selectionLength = 0;
                selectionStart = 0;
                caretIndex = 0;
                UpdateSelection();
                OnTextChanged(tce);

                e.Handled = true;
                UpdateVisibleText();
                UpdateTextHintLabel();
                Invalidate();
            }
        }
        else if (e.Key == CKey::V)
        {
            std::string clipboardText = Clipboard::GetText();
            if (!clipboardText.empty())
            {
                size_t clipboardTextLength = clipboardText.length();

                if (selectionLength > 0)
                {
                    TextChangedEventArgs tce(selectionLength, selectionStart, 0, 0);

                    std::string removedText = internalText.substr(tce.RemovedOffset, tce.RemovedLength);
                    auto command = std::make_unique<TextInsertCommand>(this, tce.RemovedOffset, removedText, true);
                    undoRedoManager.SetNextCommand(std::move(command));

                    Remove(selectionStart, selectionLength);
                    selectionLength = 0;

                    OnTextChanged(tce);
                }
                // else if (textLength > 0)
                // {
                //     TextChangedEventArgs tce(0, 0, textLength, 0);

                //     std::string removedText = internalText.substr(tce.RemovedOffset, tce.RemovedLength);
                //     auto command = std::make_unique<TextInsertCommand>(this, tce.RemovedOffset, removedText, true);
                //     undoRedoManager.SetNextCommand(std::move(command));

                //     Remove(0, textLength);
                //     selectionLength = 0;

                //     OnTextChanged(tce);
                // }

                TextChangedEventArgs tce(clipboardTextLength, caretIndex, 0, 0);

                auto command = std::make_unique<TextInsertCommand>(this, tce.AddedOffset, clipboardText, false);
                undoRedoManager.SetNextCommand(std::move(command));

                Insert(caretIndex, clipboardText);

                UpdateVisibleText();
                UpdateTextHintLabel();

                selectionStart += clipboardTextLength;
                SetCaretIndex(selectionStart);

                OnTextChanged(tce);

                e.Handled = true;
                Invalidate();
            }
        }
    }

    //******************************************************************************
    // Protected overrides
    //******************************************************************************

    void TextBox::OnForegroundChanged(EventArgs &e)
    {
        Container::OnForegroundChanged(e);
        UpdateForeground();
    }

    void TextBox::OnClick()
    {
        if (!GetIsFocused())
        {
            Focus();
        }

        Container::OnClick();
    }

    void TextBox::OnGotKeyboardFocus(EventArgs &e)
    {
        isCaretVisible = true;
        UpdateCaret();
        caretTimer.Start();

        Container::OnGotKeyboardFocus(e);
    }
    void TextBox::OnLostKeyboardFocus(EventArgs &e)
    {
        caretTimer.Stop();
        isCaretVisible = false;
        SetSelectionLength(0);

        Container::OnLostKeyboardFocus(e);
    }

    void TextBox::OnKeyDown(KeyEventArgs &e)
    {
        if (e.Handled)
            return;

        if (e.Key != CKey::Enter || (e.Key == CKey::Enter && !acceptsReturn))
        {
            Container::OnKeyDown(e);
        }

        if (!isEditEnabled || e.Handled)
        {
            e.Handled = true;
            return;
        }

        bool isSelection = selectionLength != 0;

        if (InputHandler::IsModifierKey(e.Key))
        {
            return;
        }

        if (InputHandler::IsControl())
        {
            HandleControl(e, isSelection);
            return;
        }
        else if (GetIsFocused())
        {
            if (InputHandler::IsAlt())
            {
                return;
            }
            else if (e.Key == CKey::Enter)
            {
                Insert(caretIndex, '\n');
            }
            else if (e.Key == CKey::Backspace)
            {
                if (textLength > 0)
                {
                    TextChangedEventArgs tce(0, 0, isSelection ? selectionLength : 1, selectionStart = isSelection ? selectionStart : caretIndex - 1);

                    std::string removedText = internalText.substr(tce.RemovedOffset, tce.RemovedLength);
                    auto command = std::make_unique<TextInsertCommand>(this, tce.RemovedOffset, removedText, true);
                    undoRedoManager.SetNextCommand(std::move(command));

                    Remove(tce.RemovedOffset, tce.RemovedLength);

                    if (isSelection)
                    {
                        SetSelectionLength(0);
                        SetCaretIndex(selectionStart);
                    }
                    else
                    {
                        SetCaretIndex(caretIndex - 1);
                    }

                    OnTextChanged(tce);
                }
            }
            else if (e.Key == CKey::Delete)
            {
                if (textLength > 0)
                {
                    TextChangedEventArgs tce(0, 0, isSelection ? selectionLength : 1, selectionStart);

                    std::string removedText = internalText.substr(tce.RemovedOffset, tce.RemovedLength);
                    auto command = std::make_unique<TextInsertCommand>(this, tce.RemovedOffset, removedText, true);
                    undoRedoManager.SetNextCommand(std::move(command));

                    Remove(selectionStart, tce.RemovedLength);

                    if (isSelection)
                    {
                        SetSelectionLength(0);
                    }

                    SetCaretIndex(selectionStart);

                    OnTextChanged(tce);
                }
            }
            else if (e.Key == CKey::Home)
            {
                selectionLength = InputHandler::IsShift()
                                      ? selectionStart < caretIndex
                                            ? selectionStart
                                            : selectionLength + caretIndex
                                      : 0;

                SetCaretIndex(selectionStart = 0);

                e.Handled = true;
                UpdateSelection();
                Invalidate();
                return;
            }
            else if (e.Key == CKey::End)
            {
                selectionStart = InputHandler::IsShift()
                                     ? selectionLength == 0
                                           ? caretIndex
                                       : caretIndex == selectionStart
                                           ? selectionStart + selectionLength
                                           : selectionStart
                                     : textLength;

                selectionLength = InputHandler::IsShift()
                                      ? textLength - selectionStart
                                      : 0;

                e.Handled = true;
                SetCaretIndex(textLength);
                UpdateSelection();
                Invalidate();
                return;
            }
            else if (e.Key == CKey::Up)
            {
                if (InputHandler::IsShift())
                {
                    if (caretLineNumber == 0)
                    {
                        if (caretIndex > 0)
                        {
                            if (selectionLength > 0)
                            {
                                if (selectionStart == caretIndex)
                                {
                                    selectionLength += caretIndex;
                                    selectionStart = 0;
                                    SetCaretIndex(0);
                                }
                                else
                                {
                                    selectionLength = 0;
                                    SetCaretIndex(selectionStart);
                                }
                            }
                            else
                            {
                                selectionLength = caretIndex;
                                selectionStart = 0;
                                SetCaretIndex(0);
                            }

                            UpdateSelection();
                        }
                    }
                }
                else
                {
                    if (numberOfLines == 1)
                    {
                        selectionLength = 0;
                        UpdateSelection();
                    }
                }

                e.Handled = true;
                Invalidate();
                return;
            }
            else if (e.Key == CKey::Down)
            {
                if (InputHandler::IsShift())
                {
                    if (numberOfLines == 1)
                    {
                        if (caretIndex < textLength - 1)
                        {
                            if (selectionLength > 0)
                            {
                                if (selectionStart + selectionLength == caretIndex)
                                {
                                    selectionLength = textLength - selectionStart;
                                    SetCaretIndex(textLength);
                                }
                                else
                                {
                                    selectionStart = selectionLength;
                                    selectionLength = 0;
                                    SetCaretIndex(selectionStart);
                                }
                            }
                            else
                            {
                                selectionStart = caretIndex;
                                selectionLength = textLength - selectionStart;
                                SetCaretIndex(textLength);
                            }

                            UpdateSelection();
                        }
                    }
                }
                else
                {
                    if (numberOfLines == 1)
                    {
                        selectionLength = 0;
                        UpdateSelection();
                    }
                }

                e.Handled = true;
                Invalidate();
                return;
            }
            else if (e.Key == CKey::PageDown || e.Key == CKey::PageUp)
            {
                return;
            }
            else if (e.Key == CKey::Left)
            {
                bool change = selectionStart - 1 >= 0;
                // selectionStart = change ? selectionStart - 1 : selectionStart;

                if (InputHandler::IsShift())
                {
                    if (selectionLength == 0)
                    {
                        selectionStart = change && selectionStart > 0 ? selectionStart - 1 : selectionStart;
                        selectionLength = change ? 1 : 0;
                        SetCaretIndex(selectionStart);
                    }
                    else
                    {
                        if (caretIndex > selectionStart)
                        {
                            selectionLength--;
                            SetCaretIndex(caretIndex - 1);
                        }
                        else
                        {
                            selectionStart = change && selectionStart > 0 ? selectionStart - 1 : selectionStart;
                            selectionLength = change ? selectionLength + 1 : selectionLength;
                            SetCaretIndex(selectionStart);
                        }
                    }
                }
                else
                {
                    if (selectionLength > 0)
                    {
                        SetCaretIndex(selectionStart);
                    }
                    else
                    {
                        SetCaretIndex(caretIndex - 1);
                        selectionStart = caretIndex;
                    }

                    selectionLength = 0;
                }

                e.Handled = true;
                UpdateSelection();
                Invalidate();
                return;
            }
            else if (e.Key == CKey::Right)
            {
                if (InputHandler::IsShift())
                {
                    if (selectionLength == 0)
                    {
                        selectionStart = caretIndex;
                        selectionLength = 1;
                        SetCaretIndex(caretIndex + 1);
                    }
                    else
                    {
                        if (caretIndex == selectionStart)
                        {
                            bool change = selectionStart + 1 <= textLength;

                            selectionStart = change ? selectionStart + 1 : selectionStart;
                            selectionLength--;
                            SetCaretIndex(selectionStart);
                        }
                        else
                        {
                            bool change = selectionStart + selectionLength + 1 <= textLength;
                            selectionLength = change ? selectionLength + 1 : selectionLength;
                            SetCaretIndex(caretIndex + 1);
                        }
                    }
                }
                else
                {
                    if (selectionLength > 0)
                    {
                        SetCaretIndex(selectionStart + selectionLength);
                    }
                    else
                    {
                        SetCaretIndex(caretIndex + 1);
                    }

                    selectionStart = caretIndex;
                    selectionLength = 0;
                }

                e.Handled = true;
                UpdateSelection();
                Invalidate();
                return;
            }
            else if (e.KeyChar != '\0')
            {
                TextChangedEventArgs tce(1, caretIndex, 0, 0);

                std::string addedText(1, e.KeyChar);
                auto command = std::make_unique<TextInsertCommand>(this, tce.AddedOffset, addedText, false);
                undoRedoManager.SetNextCommand(std::move(command));

                Insert(caretIndex, e.KeyChar);
                SetCaretIndex(caretIndex + 1);
                selectionStart = caretIndex;
                OnTextChanged(tce);
            }

            e.Handled = true;
            UpdateTextHintLabel();

            Invalidate();
        }
    }

    void TextBox::OnInputPressed(MouseEventArgs &e)
    {
        Container::OnInputPressed(e);

        if (!GetIsFocused())
        {
            Focus();
        }

        SetIsMouseCaptured(true);

        int x = e.Position.X - textLabel.GetLeft();

        SetCaretIndex(selectionStart = mouseSelectionStartIndex = GetMouseCharacterIndex(x));
        SetSelectionLength(0);
    }
    void TextBox::OnInputReleased(MouseEventArgs &e)
    {
        Container::OnInputReleased(e);

        SetIsMouseCaptured(false);

        if (selectionLength != 0)
        {
            e.Handled = true;
        }
    }

    void TextBox::OnInputMove(MouseEventArgs &e)
    {
        Container::OnInputMove(e);

        if (IsMouseCaptured)
        {
            int x = e.Position.X - textLabel.GetLeft();

            size_t index = GetMouseCharacterIndex(x);

            if (index < mouseSelectionStartIndex)
            {
                selectionLength = mouseSelectionStartIndex - index;
                selectionStart = index;
            }
            else if (index > mouseSelectionStartIndex)
            {
                selectionLength = index - mouseSelectionStartIndex;
                selectionStart = mouseSelectionStartIndex;
            }
            else
            {
                selectionLength = 0;
            }
            SetCaretIndex(index);

            UpdateSelection();
        }
    }

    int TextBox::OnMeasureWidth(int available)
    {
        if (GetHorizontalAlignment() == HorizontalAlignment::Stretch)
            return available;

        return textLabel.MeasureWidth(available - GetPadding().GetWidth());
    }
    int TextBox::OnMeasureHeight(int available)
    {
        if (GetVerticalAlignment() == VerticalAlignment::Stretch)
            return available;

        return textLabel.MeasureHeight(available - GetPadding().GetHeight());
    }

    void TextBox::OnSizeChanged(const Size &newSize)
    {
        Container::OnSizeChanged(newSize);

        // if (GetTextAlignment() == HorizontalAlignment::Left)
        {
            // TODO only if label alignment is left?
            labelLeft = (int)((GetActualWidth() - textLabel.GetActualWidth()) * 0.5);
        }
    }

    void TextBox::OnUpdate(const Rectangle &bounds)
    {
        Container::OnUpdate(bounds);

        int height = textLabel.GetFontSize() + 2;

        if (height > 0)
        {
            caret.SetHeight(height);
            selectionBorder.SetHeight(height);
        }
        // Use BoxModel method to calculate client bounds for the caret
        caret.Update(GetClientBounds());
    }
    void TextBox::OnRender()
    {
        Container::OnRender();

        if (isCaretVisible)
        {
            caret.Render();
        }
    }

    //******************************************************************************
    // Protected
    //******************************************************************************

    void TextBox::OnTextChanged(TextChangedEventArgs &e)
    {
        CheckInvalidCharacters();

        TextChanged(e);
    }

    //******************************************************************************
    // Public
    //******************************************************************************

    void TextBox::SetDPIScale(float scaleX, float scaleY)
    {
        Container::SetDPIScale(scaleX, scaleY);
        caret.SetDPIScale(scaleX, scaleY);
        selectionBorder.SetDPIScale(scaleX, scaleY);
    }

    void TextBox::Insert(size_t index, const std::string &s)
    {
        size_t sLength = s.length();
        std::string tmp;

        tmp = internalText.insert(index, s);
        internalText = tmp;
        textLength += sLength;

        UpdateVisibleText();
    }
    void TextBox::Insert(size_t index, char c)
    {
        std::string tmp;
        size_t sLength = 1;

        if (c == 0)
            return;

        tmp = internalText.insert(index, 1, c);
        internalText = tmp;
        textLength += sLength;

        UpdateVisibleText();
    }
    void TextBox::Remove(size_t index, size_t count)
    {
        if (index < textLength && index >= 0)
        {
            std::string tmp = internalText.substr(0, index) + internalText.substr(index + count);
            internalText = tmp;
            textLength = internalText.length();

            UpdateVisibleText();
        }
    }
    void TextBox::SelectAll()
    {
        selectionStart = 0;
        SetCaretIndex(selectionLength = textLength);
        UpdateSelection();
    }
    void TextBox::Erase()
    {
        if (!internalText.empty())
        {
            SecureClear(&internalText[0], internalText.size()); // Securely overwrite memory
        }
        internalText.clear(); // Clear the string
        textLength = 0;       // Reset text length to match cleared content
    }
}
