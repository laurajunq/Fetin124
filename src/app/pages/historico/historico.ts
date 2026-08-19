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

    this.firebaseService.getLeituras()
      .subscribe((dados: any[]) => {

        if (!dados) {
          this.leituras = [];
          return;
        }

        this.leituras = dados.reverse();

      });

  }

}