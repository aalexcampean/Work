import { Component } from '@angular/core';
import {Router} from "@angular/router";

@Component({
  selector: 'login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  title = 'Login';
  userNameInput = "";

  public constructor(private router: Router) {
  }

  public handleLogin(): void {
    sessionStorage.setItem('username', this.userNameInput);
    this.router.navigate(['/subscriptions']);
  }
}
