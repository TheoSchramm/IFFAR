import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { CheeseService } from '../../services/cheese.service';
import { MatIcon } from '@angular/material/icon';
import { Router } from '@angular/router';
import { CapitalizeTitlePipe } from '../../pipes/capitalize-title.pipe';
import {MatTableModule} from '@angular/material/table';
import { Observable } from 'rxjs';
import { MatButtonModule } from '@angular/material/button';
import {MatCardModule} from '@angular/material/card';

@Component({
  selector: 'app-home',
  standalone: true,
  imports: [CommonModule, MatIcon, CapitalizeTitlePipe, MatTableModule, MatButtonModule, MatCardModule],
  templateUrl: './home.component.html',
  styleUrl: './home.component.scss'
})
export class HomeComponent {
  cheeses?: Observable<any>;

  constructor(private cheeseService: CheeseService, private route:Router, ){
    this.cheeses = cheeseService.getAllCheese();
  }
  deleteCheese(key: string){
    this.cheeseService.eatCheese(key);
  }
  updateCheese(key: string){
    this.route.navigateByUrl(`cheese/${key}`);
}
}
