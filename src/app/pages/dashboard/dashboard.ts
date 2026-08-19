import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';

import { FirebaseService } from '../../core/services/firebase.service';

@Component({
  selector: 'app-dashboard',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './dashboard.html',
  styleUrl: './dashboard.css'
})
export class Dashboard implements OnInit {

  // =========================
  // DADOS DA LUVA
  // =========================

  movimento: string = 'AGUARDANDO';

  intensidade: number = 0;

  vibracao: string = 'DESATIVADO';


  // =========================
  // DADOS DO SENSOR
  // =========================

  gx: number = 0;

  gy: number = 0;

  gz: number = 0;


  // =========================
  // LOGS
  // =========================

  logs: string[] = [
    'Sistema iniciado...',
    'Aguardando dados da luva...'
  ];


  // =========================
  // CONSTRUTOR
  // =========================

  constructor(
    private firebaseService: FirebaseService,
    private router: Router
  ) {}


  // =========================
  // INICIALIZAÇÃO
  // =========================

  ngOnInit(): void {

    this.firebaseService.getLuva()
      .subscribe((dados: any) => {

        if (!dados) {
          return;
        }


        // =========================
        // DADOS PRINCIPAIS
        // =========================

        this.movimento =
          dados.movimento ?? 'PARADO';

        this.intensidade =
          dados.intensidade ?? 0;

        this.vibracao =
          dados.vibracao ?? 'DESATIVADO';


        // =========================
        // DADOS DO SENSOR
        // =========================

        this.gx =
          dados.gx ?? 0;

        this.gy =
          dados.gy ?? 0;

        this.gz =
          dados.gz ?? 0;


        // =========================
        // NOVO LOG
        // =========================

        const novoLog =
          `${new Date().toLocaleTimeString()} - ${this.movimento} | Intensidade: ${this.intensidade}`;


        if (
          this.logs.length === 0 ||
          this.logs[0] !== novoLog
        ) {

          this.logs.unshift(novoLog);


          // Mantém no máximo 15 logs

          if (this.logs.length > 15) {
            this.logs.pop();
          }

        }

      });

  }


  // =========================
  // TESTE DE VIBRAÇÃO
  // =========================

  testeVibracao(): void {

    const novoLog =
      `${new Date().toLocaleTimeString()} - Teste manual de vibração`;


    this.logs.unshift(novoLog);


    // Mantém no máximo 15 logs

    if (this.logs.length > 15) {
      this.logs.pop();
    }


    alert('Teste de vibração executado!');

  }

}