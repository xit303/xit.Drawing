#pragma once

#include <UndoRedoCommand.h>
#include <string>

namespace xit::Drawing
{
    class TextBox; // Forward declaration

    class TextInsertCommand : public UndoRedoCommand
    {
    private:
        TextBox *textBox;
        size_t index;
        std::string text;
        bool undoInsert;

    public:
        TextInsertCommand(TextBox *textBox, size_t index, const std::string &text, bool undoInsert)
            : textBox(textBox), index(index), text(text), undoInsert(undoInsert) {}

        void Execute() override;
        void Undo() override;
    };
}