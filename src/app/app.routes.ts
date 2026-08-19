import { Routes } from '@angular/router';

import { authGuard } from './pages/guards/auth-guard';

export const routes: Routes = [

  // =========================
  // PÁGINA INICIAL
  // =========================

  {
    path: '',
    redirectTo: 'sobre',
    pathMatch: 'full'
  },


  // =========================
  // LOGIN
  // =========================

  {
    path: 'login',
    loadComponent: () =>
      import('./pages/login/login')
        .then(m => m.Login)
  },


  // =========================
  // SOBRE
  // =========================

  {
    path: 'sobre',
    loadComponent: () =>
      import('./pages/sobre/sobre')
        .then(m => m.Sobre)
  },


  // =========================
  // DASHBOARD
  // =========================

  {
    path: 'dashboard',
    loadComponent: () =>
      import('./pages/dashboard/dashboard')
        .then(m => m.Dashboard),

    canActivate: [authGuard]
  },


  // =========================
  // HISTÓRICO
  // =========================

  {
    path: 'historico',
    loadComponent: () =>
      import('./pages/historico/historico')
        .then(m => m.Historico),

    canActivate: [authGuard]
  }

];