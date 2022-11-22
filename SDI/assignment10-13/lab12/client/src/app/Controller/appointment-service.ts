import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, map, Observable, of} from 'rxjs';
import {AppointmentDTO, AppointmentsDTO} from "../Model/appointmentDTO";

@Injectable({
  providedIn: 'root'
})
export class AppointmentService {
  private baseURL = 'http://localhost:8080/api/appointments';
  private headers = new HttpHeaders()
    .set('content-type', 'application/json')
    .set('Access-Control-Allow-Origin', '*');

  appointments: BehaviorSubject<Array<AppointmentDTO>> = new BehaviorSubject(new Array());

  constructor(private http: HttpClient) {
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.error(error); // log to console
      return of(result as T);
    };
  }

  getAllAppointments(): Observable<AppointmentsDTO> {
    return this.http.get<AppointmentsDTO>(this.baseURL, {headers: this.headers})
      .pipe(catchError(this.handleError<AppointmentsDTO>('getAllAppointments')));
  }

  addAppointment(data: AppointmentDTO) {
    const body = JSON.stringify({
      'petId': data.petId,
      'vetId': data.vetId,
      'type': data.type,
      'date': data.date,
    });
    console.log(body);

    return this.http.post(this.baseURL, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }

  deleteAppointment(id: number) {
    return this.http.delete(this.baseURL + `/${id}`)
      .subscribe(data => {
        console.log(data);
      });
  }

  updateAppointment(data: AppointmentDTO) {
    const body = JSON.stringify({
      "id": data.id,
      'petId': data.petId,
      'vetId': data.vetId,
      'type': data.type,
      'date': data.date,
    });

    return this.http.put(this.baseURL + `/${data.id}`, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }
}
