#include <Drawing/TextInsertCommand.h>
#include <Drawing/TextBox.h>

namespace xit::Drawing
{
    void TextInsertCommand::Execute()
    {
        if (undoInsert)
        {
            textBox->Remove(index, text.length());
            textBox->SetCaretIndex(index);
        }
        else
        {
            textBox->Insert(index, text);
            textBox->SetCaretIndex(index + text.length());
        }
    }

    void TextInsertCommand::Undo()
    {
        if (undoInsert)
        {
            textBox->Insert(index, text);
            textBox->SetCaretIndex(index + text.length());
        }
        else
        {
            textBox->Remove(index, text.length());
            textBox->SetCaretIndex(index);
        }
    }
}