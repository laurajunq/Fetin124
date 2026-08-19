import { Injectable, inject } from '@angular/core';
import {
  Database,
  objectVal,
  listVal,
  ref
} from '@angular/fire/database';

@Injectable({
  providedIn: 'root'
})
export class FirebaseService {

  private db = inject(Database);

  // Dados atuais da luva
  getLuva() {

    const luvaRef = ref(
      this.db,
      'luva'
    );

    return objectVal(luvaRef);

  }

  // Histórico de leituras
  getLeituras() {

    const leiturasRef = ref(
      this.db,
      'leituras'
    );

    return listVal(leiturasRef);

  }

}