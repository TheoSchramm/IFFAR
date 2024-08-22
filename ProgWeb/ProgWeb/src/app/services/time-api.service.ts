import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { timeApiModel } from '../models/timeApi.model';

@Injectable({
    providedIn: 'root'
})

export class TimeApiService {
  constructor(private http: HttpClient) {}
  request(timeZone: string): Observable<timeApiModel> {
        const url = `https://timeapi.io/api/time/current/zone?timeZone=${timeZone}`;
        return this.http.get<any>(url);
    }
}