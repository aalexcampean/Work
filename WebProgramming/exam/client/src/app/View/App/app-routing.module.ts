import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import {AppComponent} from "./app.component";
import {ProjectsTableComponent} from "../ProjectsTable/projects-table.component";
import {LoginComponent} from "../Login/login.component";
import {AuthGuard} from "./auth-guard.service";

const routes: Routes = [
  {
    path: 'login',
    component: LoginComponent
  },
  {
    path: 'subscriptions',
    component: ProjectsTableComponent,
    canActivate: [AuthGuard]
  },
  {
    path: '',
    redirectTo: 'subscriptions',
    pathMatch: 'full',
  },
  {
    path: '**',
    redirectTo: 'subscriptions',
    pathMatch: 'full',
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}
