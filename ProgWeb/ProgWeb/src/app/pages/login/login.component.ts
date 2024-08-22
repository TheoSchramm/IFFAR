import { Component } from '@angular/core';
import { MatIcon } from '@angular/material/icon';
import { FormGroup, FormControl, ReactiveFormsModule, Validators } from '@angular/forms';
import { MatButtonModule } from '@angular/material/button';
import { MatInput, MatInputModule } from '@angular/material/input';
import { LoginService } from '../../services/login.service';
import { Router } from '@angular/router';
import { AppInputComponent } from '../../components/app-input/app-input.component';
import { AppButtonComponent } from '../../components/app-button/app-button.component';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [MatIcon, MatInputModule, MatButtonModule, ReactiveFormsModule, AppInputComponent, AppButtonComponent],
  templateUrl: './login.component.html',
  styleUrl: './login.component.scss'
})
export class LoginComponent {
  form = new FormGroup({
    email: new FormControl('', [Validators.required, Validators.email]),
    password: new FormControl('', [Validators.required]),
  });

  constructor(protected login: LoginService, private router: Router) { }

  logIn() {
    if (this.form.valid) {
      const { email, password } = this.form.value;
      this.login.logIn(email!, password!).then((response) =>
        { this.router.navigate(['home']) })
    }
  }
}
