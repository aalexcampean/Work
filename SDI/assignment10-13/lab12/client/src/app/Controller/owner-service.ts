import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, map, Observable, of} from 'rxjs';
import {OwnerDTO, OwnersDTO} from "../Model/ownerDTO";
import {PetsDTO} from "../Model/petDTO";

@Injectable({
  providedIn: 'root'
})
export class OwnerService {
  private baseURL = 'http://localhost:8080/api/owners';
  private headers = new HttpHeaders()
    .set('content-type', 'application/json')
    .set('Access-Control-Allow-Origin', '*');

  owners: BehaviorSubject<Array<OwnerDTO>> = new BehaviorSubject(new Array());

  constructor(private http: HttpClient) {
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.error(error); // log to console
      return of(result as T);
    };
  }

  getAllOwners(): Observable<OwnersDTO> {
    return this.http.get<OwnersDTO>(this.baseURL, {headers: this.headers})
      .pipe(catchError(this.handleError<OwnersDTO>('getAllOwners')));
  }

  getOwnerPets(id: number): Observable<PetsDTO> {
    return this.http.get<PetsDTO>(this.baseURL + `/pets/${id}`, {headers: this.headers})
      .pipe(catchError(this.handleError<PetsDTO>('getOwnerPets')));
  }

  addOwner(data: OwnerDTO) {
    const body = JSON.stringify({
      'firstName': data.firstName,
      'lastName': data.lastName,
      'email': data.email,
      'phoneNumber': data.phoneNumber,
      'dateOfBirth': data.dateOfBirth
    });
    console.log(body);

    return this.http.post(this.baseURL, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }

  deleteOwner(id: number) {
    return this.http.delete(this.baseURL + `/${id}`)
      .subscribe(data => {
        console.log(data);
      });
  }

  updateOwner(data: OwnerDTO) {
    const body = JSON.stringify({
      "id": data.id,
      'firstName': data.firstName,
      'lastName': data.lastName,
      'email': data.email,
      'phoneNumber': data.phoneNumber,
      'dateOfBirth': data.dateOfBirth
    });

    return this.http.put(this.baseURL + `/${data.id}`, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }
}
