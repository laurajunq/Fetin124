import { Routes } from '@angular/router';

export const routes: Routes = [

  {
    path: '',
    redirectTo: 'dashboard',
    pathMatch: 'full'
  },

  {
    path: 'dashboard',
    loadComponent: () =>
      import('./pages/dashboard/dashboard')
      .then(m => m.Dashboard)
  },

  {
    path: 'historico',
    loadComponent: () =>
      import('./pages/historico/historico')
      .then(m => m.Historico)
  },

  {
    path: 'sobre',
    loadComponent: () =>
      import('./pages/sobre/sobre')
      .then(m => m.Sobre)
  }

];