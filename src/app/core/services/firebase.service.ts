import { Injectable, inject } from '@angular/core';
import { Database, objectVal, ref } from '@angular/fire/database';

@Injectable({
  providedIn: 'root'
})
export class FirebaseService {

  private db = inject(Database);

  getLuva() {

    const luvaRef = ref(
      this.db,
      'luva'
    );

    return objectVal(luvaRef);

  }

}