import { CommonModule } from '@angular/common';
import {
  booleanAttribute,
  Component,
  EventEmitter,
  input,
  Input,
  Output,
} from '@angular/core';
import { MatButton, MatButtonModule } from '@angular/material/button';
import { MatIcon } from '@angular/material/icon';
import { MatInputModule } from '@angular/material/input';
import { MatProgressSpinnerModule } from '@angular/material/progress-spinner';

@Component({
  selector: 'app-button',
  standalone: true,
  imports: [CommonModule, MatIcon, MatButtonModule, MatProgressSpinnerModule],
  templateUrl: './app-button.component.html',
  styleUrl: './app-button.component.scss',
})
export class AppButtonComponent {
  expanded = input(true, {
    transform: booleanAttribute,
  });
  @Input()
  label = '';
  @Input()
  icon = '';
  @Input()
  loading = false;
  @Input()
  action: any;
  @Output()
  onClick = new EventEmitter();

  do_action() {
    this.onClick.emit();
  }
}
