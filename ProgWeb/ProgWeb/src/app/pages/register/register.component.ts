import { Component } from '@angular/core';
import { AppButtonComponent } from '../../components/app-button/app-button.component';
import { AppInputComponent } from '../../components/app-input/app-input.component';
import { MatIcon } from '@angular/material/icon';
import { ReactiveFormsModule, FormGroup, FormControl, Validators } from '@angular/forms';
import { LoginService } from '../../services/login.service';
import { MatSnackBar } from '@angular/material/snack-bar';
import { Router } from '@angular/router';
import { MatButtonModule } from '@angular/material/button';

@Component({
  selector: 'app-register',
  standalone: true,
  imports: [AppButtonComponent, AppInputComponent, MatIcon, ReactiveFormsModule, MatButtonModule],
  templateUrl: './register.component.html',
  styleUrl: './register.component.scss'
})
export class RegisterComponent {
  form = new FormGroup({
    name: new FormControl('', [Validators.required]),
    email: new FormControl('', [Validators.email, Validators.required]),
    pwd: new FormControl('', [Validators.required, Validators.minLength(6)]),
    _pwd: new FormControl('', [
      Validators.required,
      Validators.minLength(6),
    ]),
  });

  constructor(
    protected login: LoginService,
    private snack: MatSnackBar,
    private router: Router
  ) { }

  register() {
    if (this.form.valid) {
      const { name, email, pwd, _pwd } = this.form.value;
      if (pwd != _pwd) {
        this.snack.open('As senhas precisam ser iguais', 'Ok');
        return;
      }
      this.login
        .createNewAccount(email!, pwd!, name!)
        .then((response) => {
          this.snack
            .open('Cadastro realizado com sucesso!', 'Ok')
            .onAction()
            .subscribe(() => {
              this.router.navigate(['login']);
            });
        })
        .catch((e) => {
          this.snack.open(e.message, 'Ok');
        });
    }
  }
}
