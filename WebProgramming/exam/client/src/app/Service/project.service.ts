import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, Observable, of} from 'rxjs';
import {ProjectDTO} from "../Model/projectDTO";

@Injectable({
  providedIn: 'root'
})
export class ProjectService {
  private baseURL = 'https://localhost:7286/api';
  private headers = new HttpHeaders()
      .set('content-type', 'application/json')
      .set('Access-Control-Allow-Origin', '*');

  constructor(private http: HttpClient) {
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.error(error); // log to console
      return of(result as T);
    };
  }

  getAllProjects(): Observable<Array<ProjectDTO>> {
    return this.http.get<Array<ProjectDTO>>(this.baseURL)
      .pipe(catchError(this.handleError<Array<ProjectDTO>>('getAllChannels', [])));
  }

  getAllChannelsByUser(userName: string): Observable<Array<ProjectDTO>> {
    return this.http.get<Array<ProjectDTO>>(this.baseURL + `/member/${userName}`)
      .pipe(catchError(this.handleError<Array<ProjectDTO>>('getAllChannelsByUser', [])));
  }

  addMemberToProjects(userName: string, projects: Array<string>) {
    const body = JSON.stringify(projects);

    return this.http.put(this.baseURL + `/member/${userName}`, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }
}
