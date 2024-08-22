import { Injectable } from '@angular/core';
import { AngularFireAuth } from '@angular/fire/compat/auth';

@Injectable({
  providedIn: 'root',
})
export class LoginService {
  private loadingState: boolean = false;
  private currentUser: any;

  constructor(private auth: AngularFireAuth) {
    auth.authState.subscribe((user) => {
      this.currentUser = user;
    });
  }

  async createNewAccount(email: string, password: string, name: string) {
    this.loadingState = true;
    return this.auth
      .createUserWithEmailAndPassword(email, password)
      .then((response) => {
        response.user?.updateProfile({
          displayName: name,
        });
        return new Promise((resolved, rejected) => {
          resolved(true);
        });
      })
      .finally(() => (this.loadingState = false));
  }

  recoverPassword(email: string) {
    this.auth.sendPasswordResetEmail(email);
    return new Promise((resolved, rejected) => {resolved(true)})
  }

  logIn(email: string, password: string): Promise<any> {
    this.loadingState = true;
    return this.auth
      .signInWithEmailAndPassword(email, password)
      .finally(() => (this.loadingState = false));
  }

  public get getLoading() {
    return this.loadingState;
  }
}
