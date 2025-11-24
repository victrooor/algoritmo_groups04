#pragma once
#include "mascota.h"

namespace TemaSprites {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public Form {
    public:
        MyForm(void) {
            InitializeComponent();
            this->DoubleBuffered = true;//activa el doble bufer y evita parpadeos(flickering)
            this->Load += gcnew EventHandler(this, &MyForm::MyForm_Load);//significa:Cuando el formulario termine de cargarse, ejecuta el metodo MyForm_Load
        }

    protected:
        ~MyForm() {
            if (components) delete components;
        }

    private:
        Graphics^ gr;
        BufferedGraphics^ buffer;
        mascota* objMascota;
        Direccion teclapulsada = Derecha;
        Timer^ timer1;
        IContainer^ components;

        void InitializeComponent(void) {
            components = gcnew System::ComponentModel::Container();
            timer1 = gcnew System::Windows::Forms::Timer(components);
            this->SuspendLayout();
            // 
            // timer1
            // 
            timer1->Interval = 16;  // ~60 FPS
            timer1->Enabled = true;
            timer1->Tick += gcnew EventHandler(this, &MyForm::timer1_Tick);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = Drawing::SizeF(8, 16);
            this->AutoScaleMode = Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = Drawing::Size(568, 591);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->KeyDown += gcnew KeyEventHandler(this, &MyForm::MyForm_KeyDown);
            this->ResumeLayout(false);
        }

        // Load event: inicializar gráficos y buffer
        void MyForm_Load(Object^ sender, EventArgs^ e) {
            gr = this->CreateGraphics();
            buffer = BufferedGraphicsManager::Current->Allocate(gr, this->ClientRectangle);
            objMascota = new mascota();
            objMascota->setX(100);
            objMascota->setY(100);
            objMascota->setImagen("sprites\\pikachu.png");
        }

        // Timer tick: actualizar y renderizar
        void timer1_Tick(Object^ sender, EventArgs^ e) {
            // Rebotar en bordes X
            if (objMascota->getx() + objMascota->getDx() < 0) teclapulsada = Derecha;
            else if (objMascota->getx() + objMascota->getDx() + objMascota->getW() > this->ClientSize.Width) teclapulsada = Izquierda;
            // Rebotar en bordes Y
            if (objMascota->gety() + objMascota->getDy() < 0) teclapulsada = Abajo;
            else if (objMascota->gety() + objMascota->getDy() + objMascota->getH() > this->ClientSize.Height) teclapulsada = Arriba;

            objMascota->cambia_dx_dy(teclapulsada);

            // Dibujar
            buffer->Graphics->Clear(this->BackColor);
            objMascota->mover(buffer->Graphics, teclapulsada);
            buffer->Render(gr);
        }

        // KeyDown: cambiar dirección con tecla
        void MyForm_KeyDown(Object^ sender, KeyEventArgs^ e) {
            switch (e->KeyCode) {
            case Keys::Up:    teclapulsada = Arriba;    break;
            case Keys::Down:  teclapulsada = Abajo;     break;
            case Keys::Left:  teclapulsada = Izquierda; break;
            case Keys::Right: teclapulsada = Derecha;   break;
            }
        }
    };

} // namespace TemaSprites
