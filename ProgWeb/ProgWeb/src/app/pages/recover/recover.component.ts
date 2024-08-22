import { Component } from '@angular/core';
import { MatIcon } from '@angular/material/icon';
import { FormGroup, FormControl, ReactiveFormsModule, Validators } from '@angular/forms';
import { MatButtonModule } from '@angular/material/button';
import { MatInput, MatInputModule } from '@angular/material/input';
import { LoginService } from '../../services/login.service';
import { Router } from '@angular/router';
import { AppInputComponent } from '../../components/app-input/app-input.component';
import { AppButtonComponent } from '../../components/app-button/app-button.component';
import { MatSnackBar } from '@angular/material/snack-bar';

@Component({
  selector: 'app-recover',
  standalone: true,
  imports: [MatIcon, MatInputModule, MatButtonModule, ReactiveFormsModule, AppInputComponent, AppButtonComponent],
  templateUrl: './recover.component.html',
  styleUrl: './recover.component.scss'
})
export class RecoverComponent {
  form = new FormGroup({
    email: new FormControl('', [Validators.required, Validators.email]),
  });

  constructor(protected login: LoginService, private router: Router, private snack: MatSnackBar) { }

  recover() {
    if (this.form.valid) {
      const { email } = this.form.value;
      this.login.recoverPassword(email!).then((response) => {
        this.snack
          .open('Email enviado com sucesso!', 'Ok')
          .onAction()
          .subscribe(() => {
            this.router.navigate(['login']);
          });
      })
    }
  }
}


