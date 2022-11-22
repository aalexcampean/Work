import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import {AppComponent} from "./app.component";
import {ArticlesTableComponent} from "../ArticlesTable/articles-table.component";
import {LoginComponent} from "../Login/login.component";
import {AuthGuard} from "./auth-guard.service";

const routes: Routes = [
  {
    path: 'login',
    component: LoginComponent
  },
  {
    path: 'articles',
    component: ArticlesTableComponent,
    canActivate: [AuthGuard]
  },
  {
    path: '',
    redirectTo: 'articles',
    pathMatch: 'full',
  },
  {
    path: '**',
    redirectTo: 'articles',
    pathMatch: 'full',
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}
