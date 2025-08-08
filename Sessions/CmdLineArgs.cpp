#include <bits/stdc++.h>
using namespace std;

void PrintErrorMessage()
{
    cout << "Usage: ./program --input=<inputFile> --from=<sourceLang> --accuracy=<float>\n";
}

void Translate(const string &inputFile, const string &from, float accuracy)
{
    cout << "Translating '" << inputFile << "' from '" << from << "' with accuracy " << accuracy << "\n";
    // Translation logic goes here
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        PrintErrorMessage();
        return 1;
    }

    string inputFile, from;
    float accuracy;

    try
    {
        std::regex pattern("--(.*)=(.*)");
        smatch match;

        for (int i = 1; i < argc; i++)
        {
            string arg = argv[i];
            if (regex_match(arg, match, pattern))
            {
                string key = match[1];
                string value = match[2];

                if (key == "input")
                    inputFile = value;
                else if (key == "from")
                    from = value;
                else if (key == "accuracy")
                    accuracy = std::stof(value);
            }
        }

        if (inputFile.empty() || from.empty() || accuracy < 0.0f)
        {
            PrintErrorMessage();
            return 1;
        }

        Translate(inputFile, from, accuracy);
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
