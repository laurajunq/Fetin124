import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FirebaseService } from '../../core/services/firebase.service';

@Component({
  selector: 'app-dashboard',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './dashboard.html',
  styleUrl: './dashboard.css'
})
export class Dashboard implements OnInit {

  movimento: string = 'AGUARDANDO';
  intensidade: number = 0;
  vibracao: string = 'DESATIVADO';

  gx: number = 0;
  gy: number = 0;
  gz: number = 0;

  logs: string[] = [
    'Sistema iniciado...',
    'Aguardando dados da luva...'
  ];

  constructor(
    private firebaseService: FirebaseService
  ) {}

  ngOnInit(): void {

    this.firebaseService.getLuva()
      .subscribe((dados: any) => {

        if (!dados) {
          return;
        }

        this.movimento = dados.movimento ?? 'PARADO';
        this.intensidade = dados.intensidade ?? 0;
        this.vibracao = dados.vibracao ?? 'DESATIVADO';

        this.gx = dados.gx ?? 0;
        this.gy = dados.gy ?? 0;
        this.gz = dados.gz ?? 0;

        const novoLog =
          `${new Date().toLocaleTimeString()} - ${this.movimento} | Intensidade: ${this.intensidade}`;

        if (this.logs.length === 0 || this.logs[0] !== novoLog) {

          this.logs.unshift(novoLog);

          if (this.logs.length > 15) {
            this.logs.pop();
          }

        }

      });

  }

  testeVibracao(): void {

    const novoLog =
      `${new Date().toLocaleTimeString()} - Teste manual de vibração`;

    this.logs.unshift(novoLog);

    if (this.logs.length > 15) {
      this.logs.pop();
    }

    alert('Teste de vibração executado!');

  }

}