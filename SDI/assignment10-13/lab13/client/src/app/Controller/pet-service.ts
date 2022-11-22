import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, map, Observable, of} from 'rxjs';
import {PetDTO, PetsDTO} from "../Model/petDTO";
import {OwnerDTO} from "../Model/ownerDTO";
import {AppointmentsDTO} from "../Model/appointmentDTO";

@Injectable({
  providedIn: 'root'
})
export class PetService {
  private baseURL = 'http://localhost:8080/api/pets';
  private headers = new HttpHeaders()
    .set('content-type', 'application/json')
    .set('Access-Control-Allow-Origin', '*');

  pets: BehaviorSubject<Array<PetDTO>> = new BehaviorSubject(new Array());

  constructor(private http: HttpClient) {
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.error(error); // log to console
      return of(result as T);
    };
  }

  getAllPets(): Observable<PetsDTO> {
    return this.http.get<PetsDTO>(this.baseURL, {headers: this.headers})
      .pipe(catchError(this.handleError<PetsDTO>('getAllPets')));
  }

  getAllPaginatedPets(pageNumber: number, pageSize: number): Observable<PetsDTO> {
    return this.http.get<PetsDTO>(`${(this.baseURL)}/pageNumber=${pageNumber - 1}&pageSize=${pageSize}`, {headers: this.headers})
      .pipe(catchError(this.handleError<PetsDTO>('getAllPaginatedPets')));
  }

  getPetOwner(id: number): Observable<OwnerDTO> {
    return this.http.get<OwnerDTO>(this.baseURL + `/owner/${id}`, {headers: this.headers})
      .pipe(catchError(this.handleError<OwnerDTO>('getPetOwner')));
  }

  getPetAppointments(id: number): Observable<AppointmentsDTO> {
    return this.http.get<AppointmentsDTO>(this.baseURL + `/appointments/${id}`, {headers: this.headers})
      .pipe(catchError(this.handleError<AppointmentsDTO>('getPetAppointments')));
  }

  addPet(data: PetDTO) {
    const body = JSON.stringify({
      'species': data.species,
      'breed': data.breed,
      'name': data.name,
      'dateOfEnrolment': data.dateOfEnrolment,
      'ownerId': data.ownerId
    });
    console.log(body);

    return this.http.post(this.baseURL, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }

  deletePet(id: number) {
    return this.http.delete(this.baseURL + `/${id}`)
      .subscribe(data => {
        console.log(data);
      });
  }

  updatePet(data: PetDTO) {
    const body = JSON.stringify({
      "id": data.id,
      'species': data.species,
      'breed': data.breed,
      'name': data.name,
      'dateOfEnrolment': data.dateOfEnrolment,
      'ownerId': data.ownerId
    });

    return this.http.put(this.baseURL + `/${data.id}`, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }
}
