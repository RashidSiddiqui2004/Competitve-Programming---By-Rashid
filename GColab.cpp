#include <iostream>
#include <string>
using namespace std;

// Different states of a cell
enum CellState
{
    UNEXECUTED,
    RUNNING,
    EXECUTED,
    INTERRUPTED
};

// Functional requirements of GColab Editor
// 1. User can add and delete cells
// 2. User can move a cell upwards or downwards.
// 3. User can change the state of a cell, from unexecuted to running, from running to interrupted

class GColabCell
{
private:
    string code;
    int cellId;
    CellState state;

public:
    GColabCell *prev;
    GColabCell *next;

    GColabCell(int cellId, string code)
    {
        this->cellId = cellId;
        this->code = code;
        this->state = UNEXECUTED;
        this->prev = nullptr;
        this->next = nullptr;
    }

    void getCode()
    {
        cout << this->code << endl;
    }

    void setCode(string updatedCode)
    {
        this->code = updatedCode;
    }

    int getCellId()
    {
        return this->cellId;
    }

    CellState getState()
    {
        return this->state;
    }

    void setState(CellState newState)
    {
        this->state = newState;
    }
};

class GColab
{
private:
    static int cellCounter;
    string notebookTitle;

    GColabCell *rootCell;
    GColabCell *cellIterator;

public:
    GColab(string title) : notebookTitle(title)
    {
        cellCounter = 0;
        GColabCell *newCell = new GColabCell(cellCounter, "#Write your code here");
        rootCell = newCell;
        cellIterator = rootCell;
        cellCounter += 1;
    }

    ~GColab()
    {
        // Clean up memory
        GColabCell *current = rootCell;
        while (current != nullptr)
        {
            GColabCell *next = current->next;
            delete current;
            current = next;
        }
    }

    void addNewCell()
    {
        GColabCell *newCell = new GColabCell(cellCounter, "#Write your code here");
        newCell->prev = cellIterator;
        cellIterator->next = newCell;
        cellIterator = cellIterator->next;
        cellCounter += 1;
    }

    void deleteExistingCell(int cellIdToDelete)
    {
        GColabCell *temp = rootCell;

        if (temp->getCellId() == cellIdToDelete)
        {
            rootCell = temp->next;
            if (rootCell)
            {
                rootCell->prev = nullptr;
            }
            delete temp;
            return;
        }

        while (temp && temp->next)
        {
            int nextCellId = temp->next->getCellId();
            if (nextCellId == cellIdToDelete)
            {
                GColabCell *nextToNextCell = temp->next->next;
                delete temp->next;
                temp->next = nextToNextCell;
                if (nextToNextCell)
                {
                    nextToNextCell->prev = temp;
                }
                return;
            }
            temp = temp->next;
        }

        cout << "Cell with ID " << cellIdToDelete << " not found." << endl;
    }

    void swapWithPreviousCell(int cellId)
    {
        GColabCell *current = rootCell;
        while (current && current->getCellId() != cellId)
        {
            current = current->next;
        }

        if (!current || !current->prev)
        {
            cout << "Cannot swap: cell is either the first cell or does not exist." << endl;
            return;
        }

        GColabCell *previous = current->prev;

        if (previous->prev)
        {
            previous->prev->next = current;
        }
        else
        {
            rootCell = current;
        }
        if (current->next)
        {
            current->next->prev = previous;
        }

        previous->next = current->next;
        current->prev = previous->prev;
        previous->prev = current;
        current->next = previous;
    }

    void swapWithNextCell(int cellId)
    {
        GColabCell *current = rootCell;
        while (current && current->getCellId() != cellId)
        {
            current = current->next;
        }

        if (!current || !current->next)
        {
            cout << "Cannot swap: cell is either the last cell or does not exist." << endl;
            return;
        }

        GColabCell *next = current->next;

        if (current->prev)
        {
            current->prev->next = next;
        }
        else
        {
            rootCell = next;
        }
        if (next->next)
        {
            next->next->prev = current;
        }

        current->next = next->next;
        next->prev = current->prev;
        current->prev = next;
        next->next = current;
    }

    void displayNotebook()
    {
        GColabCell *current = rootCell;
        while (current)
        {
            cout << "Cell ID: " << current->getCellId() << endl;
            cout << "Code: ";
            current->getCode();
            cout << "State: " << current->getState() << endl;
            cout << "-------------------" << endl;
            current = current->next;
        }
    }
};

int GColab::cellCounter = 0;

int main()
{
    string colabTitle = "ColabX";

    GColab *noteBook = new GColab(colabTitle);

    noteBook->addNewCell();
    noteBook->addNewCell();
    noteBook->displayNotebook();

    noteBook->swapWithPreviousCell(1);
    noteBook->displayNotebook();

    noteBook->deleteExistingCell(0);
    noteBook->displayNotebook();

    noteBook->swapWithNextCell(2);

    delete noteBook;
    return 0;
}