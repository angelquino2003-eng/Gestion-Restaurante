#pragma once

#include <msclr/marshal_cppstd.h>
#include "PanelOperaciones.h"
#include "../Usuario.h"
#include "../Definiciones.h"
#include "../Historial.h"
#include "../Mesa.h"
#include "../Pedido.h"
#include "../Producto.h"
#include "../Reserva.h"

namespace SistemaRestauranteGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MenuPrincipal
	/// </summary>
	public ref class MenuPrincipal : public System::Windows::Forms::Form
	{
	private:
		TpUsuario listaUsuarios;
		TpUsuario logueado;
		TpProducto listaProductos;
		TpMesa listaMesas;
		TpPedido frenteCocina;
		TpPedido finalCocina;
		TpHistorial pilaAcciones;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::DataGridView^ dgvMenuPublico;
	private: System::Windows::Forms::Button^ btnSalir;


		   TpReserva listaReservas;
	public:
		MenuPrincipal(void)
		{
			InitializeComponent();
			
			listaUsuarios = NULL;
			logueado = NULL;
			listaProductos = NULL;
			listaMesas = NULL;
			frenteCocina = NULL;
			finalCocina = NULL;
			pilaAcciones = NULL;
			listaReservas = NULL;

			listaUsuarios = registrarUsuario(listaUsuarios, 1, "admin", "admin123", "Administrador");
			listaUsuarios = registrarUsuario(listaUsuarios, 2, "fernando", "1234", "Cliente");
			listaUsuarios = registrarUsuario(listaUsuarios, 3, "diego", "qwer", "Trabajador");

			listaProductos = agregarProducto(listaProductos, 101, "Combo Hamburguesa Big Boss", 20, 18.50f);
			listaProductos = agregarProducto(listaProductos, 102, "Pollo Frito Crujiente KFC", 15, 21.90f);
			listaProductos = agregarProducto(listaProductos, 103, "Mostrito con Pollo a la Brasa", 0, 19.00f);

			listaMesas = agregarMesa(listaMesas, 1, 2);
			listaMesas = agregarMesa(listaMesas, 2, 4);
			listaMesas = agregarMesa(listaMesas, 3, 6);
		}
	private:
		void cargarMenuPublico() {
			dgvMenuPublico->Rows->Clear();
			dgvMenuPublico->Columns->Clear();

			dgvMenuPublico->Columns->Add("ColID", "ID");
			dgvMenuPublico->Columns->Add("ColNombre", "Plato / Combo");
			dgvMenuPublico->Columns->Add("ColPrecio", "Precio (S/.)");
			dgvMenuPublico->Columns->Add("ColStock", "Disponibilidad");

			dgvMenuPublico->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenuPublico->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenuPublico->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenuPublico->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			// Recorremos la lista de productos
			TpProducto p = listaProductos;
			while (p != NULL) {
				String^ idStr = p->id.ToString();
				String^ nomStr = msclr::interop::marshal_as<String^>(p->nombre);
				String^ precioStr = p->precio.ToString("F2");

				String^ estadoStock = "";
				if (p->stock == 0) {
					estadoStock = "NO DISPONIBLE";
				}
				else {
					estadoStock = "Stock: " + p->stock.ToString();
				}

				dgvMenuPublico->Rows->Add(idStr, nomStr, precioStr, estadoStock);
				p = p->sig;
			}

			// Hacemos que la tabla sea de solo lectura para que los usuarios no puedan editarla
			dgvMenuPublico->ReadOnly = true;
			dgvMenuPublico->AllowUserToAddRows = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MenuPrincipal()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtUsuario;
	private: System::Windows::Forms::TextBox^ txtPass;


	private: System::Windows::Forms::Button^ button1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtUsuario = (gcnew System::Windows::Forms::TextBox());
			this->txtPass = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->dgvMenuPublico = (gcnew System::Windows::Forms::DataGridView());
			this->btnSalir = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMenuPublico))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Usuario:";
			this->label1->Click += gcnew System::EventHandler(this, &MenuPrincipal::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 62);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Contraseña:";
			this->label2->Click += gcnew System::EventHandler(this, &MenuPrincipal::label2_Click);
			// 
			// txtUsuario
			// 
			this->txtUsuario->Location = System::Drawing::Point(122, 16);
			this->txtUsuario->Name = L"txtUsuario";
			this->txtUsuario->Size = System::Drawing::Size(100, 20);
			this->txtUsuario->TabIndex = 2;
			this->txtUsuario->TextChanged += gcnew System::EventHandler(this, &MenuPrincipal::textBox1_TextChanged);
			// 
			// txtPass
			// 
			this->txtPass->Location = System::Drawing::Point(122, 59);
			this->txtPass->Name = L"txtPass";
			this->txtPass->PasswordChar = '*';
			this->txtPass->Size = System::Drawing::Size(100, 20);
			this->txtPass->TabIndex = 3;
			this->txtPass->TextChanged += gcnew System::EventHandler(this, &MenuPrincipal::txtPass_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(120, 106);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(102, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Iniciar Sesión";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MenuPrincipal::button1_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->btnSalir);
			this->panel1->Controls->Add(this->txtUsuario);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->txtPass);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel1->Location = System::Drawing::Point(272, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(233, 337);
			this->panel1->TabIndex = 5;
			// 
			// dgvMenuPublico
			// 
			this->dgvMenuPublico->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvMenuPublico->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvMenuPublico->Location = System::Drawing::Point(0, 0);
			this->dgvMenuPublico->Name = L"dgvMenuPublico";
			this->dgvMenuPublico->Size = System::Drawing::Size(272, 337);
			this->dgvMenuPublico->TabIndex = 6;
			// 
			// btnSalir
			// 
			this->btnSalir->Location = System::Drawing::Point(12, 106);
			this->btnSalir->Name = L"btnSalir";
			this->btnSalir->Size = System::Drawing::Size(102, 23);
			this->btnSalir->TabIndex = 5;
			this->btnSalir->Text = L"Salir";
			this->btnSalir->UseVisualStyleBackColor = true;
			this->btnSalir->Click += gcnew System::EventHandler(this, &MenuPrincipal::btnSalir_Click);
			// 
			// MenuPrincipal
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(505, 337);
			this->Controls->Add(this->dgvMenuPublico);
			this->Controls->Add(this->panel1);
			this->Name = L"MenuPrincipal";
			this->Text = L"Sistema de Gestión de Restaurante";
			this->Load += gcnew System::EventHandler(this, &MenuPrincipal::MenuPrincipal_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMenuPublico))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		
		std::string userCpp = msclr::interop::marshal_as<std::string>(txtUsuario->Text);
		std::string passCpp = msclr::interop::marshal_as<std::string>(txtPass->Text);

		logueado = login(listaUsuarios, userCpp, passCpp);

		if (logueado != NULL) {
			String^ nombreBienvenida = msclr::interop::marshal_as<String^>(logueado->nombre);
			MessageBox::Show("Bienvenido, " + nombreBienvenida, "Acceso Concedido");

			// Aquí ocultaríamos el login y abriríamos el panel de operaciones
			this->Hide(); 
			PanelOperaciones^ panel = gcnew PanelOperaciones(logueado, listaUsuarios, listaProductos, listaMesas, frenteCocina, finalCocina, pilaAcciones, listaReservas);
			panel->ShowDialog();
			this->Show();
			txtUsuario->Clear();
			txtPass->Clear();
		}
		else {
			MessageBox::Show("Credenciales inválidas", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

	}
private: System::Void txtPass_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void MenuPrincipal_Load(System::Object^ sender, System::EventArgs^ e) {
	cargarMenuPublico();
}
private: System::Void btnSalir_Click(System::Object^ sender, System::EventArgs^ e) {
	if (MessageBox::Show("¿Desea salir completamente del sistema?", "Salir", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
		Application::Exit(); // Esto mata el proceso completo del programa
	}
}
};
}
