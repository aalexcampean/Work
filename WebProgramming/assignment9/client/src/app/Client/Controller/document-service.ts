import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, Observable, of} from 'rxjs';
import {DocumentDTO} from "../Model/documentDTO";

@Injectable({
  providedIn: 'root'
})
export class DocumentsController {
  private baseURL = 'https://localhost:7193/api';
  private headers = new HttpHeaders()
      .set('content-type', 'application/json')
      .set('Access-Control-Allow-Origin', '*');

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
    if (type == '') return this.getAllFiles();
    return this.http.get<Array<DocumentDTO>>(this.baseURL + `/type/${type}`)
      .pipe(catchError(this.handleError<Array<DocumentDTO>>('getAllFilesByType', [])));
  }

  getAllFilesByFormat(format: string): Observable<Array<DocumentDTO>> {
    if (format == 'ALL') return this.getAllFiles();
    return this.http.get<Array<DocumentDTO>>(this.baseURL + `/format/${format}`)
      .pipe(catchError(this.handleError<Array<DocumentDTO>>('getAllFilesByFormat', [])));
  }

  addFile(data: DocumentDTO) {
    const body = JSON.stringify({
      'operation': 'addFile',
      'title': data.title,
      'author': data.author,
      'noPages': data.numberOfPages,
      'type': data.type,
      'format': data.format
    });
    console.log(body);

    return this.http.post(this.baseURL + '/document', body, {headers: this.headers})
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
      "noPages": data.numberOfPages,
      "type": data.type,
      "format": data.format
    });

    return this.http.put(this.baseURL + `/document/${data.id}`, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }

  deleteFile(id: number) {
    return this.http.delete(this.baseURL + `/document/${id}`)
      .subscribe(data => {
        console.log(data);
      });
  }
}
