import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, Observable, of} from 'rxjs';
import {ArticlesDTO} from "../Model/articleDTO";
import {SendArticleDTO} from "../Model/sendArticleDTO";

@Injectable({
    providedIn: 'root'
})
export class ArticleService {
    private baseURL = 'http://localhost:8080/api/articles';
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

    getUserArticles(userName: string): Observable<ArticlesDTO> {
        return this.http.get<ArticlesDTO>(this.baseURL + `/user/${userName}`, {headers: this.headers})
            .pipe(catchError(this.handleError<ArticlesDTO>('getUserArticles')));
    }

    getUserArticlesByJournalName(userName: string, journalName: string): Observable<ArticlesDTO> {
        return this.http.get<ArticlesDTO>(this.baseURL + `/user/${userName}/${journalName}`, {headers: this.headers})
            .pipe(catchError(this.handleError<ArticlesDTO>('getUserArticlesByJournalName')));
    }

    addArticleToJournal(article: SendArticleDTO) {
        const body = JSON.stringify(article);

        return this.http.post(this.baseURL, body, {headers: this.headers})
            .subscribe(data => {
                console.log(data);
            });
    }
}
