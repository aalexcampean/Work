import {NgModule} from '@angular/core';
import {BrowserModule} from '@angular/platform-browser';

import {AppRoutingModule} from './app-routing.module';
import {AppComponent} from './app.component';
import {NgbModule} from '@ng-bootstrap/ng-bootstrap';
import {OwnersTableComponent} from "../Owner/OwnersTable/owners-table.component";
import {CustomNavigationBar} from "../ReusableComponents/NavigationBar/navigation-bar.component";
import {LandingMenuComponent} from "../LandingPage/landing-menu.component";
import {HttpClientModule} from "@angular/common/http";
import {OwnersModalComponent} from "../Owner/OwnersModal/owners-modal.component";
import {FormsModule} from "@angular/forms";
import {MdbModalModule} from 'mdb-angular-ui-kit/modal';
import {PetsModalComponent} from "../ReusableComponents/PetsModal/pets-modal.component";
import {AddUpdatePetsModalComponent} from "../Pets/AddUpdatePetsModal/add-update-pets-modal.component";
import {PetsTableComponent} from "../Pets/PetsTable/pets-table.component";
import {PetsOwnerModalComponent} from "../Pets/PetsOwnerModal/pets-owner-modal.component";
import {AppointmentsModalComponent} from "../ReusableComponents/AppointmentsModal/appointments-modal.component";
import {AppointmentsTableComponent} from "../Appointmets/AppointmentsTable/appointments-table.component";
import {AddUpdateAppointmentsModalComponent} from "../Appointmets/AddUpdateAppointmentsModal/add-update-appointments-modal.component";
import {VetsTableComponent} from "../Vets/VetsTable/vets-table.component";
import {VetsModalComponent} from "../Vets/VetsModal/vets-modal.component";

@NgModule({
  declarations: [
    AppComponent,
    CustomNavigationBar,
    PetsModalComponent,
    AppointmentsModalComponent,
    LandingMenuComponent,
    OwnersTableComponent,
    OwnersModalComponent,
    PetsTableComponent,
    AddUpdatePetsModalComponent,
    PetsOwnerModalComponent,
    AddUpdateAppointmentsModalComponent,
    AppointmentsTableComponent,
    VetsTableComponent,
    VetsModalComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    NgbModule,
    FormsModule,
    MdbModalModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule {
}
