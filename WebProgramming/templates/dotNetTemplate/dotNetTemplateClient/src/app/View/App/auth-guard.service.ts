import {Injectable} from '@angular/core';
import {CanActivate} from '@angular/router';
import {Router} from '@angular/router';

@Injectable()
export class AuthGuard implements CanActivate {
    //Constructor
    public constructor(private router: Router) {
    }

    public canActivate() {
        if (sessionStorage.getItem('username') == null) {
            this.router.navigate(['/login']);
        }
        return true;
    }
}
