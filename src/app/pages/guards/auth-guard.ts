import { inject } from '@angular/core';
import {
  CanActivateFn,
  Router
} from '@angular/router';

export const authGuard: CanActivateFn = () => {

  const router = inject(Router);

  const usuarioLogado =
    sessionStorage.getItem('handpulseLogado');

  if (usuarioLogado === 'true') {
    return true;
  }

  return router.createUrlTree(['/login']);
};