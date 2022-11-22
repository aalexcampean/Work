import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, map, Observable, of} from 'rxjs';
import {OwnerDTO, OwnersDTO} from "../Model/ownerDTO";
import {PetsDTO} from "../Model/petDTO";
import {BirthCertificateDTO, BirthCertificatesDTO} from "../Model/birthCertificateDTO";

@Injectable({
  providedIn: 'root'
})
export class BirthCertificatesService {
  private baseURL = 'http://localhost:8080/api/birthCertificates';
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

  getAllBirthCertificates(): Observable<BirthCertificatesDTO> {
    return this.http.get<BirthCertificatesDTO>(this.baseURL, {headers: this.headers})
      .pipe(catchError(this.handleError<BirthCertificatesDTO>('getAllBirthCertificates')));
  }

  addBirthCertificate(data: BirthCertificateDTO) {
    const body = JSON.stringify({
      'text': data.text,
      'location': data.location,
      'date': data.date,
      'healthGrade': data.healthGrade,
      'petId': data.petId
    });
    console.log(body);

    return this.http.post(this.baseURL, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }

  deleteBirthCertificate(id: number) {
    return this.http.delete(this.baseURL + `/${id}`)
      .subscribe(data => {
        console.log(data);
      });
  }

  updateBirthCertificate(data: BirthCertificateDTO) {
    const body = JSON.stringify({
      "id": data.id,
      'text': data.text,
      'location': data.location,
      'date': data.date,
      'healthGrade': data.healthGrade,
      'petId': data.petId
    });

    return this.http.put(this.baseURL + `/${data.id}`, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }
}
