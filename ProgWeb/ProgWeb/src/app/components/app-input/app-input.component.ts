import { Component, Input, OnInit } from '@angular/core';
import { FormControl, ReactiveFormsModule } from '@angular/forms';
import { MatInputModule } from '@angular/material/input';

@Component({
  selector: 'app-input',
  standalone: true,
  imports: [MatInputModule, ReactiveFormsModule],
  templateUrl: './app-input.component.html',
  styleUrl: './app-input.component.scss',
})
export class AppInputComponent implements OnInit {
  @Input()
  label = '';
  @Input()
  type = 'text';
  @Input()
  placeholder = '';
  @Input()
  control = new FormControl();

  @Input()
  errorKey = '';
  @Input()
  errorMsg = '';

  erros = new Map();

  constructor() {
    this.erros.set('required', 'Campo obrigatório!!');
    this.erros.set('email', 'Formato de e-mail inválido');
    this.erros.set('minlength', 'Mínimo de 6 caracteres');
  }

  ngOnInit() {
    this.erros.set(this.errorKey, this.errorMsg);
  }
}
