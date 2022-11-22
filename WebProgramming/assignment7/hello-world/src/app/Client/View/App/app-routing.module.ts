import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import {AppComponent} from "./app.component";
import {DocumentManagerComponent} from "../DocumentManager/document-manager.component";
import {LandingMenuComponent} from "../LandingPage/landing-menu.component";

const routes: Routes = [
  {
    path: 'home',
    component: LandingMenuComponent
  },
  {
    path: 'document-manager',
    component: DocumentManagerComponent
  },
  {
    path: '',
    redirectTo: '/home',
    pathMatch: 'full'
  },
  {
    path: '**',
    redirectTo: '/home',
    pathMatch: 'full'
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}
