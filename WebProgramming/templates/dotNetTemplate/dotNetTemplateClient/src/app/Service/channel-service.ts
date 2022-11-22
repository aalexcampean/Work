import {Injectable} from '@angular/core';
import {HttpClient, HttpHeaders} from '@angular/common/http';
import {BehaviorSubject, catchError, Observable, of} from 'rxjs';
import {ChannelDTO} from "../Model/channelDTO";

@Injectable({
  providedIn: 'root'
})
export class ChannelService {
  private baseURL = 'https://localhost:7225/api';
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

  getAllChannels(): Observable<Array<ChannelDTO>> {
    return this.http.get<Array<ChannelDTO>>(this.baseURL)
      .pipe(catchError(this.handleError<Array<ChannelDTO>>('getAllChannels', [])));
  }

  getAllChannelsByOwner(ownerName: string): Observable<Array<ChannelDTO>> {
    if (ownerName == '') return this.getAllChannels();
    return this.http.get<Array<ChannelDTO>>(this.baseURL + `/owner/${ownerName}`)
      .pipe(catchError(this.handleError<Array<ChannelDTO>>('getAllChannelsByOwner', [])));
  }

  getAllChannelsByUser(userName: string): Observable<Array<ChannelDTO>> {
    return this.http.get<Array<ChannelDTO>>(this.baseURL + `/user/${userName}`)
      .pipe(catchError(this.handleError<Array<ChannelDTO>>('getAllChannelsByUser', [])));
  }

  subscribeUserToChannel(userName: string, channel: ChannelDTO) {
    const body = JSON.stringify({
      "id": channel.id,
      "ownerId": channel.ownerId,
      "name": channel.name,
      "description": channel.description,
      "subscribers": channel.subscribers
    });

    return this.http.put(this.baseURL + `/user/${userName}`, body, {headers: this.headers})
      .subscribe(data => {
        console.log(data);
      });
  }
}
