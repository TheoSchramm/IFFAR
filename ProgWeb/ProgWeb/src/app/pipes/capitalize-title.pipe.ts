import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'capitalizeTitle',
  standalone: true
})
export class CapitalizeTitlePipe implements PipeTransform {

  transform(title: string): string {
    let words = title.split(' ');
    for (let i = 0; i < words.length; i++) {
      if (words[i].length <= 2) {
        words[i] = words[i].toLowerCase();
      } else {
        words[i] = words[i].charAt(0).toUpperCase() + words[i].slice(1).toLowerCase();
      }
    }
    return words.join(' ');
  }
}