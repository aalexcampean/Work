import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, map, Observable, of} from 'rxjs';
import {VetDTO, VetsDTO} from "../Model/vetDTO";
import {AppointmentsDTO} from "../Model/appointmentDTO";
import {PetsDTO} from "../Model/petDTO";

@Injectable({
  providedIn: 'root'
})
export class VetService {
  private baseURL = 'http://localhost:8080/api/vets';
  private headers = new HttpHeaders()
    .set('content-type', 'application/json')
    .set('Access-Control-Allow-Origin', '*');

  vets: BehaviorSubject<Array<VetDTO>> = new BehaviorSubject(new Array());

  constructor(private http: HttpClient) {
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.error(error); // log to console
      return of(result as T);
    };
  }

  getAllVets(): Observable<VetsDTO> {
    return this.http.get<VetsDTO>(this.baseURL, {headers: this.headers})
      .pipe(catchError(this.handleError<VetsDTO>('getAllVets')));
  }

  getAllPaginatedVets(pageNumber: number, pageSize: number): Observable<VetsDTO> {
    return this.http.get<VetsDTO>(`${(this.baseURL)}/pageNumber=${pageNumber - 1}&pageSize=${pageSize}`, {headers: this.headers})
      .pipe(catchError(this.handleError<VetsDTO>('getAllPaginatedVets')));
  }

  getVetAppointments(id: number): Observable<AppointmentsDTO> {
    return this.http.get<AppointmentsDTO>(this.baseURL + `/appointments/${id}`, {headers: this.headers})
      .pipe(catchError(this.handleError<AppointmentsDTO>('getVetAppointments')));
  }

  getVetPatients(id: number): Observable<PetsDTO> {
    return this.http.get<PetsDTO>(this.baseURL + `/patients/${id}`, {headers: this.headers})
      .pipe(catchError(this.handleError<PetsDTO>('getVetPatients')));
  }

  addVet(data: VetDTO) {
    const body = JSON.stringify({
      'firstName': data.firstName,
      'lastName': data.lastName,
      'email': data.email,
      'phoneNumber': data.phoneNumber,
      'dateOfBirth': data.dateOfBirth,
      'salary': data.salary,
      'rating': data.rating
    });
    console.log(body);

    return this.http.post(this.baseURL, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }

  deleteVet(id: number) {
    return this.http.delete(this.baseURL + `/${id}`)
      .subscribe(data => {
        console.log(data);
      });
  }

  updateVet(data: VetDTO) {
    const body = JSON.stringify({
      "id": data.id,
      'firstName': data.firstName,
      'lastName': data.lastName,
      'email': data.email,
      'phoneNumber': data.phoneNumber,
      'dateOfBirth': data.dateOfBirth,
      'salary': data.salary,
      'rating': data.rating
    });

    return this.http.put(this.baseURL + `/${data.id}`, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }
}
