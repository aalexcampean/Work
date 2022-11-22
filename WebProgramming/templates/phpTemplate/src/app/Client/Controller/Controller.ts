import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, Observable, of} from 'rxjs';
import {DocumentDTO} from "../Model/DocumentDTO";

@Injectable({
  providedIn: 'root'
})
export class DocumentsController {
  private baseURL = 'http://127.0.0.1:8000/Server/Controller/Controller.php';

  documents: BehaviorSubject<Array<DocumentDTO>> = new BehaviorSubject(new Array());

  constructor(private http: HttpClient) {
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.error(error); // log to console
      return of(result as T);
    };
  }

  getAllFiles(): Observable<Array<DocumentDTO>> {
    return this.http.get<Array<DocumentDTO>>(this.baseURL)
      .pipe(catchError(this.handleError<Array<DocumentDTO>>('getAllFiles', [])));
  }

  getAllFilesByType(type: string): Observable<Array<DocumentDTO>> {
    const body = JSON.stringify({
      'operation': 'getAllFilesByType',
      'type': type
    });
    return this.http.post<Array<DocumentDTO>>(this.baseURL, body)
      .pipe(catchError(this.handleError<Array<DocumentDTO>>('getAllFilesByType', [])));
  }

  getAllFilesByFormat(format: string): Observable<Array<DocumentDTO>> {
    const body = JSON.stringify({
      'operation': 'getAllFilesByFormat',
      'format': format
    });
    return this.http.post<Array<DocumentDTO>>(this.baseURL, body)
      .pipe(catchError(this.handleError<Array<DocumentDTO>>('getAllFilesByFormat', [])));
  }

  addFile(data: DocumentDTO) {
    const body = JSON.stringify({
      'operation': 'addFile',
      'title': data.title,
      'author': data.author,
      'noPages': data.noOfPages,
      'type': data.type,
      'format': data.format
    });
    console.log(body);

    return this.http.post(this.baseURL, body)
      .subscribe(data => {
        console.log(data);
      });
  }

  updateFile(data: DocumentDTO) {
    const body = JSON.stringify({
      'operation': 'updateFile',
      "id": data.id,
      "title": data.title,
      "author": data.author,
      "noPages": data.noOfPages,
      "type": data.type,
      "format": data.format
    });

    return this.http.post(this.baseURL, body)
      .subscribe(data => {
        console.log(data);
      });
  }

  deleteFile(id: number) {
    const body = JSON.stringify({
      'operation': 'deleteFile',
      'id': id
    });
    return this.http.post(this.baseURL, body)
      .subscribe(data => {
        console.log(data);
      });
  }
}
