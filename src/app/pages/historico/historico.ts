import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FirebaseService } from '../../core/services/firebase.service';

@Component({
  selector: 'app-historico',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './historico.html',
  styleUrl: './historico.css'
})
export class Historico implements OnInit {

  leituras: any[] = [];

  constructor(
    private firebaseService: FirebaseService
  ) {}

  ngOnInit(): void {

    this.firebaseService.getLuva()
      .subscribe((dados: any) => {

        if (!dados) return;

        const leitura = {
          horario: new Date().toLocaleTimeString(),
          movimento: dados.movimento ?? 'PARADO',
          intensidade: dados.intensidade ?? 0,
          vibracao: dados.vibracao ?? 'DESATIVADO',
          gx: dados.gx ?? 0,
          gy: dados.gy ?? 0,
          gz: dados.gz ?? 0
        };

        this.leituras.unshift(leitura);

        if (this.leituras.length > 50) {
          this.leituras.pop();
        }

      });

  }

}