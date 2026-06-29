#include "MenuPrincipal.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(cli::array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Cambia "SistemaRestauranteGUI" por el nombre exacto de tu proyecto
    SistemaRestauranteGUI::MenuPrincipal form;
    Application::Run(% form);

    return 0;
}