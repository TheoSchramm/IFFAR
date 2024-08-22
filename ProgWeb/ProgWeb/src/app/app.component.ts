import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet } from '@angular/router';
import { MatIconModule } from '@angular/material/icon';
import { MatButtonModule } from '@angular/material/button';
import { MatToolbar } from '@angular/material/toolbar';
import { TimeApiService } from './services/time-api.service';
import { timeApiModel } from './models/timeApi.model';


@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, RouterOutlet, MatButtonModule, MatIconModule, MatToolbar],
  templateUrl: './app.component.html',
  styleUrl: './app.component.scss'
})


export class AppComponent {
  time?: timeApiModel;

  constructor(private timeApi: TimeApiService){}


  ngOnInit() {
    this.timeApi.request('America/Sao_Paulo').subscribe(response => {
      this.time = response
    });
  }
}
