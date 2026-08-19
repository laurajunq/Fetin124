import { Component } from '@angular/core';
import { Router, RouterLink } from '@angular/router';

@Component({
  selector: 'app-navbar',
  standalone: true,

  imports: [
    RouterLink
  ],

  templateUrl: './navbar.html',
  styleUrl: './navbar.css'
})
export class Navbar {

  constructor(
    private router: Router
  ) {}


  // =========================
  // VERIFICA LOGIN
  // =========================

  get estaLogado(): boolean {

    return sessionStorage.getItem(
      'handpulseLogado'
    ) === 'true';

  }


  // =========================
  // SAIR
  // =========================

  sair(): void {

    sessionStorage.removeItem(
      'handpulseLogado'
    );

    this.router.navigate(['/sobre']);

  }

}