import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import {LandingMenuComponent} from "../LandingPage/landing-menu.component";
import {OwnersTableComponent} from "../Owner/OwnersTable/owners-table.component";
import {PetsTableComponent} from "../Pets/PetsTable/pets-table.component";
import {AppointmentsTableComponent} from "../Appointmets/AppointmentsTable/appointments-table.component";
import {VetsTableComponent} from "../Vets/VetsTable/vets-table.component";
import {AddOwnerComponent} from "../Owner/AddOwner/add-owner.component";
import {DeleteOwnerComponent} from "../Owner/DeleteOwner/delete-owner.component";

const routes: Routes = [
  {
    path: 'home',
    component: LandingMenuComponent
  },
  {
    path: 'owners',
    component: OwnersTableComponent
  },
  {
    path: 'owners/add-owners',
    component: AddOwnerComponent
  },
  {
    path: 'delete-owners',
    component: DeleteOwnerComponent
  },
  {
    path: 'pets',
    component: PetsTableComponent
  },
  {
    path: 'appointments',
    component: AppointmentsTableComponent
  },
  {
    path: 'vets',
    component: VetsTableComponent
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
export class AppRoutingModule { }
