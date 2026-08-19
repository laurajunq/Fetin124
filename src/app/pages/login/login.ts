import { Component } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router, RouterLink } from '@angular/router';

@Component({
  selector: 'app-login',
  standalone: true,

  imports: [
    FormsModule,
    RouterLink
  ],

  templateUrl: './login.html',
  styleUrl: './login.css'
})
export class Login {

  usuario = '';

  senha = '';

  erro = false;


  constructor(
    private router: Router
  ) {}


  // =========================
  // LOGIN
  // =========================

  entrar(): void {

    const usuarioValido = 'usuario@teste.com';

    const senhaValida = '1234';


    if (
      this.usuario === usuarioValido &&
      this.senha === senhaValida
    ) {

      this.erro = false;


      // Salva o estado de login

      sessionStorage.setItem(
        'handpulseLogado',
        'true'
      );


      // Vai para o Dashboard

      this.router.navigate([
        '/dashboard'
      ]);

    } else {

      this.erro = true;

    }

  }

}