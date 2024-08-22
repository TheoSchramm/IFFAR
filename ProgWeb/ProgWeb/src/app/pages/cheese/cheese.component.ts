import { Component } from '@angular/core';
import { AppInputComponent } from '../../components/app-input/app-input.component';
import { AppButtonComponent } from '../../components/app-button/app-button.component';
import { ActivatedRoute } from '@angular/router';
import {
  FormControl,
  FormGroup,
  ReactiveFormsModule,
  Validators,
} from '@angular/forms';
import { CheeseService } from '../../services/cheese.service';
import { CheeseModel } from '../../models/cheese.model';
import { Router } from '@angular/router';


@Component({
  selector: 'app-cheese',
  standalone: true,
  imports: [AppInputComponent, AppButtonComponent, ReactiveFormsModule],
  templateUrl: './cheese.component.html',
  styleUrl: './cheese.component.scss'
})
export class CheeseComponent {
  form = new FormGroup({
    name: new FormControl('', [Validators.required]),
    description: new FormControl('', [Validators.required]),
    age: new FormControl('', [Validators.required]),
  })

  key?: string | null
  constructor(protected cheeseService: CheeseService, private route: Router, private activatedRoute: ActivatedRoute){
    this.key = this.activatedRoute.snapshot.paramMap.get('key')
    if (this.key){
      cheeseService.getCheese(this.key).subscribe((
        response: CheeseModel) => this.form.setValue({
          name: response?.['name'],
          description: response?.['description'],
          age: response?.['age'].toString()
        }))
    }
  }

  save(){
    if (this.form.valid) {
      const cheese = this.form.value as unknown as CheeseModel;
      this.cheeseService.saveCheese(cheese, this.key).then(() => this.route.navigate(['home']))
    }
  }

}
