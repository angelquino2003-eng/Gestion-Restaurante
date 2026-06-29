#pragma once

#include <msclr/marshal_cppstd.h>
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
	/// Summary for PanelOperaciones
	/// </summary>
	public ref class PanelOperaciones : public System::Windows::Forms::Form
	{
	private:
		TpUsuario usrActual;
		TpUsuario lstUsr;
		TpProducto lstProd;
		TpMesa lstMesas;
		TpPedido frenteCocina;
		TpPedido finalCocina;
		TpHistorial pilaHist;
		TpReserva lstRes;

		// Contadores globales
		int idPedGlobal = 1;
		int idAccGlobal = 1;

	private: System::Windows::Forms::DataGridView^ dgvMenu;
	private: System::Windows::Forms::TextBox^ txtCantProd;

	private: System::Windows::Forms::TextBox^ txtIdProd;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DataGridView^ dgvInventario;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ cmbAccionInv;
	private: System::Windows::Forms::Button^ btnProcesarInv;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::DataGridView^ dgvMesas;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::DataGridView^ dgvReservas;

	private: System::Windows::Forms::DateTimePicker^ dtpFecha;
	private: System::Windows::Forms::DateTimePicker^ dtpHora;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ txtIdMesa;
	private: System::Windows::Forms::TextBox^ txtNumPersonas;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Button^ btnDeshacer;
	private: System::Windows::Forms::DataGridView^ dgvHistorial;
	private: System::Windows::Forms::DataGridView^ dgvCocina;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Button^ btnDespachar;

	private: System::Windows::Forms::Button^ btnAtender;
	private: System::Windows::Forms::Button^ btnEncolar;
	private: System::Windows::Forms::TextBox^ txtDistancia;
	private: System::Windows::Forms::TextBox^ txtSubtotal;
	private: System::Windows::Forms::ComboBox^ cmbTipoPedido;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ txtTelefono;
	private: System::Windows::Forms::TextBox^ txtDireccion;
	private: System::Windows::Forms::TextBox^ txtRepartidor;
	private: System::Windows::Forms::TextBox^ txtDeliveryId;
	private: System::Windows::Forms::TabPage^ tabPageUsuarios;
	private: System::Windows::Forms::DataGridView^ dgvUsuarios;







		   int idReservaActual = 1;

	public:
		PanelOperaciones(TpUsuario usuarioLogueado, TpUsuario usuarios, TpProducto productos, TpMesa mesas, TpPedido frenteC, TpPedido finalC, TpHistorial historial, TpReserva reservas)
		{
			InitializeComponent();

			// Guardamos los datos recibidos en las variables de la clase
			usrActual = usuarioLogueado;
			lstUsr = usuarios;
			lstProd = productos;
			lstMesas = mesas;
			frenteCocina = frenteC;
			finalCocina = finalC;
			pilaHist = historial;
			lstRes = reservas;

			if (usrActual->rol != "Administrador") {
				tabControl1->TabPages->Remove(tabPageUsuarios);
			}
			// Lógica de roles: Ocultar pestañas si el usuario es "Cliente"
			if (usrActual->rol == "Cliente") {
				// Ocultamos todo menos "Menú Digital" y "Reservas"
				tabControl1->TabPages->Remove(tabPage2);
				tabControl1->TabPages->Remove(tabPage3);
				tabControl1->TabPages->Remove(tabPage5);
				tabControl1->TabPages->Remove(tabPage6);
			}
		}
	private:
		void cargarMenuDigital() {
			dgvMenu->Rows->Clear();
			dgvMenu->Columns->Clear();

			dgvMenu->Columns->Add("ColID", "ID");
			dgvMenu->Columns->Add("ColNombre", "Plato / Combo");
			dgvMenu->Columns->Add("ColPrecio", "Precio (S/.)");
			dgvMenu->Columns->Add("ColStock", "Disponibilidad");

			dgvMenu->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenu->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenu->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMenu->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			TpProducto p = lstProd;
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

				dgvMenu->Rows->Add(idStr, nomStr, precioStr, estadoStock);
				p = p->sig;
			}
		}
	private:
		void cargarInventario() {
			dgvInventario->Rows->Clear();
			dgvInventario->Columns->Clear();

			dgvInventario->Columns->Add("ColID", "ID");
			dgvInventario->Columns->Add("ColNombre", "Producto");
			dgvInventario->Columns->Add("ColStock", "Stock Actual");

			dgvInventario->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvInventario->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvInventario->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			TpProducto p = lstProd;
			while (p != NULL) {
				String^ idStr = p->id.ToString();
				String^ nomStr = msclr::interop::marshal_as<String^>(p->nombre);
				String^ stockStr = p->stock.ToString();

				dgvInventario->Rows->Add(idStr, nomStr, stockStr);
				p = p->sig;
			}
		}
	private:
		void cargarMesas() {
			//Limpiamos la tabla
			dgvMesas->Rows->Clear();
			dgvMesas->Columns->Clear();

			//Definimos las columnas
			dgvMesas->Columns->Add("ColIDMesa", "Mesa #");
			dgvMesas->Columns->Add("ColCapacidad", "Capacidad (Personas)");
			dgvMesas->Columns->Add("ColEstado", "Estado Actual");

			//Ajustamos el tamaño de las columnas
			dgvMesas->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMesas->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvMesas->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			//Recorremos la lista enlazada de mesas
			TpMesa m = lstMesas;
			while (m != NULL) {
				// Convertimos a String^ para Windows Forms
				String^ idStr = m->id.ToString();
				String^ capStr = m->capacidad.ToString();
				String^ estStr = msclr::interop::marshal_as<String^>(m->estado);

				//Agregamos la fila
				dgvMesas->Rows->Add(idStr, capStr, estStr);
				m = m->sig;
			}
		}
	private:
		void cargarReservas() {
			//Limpiamos la tabla
			dgvReservas->Rows->Clear();
			dgvReservas->Columns->Clear();

			//Definimos las columnas
			dgvReservas->Columns->Add("ColID", "ID");
			dgvReservas->Columns->Add("ColFecha", "Fecha");
			dgvReservas->Columns->Add("ColHora", "Hora");
			dgvReservas->Columns->Add("ColNumP", "Personas");
			dgvReservas->Columns->Add("ColMesa", "Mesa #");

			//Ajustamos el tamaño de las columnas
			dgvReservas->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvReservas->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvReservas->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvReservas->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvReservas->Columns[4]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			//Recorremos la lista enlazada
			TpReserva r = lstRes;
			while (r != NULL) {
				String^ idStr = r->id.ToString();
				String^ fStr = msclr::interop::marshal_as<String^>(r->fecha);
				String^ hStr = msclr::interop::marshal_as<String^>(r->hora);
				String^ npStr = r->numPersonas.ToString();
				String^ mStr = r->idMesa.ToString();

				dgvReservas->Rows->Add(idStr, fStr, hStr, npStr, mStr);

				r = r->sig;
			}
		}
	private:
		void cargarHistorial() {
			//Limpiamos la tabla
			dgvHistorial->Rows->Clear();
			dgvHistorial->Columns->Clear();

			//Definimos las columnas
			dgvHistorial->Columns->Add("ColID", "ID Acción");
			dgvHistorial->Columns->Add("ColDesc", "Descripción del Evento");

			//Ajustamos el tamaño de las columnas
			dgvHistorial->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvHistorial->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			//Recorremos la pila
			TpHistorial h = pilaHist;
			while (h != NULL) {
				String^ idStr = h->idAccion.ToString();
				String^ descStr = msclr::interop::marshal_as<String^>(h->descripcion);

				dgvHistorial->Rows->Add(idStr, descStr);

				h = h->sig;
			}
		}
	private:
		void cargarCocina() {
			dgvCocina->Rows->Clear();
			dgvCocina->Columns->Clear();

			dgvCocina->Columns->Add("ColID", "ID");
			dgvCocina->Columns->Add("ColTipo", "Tipo");
			dgvCocina->Columns->Add("ColEst", "Estado");
			dgvCocina->Columns->Add("ColTotal", "Total (S/.)");

			dgvCocina->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvCocina->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvCocina->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvCocina->Columns[3]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			// Recorremos la cola desde el frente
			TpPedido p = frenteCocina;
			while (p != NULL) {
				String^ idStr = p->id.ToString();
				String^ tipoStr = msclr::interop::marshal_as<String^>(p->tipo);
				String^ estStr = msclr::interop::marshal_as<String^>(p->estado);
				String^ totStr = p->total.ToString("F2"); // Muestra el total ya calculado con IGV y Envio

				dgvCocina->Rows->Add(idStr, tipoStr, estStr, totStr);
				p = p->sig;
			}
		}
	private:
		void cargarUsuarios() {
			dgvUsuarios->Rows->Clear();
			dgvUsuarios->Columns->Clear();

			dgvUsuarios->Columns->Add("ColID", "ID");
			dgvUsuarios->Columns->Add("ColUser", "Nombre de Usuario");
			dgvUsuarios->Columns->Add("ColRol", "Rol en el Sistema");

			dgvUsuarios->Columns[0]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvUsuarios->Columns[1]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;
			dgvUsuarios->Columns[2]->AutoSizeMode = DataGridViewAutoSizeColumnMode::AllCells;

			// Recorremos la lista de usuarios
			TpUsuario u = lstUsr;
			while (u != NULL) {
				String^ idStr = u->id.ToString();
				String^ nomStr = msclr::interop::marshal_as<String^>(u->nombre);
				String^ rolStr = msclr::interop::marshal_as<String^>(u->rol);

				dgvUsuarios->Rows->Add(idStr, nomStr, rolStr);
				u = u->sig;
			}
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PanelOperaciones()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^ tabControl1;
	protected:

	protected:

	protected:

	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::TabPage^ tabPage5;
	private: System::Windows::Forms::TabPage^ tabPage6;
	private: System::Windows::Forms::TabPage^ tabPage1;

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
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->dgvMenu = (gcnew System::Windows::Forms::DataGridView());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->dgvInventario = (gcnew System::Windows::Forms::DataGridView());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btnProcesarInv = (gcnew System::Windows::Forms::Button());
			this->txtCantProd = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtIdProd = (gcnew System::Windows::Forms::TextBox());
			this->cmbAccionInv = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->dgvMesas = (gcnew System::Windows::Forms::DataGridView());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->dgvReservas = (gcnew System::Windows::Forms::DataGridView());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->txtIdMesa = (gcnew System::Windows::Forms::TextBox());
			this->txtNumPersonas = (gcnew System::Windows::Forms::TextBox());
			this->dtpHora = (gcnew System::Windows::Forms::DateTimePicker());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->dtpFecha = (gcnew System::Windows::Forms::DateTimePicker());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->dgvCocina = (gcnew System::Windows::Forms::DataGridView());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->txtTelefono = (gcnew System::Windows::Forms::TextBox());
			this->txtDireccion = (gcnew System::Windows::Forms::TextBox());
			this->txtRepartidor = (gcnew System::Windows::Forms::TextBox());
			this->txtDeliveryId = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->btnDespachar = (gcnew System::Windows::Forms::Button());
			this->btnAtender = (gcnew System::Windows::Forms::Button());
			this->btnEncolar = (gcnew System::Windows::Forms::Button());
			this->txtDistancia = (gcnew System::Windows::Forms::TextBox());
			this->txtSubtotal = (gcnew System::Windows::Forms::TextBox());
			this->cmbTipoPedido = (gcnew System::Windows::Forms::ComboBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			this->dgvHistorial = (gcnew System::Windows::Forms::DataGridView());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->btnDeshacer = (gcnew System::Windows::Forms::Button());
			this->tabPageUsuarios = (gcnew System::Windows::Forms::TabPage());
			this->dgvUsuarios = (gcnew System::Windows::Forms::DataGridView());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMenu))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvInventario))->BeginInit();
			this->panel1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMesas))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvReservas))->BeginInit();
			this->panel2->SuspendLayout();
			this->tabPage5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvCocina))->BeginInit();
			this->panel4->SuspendLayout();
			this->tabPage6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvHistorial))->BeginInit();
			this->panel3->SuspendLayout();
			this->tabPageUsuarios->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUsuarios))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage6);
			this->tabControl1->Controls->Add(this->tabPageUsuarios);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(590, 533);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->dgvMenu);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(582, 507);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Menú Digital";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// dgvMenu
			// 
			this->dgvMenu->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvMenu->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvMenu->Location = System::Drawing::Point(3, 3);
			this->dgvMenu->Name = L"dgvMenu";
			this->dgvMenu->Size = System::Drawing::Size(576, 501);
			this->dgvMenu->TabIndex = 0;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->dgvInventario);
			this->tabPage2->Controls->Add(this->panel1);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(582, 507);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Inventario";
			this->tabPage2->UseVisualStyleBackColor = true;
			this->tabPage2->Click += gcnew System::EventHandler(this, &PanelOperaciones::tabPage2_Click);
			// 
			// dgvInventario
			// 
			this->dgvInventario->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvInventario->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvInventario->Location = System::Drawing::Point(3, 3);
			this->dgvInventario->Name = L"dgvInventario";
			this->dgvInventario->Size = System::Drawing::Size(345, 501);
			this->dgvInventario->TabIndex = 4;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->btnProcesarInv);
			this->panel1->Controls->Add(this->txtCantProd);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->txtIdProd);
			this->panel1->Controls->Add(this->cmbAccionInv);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel1->Location = System::Drawing::Point(348, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(231, 501);
			this->panel1->TabIndex = 8;
			// 
			// btnProcesarInv
			// 
			this->btnProcesarInv->Location = System::Drawing::Point(122, 126);
			this->btnProcesarInv->Name = L"btnProcesarInv";
			this->btnProcesarInv->Size = System::Drawing::Size(75, 23);
			this->btnProcesarInv->TabIndex = 7;
			this->btnProcesarInv->Text = L"Procesar";
			this->btnProcesarInv->UseVisualStyleBackColor = true;
			this->btnProcesarInv->Click += gcnew System::EventHandler(this, &PanelOperaciones::button2_Click);
			// 
			// txtCantProd
			// 
			this->txtCantProd->Location = System::Drawing::Point(122, 48);
			this->txtCantProd->Name = L"txtCantProd";
			this->txtCantProd->Size = System::Drawing::Size(100, 20);
			this->txtCantProd->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(75, 88);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Acción:";
			// 
			// txtIdProd
			// 
			this->txtIdProd->Location = System::Drawing::Point(122, 12);
			this->txtIdProd->Name = L"txtIdProd";
			this->txtIdProd->Size = System::Drawing::Size(100, 20);
			this->txtIdProd->TabIndex = 0;
			// 
			// cmbAccionInv
			// 
			this->cmbAccionInv->FormattingEnabled = true;
			this->cmbAccionInv->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Descontar por Venta", L"Reabastecer" });
			this->cmbAccionInv->Location = System::Drawing::Point(122, 85);
			this->cmbAccionInv->Name = L"cmbAccionInv";
			this->cmbAccionInv->Size = System::Drawing::Size(100, 21);
			this->cmbAccionInv->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(49, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"ID Producto:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(5, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(113, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Cantidad de unidades:";
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->dgvMesas);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(582, 507);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Salón (Mesas)";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// dgvMesas
			// 
			this->dgvMesas->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvMesas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvMesas->Location = System::Drawing::Point(3, 3);
			this->dgvMesas->Name = L"dgvMesas";
			this->dgvMesas->Size = System::Drawing::Size(576, 501);
			this->dgvMesas->TabIndex = 0;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->dgvReservas);
			this->tabPage4->Controls->Add(this->panel2);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(582, 507);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Reservas";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// dgvReservas
			// 
			this->dgvReservas->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvReservas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvReservas->Location = System::Drawing::Point(3, 3);
			this->dgvReservas->Name = L"dgvReservas";
			this->dgvReservas->Size = System::Drawing::Size(303, 501);
			this->dgvReservas->TabIndex = 0;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->txtIdMesa);
			this->panel2->Controls->Add(this->txtNumPersonas);
			this->panel2->Controls->Add(this->dtpHora);
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->dtpFecha);
			this->panel2->Controls->Add(this->label7);
			this->panel2->Controls->Add(this->label6);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel2->Location = System::Drawing::Point(306, 3);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(273, 501);
			this->panel2->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(68, 150);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(113, 41);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Registrar Reserva";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &PanelOperaciones::button2_Click_1);
			// 
			// txtIdMesa
			// 
			this->txtIdMesa->Location = System::Drawing::Point(131, 109);
			this->txtIdMesa->Name = L"txtIdMesa";
			this->txtIdMesa->Size = System::Drawing::Size(100, 20);
			this->txtIdMesa->TabIndex = 8;
			// 
			// txtNumPersonas
			// 
			this->txtNumPersonas->Location = System::Drawing::Point(131, 79);
			this->txtNumPersonas->Name = L"txtNumPersonas";
			this->txtNumPersonas->Size = System::Drawing::Size(100, 20);
			this->txtNumPersonas->TabIndex = 7;
			// 
			// dtpHora
			// 
			this->dtpHora->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dtpHora->Location = System::Drawing::Point(68, 46);
			this->dtpHora->Name = L"dtpHora";
			this->dtpHora->ShowUpDown = true;
			this->dtpHora->Size = System::Drawing::Size(93, 20);
			this->dtpHora->TabIndex = 6;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(19, 53);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(33, 13);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Hora:";
			// 
			// dtpFecha
			// 
			this->dtpFecha->Location = System::Drawing::Point(68, 13);
			this->dtpFecha->Name = L"dtpFecha";
			this->dtpFecha->Size = System::Drawing::Size(200, 20);
			this->dtpFecha->TabIndex = 4;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(19, 116);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(56, 13);
			this->label7->TabIndex = 3;
			this->label7->Text = L"Mesa (ID):";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(19, 86);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(84, 13);
			this->label6->TabIndex = 2;
			this->label6->Text = L"N° de Personas:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(19, 19);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(40, 13);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Fecha:";
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->dgvCocina);
			this->tabPage5->Controls->Add(this->panel4);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(582, 507);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Pedidos y Cocina";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// dgvCocina
			// 
			this->dgvCocina->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvCocina->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvCocina->Location = System::Drawing::Point(3, 3);
			this->dgvCocina->Name = L"dgvCocina";
			this->dgvCocina->Size = System::Drawing::Size(317, 501);
			this->dgvCocina->TabIndex = 0;
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->txtTelefono);
			this->panel4->Controls->Add(this->txtDireccion);
			this->panel4->Controls->Add(this->txtRepartidor);
			this->panel4->Controls->Add(this->txtDeliveryId);
			this->panel4->Controls->Add(this->label17);
			this->panel4->Controls->Add(this->label16);
			this->panel4->Controls->Add(this->label15);
			this->panel4->Controls->Add(this->btnDespachar);
			this->panel4->Controls->Add(this->btnAtender);
			this->panel4->Controls->Add(this->btnEncolar);
			this->panel4->Controls->Add(this->txtDistancia);
			this->panel4->Controls->Add(this->txtSubtotal);
			this->panel4->Controls->Add(this->cmbTipoPedido);
			this->panel4->Controls->Add(this->label14);
			this->panel4->Controls->Add(this->label13);
			this->panel4->Controls->Add(this->label12);
			this->panel4->Controls->Add(this->label11);
			this->panel4->Controls->Add(this->label10);
			this->panel4->Controls->Add(this->label9);
			this->panel4->Controls->Add(this->label8);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel4->Location = System::Drawing::Point(320, 3);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(259, 501);
			this->panel4->TabIndex = 1;
			// 
			// txtTelefono
			// 
			this->txtTelefono->Location = System::Drawing::Point(136, 355);
			this->txtTelefono->Name = L"txtTelefono";
			this->txtTelefono->Size = System::Drawing::Size(100, 20);
			this->txtTelefono->TabIndex = 18;
			// 
			// txtDireccion
			// 
			this->txtDireccion->Location = System::Drawing::Point(136, 322);
			this->txtDireccion->Name = L"txtDireccion";
			this->txtDireccion->Size = System::Drawing::Size(100, 20);
			this->txtDireccion->TabIndex = 17;
			// 
			// txtRepartidor
			// 
			this->txtRepartidor->Location = System::Drawing::Point(136, 295);
			this->txtRepartidor->Name = L"txtRepartidor";
			this->txtRepartidor->Size = System::Drawing::Size(100, 20);
			this->txtRepartidor->TabIndex = 16;
			// 
			// txtDeliveryId
			// 
			this->txtDeliveryId->Location = System::Drawing::Point(136, 265);
			this->txtDeliveryId->Name = L"txtDeliveryId";
			this->txtDeliveryId->Size = System::Drawing::Size(100, 20);
			this->txtDeliveryId->TabIndex = 15;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(6, 359);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(64, 16);
			this->label17->TabIndex = 14;
			this->label17->Text = L"Teléfono:";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(6, 326);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(67, 16);
			this->label16->TabIndex = 13;
			this->label16->Text = L"Dirección:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(6, 299);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(112, 16);
			this->label15->TabIndex = 12;
			this->label15->Text = L"ID del Repartidor:";
			// 
			// btnDespachar
			// 
			this->btnDespachar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDespachar->Location = System::Drawing::Point(36, 398);
			this->btnDespachar->Name = L"btnDespachar";
			this->btnDespachar->Size = System::Drawing::Size(129, 23);
			this->btnDespachar->TabIndex = 11;
			this->btnDespachar->Text = L"Despachar";
			this->btnDespachar->UseVisualStyleBackColor = true;
			this->btnDespachar->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnDespachar_Click);
			// 
			// btnAtender
			// 
			this->btnAtender->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAtender->Location = System::Drawing::Point(9, 204);
			this->btnAtender->Name = L"btnAtender";
			this->btnAtender->Size = System::Drawing::Size(129, 23);
			this->btnAtender->TabIndex = 10;
			this->btnAtender->Text = L"Atender Siguiente";
			this->btnAtender->UseVisualStyleBackColor = true;
			this->btnAtender->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnAtender_Click);
			// 
			// btnEncolar
			// 
			this->btnEncolar->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnEncolar->Location = System::Drawing::Point(36, 157);
			this->btnEncolar->Name = L"btnEncolar";
			this->btnEncolar->Size = System::Drawing::Size(129, 23);
			this->btnEncolar->TabIndex = 10;
			this->btnEncolar->Text = L"Encolar Pedido";
			this->btnEncolar->UseVisualStyleBackColor = true;
			this->btnEncolar->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnEncolar_Click);
			// 
			// txtDistancia
			// 
			this->txtDistancia->Location = System::Drawing::Point(115, 121);
			this->txtDistancia->Name = L"txtDistancia";
			this->txtDistancia->Size = System::Drawing::Size(100, 20);
			this->txtDistancia->TabIndex = 9;
			// 
			// txtSubtotal
			// 
			this->txtSubtotal->Location = System::Drawing::Point(115, 79);
			this->txtSubtotal->Name = L"txtSubtotal";
			this->txtSubtotal->Size = System::Drawing::Size(100, 20);
			this->txtSubtotal->TabIndex = 8;
			// 
			// cmbTipoPedido
			// 
			this->cmbTipoPedido->FormattingEnabled = true;
			this->cmbTipoPedido->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Salon", L"Delivery" });
			this->cmbTipoPedido->Location = System::Drawing::Point(115, 43);
			this->cmbTipoPedido->Name = L"cmbTipoPedido";
			this->cmbTipoPedido->Size = System::Drawing::Size(121, 21);
			this->cmbTipoPedido->TabIndex = 7;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(6, 269);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(92, 16);
			this->label14->TabIndex = 6;
			this->label14->Text = L"ID del Pedido:";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(6, 121);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(96, 16);
			this->label13->TabIndex = 5;
			this->label13->Text = L"Distancia (Km):";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(6, 83);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(59, 16);
			this->label12->TabIndex = 4;
			this->label12->Text = L"Subtotal:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(6, 44);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(103, 16);
			this->label11->TabIndex = 3;
			this->label11->Text = L"Tipo de pedido:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(6, 240);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(73, 18);
			this->label10->TabIndex = 2;
			this->label10->Text = L"Delivery:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(6, 183);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(159, 18);
			this->label9->TabIndex = 1;
			this->label9->Text = L"Atención en Cocina:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(6, 12);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(118, 18);
			this->label8->TabIndex = 0;
			this->label8->Text = L"Nuevo Pedido:";
			// 
			// tabPage6
			// 
			this->tabPage6->Controls->Add(this->dgvHistorial);
			this->tabPage6->Controls->Add(this->panel3);
			this->tabPage6->Location = System::Drawing::Point(4, 22);
			this->tabPage6->Name = L"tabPage6";
			this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			this->tabPage6->Size = System::Drawing::Size(582, 507);
			this->tabPage6->TabIndex = 5;
			this->tabPage6->Text = L"Historial";
			this->tabPage6->UseVisualStyleBackColor = true;
			// 
			// dgvHistorial
			// 
			this->dgvHistorial->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvHistorial->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvHistorial->Location = System::Drawing::Point(3, 3);
			this->dgvHistorial->Name = L"dgvHistorial";
			this->dgvHistorial->Size = System::Drawing::Size(413, 501);
			this->dgvHistorial->TabIndex = 0;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->btnDeshacer);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel3->Location = System::Drawing::Point(416, 3);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(163, 501);
			this->panel3->TabIndex = 1;
			// 
			// btnDeshacer
			// 
			this->btnDeshacer->Location = System::Drawing::Point(12, 14);
			this->btnDeshacer->Name = L"btnDeshacer";
			this->btnDeshacer->Size = System::Drawing::Size(144, 32);
			this->btnDeshacer->TabIndex = 0;
			this->btnDeshacer->Text = L"Deshacer Última Acción";
			this->btnDeshacer->UseVisualStyleBackColor = true;
			this->btnDeshacer->Click += gcnew System::EventHandler(this, &PanelOperaciones::btnDeshacer_Click);
			// 
			// tabPageUsuarios
			// 
			this->tabPageUsuarios->Controls->Add(this->dgvUsuarios);
			this->tabPageUsuarios->Location = System::Drawing::Point(4, 22);
			this->tabPageUsuarios->Name = L"tabPageUsuarios";
			this->tabPageUsuarios->Padding = System::Windows::Forms::Padding(3);
			this->tabPageUsuarios->Size = System::Drawing::Size(582, 507);
			this->tabPageUsuarios->TabIndex = 6;
			this->tabPageUsuarios->Text = L"Usuarios";
			this->tabPageUsuarios->UseVisualStyleBackColor = true;
			// 
			// dgvUsuarios
			// 
			this->dgvUsuarios->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvUsuarios->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgvUsuarios->Location = System::Drawing::Point(3, 3);
			this->dgvUsuarios->Name = L"dgvUsuarios";
			this->dgvUsuarios->Size = System::Drawing::Size(576, 501);
			this->dgvUsuarios->TabIndex = 0;
			// 
			// PanelOperaciones
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(590, 533);
			this->Controls->Add(this->tabControl1);
			this->Name = L"PanelOperaciones";
			this->Text = L"Sistema de Gestión de Restaurante";
			this->Load += gcnew System::EventHandler(this, &PanelOperaciones::PanelOperaciones_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMenu))->EndInit();
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvInventario))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMesas))->EndInit();
			this->tabPage4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvReservas))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->tabPage5->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvCocina))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->tabPage6->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvHistorial))->EndInit();
			this->panel3->ResumeLayout(false);
			this->tabPageUsuarios->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUsuarios))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void PanelOperaciones_Load(System::Object^ sender, System::EventArgs^ e) {
		cargarMenuDigital();
		cargarInventario();
		cargarMesas();
		cargarReservas();
		cargarHistorial();
		cargarCocina();
		cargarUsuarios();
	}
	private: System::Void tabPage2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	cargarMenuDigital();
	
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	// Asegurarnos de que el usuario llenó las cajas
	if (txtIdProd->Text == "" || txtCantProd->Text == "" || cmbAccionInv->SelectedIndex == -1) {
		MessageBox::Show("Por favor complete todos los campos.", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		// Convertir el texto de Windows Forms a números de C++
		int idProd = System::Convert::ToInt32(txtIdProd->Text);
		int cant = System::Convert::ToInt32(txtCantProd->Text);
		String^ accionSeleccionada = cmbAccionInv->SelectedItem->ToString();

		// LOGICA DE NEGOCIO
		if (accionSeleccionada == "Descontar por Venta") {
			if (verificarStock(lstProd, idProd, cant) == true) {
				actualizarStock(lstProd, idProd, cant);

				std::string desc = "Venta/Descuento de producto ID " + std::to_string(idProd);
				TpHistorial tempHist = pilaHist;
				registrarAccion(tempHist, idAccGlobal, desc);
				pilaHist = tempHist;
				idAccGlobal++;

				MessageBox::Show("Stock descontado correctamente.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Stock insuficiente o producto no encontrado.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		else if (accionSeleccionada == "Reabastecer") {
			// Pasamos la cantidad en negativo para que sume
			actualizarStock(lstProd, idProd, -cant);

			std::string desc = "Reabastecimiento de producto ID " + std::to_string(idProd);
			TpHistorial tempHist = pilaHist;
			registrarAccion(tempHist, idAccGlobal, desc);
			pilaHist = tempHist;
			idAccGlobal++;

			MessageBox::Show("Almacén reabastecido correctamente.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		//ACTUALIZAR LAS VISTAS
		cargarInventario();   // Refresca la tabla de inventario
		cargarMenuDigital();  // Refresca la tabla del menu publico
		cargarHistorial();

		//LIMPIAR EL FORMULARIO
		txtIdProd->Clear();
		txtCantProd->Clear();
		cmbAccionInv->SelectedIndex = -1;

	}
	catch (System::FormatException^) { // Atrapamos el error si el usuario escribe letras en vez de números
		MessageBox::Show("El ID y la Cantidad deben ser números enteros.", "Error de Formato", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {
	//Validamos que las cajas de texto restantes no estén vacías
	if (txtNumPersonas->Text == "" || txtIdMesa->Text == "") {
		MessageBox::Show("Por favor complete el número de personas y el ID de la mesa.", "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		//Extraemos los valores de los controles
		int numP = System::Convert::ToInt32(txtNumPersonas->Text);
		int idM = System::Convert::ToInt32(txtIdMesa->Text);
		// Extraemos la fecha con el formato deseado (DD/MM/AAAA)
		String^ fechaFormateada = dtpFecha->Value.ToString("dd/MM/yyyy");
		// Extraemos la hora con formato (HH:MM)
		String^ horaFormateada = dtpHora->Value.ToString("HH:mm");

		// Convertimos a std::string para pasarlo a tu backend
		std::string fechaCpp = msclr::interop::marshal_as<std::string>(fechaFormateada);
		std::string horaCpp = msclr::interop::marshal_as<std::string>(horaFormateada);
		// ------------------------------------

		//Validar disponibilidad de mesa
		if (verificarMesaLibre(lstMesas, idM, numP) == false) {
			MessageBox::Show("La mesa seleccionada no está libre o no tiene capacidad suficiente.", "Error de Reserva", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		//Crear la reserva
		lstRes = crearReserva(lstRes, lstMesas, idReservaActual, fechaCpp, horaCpp, numP, idM);

		//REGISTRAR EN EL HISTORIAL
		std::string desc = "Se registro la Reserva #" + std::to_string(idReservaActual);
		TpHistorial tempHist = pilaHist;
		registrarAccion(tempHist, idAccGlobal, desc); // Llama al backend C++
		pilaHist = tempHist;

		idReservaActual++;
		idAccGlobal++;

		//ACTUALIZACION
		MessageBox::Show("Reserva confirmada con éxito. Mesa " + idM + " bloqueada.", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);

		cargarReservas();
		cargarMesas();
		cargarHistorial();

		//LIMPIAR EL FORMULARIO
		txtNumPersonas->Clear();
		txtIdMesa->Clear();
		//Resetea los DateTimePickers a la fecha y hora actual
		//dtpFecha->Value = System::DateTime::Now;
		//dtpHora->Value = System::DateTime::Now;

	}
	catch (System::FormatException^) {
		MessageBox::Show("El número de personas y el ID de la mesa deben ser números.", "Error de Formato", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnDeshacer_Click(System::Object^ sender, System::EventArgs^ e) {
	//Valida que la pila no esté vacía
	if (pilaHist == NULL) {
		MessageBox::Show("No hay acciones en el registro para deshacer.", "Historial Vacío", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return;
	}

	//Extrae la descripción antes de eliminar el nodo para poder mostrarla en el mensaje
	String^ descDeshecha = msclr::interop::marshal_as<String^>(pilaHist->descripcion);

	//Pasa a una variable local, elimina el primer nodo (Pop), y regresa el resultado
	TpHistorial tempHist = pilaHist;
	deshacerAccion(tempHist); // Llama al backend C++
	pilaHist = tempHist;

	//Actualiza y avisa al usuario
	cargarHistorial();
	MessageBox::Show("Se eliminó del registro:\n" + descDeshecha, "Deshacer exitoso", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

private: System::Void btnEncolar_Click(System::Object^ sender, System::EventArgs^ e) {
	if (cmbTipoPedido->SelectedIndex == -1 || txtSubtotal->Text == "") return;

	try {
		String^ tipoWin = cmbTipoPedido->SelectedItem->ToString();
		std::string tipoCpp = msclr::interop::marshal_as<std::string>(tipoWin);

		float sub = (float)System::Convert::ToDouble(txtSubtotal->Text);
		float dist = 0;

		if (tipoWin == "Delivery") {
			if (txtDistancia->Text == "") {
				MessageBox::Show("Ingrese la distancia para el delivery.");
				return;
			}
			dist = (float)System::Convert::ToDouble(txtDistancia->Text);
		}

		TpPedido tempFrente = frenteCocina;
		TpPedido tempFinal = finalCocina;

		encolarPedido(tempFrente, tempFinal, idPedGlobal, tipoCpp, sub, dist);

		frenteCocina = tempFrente;
		finalCocina = tempFinal;

		// Historial
		std::string desc = "Se encolo el Pedido #" + std::to_string(idPedGlobal);
		TpHistorial tempHist = pilaHist;
		registrarAccion(tempHist, idAccGlobal, desc);
		pilaHist = tempHist;

		idPedGlobal++;
		idAccGlobal++;

		cargarCocina();
		cargarHistorial();
		txtSubtotal->Clear();
		txtDistancia->Clear();
	}
	catch (System::FormatException^) {
		MessageBox::Show("Ingrese montos numéricos válidos.");
	}
}
private: System::Void btnAtender_Click(System::Object^ sender, System::EventArgs^ e) {
	if (frenteCocina == NULL) {
		MessageBox::Show("La cola está vacía.");
		return;
	}

	TpPedido tempFrente = frenteCocina;
	atenderPedidoCocina(tempFrente);
	frenteCocina = tempFrente;

	// Si la cola se vació, actualizamos también el puntero final
	if (frenteCocina == NULL) finalCocina = NULL;

	// Historial
	TpHistorial tempHist = pilaHist;
	registrarAccion(tempHist, idAccGlobal, "Se despacho pedido de Cocina");
	pilaHist = tempHist;
	idAccGlobal++;

	cargarCocina();
	cargarHistorial();
}
private: System::Void btnDespachar_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtDeliveryId->Text == "" || txtRepartidor->Text == "" || txtDireccion->Text == "" || txtTelefono->Text == "") {
		MessageBox::Show("Llene todos los datos del delivery.");
		return;
	}

	try {
		int idPed = System::Convert::ToInt32(txtDeliveryId->Text);
		int idRep = System::Convert::ToInt32(txtRepartidor->Text);
		std::string dir = msclr::interop::marshal_as<std::string>(txtDireccion->Text);
		std::string tel = msclr::interop::marshal_as<std::string>(txtTelefono->Text);

		despacharDelivery(frenteCocina, idPed, idRep, dir, tel);

		// Historial
		std::string desc = "Despacho delivery de Pedido #" + std::to_string(idPed);
		TpHistorial tempHist = pilaHist;
		registrarAccion(tempHist, idAccGlobal, desc);
		pilaHist = tempHist;
		idAccGlobal++;

		cargarCocina();
		cargarHistorial();
		txtDeliveryId->Clear();
		txtRepartidor->Clear();
		txtDireccion->Clear();
		txtTelefono->Clear();
	}
	catch (System::FormatException^) {
		MessageBox::Show("Los IDs deben ser números enteros.");
	}
}
};
}
